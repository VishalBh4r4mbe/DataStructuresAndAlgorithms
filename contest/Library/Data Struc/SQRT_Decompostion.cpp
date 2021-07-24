// #include <bits/stdc++.h>
// int MAXN= 1e6+7;
// int BLOCK_SIZE = (sqrt(MAXN)+0.5);




// //REMEMBER THERE IS SOMETHING CALLED AS SQRT TREE WHICH HAS O(1) query and shit, check it out on CP Algorithms


// struct Query{
//     int l,r,idx;
//     bool operator<(Query other)const{
//         return {l/BLOCK_SIZE,r}<{other.l/BLOCK_SIZE,other.r};
//     }
// };

// vector<int> mo_sAlgorithm(vector<Query> &queries){
//     vector<int> ans (queries.size());
//     sort(queries.begin(), queries.end());
//     int curLeft=0,curRight=-1;
//     int curValue = 0;
//     for(auto query : queries){
//         while(curLeft>query.l){
//             curLeft--;
//             curValue+=arr[curLeft];
//         }
//         while(curRight<query.r){
//             curRight++;
//             curValue+=arr[curRight];
//         }
//         while(curLeft<query.l){
//             curValue-=arr[curLeft];
//             curLeft++;
//         }
//         while(curRight>query.r){
//             curValue-=arr[curRight];
//             curRight--;
//         }
//         ans[query.idx]=curValue;
//     }
//     return ans;
// }

//Optimised Mo's Algorithm with Hilbert Curve
using namespace std;

//)(n+q(root(N))) ->    q(rootN)
inline long long int gilbertOrder(int x, int y, int pow, int rotate) {
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
		long long int add = gilbertOrder(nx, ny, pow-1, nrot);
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
    cout<<"something is running";
}


