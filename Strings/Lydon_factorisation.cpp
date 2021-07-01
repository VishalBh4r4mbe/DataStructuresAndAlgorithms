#include "bits/stdc++.h"
using namespace std;
vector<string> factorise(string const& s) {
    int n = s.size();
    int i = 0;
    vector<string> factorization;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {   // if wi<wi+1 is needed change <= -> >=
            if (s[k] < s[j])                // and < to > here
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k) {
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}