#include <eosiolib/eosio.hpp>
#include "./eosio.token.hpp"

using namespace eosio;

extern "C" {
    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
      if( code == N(eosio.token) && action == N(transfer) ) {
        eosio::token t(N(eosio.token));
        const auto sym_name = eosio::symbol_type(S(4,EOS)).name();
        uint64_t my_balance = t.get_balance(receiver, sym_name).amount;
        uint64_t max_amount = my_balance * 0.01;

        auto transfer_args = unpack_action_data<eosio::token::transfer_args>();
        uint64_t transfer_amount = transfer_args.quantity.amount;
        eosio_assert( transfer_amount <= max_amount, "Your transfer amount is too large " );
      }
   }
}
