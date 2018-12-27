# eos contract attack test

## contract

want to figure out is there a way to protect contract from another contract attack.

if test pass, this contract should pass:  
1. direction call attack. (contract attack1)  
   ```cleos -u http://jungle2.cryptolions.io:80 push action attacktest22 attack '{}' -p attacktest22```
   result: not pass
2. proxy call attack. (contract attack2)  
   ```cleos -u http://jungle2.cryptolions.io:80 transfer attacktest22 attacktest23 "0.0001 EOS" ""```
   result: not pass
3. defer call attack. (contract attack3)  
   ```cleos -u http://jungle2.cryptolions.io:80 push action attacktest24 attack '{}' -p attacktest24```
   result: pass
