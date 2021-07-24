#include "bits/stdc++.h"
using namespace std;
class Timer { private: chrono::time_point <chrono::steady_clock> Begin, End; public: Timer () : Begin(), End (){ Begin = chrono::steady_clock::now(); } ~Timer () { End = chrono::steady_clock::now();cerr << "\nDuration: " << ((chrono::duration <double>)(End - Begin)).count() << "s\n"; } } T;
typedef long long ll;
#define int ll
mt19937 rnd;
//check
/*
	 	QUERY TYPES:
		1. ADD x y D: Add D to each number in sub-sequence {Ax ... Ay}. For example, performing "ADD 2 4 1" on {1, 2, 3, 4, 5} results in {1, 3, 4, 5, 5}
		2. REVERSE x y: reverse the sub-sequence {Ax ... Ay}. For example, performing "REVERSE 2 4" on {1, 2, 3, 4, 5} results in {1, 4, 3, 2, 5}
		3. REVOLVE x y T: rotate sub-sequence {Ax ... Ay} T times. For example, performing "REVOLVE 2 4 2" on {1, 2, 3, 4, 5} results in {1, 3, 4, 2, 5}
		4. INSERT x P: insert P after Ax. For example, performing "INSERT 2 4" on {1, 2, 3, 4, 5} results in {1, 2, 4, 3, 4, 5}
		5. DELETE x: delete Ax. For example, performing "DELETE 2" on {1, 2, 3, 4, 5} results in {1, 3, 4, 5}
		6. MIN x y: what is the minimum number in sub-sequence {Ax ... Ay}. For example, the correct answer to "MIN 2 4" on {1, 2, 3, 4, 5} is 2
		7. SUM x y: what is the sum of all numbers in sub-sequence {Ax...Ay}. For example, the answer to "SUM 3 5" on {1, 2, 3, 4, 5} is 12
	*/
struct TreapNode {
	int data, priority;
	array<TreapNode*, 2> kids;
	int subtreeSize, sum, toProp;
    int minimum ;
    bool rev;
 
	TreapNode(int _data){
        data = _data; // value
        subtreeSize =1; // size
        sum = _data; // sum
        toProp =0; // lazyprops
        rev= false;  //is reversed?
        minimum = _data; // minimum
        kids[0]=kids[1]=nullptr; // left child -> 0 , right child ->1
    }
};
//checks
int size(TreapNode *me) {
	return me == NULL ? 0 : me->subtreeSize;
}
//check
void recalc(TreapNode *me) {
	if (me==NULL) return;
	me->subtreeSize = 1;
	me->sum = me->data + me->toProp*size(me);
    for (TreapNode* t:me->kids) if (t != NULL){ 
		me->subtreeSize += t->subtreeSize;
		me->sum += t->sum+t->toProp*size(t);
		me->minimum = min(me->minimum,t->minimum);
	}
}
void prop(TreapNode *me) {
	if (me==NULL) return;
	if (me->toProp == 0&&me->rev==false) return;
	
	for (TreapNode *t:me->kids) if (t != NULL) {
		t->toProp += me->toProp;
		t->rev^=1;
	}
	if(me->rev)swap(me->kids[0],me->kids[1]);
	me->rev= false;
	me->data+=me->toProp;
	me->toProp=0;
	recalc(me);
}
 
TreapNode* merge(TreapNode *l, TreapNode *r) {
	if (l==NULL) return r;
	if (r==NULL) return l;
	prop(l); prop(r);
	if (((rnd()<<15)+ rnd())%(l->subtreeSize+r->subtreeSize)<l->subtreeSize) {
		l->kids[1]=merge(l->kids[1], r);
		recalc(l);
		return l;
	}
	else {
		r->kids[0]=merge(l, r->kids[0]);
		recalc(r);
		return r;
	}
}
 
array<TreapNode*, 2> split(TreapNode *me, int nInLeft) {
	if (me == NULL) return {NULL, NULL};
	prop(me);
	if (size(me->kids[0])>=nInLeft) {
		array<TreapNode*, 2> leftRes=split(me->kids[0], nInLeft);
		me->kids[0]=leftRes[1];
		recalc(me);
		return {leftRes[0], me};
	}
	else {
		nInLeft = nInLeft - size(me->kids[0]) - 1;
		array<TreapNode*, 2> rightRes = split(me->kids[1], nInLeft);
		me->kids[1] = rightRes[0];
		recalc(me);
		return {me, rightRes[1]};
	}
	return {NULL, NULL};
}
TreapNode* rangeAdd(TreapNode* t, int l, int r, int toAdd) {
	array<TreapNode*, 2> a=split(t, l), b=split(a[1], r-l+1);
	b[0]->toProp+=toAdd;
	return merge(a[0], merge(b[0], b[1]));
}

