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
            string action_name = name{first_action.name}.to_string();
            string _account_name = name{first_action.account}.to_string();
            print("action size: ", trx.actions.size(), " ");
            print(action_name, " ", _account_name);
            // eosio_assert(trx.actions.size() == 1, "no allow contract action");
        }
};