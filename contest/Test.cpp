#include<bits/stdc++.h>
using namespace std;
vector<pair<long long int,long long int>> dp;
vector<int> a;
void recur(int prevMask){
	for(int i=0;i<a.size();i++){
		for(int j=0;j<a.size();j++){
			if(i==j||(prevMask>>i)&1||(prevMask>>j)&1)continue;
			else{
				int curMask = prevMask;
				curMask|=(1<<i);
				curMask|=(1<<j);
				dp[curMask].first = max(dp[curMask].first,dp[prevMask].first + a[i]^a[j]);
				dp[curMask].second = min(dp[curMask].second,dp[prevMask].second + a[i]^a[j]);
				recur(curMask);
			}
		}
	}
}
 
int main(){
	int n;
	cin>>n;
	a.resize(n);
	for(auto &x : a){
		cin>>x;
	}
	dp.resize(1<<n,{-1,1e18});
	dp[0]={0,0};
	recur(0);
	cout<<dp.back().first<<" "<<dp.back().second<<endl;
}
