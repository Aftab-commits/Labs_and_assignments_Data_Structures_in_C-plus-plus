// In this file i would be dealing with all the types of the linked lists
#include<iostream>
using namespace std;


// i am making to this to check if the data type is int:
template<typename obj>
struct isInt{
    static const int value = -1;
};
template<>
struct isInt<int>{
    static const int value = 0;
};



template<typename obj>
struct snode{
    obj data;
    snode<obj> * next;

    snode(obj d, snode<obj> * n): data(d), next(n){

    }
};

template<typename obj>
class s_list{
    snode<obj> * head;
    snode<obj> * tail;


    void display_reverse_p(snode<obj> * cur){
        // it will be called by head
        // i will do this by recursion:
        if(cur == nullptr){
            return;
        }
        display_reverse_p(cur->next);
        cout<<cur->data<<endl;
    }

    snode<obj> * del_by_node(snode<obj> * n){
        // this will delete the required node and return the node one after it
        snode<obj> * tmp;
        if(head == nullptr || n == nullptr){
            return nullptr;
        }
        if(head == n){
            tmp = head; 
            head = head->next;
            delete tmp;
            if(head == nullptr){
                tail = head;
            }
            return head;
        }

        for(snode<obj> * cur = head; cur!=nullptr; cur= cur->next){
            if(cur->next == n){
                tmp = cur->next;
                if(tmp == tail){
                    cur->next = nullptr;
                    tail = cur;
                    delete tmp;
                    return nullptr;
                }
                cur->next = cur->next->next;
                delete tmp;
                return cur->next;
            }
        }
        return nullptr;
    }

    int size_list(){
        // this function will give us the size of the list:
        int size = 0; 
        for(snode<obj> * cur = head; cur!=nullptr ;cur= cur->next){
            size++;
        }
        return size;
    }

    public:
    s_list(){
        head = nullptr;
        tail = nullptr;
    }
    ~s_list(){
        delete head;
        delete tail;
    }

    void insert_end(obj d){
        snode<obj> * n = new snode<obj>(d, nullptr);;
        if(head == nullptr){
            head = tail = n;
            return;
        }
        tail->next = n;
        tail = n;
    }

    void display_reverse(){
        display_reverse_p(head);
    }

    // reverse the list function:
    void reverse(){
        // Only the links are changed
        if(head == nullptr){
            return;
        }
        if(head == tail){
            return;
        }
        snode<obj>* prev = nullptr;
        snode<obj> * n ;
        snode<obj> * cur = head;
        tail = head;
        while(cur!=nullptr){
            n = cur->next;
            cur->next = prev;
            prev = cur;
            cur = n; 
        }
        head = prev;
    }


    void display(){
        // this displays the list:
        for(snode<obj> * cur = head; cur!= nullptr; cur= cur->next){
            cout<<cur->data<<endl;
        }
    }

    snode<obj> * del_by_val(obj d){
        // this will delete the required node and return the node one before it
        snode<obj> * tmp;
        if(head == nullptr){
            return nullptr;
        }
        if(head->data == d && head->next == nullptr){
            tmp = head;
            head = tail = nullptr;
            delete tmp;
            return nullptr;
        }
        for(snode<obj> * cur = head; cur!=nullptr; cur= cur->next){
            if(cur->next->data == d){
                tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
                return cur;
            }
        }
        return nullptr;
    }
    void rem_duplicate(){
        // this function will remove all the duplicates leaving unique values:
        snode<obj> * tmp;
        for(snode<obj> * cur = head ; cur!=nullptr ; cur=cur->next){
            for(snode<obj> * n = cur->next ; n!=nullptr ;){
                if(n->data == cur->data){
                    tmp = n;
                    n = del_by_node(tmp);
                }
                else{
                    n=n->next;
                }
            }
        }
    }
    void rem_duplicate_by_value(obj d){
        // this function will remove all the duplicates leaving unique values:
        snode<obj> * tmp;
        for(snode<obj> * cur = head ; cur!=nullptr ; ){
            if(cur->data == d){
                tmp = cur;
                cur = del_by_node(tmp);
            }   
            else{
               cur=cur->next;
            }
        }
    }

    // i have to detect if the singly list have a cycle:
    int check_cycle(){
        if(head == nullptr){
            return 0; // no cycle
        }
        if(head == tail && tail->next == nullptr){
            return 0; // no cycle
        }
        if(head == tail && tail->next == head){
            return -1; // cycle
        }
        snode<obj> * fast = head;
        snode<obj> * slow = head;
        do{
            // if the list has a a cycle then there will reach a point where the
            // the fast and the slow pointer are same other wise the fast will reach
            // the nullptr
            if(fast==nullptr || fast->next == nullptr){
                return 0;
            }
            fast = fast->next->next;
            slow = slow->next; 
        }while(fast!=slow);
        return -1;
        
    }

