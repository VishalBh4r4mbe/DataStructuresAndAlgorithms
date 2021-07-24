#include <bits/stdc++.h>
using namespace std;
//for 'a' - 'z' change 26 to something accordingly 
//Array implemenation of Trie
const int MaxNodes = 1e5+7;
int ender[MaxNodes];
int trie[26][MaxNodes];

bool created[MaxNodes];
int curSize= 0;
void insert(string &str){
    int curv=0;
    for(int i =0;i<str.size();i++){
        int curChar = str[i]-'a';
        if(!created[trie[curChar][curv]]){
            trie[curChar][curv]= ++curSize;
            created[curSize]=1;
        }
        curv=trie[curChar][curv];
    }
    ++ender[curv];
}

bool search(const string &str){
    int curv=0;
    for(int i=0;i<str.size();i++){
        int curChar = str[i]-'a';
        if(!created[trie[curChar][curv]]){
            return false;
        }
        curv=trie[curChar][curv];
    }
    return true;
}

template<int maxNodes= 1e5+7> class Trie{
    int ender[MaxNodes]={0};
    int trie[26][MaxNodes]={0};
    bool created[MaxNodes]={0};
    int curSize= 0;
    void insert(string &str){
        int curv=0;
        for(int i =0;i<str.size();i++){
            int curChar = str[i]-'a';
            if(!created[trie[curChar][curv]]){
                trie[curChar][curv]= ++curSize;
                created[curSize]=1;
            }
            curv=trie[curChar][curv];
        }
        ++ender[curv];
    }
    bool search(const string &str){
        int curv=0;
        for(int i=0;i<str.size();i++){
            int curChar = str[i]-'a';
            if(!created[trie[curChar][curv]]){
                return false;
            }
            curv=trie[curChar][curv];
        }
        return true;
    }
};
int main(){
    string s = "idk";
    insert(s);
    string sea= "id";
    cout<<search(sea);
}

//Node based implemenation on Trie
class TrieNode{
    TrieNode *children[26]{nullptr};
    bool endOfWord{false};
};
class Trie{ 
    private:
        TrieNode *root;
    public:
        Trie(){
            root= new TrieNode();
        }
        void insert(string &str){
            TrieNode *cur=root;
            for(int i=0;i<str.size();i++){
                if(cur->children[str[i]-'a']==nullptr){
                    cur->children[str[i]-'a']= new TrieNode();
                    cur = cur->children[str[i]-'a'];
                }
                else{
                    cur = cur->children[str[i]-'a'];
                }
                if(i==str.size()-1)cur->endOfWord=true;
            }
        }
        void search(string &str){
            TrieNode *cur=root;
            for(int i=0;i<str.size();i++){
                if(cur->children[str[i]-'a']==nullptr){
                    return false;
                }
                else{
                    cur = cur->children[str[i]-'a'];
                }
            }
        }
        return true;
}
