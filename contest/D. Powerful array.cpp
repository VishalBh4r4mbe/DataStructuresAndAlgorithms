#include<bits/stdc++.h>
#define MAXN 200010
#define MAXX 1000010
using namespace std;
int block;
long long arr[MAXN+1],freq[MAXX+1],sol[MAXN+1];
inline long long int hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	long long int subSquareSize = 1LL << (2*pow - 2);
	long long int ans = seg * subSquareSize;
	long long int add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct Query{
    int l,r,idx;
    long long int order;
    Query(int _l,int _r,int id){
        l=_l;
        r=_r;
        idx=id;
        order = hilbertOrder(l,r,21,0); //Change 21 according to the fact that 2^k>n
    }
    bool operator<(Query other)const{
        return order< other.order;
    }
};
int main(){
	ios::sync_with_stdio(false);
	int n,t,l,r,lx,rx;
	long long x=0;
	cin>>n>>t;
    vector<Query> qry;
	for(int i=0;i<n;i++)
		cin>>arr[i];
	for(int i=0;i<t;i++){
		int l , r ;
        cin>>l>>r;
        l--;r--;
        qry.push_back(Query(l,r,i));
	}
	sort(qry.begin(),qry.end());
	for(int i=0;i<t;i++)
		cerr<<qry[i].l<<" "<<qry[i].r<<"\n";
	l=0;
	r=-1;
	for(int i=0;i<t;i++){
		lx=qry[i].l;
		rx=qry[i].r;
		while(l>lx){
			l--;
			x+=(((2LL*freq[arr[l]])+1)*arr[l]);
			freq[arr[l]]++;
		}
		while(l<lx){
			x-=(((2LL*freq[arr[l]])-1)*arr[l]);
			freq[arr[l]]--;
			l++;
		}
		while(r<=rx){
			x+=(((2LL*freq[arr[r]])+1)*arr[r]);
			freq[arr[r]]++;
			r++;
		}
		while(r>(rx+1)){
			r--;
			x-=(((2LL*freq[arr[r]])-1)*arr[r]);
			freq[arr[r]]--;
		}
		sol[qry[i].idx]=x;
	}
	for(int i=0;i<t;i++)
		cout<<sol[i]<<"\n";
	return 0;
}