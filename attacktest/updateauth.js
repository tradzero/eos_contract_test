const Eos = require('eosjs')
eos = Eos({
    chainId: "e70aaab8997e1dfce58fbfac80cbbb8fecec7b99cf982a9444273cbc64c41473",
    httpEndpoint: 'http://jungle2.cryptolions.io',
    keyProvider: ''
});

function updateAuth(account, key) {
    var params = {
        account: account,
        parent: "owner",
        permission: "active",
        auth: {
            "threshold": 1,
            "keys": [{"key": key, "weight": 1}],
            "accounts": [{"permission": {"actor": account, "permission": "eosio.code"}, "weight": 1}]
        }
    };

    eos.contract('eosio').then(function(c){ c.updateauth(params, { authorization: `${account}@active`, broadcast: true, sign: true}).catch(function (e) {
        console.error(e);
    }); });
}

updateAuth('attacktest11', '');
updateAuth('attacktest22', '');
updateAuth('attacktest23', '');
updateAuth('attacktest24', '');
