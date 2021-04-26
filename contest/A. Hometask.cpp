#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100000 + 10;
char s[N],a[N];
int main(){
    int k;
    scanf("%s%d",s,&k);
    while(k--){
        char c[3]; scanf("%s",c);
        a[c[0]]=c[1], a[c[1]] = c[0];
    }
    int n = strlen(s);
    int ans = 0;
    for(int i=0,j=0;i<n;i=j){
        while(j<n&&(s[j]==s[i]||s[j]==a[s[i]])) j++;
        int cnt[2] = {0};
        for(int k=i;k<j;k++) cnt[s[i]==s[k]]++;
        ans += min(cnt[0],cnt[1]);
    }
    cout<<ans<<endl;
}
