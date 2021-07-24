#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rnd;
//check
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
int random(){return (rnd()<<15)+ rnd();}
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
	if (random()%(l->subtreeSize+r->subtreeSize)<l->subtreeSize) {
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
void printInorder(TreapNode* t){
    if(t==nullptr) return;
    printInorder(t->kids[0]);
    cout<<t->data<<" ";
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

// class Treap{
// 	private:
// 		TreapNode *root;
// 		int size(TreapNode *me) {
// 			return me == NULL ? 0 : me->subtreeSize;
// 		}
// 		//check
// 		void recalc(TreapNode *me) {
// 			if (me==NULL) return;
// 			me->subtreeSize = 1;
// 			me->sum = me->data + me->toProp*size(me);
// 			for (TreapNode* t:me->kids) if (t != NULL){ 
// 				me->subtreeSize += t->subtreeSize;
// 				me->sum += t->sum+t->toProp*size(t);
// 				me->minimum = min(me->minimum,t->minimum);
// 			}
// 		}
// 		int random(){return (rnd()<<15)+ rnd();}
// 		void prop(TreapNode *me) {
// 			if (me==NULL) return;
// 			if (me->toProp == 0&&me->rev==false) return;
			
// 			for (TreapNode *t:me->kids) if (t != NULL) {
// 				t->toProp += me->toProp;
// 				t->rev^=1;
// 			}
// 			if(me->rev)swap(me->kids[0],me->kids[1]);
// 			me->rev= false;
// 			me->data+=me->toProp;
// 			me->toProp=0;
// 			recalc(me);
// 		}

// 		TreapNode* merge(TreapNode *l, TreapNode *r) {
// 			if (l==NULL) return r;
// 			if (r==NULL) return l;
// 			prop(l); prop(r);
// 			if (random()%(l->subtreeSize+r->subtreeSize)<l->subtreeSize) {
// 				l->kids[1]=merge(l->kids[1], r);
// 				recalc(l);
// 				return l;
// 			}
// 			else {
// 				r->kids[0]=merge(l, r->kids[0]);
// 				recalc(r);
// 				return r;
// 			}
// 		}

// 		array<TreapNode*, 2> split(TreapNode *me, int nInLeft) {
// 			if (me == NULL) return {NULL, NULL};
// 			prop(me);
// 			if (size(me->kids[0])>=nInLeft) {
// 				array<TreapNode*, 2> leftRes=split(me->kids[0], nInLeft);
// 				me->kids[0]=leftRes[1];
// 				recalc(me);
// 				return {leftRes[0], me};
// 			}
// 			else {
// 				nInLeft = nInLeft - size(me->kids[0]) - 1;
// 				array<TreapNode*, 2> rightRes = split(me->kids[1], nInLeft);
// 				me->kids[1] = rightRes[0];
// 				recalc(me);
// 				return {me, rightRes[1]};
// 			}
// 			return {NULL, NULL};
// 		}
// 		TreapNode* rangeAdd(TreapNode* t, int l, int r, int toAdd) {
// 			array<TreapNode*, 2> a=split(t, l), b=split(a[1], r-l+1);
// 			b[0]->toProp+=toAdd;
// 			return merge(a[0], merge(b[0], b[1]));
// 		}
// 		void printInorder(TreapNode* t){
// 			if(t==nullptr) return;
// 			printInorder(t->kids[0]);
// 			cout<<t->data<<" ";
// 			printInorder(t->kids[1]);
// 		}
// 		int sum(TreapNode* t,int l , int r){
// 			array<TreapNode*,2> a = split(t,l);
// 			array<TreapNode*,2> b = split(a[1],r-l + 1);
// 			int sum = b[0]->sum;
// 			t = merge(a[0], merge(b[0], b[1]));
// 			return sum;
// 		}
// 		int minimum(TreapNode* t,int l , int r){
// 			array<TreapNode*,2> a = split(t,l);
// 			array<TreapNode*,2> b = split(a[1],r-l + 1);
// 			int mini = b[0]->minimum;
// 			t = merge(a[0], merge(b[0], b[1]));
// 			return mini;
// 		}
// 		TreapNode* insert(TreapNode *t,int idx,int val){
// 			if(idx>size(t))return merge(t,new TreapNode(val));
// 			array<TreapNode*, 2> temp  = split(t,idx);
// 			temp[0] = merge(temp[0],new TreapNode(val));
// 			t = merge(temp[0],temp[1]);
// 			return t;
// 		}
// 		TreapNode* erase(TreapNode* t,int idx){
// 			if(size(t)<idx)return t;
			
// 			array<TreapNode*, 2> temp = split(t,idx);
// 			array<TreapNode*, 2> temp2 = split(temp[1],1);
// 			t = merge(temp[0],temp2[1]);
// 			return t;
// 		}
// 		TreapNode* reverse(TreapNode* t, int l , int r){
// 			array<TreapNode*, 2> temp1 = split(t,l);
// 			array<TreapNode*, 2> temp2 = split(temp1[1],r-l + 1);
// 			temp2[0]->rev ^=1;
// 			return merge(temp1[0],merge(temp2[0],temp2[1]));
// 		}
// 		TreapNode* rotate(TreapNode* t, int l, int r , int k){
// 			if(l>r)return t;
// 			array<TreapNode*, 2> temp1 = split(t,l);
// 			array<TreapNode*, 2> temp2 = split(temp1[1],r-l + 1);
// 			k%=size(temp2[0]);
// 			array<TreapNode*, 2> temp3= split(temp2[0],size(temp2[0])-k);
// 			return merge(temp1[0],merge(temp3[1],merge(temp3[0],temp2[1])));
// 		}


// 		int getHeight(TreapNode *t){
// 			if(t==nullptr) return 0;
// 			else{
// 				return 1 + max(getHeight(t->kids[0]),getHeight(t->kids[1]));
// 			}
// 		}

// 	public:
// 		int height(){
// 			return getHeight(this->root);
// 		}
		

// }
int main() {

    TreapNode* treap =nullptr;
	int n,m,q;
	cin>>n>>q>>m;
	
	deleteTreap(treap);
	return 0;
}