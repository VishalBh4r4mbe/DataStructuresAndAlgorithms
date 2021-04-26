/* 
    KEEP IN MIND THAT SPARSE MATRIX ONLY SUPPORTS IDEMPOTENT FUNCTIONS
*/

// define a function f() to be performed
 
int f(int x, int y=0){
    //function 
    //for ex. return(x+y);
}
int log[MAXN+1];
log[1] = 0;
for (int i = 2; i <= MAXN; i++)
    log[i] = log[i/2] + 1;
}
//Pre-Computation
K = log[n];

for (int i = 0; i < N; i++)
    st[i][0] = f(array[i]);

for (int j = 1; j <= K; j++)
    for (int i = 0; i + (1 << j) <= N; i++)
        st[i][j] = f(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);


//If a minimum query , we can do computation in O(1) time , as you can just ask for a range min in overlap .
int j = log[R - L + 1];
int minimum = min(st[L][j], st[R - (1 << j) + 1][j]);

//*****************************************************************//

int sum(int L , int R){
    long long sum = 0;
    for (int j = K; j >= 0; j--) {
        if ((1 << j) <= R - L + 1) {
            sum += st[L][j];
            L += 1 << j;
        }
    }
}