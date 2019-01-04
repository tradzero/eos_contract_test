#include "./dice.hpp"

using namespace eosio;

ACTION dice::init()
{
    require_auth(_self);
    _global.emplace( _self, [&]( auto& g ) {
        g.total_amount = asset(0, EOS_SYMBOL);
    });
}

void dice::transfer(name from, name to, asset quantity, string memo)
{
    if (to == _self) {
        assert_quantity(quantity);
        string type = get_type(memo);
        if (type == "bet") {
            bet(from, quantity, memo);
        }
    }
}

void dice::bet(name player, asset quantity, string memo)
{
    assert_amount(quantity);

    string seed;
    uint8_t bet;
    parse_memo(memo, seed, bet);
    eosio_assert(bet >= MIN_BET && bet <= MAX_BET, "bet not match range");
    check_unsettle_bet(player);
}

extern "C"
{
    void apply(name receiver, name code, uint64_t action)
    {
        auto self = receiver;
        if (action == "transfer"_n.value && code == EOS_CONTRACT)
        {
            execute_action(receiver, code, &dice::transfer);
            return;
        }
        if (code == self || (action == "onerror"_n.value && code == "eosio"_n)) {
            switch (action) {
                EOSIO_DISPATCH_HELPER( dice, (init) ) 
            }
        }
    }
}

// EOSIO_DISPATCH(dice, (init))