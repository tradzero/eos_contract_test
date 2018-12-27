#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/transaction.hpp>

using namespace eosio;
using namespace std;

class test : public contract {
    public:
        test(account_name self)
            :contract(self){};

        void transfer(account_name from, account_name to, asset quantity, string memo);
        [[eosio::action]]
        void receipt(account_name account, string memo);
    private:
        void assert_action()
        {
            auto tx_size = transaction_size();
            char tx[tx_size];
            auto read_size = read_transaction(tx, tx_size);
            eosio_assert( tx_size == read_size, "read_transaction failed");
            auto trx = unpack<transaction>( tx, read_size );
            action first_action = trx.actions.front();
            auto action_data = first_action.data;
            eosio_assert(first_action.name == N(transfer) && first_action.account == N(eosio.token), "only allow EOS transfer");

            struct transfer_args {
                account_name  from;
                account_name  to;
                asset         quantity;
                string        memo;
            };

            // unpack first action data
            constexpr size_t max_stack_buffer_size = 512;
            size_t size = action_data.size();
            const bool heap_allocation = max_stack_buffer_size < size;
            char* buffer = (char*)( heap_allocation ? malloc(size) : alloca(size) );
            auto transfer_data = unpack<transfer_args>(&action_data[0], size);
            if ( heap_allocation ) {
                free(buffer);
            }

            eosio_assert(transfer_data.to == _self, "no allow proxy transfer");
        }


};