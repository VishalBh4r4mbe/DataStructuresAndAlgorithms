#include <bits/stdc++.h>
using namespace std;
//class Timer { private: chrono::time_point <chrono::steady_clock> Begin, End; public: Timer () : Begin(), End (){ Begin = chrono::steady_clock::now(); } ~Timer () { End = chrono::steady_clock::now();cerr << "\nDuration: " << ((chrono::duration <double>)(End - Begin)).count() << "s\n"; } } T;
//mt19937 rng((long long int) chrono::high_resolution_clock::now().time_since_epoch().count());
//long long int randRange(long long int l,long long int r){
//    return (rng())%(r-l+1) + l;
//}
vector<long long int> primes,leastPrimeFactor;
void fillPrimes(long long int N){
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
int main(){
    ofstream out;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    uniform_int_distribution<long long int> hun(1,100);
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen2(rd());
    std::uniform_int_distribution<long long int> distrib3(0, 1e9);
    fillPrimes(1000);

    int tcs = 2;
    int NLIMIT = 2e5;
    int P = primes.size()-1;

    for(int i =1;i<=tcs;i++){
        string s = to_string(i);
        out.open("./A_tests/"+s+".txt");
        std::uniform_int_distribution<long long int> distrib(1,NLIMIT);
        std::uniform_int_distribution<long long int> distrib2(1,1e9);
        std::uniform_int_distribution<long long int> distrib3(1, 100);

        int t = 100;
        out<<t<<endl;
        for(int i =1;i<=t;i++){
            int n= NLIMIT/t;
            std::uniform_int_distribution<long long int> distribi(2,n);
            
            n = distribi(gen);
            std::uniform_int_distribution<long long int> distrib3(1,n-1);
            out<<n<<" "<<distrib3(gen)<<endl;
            for(int j =0;j<n;j++){
                out<<distrib2(gen)<<" ";
            }
            out<<endl;
        }
        out<<endl;
        out.close();

    }
}