#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
#define MOD                 1000000007LL
#define EPS                 1e-9
#define io                  ios_base::sync_with_stdio(false);cin.tie(NULL);
 
const int N = 3e5+5;
const int M = 3e5+5;
const int SQN = sqrt(N) + 1;
 
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

struct query{
    int l,r,idx;
    long long int order;
    query(){
      
    }
    query(int _l,int _r,int id){
        l=_l;
        r=_r;
        idx=id;
        order = hilbertOrder(l,r,21,0); //Change 21 according to the fact that 2^k>n
    }
    bool operator<(query other)const{
        return order< other.order;
    }
};
 
query Q[M];
int ans[M];
int n, q;
int arr[N];
int ans2[M];
int freq[N], counter[N];
 
int main(){
 scanf("%d%d", &n, &q);
 for(int i = 1;i <= n; i++)
  scanf("%d", arr+i);
 for(int i = 1;i <= q; i++){
  int l, r;
  scanf("%d%d", &l, &r);
  Q[i] = query(l, r, i);
 }
 sort(Q+1, Q+1+q);
 int curl = 1, curr = 0;
 int t_ans = 0;
 for(int i = 1;i <= q; i++){
  int l = Q[i].l;
  int r = Q[i].r;
  int idx = Q[i].idx;
  ans2[idx]=r-l+1;
  while(curr < r){
   ++curr;
   int val = arr[curr];
   int c = freq[val];
   counter[c]--;
   freq[val]++;
   counter[freq[val]]++;
   t_ans = max(t_ans, freq[val]);
  }
  while(curl > l){
   --curl;
   int val = arr[curl];
   int c = freq[val];
   counter[c]--;
   freq[val]++;
   counter[freq[val]]++;
   t_ans = max(t_ans, freq[val]);
  }
  while(curr > r){
   int val = arr[curr];
   int c = freq[val];
   counter[c]--;
   freq[val]--;
   counter[freq[val]]++;
   while(counter[t_ans] == 0) t_ans--;
   --curr;
  }
  while(curl < l){
   int val = arr[curl];
   counter[freq[val]]--;
   freq[val]--;
   counter[freq[val]]++;
   while(counter[t_ans] == 0) t_ans--;
   ++curl;
  }
  ans[idx] = t_ans;
 }
 for(int i = 1;i <= q; i++){
        ll x=ans2[i];
        ll val=ans[i];
        cout<<max(2*val-x,1ll)<<endl;
 }
 return 0;
}