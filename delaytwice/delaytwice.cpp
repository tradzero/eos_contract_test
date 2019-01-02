#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/transaction.hpp>

using namespace eosio;
using namespace std;

class delaytwice : public contract
{
  public:
    using contract::contract;

    [[eosio::action]] void delay(int time)
    {
        eosio_assert(time <= 2, "only support delay twice");
        if (time == 2) {
            action(permission_level{ _self, N(active) },
                _self,
                N(receipt),
                make_tuple(tapos_block_num(), tapos_block_prefix())).send();
        } else {
            time += 1;

            action(permission_level{ _self, N(active) },
                _self,
                N(receipt),
                make_tuple(tapos_block_num(), tapos_block_prefix())).send();
            transaction tx{};
            tx.actions.emplace_back(permission_level{ _self, N(active) }, _self, N(delay),
                make_tuple(time));
            tx.delay_sec = 0;
            tx.send(now() + time, _self);
        }
    }

    [[eosio::action]] void receipt(int tapos_block_num, int tapos_block_prefix)
    {

    }
};

EOSIO_ABI(delaytwice, (delay))
