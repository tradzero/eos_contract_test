#include "contract.hpp"

void test::transfer(account_name from, account_name to, asset quantity, string memo)
{
    assert_action();
    string send_memo = "pass test";
    action(permission_level{ _self, N(active) }, _self, N(receipt),
                make_tuple(from, send_memo)).send();
}

void test::receipt(account_name account, string memo)
{
    require_auth(_self);
    require_recipient(account);
}

extern "C" {
    void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
        test thiscontract(receiver);
        if ( action == N(transfer) && code == N(eosio.token) )
        {
            execute_action(&thiscontract, &test::transfer);
            return;
        }
        switch (action) { EOSIO_API(test, (receipt)) };
    }
}
