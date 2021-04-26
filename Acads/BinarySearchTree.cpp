#include <iostream>
#include <bits/stdc++.h>
using namespace std;
 
template <typename T> struct Node{
    Node<T>* leftChild=nullptr;
    Node<T>* rightChild=nullptr;
    T data;
    
};
template<typename T> class BST{
    private:
        Node<T>* root;
        Node<T>* search(T value){
            Node<T>* cur=root;
            while(cur!=NULL){
                if(cur->data==value)break;
                else if(cur->data>value)cur=cur->leftChild;
                else{
                    cur=cur->rightChild;
                }
            }
            return cur;
        }
        // Node<T>* findReplacement(Node<T>* node){
        //     if(node==NULL)return NULL;
        //     else if(node->rightChild==NULL&&node->leftChild==NULL){
        //         return node;
        //     }
        //     else{
        //         if(node->leftChild== NULL){
        //             return findMin(node->rightChild);
        //         }
        //         else{
        //             return findMax(node->leftChild);
        //         }
        //     }
        // }
        Node<T>* findMin(Node<T>* t){
            if(t == NULL)
                return NULL;
            else if(t->leftChild == NULL)
                return t;
            else
                return findMin(t->leftChild);
        }
 
    Node<T>* findMax(Node<T>* t) {
        if(t == NULL)
            return NULL;
        else if(t->rightChild == NULL)
            return t;
        else
            return findMax(t->rightChild);
    }
    Node<T>* deletenode(Node<T>* root, int k) {  
            if (root == NULL)return root; 
            if(root->data > k){ 
                root->leftChild = deletenode(root->leftChild, k); 
                return root; 
            } 
            else if(root->data < k){ 
                root->rightChild = deletenode(root->rightChild, k); 
                return root; 
            } 
            if (root->leftChild == NULL) { 
                Node<T>* temp = root->rightChild;
                delete root; 
                return temp; 
            } 
            else if (root->rightChild == NULL) { 
                Node<T>* temp = root->leftChild; 
                delete root; 
                return temp; 
            } 
            else {
                Node<T>* Parent = root;
                Node<T> *succ = root->rightChild; 
                while (succ->leftChild != NULL) { 
                Parent = succ; 
                succ = succ->leftChild; 
            } 
            if (Parent != root)Parent->leftChild = succ->rightChild; 
            else Parent->rightChild = succ->rightChild; 
            root->data = succ->data; 
            delete succ;          
            return root; 
            } 
        }
    public:
        vector<T> preOrder;
        BST(){
            root=NULL;
        }
        Node<T>* getHead(){
            return root;
        }
        bool insertIntoBST(T value , Node <T>* node ){
            Node<T>* toInsert = new Node<T>;
            toInsert->data = value;
            if(root==NULL){ 
                root=toInsert;
                return true;
            }
            if(node->data==value){
                delete toInsert;
                return false;
            }
            else{
                if(value>node->data){
                    if(node->rightChild!=NULL){
                        return insertIntoBST(value,node->rightChild);
                    }
                    else{
                        node->rightChild=toInsert;
                        return true;
                    }
                }
                else{
                    if(node->leftChild!=NULL){
                        return insertIntoBST(value,node->leftChild);
                    }
                    else{
                        node->leftChild = toInsert;
                        return true;
 
                    }
                }
            }
        }
        bool insert(T value){
            return insertIntoBST(value,root);
        }
        bool find(T value){
            return search(value)!=NULL;
        }
        bool remove(T value) {
            root=deletenode(root,value);
            if(root==NULL)return false;
            else{
                return true;
            }
        } 
        T max(){
            return findMax(root)->data;
        }
        T min(){
            return findMin(root)->data;
        }
};
       
int main(){
    BST<int> bst;
    
 
}   