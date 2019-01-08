#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;
using namespace std;

#define N(X) name(#X)

CONTRACT secondindex : public contract
{
  public:
    secondindex(name receiver, name code, datastream<const char *> ds)
        : contract(receiver, code, ds),
        _second(receiver, receiver.value) {};

    ACTION init()
    {
        require_auth(_self);
        _second.emplace(_self, [&] (auto &s) {
            s.id = _second.available_primary_key();
            s.second_id = 1;
            s.value = 1;
        });
        _second.emplace(_self, [&] (auto &s) {
            s.id = _second.available_primary_key();
            s.second_id = 2;
            s.value = 3;
        });
        _second.emplace(_self, [&] (auto &s) {
            s.id = _second.available_primary_key();
            s.second_id = 1;
            s.value = 2;
        });
        _second.emplace(_self, [&] (auto &s) {
            s.id = _second.available_primary_key();
            s.second_id = 2;
            s.value = 7;
        });
        _second.emplace(_self, [&] (auto &s) {
            s.id = _second.available_primary_key();
            s.second_id = 3;
            s.value = 5;
        });
        _second.emplace(_self, [&] (auto &s) {
            s.id = _second.available_primary_key();
            s.second_id = 3;
            s.value = 4;
        });
        _second.emplace(_self, [&] (auto &s) {
            s.id = _second.available_primary_key();
            s.second_id = 1;
            s.value = 8;
        });
        _second.emplace(_self, [&] (auto &s) {
            s.id = _second.available_primary_key();
            s.second_id = 2;
            s.value = 6;
        });
        _second.emplace(_self, [&] (auto &s) {
            s.id = _second.available_primary_key();
            s.second_id = 3;
            s.value = 9;
        });
    }

    ACTION getsecond()
    {
        auto idx = _second.get_index<N(secondid)>();
        auto second_index = idx.lower_bound(2);
        for ( auto itr = second_index; itr->second_id == 2 ; ++itr ) {
            print(itr->value, " ,");
        }
    }

    ACTION cleanup()
    {
        require_auth(_self);
        for (auto itr = _second.begin(); itr != _second.end();)
        {
            itr = _second.erase(itr);
        }
    }

    TABLE second {
        uint64_t id;
        uint64_t second_id;
        uint64_t value;
        uint64_t primary_key() const { return id; }
        uint64_t by_second_id() const { return second_id; }
    };
    typedef multi_index<N(second), second,
                        indexed_by<
                            N(secondid), const_mem_fun<second, uint64_t, &second::by_second_id>>>
        second_table;

  private:
    second_table _second;
};

EOSIO_DISPATCH(secondindex, (init) (getsecond) (cleanup))
