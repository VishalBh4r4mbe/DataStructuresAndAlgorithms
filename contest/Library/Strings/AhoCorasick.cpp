#include "bits/stdc++.h"
using namespace std;
struct AhoCorasickNode{
    AhoCorasickNode(){}
    AhoCorasickNode* children[26]{nullptr};
    AhoCorasickNode* suffix{nullptr};
    bool isLeaf=false;  
    int score=0;
};
class AhoCorasick{
private:
void dfs(AhoCorasickNode* node, AhoCorasickNode* other){
        node->isLeaf |= other->isLeaf;
        for(int i=0;i<26;++i){
            if(!other->children[i]){
                continue;
            }
            else if(!node->children[i]){
                node->children[i] = other->children[i];
                continue;
            }
            dfs(node->children[i],other->children[i]);
            delete other->children[i];
        }
    }
    AhoCorasickNode* root;
    int size;
    AhoCorasickNode* find(AhoCorasickNode *node, char c){
        int characterRepresentation = c-'a';
        while(node!=root){
            if(node->children[characterRepresentation])return node->children[characterRepresentation];
            else node = node->suffix;
        }
        if(node->children[characterRepresentation])return node->children[characterRepresentation];
        else return root;
    }
public:
    AhoCorasick(){root=new AhoCorasickNode();size=0;}
    ~AhoCorasick(){delete root;}
    void insert(string &s){
        AhoCorasickNode* curNode = root;
        for(auto character: s){
            int characterRepresentation  = character-'a';
            if(curNode->children[characterRepresentation]==nullptr){
                curNode->children[characterRepresentation]=new AhoCorasickNode();
            }
            curNode = curNode->children[characterRepresentation];
        }
        ++size;
        curNode->isLeaf = true;
    }
    void build(){
        queue<AhoCorasickNode*> q;
        q.push(root);
        root->suffix=root;
        while(!q.empty()){
            AhoCorasickNode* curNode = q.front();
            q.pop();
            for(int i=0;i<26;++i){
                if(curNode->children[i]){
                    AhoCorasickNode* nextNode = curNode->children[i];
                    if(curNode!=root)nextNode->suffix = find(curNode->suffix,'a'+i);
                    else nextNode->suffix = root;
                    nextNode->score = nextNode->suffix->score + nextNode->isLeaf;
                    q.push(nextNode);
                }
            }
        }
    }
    long long query(string &s){
        AhoCorasickNode* curNode = root;
        int score = 0;
        for(auto character: s){
            curNode = find(curNode,character);
            score += curNode->score;
        }
        return score;
    }
    void merge(AhoCorasick &other){
        dfs(root,other.root);
        size+=other.size;
    }
};
class OnlineAhoCorasick{
    public:
    vector<AhoCorasick> AhoCorasicks;
    void insert(string &s){
        AhoCorasick temp;
        temp.insert(s);
        AhoCorasicks.push_back(temp);
        while(AhoCorasicks.size()>1&&AhoCorasicks[AhoCorasicks.size()-2].size==AhoCorasicks[AhoCorasicks.size()-1].size){
            AhoCorasicks[AhoCorasicks.size()-2].merge(AhoCorasicks[AhoCorasicks.size()-1]);
            AhoCorasicks.pop_back();
        }   
        AhoCorasicks.back().build();
    }
    long long int query(string &s){
        long long int score = 0;
        for(auto &temp: AhoCorasicks){
            score += temp.query(s);
        }
        return score;
    }
};
int main(){
    int n;
    cin>>n;
    AhoCorasick add,del;
    while(n--){
        int type;
        string s;
        cin>>type>>s;
        if(type==1){
            add.insert(s);
        }
        else if(type==2){
            del.insert(s);
        }
        else {
            add.build();
            cout<<add.query(s)-del.query(s)<<endl;
        }
    }
}