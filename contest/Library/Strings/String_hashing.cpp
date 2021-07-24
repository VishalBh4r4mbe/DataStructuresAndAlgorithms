//     //This is for calculating a hash for a string 
// long long compute_hash(string const& s) {
//     const int p = 31;
//     const int m = 1e9 + 9;
//     long long hash_value = 0;
//     long long p_pow = 1;
//     for (char c : s) {
//         hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
//         p_pow = (p_pow * p) % m;
//     }
//     return hash_value;
// }

// //This is a efficient way to calculate hash for a substrings of a string
// string str;
// int len = str.length();
// vector<int> 
// int cur_pow=1;
// const int p = 31;               
// const int m = 1e9 + 9;
// vector<long long int>  p_pow(len + 1,1);
// vector<long long int>  p_inv_pow(len + 1,1);
// //pre Calculation
// for (ll i = 1; i < n; i++){
//     p_pow[i]=(p_pow[i-1]*p)%m;
// }
// for(ll i=1;i<n;i++){
//     p_inv_pow[i]= (powerMod(pow[i],m-2))%m;
// }

// for(ll i=1;i<=n;i++){
//     hash_value[i]= hash_value[i-1]+ ((int)(s[i-1]-'a'))*pow[i-1];
// }

template <long long int p,long long int m>
struct Hash{
    string str;
    vector<long long int> p_pow , p_inv_pow,hash_value;
    Hash(string &s){
        p_pow.resize(s.size()+1,1);
        p_inv_pow.resize(s.size()+1,1);
        hash_value.resize(s.size()+1,0);
        for (ll i = 1; i < n; i++){
            p_pow[i]=(p_pow[i-1]*p)%m;
        }
        long long int p_1 = powerMod(p,m-2,m);
        for(ll i=1;i<n;i++){
            p_inv_pow[i]= (p_inv_pow[i-1]*p_1)%m;
        }
        for(ll i=1;i<=n;i++){
            hash_value[i]= (hash_value[i-1]+ ((long long int)(s[i-1]-'a'))*pow[i-1])%m;
        }
    }
    long long int getHash(int l,int r){
        long long int hash = (hash_value[r]- hash_value[l-1])%m;
        hash= modMul(hash,p_inv_pow[l],m);
        return hash;
    }
}

// HashValue[i...j] = hash_value(0 ... j) - hash_value(0 ... i-1);
// hash_value(i ... j) = HashValue[i...j]*(p^i)^-1 under mod N;

//Also another way to think about this if now to use the p_inv_mod array is to
//multiply the difference with p_pow[n-i-1];