#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct FWHT {
    // C = SUM SUM A[i] * B[j] * x^(i xor j)
    //      i   j
    static vector<T> fastXor(const vector<T>& A, const vector<T>& B) {
        int size = 1;
        while (size < int(A.size()) || size < int(B.size()))
            size <<= 1;

        vector<T> tA(size);
        vector<T> tB(size);
        for (int i = 0; i < int(A.size()); i++)
            tA[i] = A[i];
        for (int i = 0; i < int(B.size()); i++)
            tB[i] = B[i];

        transformXor(tA, false);
        transformXor(tB, false);

        for (int i = 0; i < size; i++)
            tA[i] *= tB[i];

        transformXor(tA, true);

        return tA;
    }

    // C = SUM SUM A[i] * B[j] * x^(i or j)
    //      i   j
    static vector<T> fastOr(const vector<T>& A, const vector<T>& B) {
        int size = 1;
        while (size < int(A.size()) || size < int(B.size()))
            size <<= 1;

        vector<T> tA(size);
        vector<T> tB(size);
        for (int i = 0; i < int(A.size()); i++)
            tA[i] = A[i];
        for (int i = 0; i < int(B.size()); i++)
            tB[i] = B[i];

        transformOr(tA, false);
        transformOr(tB, false);

        for (int i = 0; i < size; i++)
            tA[i] *= tB[i];

        transformOr(tA, true);

        return tA;
    }

    // C = SUM SUM A[i] * B[j] * x^(i and j)
    //      i   j
    static vector<T> fastAnd(const vector<T>& A, const vector<T>& B) {
        int size = 1;
        while (size < int(A.size()) || size < int(B.size()))
            size <<= 1;

        vector<T> tA(size);
        vector<T> tB(size);
        for (int i = 0; i < int(A.size()); i++)
            tA[i] = A[i];
        for (int i = 0; i < int(B.size()); i++)
            tB[i] = B[i];

        transformAnd(tA, false);
        transformAnd(tB, false);

        for (int i = 0; i < size; i++)
            tA[i] *= tB[i];

        transformAnd(tA, true);

        return tA;
    }

private:
    // the size of P must be a power of 2
    static void transformXor(vector<T>& P, bool inverse) {
        int N = int(P.size());
        for (int step = 1; step < N; step <<= 1) {
            for (int i = 0; i < N; i += (step << 1)) {
                for (int j = 0; j < step; j++) {
                    T u = P[i + j];
                    T v = P[i + step + j];
                    P[i + j] = u + v;
                    P[i + step + j] = u - v;
                }
            }
        }

        if (inverse) {
            for (int i = 0; i < int(P.size()); i++)
                P[i] /= N;
        }
    }

    // the size of P must be a power of 2
    static void transformOr(vector<T>& P, bool inverse) {
        int N = int(P.size());
        for (int step = 1; step < N; step <<= 1) {
            for (int i = 0; i < N; i += (step << 1)) {
                for (int j = 0; j < step; j++) {
                    T u = P[i + j];
                    T v = P[i + step + j];
                    if (!inverse) {
                        P[i + j] = u + v;
                        P[i + step + j] = u;
                    } else {
                        P[i + j] = v;
                        P[i + step + j] = u - v;
                    }
                }
            }
        }
    }

    // the size of P must be a power of 2
    static void transformAnd(vector<T>& P, bool inverse) {
        int N = int(P.size());
        for (int step = 1; step < N; step <<= 1) {
            for (int i = 0; i < N; i += (step << 1)) {
                for (int j = 0; j < step; j++) {
                    T u = P[i + j];
                    T v = P[i + step + j];
                    if (!inverse) {
                        P[i + j] = v;
                        P[i + step + j] = v + u;
                    } else {
                        P[i + j] = v - u;
                        P[i + step + j] = u;
                    }
                }
            }
        }
    }
};
FWHT<int> fwht;
int main(){
    vector<int> arr{0,1,1,1,1,0,0,0};
    arr = fwht.fastOr(arr, arr);;
    for(auto x:arr){
        cout<<x<<" ";
    }
}