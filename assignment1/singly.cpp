// In this file i would be dealing with single linked list
#include<iostream>
#include<string>
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
        // first remove a cycle if one exists
        if(check_cycle() == -1){
            snode<obj> * slow = head;
            snode<obj> * fast = head;

            do{
                slow = slow->next;
                fast = fast->next->next;
            }while(slow != fast);

            slow = head;
            while(slow != fast){
                slow = slow->next;
                fast = fast->next;
            }

            snode<obj> * last = slow;
            while(last->next != slow){
                last = last->next;
            }
            last->next = nullptr;
        }

        // delete every node in the list
        snode<obj> * cur = head;
        while(cur != nullptr){
            snode<obj> * tmp = cur;
            cur = cur->next;
            delete tmp;
        }

        head = nullptr;
        tail = nullptr;
    }

    void insert_end(obj d){
        snode<obj> * n = new snode<obj>(d, nullptr);
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
        snode<obj> * n;
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
        for(snode<obj> * cur = head; cur!= nullptr; cur=cur->next){
            cout<<cur->data<<endl;
        }
    }

    snode<obj> * del_by_val(obj d){
        // this will delete the required node and return the node one before it
        snode<obj> * tmp;

        if(head == nullptr){
            return nullptr;
        }

        // handle the head separately
        if(head->data == d){
            tmp = head;
            head = head->next;

            if(head == nullptr){
                tail = nullptr;
            }

            delete tmp;
            return nullptr;
        }

        for(snode<obj> * cur = head;
            cur->next != nullptr;
            cur = cur->next){

            if(cur->next->data == d){
                tmp = cur->next;
                cur->next = tmp->next;

                if(tmp == tail){
                    tail = cur;
                }

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
        // this function will remove all the entries matching the given value:
        snode<obj> * tmp;
        for(snode<obj> * cur = head ; cur!=nullptr ;){
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
            // if the list has a cycle then there will reach a point where the
            // fast and the slow pointer are same otherwise the fast will reach
            // the nullptr
            if(fast==nullptr || fast->next == nullptr){
                return 0;
            }
            fast = fast->next->next;
            slow = slow->next;
        }while(fast!=slow);

        return -1;
    }

    void create_cycle(int pos){
        // the tail will point back to the pos-th node (1-based):
        if(head == nullptr || pos < 1){
            return;
        }
        snode<obj> * target = head;
        for(int k = 1; k < pos && target != nullptr; k++){
            target = target->next;
        }
        if(target == nullptr){
            return;
        }
        tail->next = target;
    }

    snode<obj> * find_middle(){
        // for an even-sized list, this returns the left middle
        snode<obj> * cur = head;
        int dest;
        int size = size_list();

        size%2 == 0 ? dest = size/2 : dest = (size/2)+1;

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

        if constexpr (isInt<obj>::value != 0){
            // this means the values of the list are not int
            return nullptr;
        }
        else{
            s_list<obj> * even = new s_list<obj>();

            for(snode<obj> * cur = head; cur!=nullptr; cur=cur->next){
                if(cur->data%2 == 0){
                    even->insert_end(cur->data);
                }
            }

            int r = is_empty();
            if(r == 0){
                delete even;
                return nullptr;
            }
            else{
                return even;
            }
        }
    }


    s_list<obj> * odd_entries(){

        if constexpr (isInt<obj>::value != 0){
            // this means the values of the list are not int
            return nullptr;
        }
        else{
            s_list<obj> * odd = new s_list<obj>();

            for(snode<obj> * cur = head; cur!=nullptr; cur=cur->next){
                if(cur->data%2 != 0){
                    odd->insert_end(cur->data);
                }
            }

            int r = is_empty();
            if(r == 0){
                delete odd;
                return nullptr;
            }
            else{
                return odd;
            }
        }
    }

    void reverse_recurse(snode<obj> * prev, snode<obj> * cur, snode<obj> * last){
        if(last == nullptr || cur == nullptr || cur == last->next){
            return;
        }

        reverse_recurse(cur,cur->next, last);
        cur->next = prev;
        prev = cur;
    }

    void full_reverse_recurse(){
        if(head == nullptr || head == tail){
            return;
        }

        snode<obj> * tmp = head;
        reverse_recurse(nullptr,head,tail);
        head = tail;
        tail = tmp;
    }

    void reverse_in_two(){
        // i have to reverse the list in two parts:
        int dest;
        int k = size_list();

        // no reversal is needed for an empty list or a single node
        if(k < 2){
            return;
        }

        k%2 == 0 ? dest = k/2 : dest = (k/2)+1;

        snode<obj> * cur = head;
        int i = 1;

        while(i<dest){
            cur = cur->next;
            i++;
        }

        snode<obj> * start = cur->next;

        reverse_recurse(tail,head,cur);
        head = cur;

        reverse_recurse(nullptr,start,tail);
        tail = start;
    }

    private:
    void swap_adjacent_front(snode<obj> * s1, snode<obj> * s2){
        // this function has to swap the adjacent entries
        int find = 0;

        for(snode<obj> * cur = head; cur!=nullptr ; cur = cur->next){
            if(cur == s1){
                find = 1;
            }
        }

        if(find == 0) return;

        if(s1->next == s2){
            // s1 is before s2
            snode<obj> * tmp;
            snode<obj> * bef = nullptr;
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

        // swap two adjacent nodes, then move to the next pair
        snode<obj> * cur = head;

        while(cur != nullptr && cur->next != nullptr){
            snode<obj> * nxt = cur->next;

            swap_adjacent_front(cur,nxt);

            // cur is now the second node of the swapped pair
            // its next node starts the next pair
            cur = cur->next;
        }
    }


};




int main(){

    cout << "1. Logs in reverse (latest first):\n";
    s_list<int> logs;
    logs.insert_end(101);
    logs.insert_end(102);
    logs.insert_end(103);
    logs.insert_end(104);
    logs.display_reverse();


    cout << "\n2. Reverse the entire list:\n";
    s_list<int> playlist;
    playlist.insert_end(1);
    playlist.insert_end(2);
    playlist.insert_end(3);
    playlist.insert_end(4);
    playlist.reverse();
    playlist.display();



    cout << "\n3. Remove duplicate contacts:\n";
    s_list<int> contacts;
    contacts.insert_end(10);
    contacts.insert_end(20);
    contacts.insert_end(10);
    contacts.insert_end(30);
    contacts.insert_end(20);
    contacts.insert_end(40);
    contacts.rem_duplicate();
    contacts.display();


    //Detect whether a cycle exists.
    cout << "\n4. Cycle detection:\n";
    s_list<int> sensor;
    sensor.insert_end(11);
    sensor.insert_end(22);
    sensor.insert_end(33);

    cout << "Before: " << (sensor.check_cycle() == -1 ? "Cycle exists" : "No cycle exists") << endl;

    sensor.create_cycle(2);
    cout << "After:  " << (sensor.check_cycle() == -1 ? "Cycle exists" : "No cycle exists") << endl;


    //Find the middle element.
    cout << "\n5. Middle element:\n";
    s_list<int> friends;
    friends.insert_end(1);
    friends.insert_end(2);
    friends.insert_end(3);
    friends.insert_end(4);
    friends.insert_end(5);
    friends.insert_end(6);

    snode<int> * middle = friends.find_middle();

    if(middle != nullptr){
        cout << "Middle element: " << middle->data << endl;
    }



    cout << "\n6. Even-priced and odd-priced entries:\n";
    s_list<int> prices;
    prices.insert_end(12);
    prices.insert_end(7);
    prices.insert_end(24);
    prices.insert_end(9);
    prices.insert_end(16);
    prices.insert_end(5);

    s_list<int> * even = prices.even_entries();
    s_list<int> * odd = prices.odd_entries();

    cout << "Even entries:\n";
    if(even != nullptr){
        even->display();
    }

    cout << "Odd entries:\n";
    if(odd != nullptr){
        odd->display();
    }

    delete even;
    delete odd;



    cout << "\n7. Reverse both halves:\n";
    s_list<int> boxes;
    boxes.insert_end(1);
    boxes.insert_end(2);
    boxes.insert_end(3);
    boxes.insert_end(4);
    boxes.insert_end(5);
    boxes.insert_end(6);
    boxes.insert_end(7);
    boxes.insert_end(8);

    boxes.reverse_in_two();
    boxes.display();



    cout << "\n8. Remove duplicate stamps:\n";
    s_list<string> stamps;
    stamps.insert_end("Rose");
    stamps.insert_end("Star");
    stamps.insert_end("Moon");
    stamps.insert_end("Rose");
    stamps.insert_end("Sun");
    stamps.insert_end("Star");

    stamps.rem_duplicate();
    stamps.display();



    cout << "\n9. Delete all occurrences of an ID:\n";
    s_list<int> books;
    books.insert_end(10);
    books.insert_end(20);
    books.insert_end(10);
    books.insert_end(30);
    books.insert_end(10);
    books.insert_end(40);

    books.rem_duplicate_by_value(10);
    books.display();



    cout << "\n10. Swap adjacent pairs:\n";
    s_list<int> tasks;
    tasks.insert_end(1);
    tasks.insert_end(2);
    tasks.insert_end(3);
    tasks.insert_end(4);
    tasks.insert_end(5);
    tasks.insert_end(6);

    tasks.swap();
    tasks.display();

    return 0;
}