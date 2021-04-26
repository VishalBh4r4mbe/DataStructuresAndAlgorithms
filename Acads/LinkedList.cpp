//Vishal Bharambe 

#include<iostream>
using namespace std;
template<class T> struct Node {
	Node<T>* next=nullptr;
    Node<T>* prev=nullptr;
	T data;
};

template <typename T> class SinglyLinkedList{
    private:
    Node<T> *head;
    Node<T> *tail;
    int length;
    Node<T> * next(Node<T>* cur){
        if(cur==tail)
    }
    public:
    SinglyLinkedList(){
        this->head=nullptr;
        this->tail=nullptr;
        this->length=0;
    }
    bool insertAtEnd(const T val){
        Node <T> *toInsert = new Node<T>;

        toInsert->data=val;
        if(head==nullptr){
            head=toInsert;
            tail=toInsert;
            length++;
            return true;
        }
        else{
            tail->next=toInsert;
            tail =toInsert;
            length++;
            return true;
        }
        return true;
    }
    bool insertAt(int idx,const T val){
        Node<T> *toInsert = new Node<T>;
        toInsert->data=val;
        if(idx>length){
            return false;
        }
        if(idx==0){
            head=toInsert;
            tail=toInsert;
            length++;
            return true;
        }
        else{
            if(head==tail){
                head->next=toInsert;
                tail=toInsert;
                length++;
            }
            else{
                Node<T> *previous=head;
                Node<T> *current = head->next;
                int cur = idx-1;
                while(cur--){
                    previous=previous->next;
                    current=current->next;
                }
                toInsert->next = current;
                previous->next = toInsert;
                if(toInsert->next==nullptr){
                    tail = toInsert;
                }
                
            }
            return true;
        }
        return false;
    }
    bool insertAtStart(const T val){
        Node<T> *toInsert = new Node<T>;
        toInsert->data = val;
        toInsert->next = head;
        head = toInsert;
        return true;
    }
    T get(int idx){
        if(idx+1>length){
            return -1;
        }
        if(idx==0){
            return head->data;
        }
        else{
            Node<T> *current= this->head;
            while(idx--){
                current = current->next;
            }
            return current->data;
        }
    }
    T operator[](int index) {
		return get(index);
	}
    int size(){
        return this-> length;
    }
    bool deleteLast(){
        if(length==0){
            return false;
        }
        else{
            Node<T>* curr = head;
            if(head->next==nullptr){
                head=nullptr;
                tail=nullptr;
                length=0;
                return true;
            }
            while(curr->next->next!=nullptr){
                curr=curr->next;
            }
            delete curr->next;
            curr->next=nullptr;
            length--;
            return true;
        }        
    }
    bool deleteFirst(){
        if(length==0){
            return false;
        }
        else{
            Node<T>* next = head->next;
            head->next=nullptr;
            delete head;
            head = next;
            length--;
            return true;
        }
    }
    bool deleteAt(int idx){
        Node<T>* curr = head;
        int cur = idx-1;
        if(idx>=length){
            return false;
        }
        else{
            while(cur--){
                curr=curr->next;
            }
            
            Node<T> *next = curr->next->next;
            delete curr->next;
            curr->next=next;
            length--;
            return true;
        }
    }
};
template <typename T> class DoublyLinkedList{
    private:
    Node<T> *head;
    Node<T> *tail;
    int length;
    public:
    DoublyLinkedList(){
        this->head=nullptr;
        this->tail=nullptr;
        this->length=0;
    }
    bool insertAtEnd(const T val){
        Node<T> *toInsert = new Node<T>;
        toInsert->data=val;
        if(length==0){
            head=toInsert;
            tail=toInsert;
            length++;
            return true;
        }
        else{
            tail->next= toInsert;
            toInsert->prev = tail;
            tail = toInsert;
            length++;
            return true;
        }
        
    }
    bool insertAtStart(const T val){
        Node<T> *toInsert = new Node<T>;
        toInsert->data=val;
        if(length==0){
            head=toInsert;
            tail=toInsert;
            length++;
            return true;
        }
        else{
            head->prev = toInsert;
            toInsert->next =head;
            head= toInsert;
            length++;
            return true;
        }
    }
    bool insertAt(int idx,const T val){
        Node<T> *toInsert = new Node<T>;
        toInsert->data=val;
        if(idx>length){
            return false;
        }
        if(length==0){
            head=toInsert;
            tail=toInsert;
            length++;
            return true;
        }
        else{
            if(idx>length/2){
                int cur = length - idx;
                Node<T>* curr = tail;
                Node<T>* last;
                if(cur==0){
                    return insertAtEnd(val);
                }
                while(cur--){
                    last=curr;
                    curr = curr->prev;
                }
                curr->next = toInsert;
                toInsert->prev = curr;
                curr->next=last;
                last->prev = toInsert;
                length++;
                return true;
            }
            else{
                Node<T>* curr = head;
                Node<T>* last;
                if(idx==0){
                    return insertAtStart(val);
                    
                }
                else{
                    while(idx--){
                        last=curr;
                        curr = curr->next;
                    }
                    last->next = toInsert;
                    toInsert->prev = last;
                    toInsert->next = curr;
                    curr->prev = toInsert;
                    length++;
                    return true;
                }
            }

        }
    }
    bool deleteLast(){
        if(length==0){
            return false;
        }
        if(length==1){
            delete tail;
            delete head;
            tail=nullptr;
            head = nullptr;
            length--;
            return true;
        }
        else{
            Node<T> *newTail = tail->prev;
            delete tail;
            tail=newTail;
            tail->next =nullptr;
            length--;
            return true;
        }
        

    }
    bool deleteFirst(){
        if(length==0){
            return false;
        }
        if(length==1){
            delete head;
            delete tail;
            head=nullptr;
            tail = nullptr;
            length--;
            return true;
        }
        else{
            Node<T> *newHead = head->next;
            delete head;
            head = newHead;
            newHead->prev = nullptr;
            length--;
            return true;
        }
    }
    bool deleteAt(int idx){
        if(idx>=length){
            return false;
        }
        if(idx==0){
            return deleteFirst();
        }
        else if(idx==length-1){
            return deleteLast();
        }
        else{
            Node<T> *last ;
            Node<T> *curr= head;
            if(idx>length/2){
                curr=tail;
                int cur  = length-idx-1;
                while(cur--){
                    curr= curr->prev;
                }
                if(curr->prev!=nullptr){
                    curr->prev->next= curr->next;
                }
                if(curr->next!=nullptr){
                    curr->next->prev = curr->prev;
                }
                delete curr;
                length--;
                return true;
            }
            else{
                while(idx--){
                    curr= curr->next;
                }
                if(curr->prev!=nullptr){
                    curr->prev->next= curr->next;
                }
                if(curr->next!=nullptr){
                    curr->next->prev = curr->prev;
                }
                delete curr;
                length--;
                return true;
            }
        }
    }
    T get(int idx){
        if(idx+1>length){
            return -1;
        }
        if(idx==0){
            return head->data;
        }
        else{
            Node<T> *current= this->head;
            while(idx--){
                current = current->next;
            }
            return current->data;
        }
    }
    T operator[](int index) {
		return get(index);
	}
    int size(){
        return this-> length;
    }
};

int main(){
    int ans =1;
    DoublyLinkedList<int> list;
    list.insertAtEnd(2);
    list.insertAtEnd(1);
    list.insertAt(1,69);
    list.deleteAt(0);
    for(int i=0; i<list.size();i++){
        cout<<list[i]<<" ";
    }    
}