vector<int> retrieval;
void getInorder(TreapNode* t){
    if(t==nullptr) return;
    prop(t);
    getInorder(t->kids[0]);
    retrieval.push_back(t->data);
    getInorder(t->kids[1]);
}
void printInorder(TreapNode* t){
    if(t==nullptr) return;
    prop(t);
    printInorder(t->kids[0]);
    cout<<(t->data)<<" ";
    printInorder(t->kids[1]);
}
int sum(TreapNode* t,int l , int r){
	array<TreapNode*,2> a = split(t,l);
	array<TreapNode*,2> b = split(a[1],r-l + 1);
	int sum = b[0]->sum;
	t = merge(a[0], merge(b[0], b[1]));
	return sum;
}
int minimum(TreapNode* t,int l , int r){
	array<TreapNode*,2> a = split(t,l);
	array<TreapNode*,2> b = split(a[1],r-l + 1);
	int mini = b[0]->minimum;
	t = merge(a[0], merge(b[0], b[1]));
	return mini;
}
TreapNode* insert(TreapNode *t,int idx,int val){
	if(idx>size(t))return merge(t,new TreapNode(val));
	array<TreapNode*, 2> temp  = split(t,idx);
	temp[0] = merge(temp[0],new TreapNode(val));
	t = merge(temp[0],temp[1]);
	return t;
}
TreapNode* erase(TreapNode* t,int idx){
	if(size(t)<idx)return t;
	
	array<TreapNode*, 2> temp = split(t,idx);
	array<TreapNode*, 2> temp2 = split(temp[1],1);
	t = merge(temp[0],temp2[1]);
	return t;
}
TreapNode* reverse(TreapNode* t, int l , int r){
	array<TreapNode*, 2> temp1 = split(t,l);
	array<TreapNode*, 2> temp2 = split(temp1[1],r-l + 1);
	temp2[0]->rev ^=1;
	return merge(temp1[0],merge(temp2[0],temp2[1]));
}
TreapNode* rotate(TreapNode* t, int l, int r , int k){
	if(l>r)return t;
	array<TreapNode*, 2> temp1 = split(t,l);
	array<TreapNode*, 2> temp2 = split(temp1[1],r-l + 1);
	k%=size(temp2[0]);
	array<TreapNode*, 2> temp3= split(temp2[0],size(temp2[0])-k);
	return merge(temp1[0],merge(temp3[1],merge(temp3[0],temp2[1])));
}
 
 
int getHeight(TreapNode *t){
	if(t==nullptr) return 0;
	else{
		return 1 + max(getHeight(t->kids[0]),getHeight(t->kids[1]));
	}
}
void deleteTreap(TreapNode *t){
	if(t==nullptr) return;
	else{
		deleteTreap(t->kids[0]);
		deleteTreap(t->kids[1]);
		delete t;
		return;
	}
}

signed main(){
    ifstream in;
    int countYes = 0;
    ofstream out;
    for(int i=1; i<7;i++){
        in.open("./A_tests/"+to_string(i)+".txt");
        out.open("./A_tests/soln"+to_string(i)+".out");
        int n,q,m;
        in>>n>>q>>m;
        TreapNode *treap = nullptr;
        for(int i =0;i<n;i++){
            int x;
            in>>x;
            treap = merge(treap,new TreapNode(x));
        }
        for(int i =0;i<q;i++){
            int type,l,r;
            in>>type>>l>>r;
            
            if(type==2){
                treap = rotate(treap,l-1,r-1,1);
            }
            else if(type==1){
                treap = reverse(treap,l-1,r-1);
            }
            else{
                treap = insert(treap,l-1,r);
            }
            // printInorder(treap);
            // cout<<endl;
        }
        getInorder(treap);
        for(int i =0;i<m;i++){
            int idx;
            in>>idx;
            idx--;
            out<<retrieval[idx]<<" ";
        }
        retrieval.clear();
        deleteTreap(treap);
        in.close();
        out.close();
    
    }
    
    return 0;
}