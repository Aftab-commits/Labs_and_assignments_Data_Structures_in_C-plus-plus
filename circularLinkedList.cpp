// here we have to be practing the circular linked list
#include<iostream>

using namespace std;
// firsst i have to create a class for the circular:

template<typename obj>
struct cnode{
    cnode<obj> * next;
    obj data;

    cnode(obj d, cnode<obj> * n): next(n), data(d){
    };
};

template<typename obj>
class circularList{
    // single linked circular
    cnode<obj> * head;
    cnode<obj> * tail;

    ~circularList(){
        delete head;
        delete tail;
    }
        // now i have to do the insertion:
    void insert_start(obj d){
        // the d has to be inserted one step before the head;
        cnode<obj> * n = new cnode<obj>(d, head);// pointing to the previous head
        if(head == nullptr){
            head = tail = n;
            tail->next = head;
        }
        else{
            // this will serve as the simple case:
            head = n;
            tail->next = n;
        }
    }
    void insert_end(obj d){
        // this is to insert the function at the end of the list
        cnode<obj> * n = new cnode<obj>(d, head);
        if(head == nullptr){
            head = tail = n;
            tail->next = head;
        }
        else{
            tail->next = n;
            tail = n;
            tail->next = head;
        }
    }

    void insert_middle(obj pos, obj d){
        // we have to insert the d after the pos
        if(head == nullptr){
            // the list is empty
            return;
        }
        cnode<obj> * cur = head;
        do{
            if(cur->data == pos){
                if(cur == tail){
                    insert_end(d);
                    return;
                }
                cnode<obj> * n = new cnode<obj>(d, cur->next);
                cur->next = n;
                break;
            }
            cur= cur->next;
        }while(cur!=head);
        return;// the element was not found
    }

    void del_node(cnode<obj> * n){
        // find the d and the delete the d;
        if(head == nullptr){
            return;
        }
        cnode<obj> * cur = head;
        cnode<obj> * tmp;
        do{
            if(cur == n){
                if( cur == head){
                    if(head == tail){
                        // this means there is only one node:
                        tmp = cur;
                        head = nullptr;
                        tail = nullptr;
                        delete cur;
                        return;
                    }
                    tmp = cur;
                    tail->next = head->next;
                    head = cur->next;
                    delete tmp;
                    return;
                }
            }
            if(cur->next == n && cur->next == tail){
                    tmp = cur->next;
                    tail = cur;
                    tail->next= head;
                    delete tmp;
                    return;
            }
            if(cur->next == n){
                tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
                return;
            }
            cur = cur->next;
        }while(cur!=head);
    }

    // now i have to create the insert and the delete functions
    public:
    // default constructor:
        circularList(){
        head = nullptr;
        head->next = head;
        tail = head; 
    } 

    // now i have to do the insertion:
    void insert_begin(obj d){
        insert_start(d);
    }
    void insert(obj d){
        insert_end(d);
    }
    void insert_find(obj d, obj pos){
        insert_middle(d,pos);
    }


    // always check the edge cases first
    void del(obj d){
        // find the d and the delete the d;
        if(head == nullptr){
            return;
        }
        cnode<obj> * cur = head;
        cnode<obj> * tmp;
        do{
            if(cur->data == d){
                if( cur == head){
                    if(head == tail){
                        // this means there is only one node:
                        tmp = cur;
                        head = nullptr;
                        tail = nullptr;
                        delete cur;
                        return;
                    }
                    tmp = cur;
                    tail->next = head->next;
                    head = cur->next;
                    delete tmp;
                    return;
                }
            }
            if(cur->next->data == d && cur->next == tail){
                    tmp = cur->next;
                    tail = cur;
                    tail->next= head;
                    delete tmp;
                    return;
            }
            if(cur->next->data == d){
                tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
                return;
            }
            cur = cur->next;
        }while(cur!=head);
    }


    void del_start(){
        // this will delete the node at the head;
        if(head == nullptr){
            return;
        }
        cnode<obj> * tmp;
        if(head == tail){
            tmp = head;
            head = tail = nullptr;
            delete tmp;
            return;
        }
        tmp = head;
        tail->next = head->next;
        head = head->next;
        delete tmp;
        return;
    }

    void del_end(){
        // this will delete the node at the tail
        if(head == nullptr){
            return;
        }
        cnode<obj> * tmp;
        if(head == tail){
            tmp = head;
            head = tail = nullptr;
            delete tmp;
            return;
        }
        cnode<obj> * cur = head;
        do{
            if(cur ->next == tail){
                tmp = tail;
                cur->next = head;
                tail = cur;
                delete tmp;
                return;
            }
            cur = cur->next;
        }while(true);
    }


    // now let me do the tasks:
    void delete_even(){
        // this function will delete those nodes whose data have even values:
        cnode<obj> *cur = head;
        do{
            if(cur->data %2 == 0){
                // it is even so delete this node
                del_node(cur);
            }
            cur = cur->next;
        }while(cur!=head);
    }
};




int main(){




}