#include <eosiolib/crypto.h>
#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>

using namespace eosio;
using namespace std;

#define MIN_BET 4
#define MAX_BET 95

#define EOS_SYMBOL symbol("EOS", 4)
#define EOS_CONTRACT "eosio.token"_n

struct seed {
    string player_seed;
    uint64_t timestamp;
    uint64_t bet_id;
    asset bet_amount;
    int tapos_block_prefix;
};
