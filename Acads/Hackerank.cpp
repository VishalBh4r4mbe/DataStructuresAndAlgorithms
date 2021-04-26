//Vishal Bharambe 
#include<bits/stdc++.h>
using namespace std;
struct Node{
    Node* leftChild= nullptr;
    Node* rightChild  = nullptr;
    char curChar='.';
};
int main(){

        int t;
        cin>>t;
        
        while(t--){
            Node* cur = nullptr;
            Node* head = nullptr;
            
            int n;
            cin>>n;
            map<int,vector<char>> idk;
            for(int i = 0; i < n;i++){
                char inp;
                int freq;
                cin>>inp>>freq;
                idk[freq].push_back(inp);
            }
            for(auto x: idk){
                for(auto y:x.second){
                    if(cur ==nullptr){
                        cur=new Node;
                        cur->leftChild = new Node;
                        cur->leftChild->curChar =y;
                        head=cur;

                    }
                    else{
                        cur->rightChild = new Node;
                        cur=cur->rightChild;
                        cur->leftChild = new Node;
                        cur->leftChild->curChar = y;
                    }
                }
            }
            string input;
            cin>>input;
            cur = head;
            string ans="";
            for(auto x:input){
                if(x=='0'){
                    ans.push_back(cur->leftChild->curChar);
                    cur=head;
                }
                else{
                    if(x=='1'){
                        if(cur->rightChild->rightChild==nullptr){
                                ans.push_back(cur->rightChild->leftChild->curChar);
                                cur=head;
                        }
                        else{
                            cur = cur->rightChild;
                        }
                    }
                }
            }
            cout<<ans;
            


        }
        
}