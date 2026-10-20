#include<iostream>
#include<string>
using namespace std;
// first i have to create a class for the circular:


struct task{
    string prior;
    string name;
    string status;
    task(string p, string n, string s): prior(p), name(n), status(s){
    };
};


template<typename obj>
struct cnode{ 
    cnode<obj> * next;
    obj data;
    cnode(obj d, cnode<obj> * n): next(n), data(d) {}
};

template<typename T>
struct isTsk {
    static const bool val = false;   
};

template<>
struct isTsk<task>{
    const static bool val = true; // i want to check if the data coming is task object or not
};

template<typename obj>
class circularList{


    cnode<obj> * head;
    cnode<obj> * tail;
    cnode<obj> * current;

    cnode<obj> *del_node(cnode<obj> *n) {
    if (head == nullptr || n == nullptr) {
        return nullptr;
    }

    cnode<obj> *cur = head;
    cnode<obj> *prev = tail;

    do {
        if (cur == n) {

            if (cur == current) {
                current = nullptr;
            }

            
            if (head == tail) {
                delete cur;
                head = tail = nullptr;
                return nullptr;
            }

            prev->next = cur->next;

            if (cur == head) {
                head = cur->next;
            }

            if (cur == tail) {
                tail = prev;
            }
            
            tail->next = head;

            delete cur;
            return prev;
        }

        prev = cur;
        cur = cur->next;

    } while (cur != head);

    return nullptr;
}

    public:
    
    ~circularList(){
        if(head == nullptr) return;
        tail->next = nullptr;         
        while(head != nullptr){
            cnode<obj> *tmp = head;
            head = head->next;
            delete tmp;               
        }
    }

    circularList(){
        head = nullptr;
        tail = nullptr;
        current = nullptr; 
    }

        void joseph_prob_odd(int m = 3) {
        if (head == nullptr || head == tail) {
            return;
        }

        int i = 0;
        cnode<obj> *cur = tail;

        while (head != tail) {
            cur = cur->next;
            i++;

            if (i % m == 0) {
                cur = del_node(cur);
            }
        }
    }

    void insert_end(obj d){
        // this function will insert the data at the end of the list
        cnode<obj> *n = new cnode<obj>(d,nullptr);
        if (head == nullptr) {
            n->next = n;
            head = tail = n;
        }
        else {
            n->next = head;
            tail->next = n;
            tail = n;
        }
    }
    

    // always check the edge cases first

    void del(obj d) {
        if (head == nullptr) {
            return;
        }

        string targetName;

        if constexpr (isTsk<obj>::val) {
            targetName = d.name;
        }

        cnode<obj> *cur = head;
        cnode<obj> *prev = tail;

        do {
            bool found = false;

            if constexpr (isTsk<obj>::val) {
                found = (cur->data.name == targetName);
            }
            else {
                found = (cur->data == d);
            }

            if (found) {
                // If the deleted node is current, clear current
                if (cur == current) {
                    current = nullptr;
                }

           
            if (head == tail) {
                delete cur;
                head = tail = nullptr;
                return;
            }

            prev->next = cur->next;

            if (cur == head) {
                head = cur->next;
            }

            if (cur == tail) {
                tail = prev;
            }

            tail->next = head;

            delete cur;
            return;
        }

        prev = cur;
        cur = cur->next;

        } while (cur != head);
    }

        obj * nextTask(){
        if(head == nullptr){
            return nullptr;
        }
        if(head == tail){
            if(head->data.status == "pend"){
                current = head;
                return &current->data;
            }
        }
        else{
            cnode<obj> * cur;
            cnode<obj> * tmp;
            if(current == nullptr){
                cur = head;            
            }
            else{
                cur = current->next;   
            }
            tmp = cur;

            do{
                if(cur->data.status == "pend"){
                    current = cur;
                    return &current->data;
                }
                cur = cur->next;
            }while (cur != tmp);
        }
        return nullptr;
    }


    void display_tasks(){
        if(head == nullptr){
            return;
        }
        cnode<obj> * cur = head; 
        int i = 1;
        do{
            if constexpr (isTsk<obj> :: val == true){
                cout<<i<<". "<<cur->data.name;
                cout<<"  "<<cur->data.prior<<endl;
                cout<<"  "<<cur->data.status<<endl;
                cout<<endl;
            }// when the circular list is of the task object
            // .The type matching is looked at the compile time but 
            // the typical if condition is checked at the run time but at the compile time the
            // code without the constexpr will cause error because the data.prior for the int type
            // list will cause error. so i want the condition to be checked at the complie time
            // that is why i use constexpr
            else{
                cout<<cur->data<<endl<<endl;
            }
            cur = cur->next;
            i++;
        }while(cur!=head);
    }

    // update status function will make the status of the task as the completed:
    void update_status(string name, string status){
        if(head == nullptr) return;
        if constexpr (isTsk<obj> :: val == false ){
            return; // this function will only work for the the task object list
        }
        else{
            cnode<obj> * cur = head;
            do{
                if(cur->data.name == name){
                    cur->data.status = status;
                    cout<<"The update status of the task "<<name<<" is "<<status<<endl; 
                    return;
                }
                cur = cur->next;
            }while(cur!=head);
        }
        return; // this means that the name is not found in the list
    }
};

int main(){
    
    circularList<int> people;
    int N = 7, M = 3;
    for(int i = 1; i <= N; i++){
        people.insert_end(i);
    }
    cout<<"Josephus with N = "<<N<<", M = "<<M<<endl;
    people.joseph_prob_odd(M);
    cout<<"Survivor position:"<<endl;
    people.display_tasks();                       

    
    circularList<task> tasks;
    tasks.insert_end(task("high",   "Design",  "pend"));
    tasks.insert_end(task("medium", "Coding",  "pend"));
    tasks.insert_end(task("low",    "Testing", "pend"));
    tasks.insert_end(task("high",   "Deploy",  "pend"));

    cout<<"\n--- All tasks ---"<<endl;
    tasks.display_tasks();

    cout<<"--- Round robin (5 calls) ---"<<endl;
    for(int i = 0; i < 5; i++){
        task *t = tasks.nextTask();
        if(t) cout<<"Next task: "<<t->name<<endl;
        else  cout<<"No pending task"<<endl;
    }
    

    cout<<"\n--- Mark Coding as completed ---"<<endl;
    tasks.update_status("Coding", "comp");

    cout<<"--- Round robin again (4 calls, Coding is skipped) ---"<<endl;
    for(int i = 0; i < 4; i++){
        task *t = tasks.nextTask();
        if(t) cout<<"Next task: "<<t->name<<endl;
        else  cout<<"No pending task"<<endl;
    }
    

    cout<<"\n--- Remove Testing ---"<<endl;
    tasks.del(task("", "Testing", ""));           
    tasks.display_tasks();

    cout<<"--- Complete everything ---"<<endl;
    tasks.update_status("Design", "comp");
    tasks.update_status("Deploy", "comp");
    task *t = tasks.nextTask();
    if(t) cout<<"Next task: "<<t->name<<endl;
    else  cout<<"No pending task"<<endl;          

    return 0;
}



