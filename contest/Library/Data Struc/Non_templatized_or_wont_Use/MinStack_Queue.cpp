#include<bits/stdc++.h>
using namespace std;

template <typename T>class MinStack{
    private:
    stack<pair<T,T>> minStack;
    //Normal 
    public:
    MinStack(){};
    int size(){ return minStack.size();}
    //Modifications
    void pop(){ 
        minStack.pop();
    }
    T top(){ return minStack.top().first;}
    T minElement(){return minStack.top().second;}
    void push(T element){ 
        T mini  = minStack.empty()?element:min(element,minStack.top().second);
        minStack.push({element,mini});
    }
};
template <typename T> class MinQueue{
    stack<pair<int, int>> s1, s2;
    int countAdded=0;
    int countRemove=0;
    public:
    MinQueue(){};
    T minimum(){
        T mini;
        if (s1.empty() || s2.empty()) 
            mini = s1.empty() ? s2.top().second : s1.top().second;
        else
            mini = min(s1.top().second, s2.top().second);  
        return mini;
    }
    void push_back(T element){
        T mini = s1.empty() ? element : min(element, s1.top().second);
        s1.push({element, mini});
    }
    void pop(){
        if (s2.empty()) {
            while (!s1.empty()) {
                int element = s1.top().first;
                s1.pop();
                int mini = s2.empty() ? element : min(element, s2.top().second);
                s2.push({element, mini});
            }
        }
        int remove_element = s2.top().first;
        s2.pop();
    }
};
int main(){ 
    MinQueue<int> st;
    st.push_back(2);
    st.push_back(4);
    st.push_back(5);
    st.pop();st.pop();st.pop();
    cout<<st.minimum();
}