#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;
using namespace std;

CONTRACT wallet : public eosio::contract {
    using contract::contract;
    public:

        ACTION init();

        void transfer(name from, name to, asset quantity, string memo);
};

ACTION wallet::init() {
    print("works");
}

extern "C" {
    void apply(uint64_t receiver, uint64_t code, uint64_t action) {

        if (action == "transfer"_n.value && code != receiver) {
            execute_action( receiver, code, &wallet::transfer );
        }
        if (code == receiver){
            switch( action ) { 
                EOSIO_DISPATCH_HELPER( wallet, (init) ) 
            }    
        }
        // eosio_exit(0);
    }
}