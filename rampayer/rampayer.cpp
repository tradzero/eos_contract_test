#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;
using namespace std;

class rampayer : public contract
{
  public:
    using contract::contract;

    [[eosio::action]] void test(account_name payer)
    {
        require_auth(payer);
        ram_table ram (_self, _self);
        ram.emplace(payer, [&](auto &h) {
            h.id = ram.available_primary_key();
            h.player = payer;
        });
    }

  private:
    struct [[eosio::table]] ram_test {
        uint64_t id;
        account_name player;
        auto primary_key()const { return id; }
    };
    typedef multi_index<N(ram), ram_test> ram_table;
};

EOSIO_ABI(rampayer, (test))
