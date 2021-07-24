#include <bits/stdc++.h>
using namespace std;

vector<int> KMPprefix(string const &str){
    int strlen  = str.length();
    vector<int> prefix(str.length(),0);
    for(int i =1;i<strlen;i++){
        int curPointer = prefix[i-1];
        while(curPointer!=0&&str[i]!=str[curPointer]){
            curPointer = prefix[curPointer-1];
        }
        if(str[i]==str[curPointer]){
            curPointer++;
        }
        prefix[i] = curPointer;

    }s
    return prefix;
}
vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main(){
    string str;
    cin>>str;
    vector<int> toPrint = KMPprefix(str);
    for(auto  x: toPrint)cout<<x<<" ";
}