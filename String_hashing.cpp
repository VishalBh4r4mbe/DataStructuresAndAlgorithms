    //This is for calculating a hash for a string 
long long compute_hash(string const& s) {
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

//This is a efficient way to calculate hash for a substrings of a string
string str;
int len = str.length();
int hash_value[len+1]={0};
int cur_pow=1;
const int p = 31;               
const int m = 1e9 + 9;
int p_pow[len];
p_pow[0]=1;
p_inv_pow[len];
//pre Calculation
for (ll i = 1; i < n; i++)
{
    p_pow[i]=(p_pow[i-1]*p)%m;
}
for(ll i=1;i<n;i++){
    p_inv_pow[i]= (powermod(pow[i],m-2))%m;
}

for(ll i=1;i<=n;i++){
    hash_value[i]= hash_value[i-1]+ ((int)(s[i-1]-'a'))*pow[i-1];
}
//aage you know what to do .

//Also another way to think about this if now to use the p_inv_mod array is to
//multiply the difference with p_pow[n-i-1];