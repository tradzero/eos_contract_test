#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using namespace std;

class toolbox : public eosio::contract {
    public:
        toolbox( account_name self )
        :contract(self){}
        [[eosio::action]]
        void promote( account_name to, string memo ) {
            eosio_assert( is_account( to ), "to account does not exist");
            require_recipient(to);
        }
};

EOSIO_ABI( toolbox, (promote) )