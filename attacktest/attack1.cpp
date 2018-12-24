#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;
using namespace std;

class attack1 : public contract
{
  public:
    using contract::contract;

    [[eosio::action]] void attack()
    {
        asset amount = asset(2, S(4, EOS));
        string memo = "";
        action(permission_level{ _self, N(active) },
           N(eosio.token),
           N(transfer),
           make_tuple(_self, N(attacktest11), amount, memo)).send();
    }
};

EOSIO_ABI(attack1, (attack))
