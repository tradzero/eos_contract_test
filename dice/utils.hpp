#include "./table.hpp" 

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;

    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

string get_type(string memo)
{
    vector<string> tmp;
    tmp = split(memo, "-");
    if (tmp.size() == 3) {
        return tmp[0];
    }
    return "";
}

void parse_memo(string memo, string &seed, uint8_t &bet)
{
    vector<string> tmp;
    tmp = split(memo, "-");
    if (tmp.size() == 3) {
        seed = tmp[1];
        bet = stoi(tmp[2]);
    }
}

