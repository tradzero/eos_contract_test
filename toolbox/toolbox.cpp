#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using namespace std;

class toolbox : public eosio::contract {
    public:
        toolbox( account_name self )
        :contract(self){}
        [[eosio::action]]
        void promote( account_name user, string memo ) {
        }
};

EOSIO_ABI( toolbox, (promote) )