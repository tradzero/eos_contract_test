#include <eosiolib/eosio.hpp>
#include <eosiolib/serialize.hpp>
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

        [[eosio::action]]
        void promotebatch( std::vector<account_name>& users, string memo ) {
            for( size_t i = 0; i < users.size(); i++ ) {
                if (is_account(users[i])) {
                    require_recipient(users[i]);
                }
            }
        }
};

EOSIO_ABI( toolbox, (promote) (promotebatch))