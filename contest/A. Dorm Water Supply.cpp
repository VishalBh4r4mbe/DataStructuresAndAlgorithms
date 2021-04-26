
#include <bits/stdc++.h>
using namespace std;
// const int dy[] = {1, 0, -1, 0};
namespace NT{
    long long int modulus = 998244353;  //Set this according to you 
    bool sieveDone = false,factorialCalc=false;
    vector<long long int> primes,leastPrimeFactor;
    vector<long long int> factorial,invFactorial;
    inline long long int modAdd(long long int a,long long int b,long long int mod = modulus){long long int ans = ( a%mod + b%mod )%mod;if(ans<0)ans+=mod;return ans;}
    inline long long int modMul(long long int a , long long int b,long long int mod = modulus){
        return ((a%mod)*(b%mod))%mod;
    }
    long long int powerMod(long long int base, long long int pw,long long int mod = modulus){
        long long int ret=1;
        if(base==1)return 1;
        while(pw){
            if(pw&1)ret=modMul(ret,base,mod);
            base = modMul(base,base,mod);
            pw>>=1;
        }
        return ret;
    }
    long long int extendedEuclid(long long int a,long long int b,long long int &x, long long int &y ){
        long long int xx=0,yy=1;y=0;x=1;
        //iterative 
        while(b){
            long long int quotient =a/b , temp = b; b=a%b;a=temp;
            temp=xx;xx=x - quotient*xx;x=temp;temp=yy;yy = y-quotient*yy;y=temp;
        }
        return a;
    }
    inline int mod_neg(int a, int b, int c){int res;if(abs(a-b)<c)res=a-b;else res=(a-b)%c;return(res<0?res+c:res);}
    inline long long int modInverse(long long int a,long long int mod = modulus){
        long long int x,y,z=0;
        long long int res= extendedEuclid(a,mod,x,y);
        return(res>1?-1:mod_neg(x,z,mod));
    }
    void findAllModuloInv(vector<long long int> &toFill,int m){
        if(toFill.size()!=m+1)toFill.resize(m+1);
        toFill[1] = 1;
        for(long long int i = 2; i < m; ++i)
            toFill[i] = m - (m/i) * toFill[m%i] % m;  
    }
    bool isPrime(long long int n) //Deterministic version of Miller Rabin's primality test
    {
        if(sieveDone&&leastPrimeFactor.size()-1<=n){
            return leastPrimeFactor[n]==n;
        }
        
        if(n<2)
            return false;
        for(long long int x:{2,3,5,7,11,13,17,19,23,29,31,37})
        {
            if(n==x)
                return true;
            bool flag=true;
            long long int  r=1;
            long long int  t=1;
            while(r<=((n-1)>>__builtin_ctzll(n-1)))
            {
                if(r&((n-1)>>__builtin_ctzll(n-1)))
                    t=((__int128)t*x)%n;
                x=((__int128)x*x)%n;
                r<<=1;
            }
            if(t==1||t==n-1)
                flag=false;
            for(r=0;r<__builtin_ctzll(n-1);r++)
            {
                t=((__int128)t*t)%n;
                if(t==n-1)
                    flag=false;
            }
            if(flag)
                return false;
        }
        return true;
    }
    void fillPrimes(long long int N){
        if(sieveDone&&leastPrimeFactor.size()-1>=N)return;
        sieveDone=true;
        if(leastPrimeFactor.size()!=N+1)leastPrimeFactor.resize(N+1);
        if(primes.size())primes.clear();
        for (int i=2; i<=N; ++i) {
            if (leastPrimeFactor[i] == 0) {
                leastPrimeFactor[i] = i;
                primes.push_back (i);
            }
            for (int j=0; j<(int)primes.size() && primes[j]<=leastPrimeFactor[i] && i*primes[j]<=N; ++j)
                leastPrimeFactor[i * primes[j]] = primes[j];
        }
    }
    void factorise(vector<long long int> &factors, long long int number){
        if(sieveDone&&leastPrimeFactor.size()-1<number){
                while(number!=1){
                    factors.push_back(leastPrimeFactor[number]);
                    number/=leastPrimeFactor[number];
                }
        }
        else{
            for(long long int i=2;i*i<=number&&number!=1;i++){
                while(number%i==0){
                    factors.push_back(i);
                    number/=i;
                }
            }
            if(number>1){
                factors.push_back(number);
            }
        }
    }
    void getFactorials(long long int N,long long int mod =modulus){
        if(factorialCalc&&factorial.size()-1>=N)return;
        factorial.resize(N+1);
        invFactorial.resize(N+1);
        factorial[0] = 1; 
        for(long long int i =1;i<N+1;i++){
            factorial[i]=modMul(factorial[i-1],i,mod);
        }
        invFactorial[N] = modInverse(factorial[N],mod); 
        for(int i=N-1;i>=0;i--)invFactorial[i] = modMul(i+1,invFactorial[i+1],mod); 
    }
    long long int nCr(int n,int r,long long int mod=modulus){
        long long int ans;
        if(r>n)ans= 0;
        if(r==n||r==0)ans= 1;
        getFactorials(n);
        ans= modMul(modMul(factorial[n],invFactorial[r],mod),invFactorial[n-r],mod);
        return ans;
    }
    long long int gcd(long long int  a,long long int b){if(a<b)swap(a,b);return(b?__gcd(a,b):a);}
    long long int lcm(long long int a , long long int b){return (a*b)/gcd(a,b);}
    long long int gcd(const vector<long long int> &arr){
        long long int ans=arr[0];for(int i=0;i<arr.size();i++)ans=gcd(arr[i],ans);  return ans;
    }
    long long int findPrimitiveRoot(long long int number,long long int greaterThan=0){
        vector<long long int> factors;
        factorise(factors,number-1);
        for (long long int res=(greaterThan<2?2:greaterThan+1); res<=number; ++res) {
            long long int flag=0;
            for(int i=0;i<factors.size();i++){if(powerMod(res,(number-1)/factors[i],number)==1){flag=1;break;}}
            if(flag==0){return res;}
        }
        return -1;
    }
    pair<long long int,long long int> chinese_remainder_theorem (long long int x, long long int a, long long int y, long long int b){
        long long int s, t;
        int d = extendedEuclid(x, y, s, t);
        if (a%d != b%d) return {0,-1};
        return {modAdd(s*b*x+t*a*y,x*y)/d, x*y/d};
    }
    //Keep in mind the coprime condition for mods
    pair<long long int,long long int> chinese_remainder_theorem (const vector<long long int> &x, const vector<long long int> &a){
        pair<long long int,long long int> ret = {x[0], a[0]};
        for (int i = 1; i < x.size(); i++){
            ret = chinese_remainder_theorem (ret.first, ret.second, x[i], a[i]);
            if (ret.second == -1) break;
        }
        
        //-1 is returned if no such number is there
        return ret;
    }
    namespace fft {
    	const long long int mod=modulus;
    	int root=-1;
    	int root_1=-1;
        bool initialized=false;
    	void init(){
    	    root =findPrimitiveRoot(mod);
    	    root_1 = modInverse(root);
    	}
    	void fft(vector<long long int>& a, bool invert) {
    		int n=a.size();
    		if(!initialized)init();
    		long long int PW=powerMod(invert?root_1:root, (mod-1)/n);
    	    for (long long int m=n, h; h=m/2, m>=2; PW=1LL*PW*PW%mod, m=h) {
                for (int i=0, w=1; i<h; ++i, w=1LL*w*PW%mod)
                for (int j=i; j<n; j+=m) {
                    int k=j+h, x=(a[j]-a[k]+mod)%mod;
                    a[j]+=a[k]; a[j] %= mod;
                    a[k]=1LL*w*x%mod;
                }
            }
            for (long long int i=0, j=1; j<n-1; ++j) {
                for (int k=n/2; k>(i^=k); k /= 2);
                if (j<i) swap(a[i], a[j]);
            }
    		if (invert) {
    			int rev=modInverse(n);
    			for (int i=0; i<n; ++i)
    				a[i]=1LL*a[i]*rev%mod;
    		}
    	}
    	vector<long long int> multiply(const vector<long long int>& a, const vector<long long int>& b) {
    		int n=max(a.size(), b.size());
    		vector<long long int> na=a, nb=b;
    		na.resize(2*n); nb.resize(2*n);
    		fft(na, false); fft(nb, false);
    		for (int i=0; i<2*n; ++i) na[i]=1LL*na[i]*nb[i]%mod;
    		fft(na, true);
            // na.resize(a.size()+b.size()-1); //uncomment when necessary
    		return na;
    	}
        vector<long long int>binExp(vector<long long int> a, long long int b) {
            vector<long long int> res{1};
            while (b > 0) {
                if (b & 1)
                    res = multiply(res,a);
                a = multiply(a,a);
                b >>= 1;
            }
            return res;
        }
        void adjustSizeForFFT(vector<long long int> &v){
            long long int size=v.size();
            long long int toSize=1;
            while(size){
                size>>=1;
                toSize<<=1;
            }
            v.resize(toSize);
        }
    };
 
    
};
using namespace NT;
typedef long long ll;
typedef long double ld;
const ld pi = acos(-1);
#define int ll
#define vi vector<ll>
#define vvi vector<vi>
#define pii pair<ll, ll>
#define vii vector<pll>
#define vs vector<string>
#define pb push_back
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
ll insum(vector<ll> &arr){
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
class Timer { private: chrono::time_point <chrono::steady_clock> Begin, End; public: Timer () : Begin(), End ()
{ Begin = chrono::steady_clock::now(); } ~Timer () { End = chrono::steady_clock::now();
cerr << "\nDuration: " << ((chrono::duration <double>)(End - Begin)).count() << "s\n"; } } T;

// const int dx[] = {0, 1, 0, -};
// const int dy[] = {1, 0, -1, 0};
vector<bool> vis;
vector<pair<int,int>>incoming,outgoing;
signed main()
{   
    fast_io();
    int t=1;
    // cin>>t;
    while (t--){
        in2(n,m);
        vis.assign(n+1,false);
        outgoing.assign(n+1,{0,0});
        incoming.assign(n+1,{0,0});
        forn(i,m){
            int u,v,diameter;
            cin>>u>>v>>diameter;
            outgoing[u] ={v,diameter};
            incoming[v] ={u,diameter};
        }
        vector<vector<int>> ans;
        for(int i =1;i<=n;i++){
            int v=i;
            int curMin= 1e18;
            int last = 0;
            if(!vis[i]&&outgoing[i].first==0&&incoming[i].first){
                while(incoming[v].first&&!vis[v]){
                    if(v == 0)break;
                    last = incoming[v].first;
                    
                    vis[v]=true;
                    curMin = min(curMin,incoming[v].second);
                    v = incoming[v].first;
                }
                vi temp{v,i,curMin};
                ans.push_back(temp);
            }
        }
        sort(all(ans));
        cout<<ans.size()<<endl;
        forn(i,ans.size())cout<<ans[i];

    }
        

}