    snode<obj> * find_middle(){
        // this is odd
        snode<obj> * cur = head;
        int dest;
        int size = size_list();
        size%2 == 0? dest = size/2 : dest = (size/2)+1;
        for(int k = 1 ; k<dest ; k++){
            cur = cur->next;
        }
        return cur;
    }
    int is_empty(){
        //this returns 0 if it is empty and -1 if not:
        if(head == nullptr){
            return 0;
        }
        else{
            return -1;
        }
    }
    s_list<obj> * even_entries(){
        s_list<obj> * even = new s_list<obj>(); 

        if(isInt<obj>::value != 0){
            // this means the value of the list are not int
            return nullptr;
        }
        for(snode<obj> * cur = head; cur!=nullptr; cur=cur->next){
            if(cur->data%2 == 0){
                even->insert_end(cur->data);
            }
        }
        int r  = is_empty();
        if(r == 0){
            return nullptr;
        }
        else{
            return even;
        }
    }


    s_list<obj> * odd_entries(){
        s_list<obj> * odd = new s_list<obj>(); 
        
        if(isInt<obj>::value != 0){
            // this means the value of the list are not int
            return nullptr;
        }
        for(snode<obj> * cur = head; cur!=nullptr; cur=cur->next){
            if(cur->data%2 != 0){
                odd->insert_end(cur->data);
            }
        }
        int r  = is_empty();
        if(r == 0){
            return nullptr;
        }
        else{
            return odd;
        }
    }

    void reverse_recurse(snode<obj> * prev, snode<obj> * cur, snode<obj> * last){
        if(cur==last->next){
            // the last->next would be null in the tail case
            return;
        }
        reverse_recurse(cur,cur->next, last);
        cur->next = prev;
        prev = cur;
    }

    void full_reverse_recurse(){
        reverse_recurse(nullptr,head,tail);
        snode<obj> tmp = head;
        head = tail;
        tail = tmp;
    }

    void reverse_in_two(){
        // i have to reverse the list in two parts:
        int dest;
        int k = size_list();
        k%2 == 0 ? dest = size_list()/2 : dest = (size_list()/2)+1;
        snode<obj> * cur = head;
        int i = 1;
        while(i<dest){
            cur = cur->next;
            i++;
        }
        snode<obj> * start = cur->next;
        snode<obj> * prev = cur;
        
        
        reverse_recurse(tail,head,cur);
        head = cur;
        reverse_recurse(nullptr,start,tail);
        tail = start;
    }

    private:
    void swap_adjacent_front(snode<obj> * s1, snode<obj> * s2){
        // this funtion has to swap the adjacent entries
        int find = 0;
        for(snode<obj> * cur = head; cur!=nullptr ; cur = cur->next){
                if(cur == s1){
                    find = 1;
                }
            }
        if(find == 0 ) return;

        if(s1->next == s2){
            // s1 is before the s1
            snode<obj> * tmp;
            snode<obj> * bef;
            int h = 0;
            int t = 0;
            if(s1 == head){
                h = 1;
            }
            if(s2 == tail){
                t = 1;
            }
            for(snode<obj> * cur = head; cur!=nullptr ; cur = cur->next){
                if(cur->next == s1){
                    bef = cur;
                    break;
                }
            }
            tmp = s2->next;
            
            if(s1!=head){
                bef->next = s2;
            }
            s2->next = s1;
            
            if(s2 == tail){
                s1->next = nullptr;
            }
            else{
                s1->next = tmp;
            }
            if(h == 1){
                head = s2;
            }
            if(t == 1){
                tail = s1;
            }
        }
        return;

    }
    public:
    void swap(){
        // this function will swap the adjacent entries:
        if(head == nullptr || head == tail){
            return;
        }

        // i have function thtat swaps the adjacent ones
        // i just have to pass the values to be swaped and
        // all the cases will handled by the function
        snode<obj> * cur = head;
        snode<obj> * nxt = head->next;
        while(cur->next != nullptr){
            swap_adjacent_front(cur,nxt);
            cur = cur->next;
            nxt = nxt->next;
        }
    }


};

int main(){
    s_list<int> logs;
    logs.insert_end(10);
    logs.insert_end(20);
    logs.insert_end(30);
    logs.insert_end(40);
    logs.insert_end(50);
    logs.insert_end(60);


    // snode<int> * n = logs.find_middle();
    // cout<<n->data<<endl; 
    // s_list<int> * even = logs.odd_entries();
    // even->display();
    // logs.full_reverse_recurse();
    // logs.reverse_in_two();
    // logs.display();
    logs.swap();
    logs.display();

}
