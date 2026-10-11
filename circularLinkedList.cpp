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
            head->next = tail->next = head;
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
            head->next = tail->next = head;
        }
        if(tail == head){
            head->next = n;
            tail = n;
            tail->next = head;
        }
        else{
            tail->next = n;
            tail = n;
            tail->next = head;
        }
    }

    void insert_middle(obj d, obj pos){
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

    // the del node will return the node previous to the one deleted
    cnode<obj> *  del_node(cnode<obj> * n){
        // find the d and the delete the d;
        if(head == nullptr){
            return nullptr;
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
                        return head;
                    }
                    tmp = cur;
                    tail->next = head->next;
                    head = cur->next;
                    delete tmp;
                    return tail;
                }
            }
            if(cur->next == n && cur->next == tail){
                    tmp = cur->next;
                    tail = cur;
                    tail->next= head;
                    delete tmp;
                    return tail;
            }
            if(cur->next == n){
                tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
                return cur;
            }
            cur = cur->next;
        }while(cur!=head);
        return nullptr;
    }

    // now i have to create the insert and the delete functions
    public:
    // default constructor:
        circularList(){
        head = nullptr;
        tail = nullptr; 
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
    // this function will only work if the obj is int

    void delete_even(){
        cnode<obj> *cur = head;
        cnode<obj> *tmp;
        // lets make a counter first:
        int size = 0;
        if(head == nullptr){
            return;
        }
        if(head -> next == head){
            if(head -> data %2 == 0)del_node(head);
            return;
        }
        do{
            size++;
            cur = cur->next;
        }while(cur!=head);
        for(int i = 0; i<size; ++i){
            if(cur->data %2 == 0){
                tmp = cur->next;
                del_node(cur);
                cur = tmp;
            }
            else{
                cur=cur->next;
            }
        }
    }

    void delete_odd(){
        cnode<obj> *cur = head;
        cnode<obj> *tmp;
        // lets make a counter first:
        int size = 0;
        if(head == nullptr){
            return;
        }
        if(head -> next == head){
            if(head -> data %2 != 0)del_node(head);
            return;
        }
        do{
            size++;
            cur = cur->next;
        }while(cur!=head);
        for(int i = 0; i<size; ++i){
            if(cur->data %2 !=0){
                tmp = cur->next;
                del_node(cur);
                cur = tmp;
            }
            else{
                cur=cur->next;
            }
        }
    }

    // now i have to create a method which will delete every third entry from the list until one
    // element is left:
    void joseph_prob_odd(){
        int i = 0;
        cnode<obj>* cur=tail;
        if(tail == nullptr){
            return;
        }
        do{
            i++;
            cur= cur->next;
            if(i%3 == 0){
                cur = del_node(cur);
            }
        }while(cur != cur->next);
    }

    // write a function that deletes all the even position node:
    void del_even_node(){
        // delete the node if the position is even:
        cnode<obj> * cur = head;
        cnode<obj> * tmp;
        int i = 0;
        if(tail == nullptr || head->next == head){
            return;
        }
        do{
            i++;
            if(i%2 == 0){
                // this means that the node is at a even position:
                tmp = cur->next;
                del_node(cur);
                cur = tmp;
            }
            else{
                cur = cur->next; 
            }
        }while(cur != head);
    }

    void delete_all() {
        if (head == nullptr) return;
        cnode<obj>* cur = head->next;
        while (cur != head) {            
            cnode<obj>* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        delete head;                     
        head = tail = nullptr;
    }

    int find(obj key) {
        if (head == nullptr) return -1;

        cnode<obj>* cur = head;
        int index = 0;
        do {
            if (cur->data == key) return index;
            cur = cur->next;
            index++;
        } while (cur != head);           

        return -1;                       
    }
    void display(){
       if(head == nullptr){ cout << "(empty)" << endl; return; }
       cnode<obj>* cur = head;
       do{ cout << cur->data << " "; cur = cur->next; }while(cur != head);
       cout << endl;
   }
};

int main(){
    circularList<int> list;

    cout << "--- insert ---" << endl;
    for(int i = 1; i <= 5; i++) list.insert(i);
    list.insert_begin(0);
    list.insert_find(3, 33);          
    list.display();                   

    cout << "--- find ---" << endl;
    cout << "index of 33: " << list.find(33) << endl;     
    cout << "index of 100: " << list.find(100) << endl;   

    cout << "--- delete ---" << endl;
    list.del(33);
    list.del_start();
    list.del_end();
    list.display();                  

    cout << "--- delete_even ---" << endl;
    list.delete_even();
    list.display();                   

    cout << "--- delete_odd ---" << endl;
    list.insert(8); list.insert(6); list.insert(7);
    list.display();                   
    list.delete_odd();
    list.display();                  

    cout << "--- josephus ---" << endl;
    list.delete_all();
    for(int i = 1; i <= 7; i++) list.insert(i);
    list.joseph_prob_odd();
    list.display();                   

    cout << "--- delete even positions ---" << endl;
    list.delete_all();
    for(int i = 1; i <= 5; i++) list.insert(i);
    list.del_even_node();
    list.display();                   
    list.delete_all();
    for(int i = 1; i <= 4; i++) list.insert(i);
    list.del_even_node();
    list.display();                  

    cout << "--- delete_all ---" << endl;
    list.delete_all();
    list.display();                   
    list.delete_all();                
    return 0;
}