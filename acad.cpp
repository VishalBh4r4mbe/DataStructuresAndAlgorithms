#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld pi = acos(-1);
#define int ll
#define vi vector<ll>
#define vvi vector<vi>
#define pii pair<ll, ll>
#define vii vector<pll>
#define vs vector<string>
#define fill(a, val) memset(a, val, sizeof(a))

#define ff first
#define ss second
#define forn(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define FOR(i,a,b) for (ll i = a; i < b; i++) 
#define rforn(i, n) for (ll i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define srt(v) sort(all(v));
#define rall(v) v.rbegin(), v.rend()
#define revsort(v) sort(rall(v))
#define rev(v) reverse(all(v));
#define PQ(type) priority_queue<type> 
#define PQD(type) priority_queue<type,vector<type>,greater<type> >  
#define FLSH fflush(stdout) 
#define space    " "            
#define fast_io()  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define in2(a,b) int a,b;cin >> a>>b;
#define pairin(v) cin>>v.first>>v.second;
#define in3(a,b,c) int a,b,c;cin>>a>>b>>c;
#define in4(a,b,c,d) int a,b,c,d;cin>>a>>b>>c>>d;
const int mod = 1e9 +7;
ll gcd(ll a,ll b){return(b?__gcd(a,b):a);} 
ll gcd(vi &arr){
  ll ans=arr[0];forn(i,arr.size())ans=gcd(arr[i],ans);  return ans;
}
ll sum(vector<ll> &arr){
	int ret=0;
	forn(i,arr.size()){
		cin>>arr[i];
		ret+=arr[i];
	}
	return ret;
}
map<int ,int> frequency(int n){
	map<int ,int> ret;
	forn(i,n){
		int x;
		cin>>x;
		ret[x]++;
	}
	return ret;
}
ll lcm(ll a, ll b){return(a*(b/gcd(a,b)));} 
ll muln(int a, int b, int c){ll res=(ll)a*b;return ((res%c)+c)%c;} 
template<typename T>T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=muln(x,p,m);p=muln(p,p,m);n>>=1;}return x;} 
template<typename T>T extended_euclid(T a, T b, T &x, T &y){T xx=0,yy=1;y=0;x=1;while(b){T q=a/b,t=b;b=a%b;a=t;
t=xx;xx=x-q*xx;x=t;t=yy;yy=y-q*yy;y=t;}return a;}
template<typename T> T add(T a, T b){return ((ll)(a+b))%mod; } 
template<typename T>T mod_inverse(T a, T n){T x,y,z=0;T d=extended_euclid(a,n,x,y);return(d>1?-1:mod_neg(x,z,n));} 
template<class T1> void deb(T1 e1) {cout << e1 << endl; } 
template<class T1,class T2> void deb(T1 e1, T2 e2){cout << e1 << space << e2 << endl;} 
template<class T1,class T2,class T3> void deb(T1 e1, T2 e2, T3 e3) {cout << e1 << space << e2 << space << e3 << endl;} 
template<class T1,class T2,class T3,class T4> void deb(T1 e1, T2 e2, T3 e3, T4 e4){cout << e1 << space << e2 << space << e3 << space << e4 << endl;} 
template<class T1,class T2,class T3,class T4,class T5> void deb(T1 e1, T2 e2, T3 e3, T4 e4, T5 e5){cout << e1 << space << e2 << space << e3 << space << e4 << space << e5 << endl;} 
template<class T1,class T2,class T3,class T4,class T5,class T6> void deb(T1 e1, T2 e2, T3 e3, T4 e4 ,T5 e5, T6 e6){cout << e1 << space << e2 << space << e3 << space << e4 << space << e5 << space << e6 << endl;} 
template <typename T> inline T PointDistanceHorVer(T x1,T y1,T x2, T y2) {return abs(x1-x2)+abs(y1-y2);} 
template <typename T> inline T PointDistanceDiagonally(T x1,T y1,T x2, T y2) {return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));} 
template <typename T> inline T PointDistanceMinimum(T x1,T y1,T x2, T y2) { T tmp1=abs(x1-x2); T tmp2=abs(y1-y2); T tmp3=abs(tmp1-tmp2); T tmp4=min(tmp1, tmp2); return tmp3+tmp4; } 
template <typename T> inline T PointDistance3D(T x1,T y1,T z1,T x2,T y2,T z2) {return sqrt(square(x2-x1)+square(y2-y1)+square(z2-z1));} 
  template <typename T> istream & operator>>(istream &in, vector<T> & v){for(auto &x: v){in>>x;} return in;}
  template <typename T> ostream& operator<<(ostream& os, const vector<T>& v) {for (int i = 0; i < v.size(); ++i) { os << v[i]; if (i != v.size() - 1) os << " "; } os << "\n"; return os; }
ll powersimp(ll x, ll n){ll ans = 1;while (n){if (n % 2 == 1)ans = ans * x;n = n / 2; x = x * x;} return ans;}
// class Timer { private: chrono::time_point <chrono::steady_clock> Begin, End; public: Timer () : Begin(), End ()
// { Begin = chrono::steady_clock::now(); } ~Timer () { End = chrono::steady_clock::now();
// cerr << "\nDuration: " << ((chrono::duration <double>)(End - Begin)).count() << "s\n"; } } T;
// const int FACSZ = 1001; // Make sure to change this 
// ll ceil_div(ll a, ll b){return (a+b-1)/b;}
// int fact[FACSZ],ifact[FACSZ]; 
// void precom(int c){ 
//     fact[0] = 1; 
//     FOR(i,1,FACSZ) fact[i] = muln(fact[i-1],i,c); 
//     ifact[FACSZ-1] = mod_inverse(fact[FACSZ-1],c); 
//     REPD(i,FACSZ-1){ 
//         ifact[i] = muln(i+1,ifact[i+1],c); 
//     } 
// } 
// int ncr(int n,int r,int c){ 
//     return muln(muln(ifact[r],ifact[n-r],c),fact[n],c); 
// }

// void add(int &a, int b)
// {
//     a += b;
//     if(a >= mod)
//         a -= mod;
// }
// const int dx[] = {0, 1, 0, -};
// const int dy[] = {1, 0, -1, 0};


signed main()
{
	

	
	
	return 0;
}

