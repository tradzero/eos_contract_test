#include "./utils.hpp"

CONTRACT dice : public contract {
  public:
    dice( name receiver, name code, datastream<const char*> ds )
        :contract(receiver, code, ds),
        _bet(receiver, receiver.value),
        _history(receiver, receiver.value),
        _global(receiver, receiver.value)
        {
        };
    // ACTION bet( name user, string seed );
    ACTION init();

    void transfer(name from, name to, asset quantity, string memo);
    void bet(name player, asset quantity, string memo);

    TABLE tb_bet {
        uint64_t id;
        asset quantity;
        name player;
        string player_seed;
        uint8_t bet;
        uint8_t result;
        uint64_t bet_at;
        uint64_t primary_key() const { return id; }
        uint64_t by_player() const {return player.value;}
    };
    typedef multi_index<"bet"_n, tb_bet,
        indexed_by<"byplayer"_n, const_mem_fun<tb_bet, uint64_t, &tb_bet::by_player>>
    > bet_table;

    TABLE tb_history {
        uint64_t id;
        uint64_t bet_id;
        name player;
        asset quantity;
        asset prize;
        string player_seed;
        uint8_t bet;
        uint8_t result;
        uint64_t bet_at;
        uint64_t primary_key() const { return id; }
    };
    typedef multi_index<"history"_n, tb_history> history_table;

    TABLE tb_global {
        uint64_t id;
        uint64_t bet_id;
        asset total_amount;
        uint64_t primary_key() const { return id; }
    };
    typedef multi_index<"global"_n, tb_global> global_table;

  private:
    bet_table _bet;
    history_table _history;
    global_table _global;

    void assert_quantity(asset quantity) {
        eosio_assert(quantity.symbol == EOS_SYMBOL, "only EOS allowed");
    }

    // todo
    void assert_amount(asset quantity) {
        
    }

    void check_unsettle_bet(name player) {
        auto idx = _bet.get_index<"byplayer"_n>();
        auto itr = idx.find(player.value);
        eosio_assert(itr->player != player, "have unsettled game");
    }
};