#include <eosiolib/eosio.hpp>
#include "eosio.token/eosio.token.hpp"

using namespace eosio;

namespace wallet{
    class deposit : contract {
        // @abi table
        struct [[eosio::table]] deposit_record {
            uint64_t id;
            account_name payer;
            int64_t amount;
            string memo;
            auto primary_key()const { return id; }
            EOSLIB_SERIALIZE(deposit_record, (id)(payer)(amount)(memo))
        };
        public:
            deposit(account_name self) : contract(self){}
            typedef eosio::multi_index<N(deposit), deposit_record> record_index;

            template<typename T>
            void saverecord(const T& t, uint64_t receiver) {
                if (t.to == _self) {
                    record_index _records(_self, _self);
                    _records.emplace(_self, [&](auto& _t) {
                        _t.id = _records.available_primary_key();
                        _t.payer = t.from;
                        _t.amount = t.quantity.amount;
                        _t.memo = t.memo;
                    });
                }
            }
    };
}

using namespace wallet;

extern "C" {
    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
      if( code == N(eosio.token) && action == N(transfer) ) {
        wallet::deposit de(receiver);
        de.saverecord(unpack_action_data<eosio::token::transfer_args>(), receiver);
      }
   }
}
