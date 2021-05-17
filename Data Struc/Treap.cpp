#include<bits/stdc++.h>
using namespace std;
//DO NOT USE, SOMETHING IS WRONG WILL FIGURE OUT
//Remember to use a Array and not a vector due to the way the thing is coded.
//Will try to change everything in a Class format.
struct TreapNode{
    int key , priority;
    int treeSize;
    TreapNode* left; TreapNode* right;
    TreapNode(){}
    TreapNode(int key , int priority):key(key), priority(priority),left(NULL),right(NULL){}
};

void split(TreapNode *t , int key , TreapNode* &left, TreapNode* &right){
    if(!t){
        left=right=nullptr;
    }
    else if(key<t->key){
        split(t->left,key,left,t->left);
        right = t;
    }
    else{
        split(t->right,key,right,t->right);
        left = t;
    }
}

void insert(TreapNode* &t,TreapNode* it){
    if(!t){
        t=it;
    }
    else{
        if(it->priority>t->priority){
            split(t,it->key,it->left,it->right);
            t=it;
        }
        else{
            insert(it->key<t->key?t->left:t->right,it);
        }
    }
}

void merge(TreapNode* &t,TreapNode* left  ,TreapNode* right ){
    if(!left||!right){
        t=left?left:right;
    }
    else{
        if(left->priority>right->priority){
            merge(left->right,left->right,right);
            t=left;
        }
        else{
            merge(left->left,left,right->left);
            t=right;
        }
    }
}
void erase(TreapNode* tree,int key){
    if(tree->key ==key){
        TreapNode* th = tree;
        merge(tree,tree->left,tree->right);
        delete th;
    }
    else{
        erase(key<tree->key ? tree->left : tree->right, key);
    }
}
int getSize(TreapNode *t){
    if(t){
        return t->treeSize;
    }
    else{
        return 0;
    }
}
void updateSize(TreapNode *t){
    if(t){
        t->treeSize  = getSize(t->left)+getSize(t->right) +1;
    }
}

//For Building the treap

void heapify(TreapNode *tree){
    if(!tree)return;
    TreapNode * maxNode=tree;
    if(tree->left!=nullptr && tree->left->priority>maxNode->priority){
        maxNode = tree->left;
    }
    if(tree->right!=nullptr && tree->right->priority>maxNode->priority){
        maxNode = tree->right;
    }
    if(maxNode!=tree){
        swap(tree->priority,maxNode->priority);
        heapify(maxNode);
    }
}

//Build returns the root Node of the treap
TreapNode* build(int *vec,  int size){
    int n=size;
    if(n==0)return nullptr;
    int middle =n/2;
    TreapNode* tree= new TreapNode(vec[middle],rand());
    tree->left = build(vec,middle);
    tree->right = build(vec+middle+1,n-middle-1);
    heapify(tree);
    updateSize(tree);
    return tree;
};
void printInorder(TreapNode* t){
    if(!t)return;
    printInorder(t->left);
    cout<<t->key<<" ";
    printInorder(t->right);
}
//Will build Implcit Version as well

int main(){
    int arr[7]={1,2,3,5,6,7,8};
    TreapNode* t= build(arr,7);
    TreapNode* left;
    TreapNode* right;
    split(t,2,left,right);
    printInorder(left);
    cout<<endl;
    printInorder(right);
    
    return 0;
}