// i have to be doing the singly linked list here:
// for that i have to be creating my own list class
// i may also be using the template to create a generic class list

// add functionality to display the Link List in reverse (both using loops and using recursive approach)
#include<iostream>

using namespace std;

// fist i have to create the list class

template <typename obj>
class List{
    struct node{
        obj data;
        node *next;

        node(data d, node &n) : data(d), next(&node)
        {}
    }
    public:
        node * head; // this is a single linked list
        node * current;
        node *tail;
        List(){
            head = null; // the list is empty
            current = head;
            tail = null;
        }

        List(node &n){
            head = *n;
            tail = *n;
            current = head;           
        }
        //now i have to create functions to add and then remove the data and then i have to move the pointer
        // current accordingly

        // this function will add the data to the end 
        void add_to_end(obj n){
            // this function will add the node at the end of the 
            
            // this will be normal if the list is not empty

            node *p = new node(n, null);
            if(head!=null){
                tail->next = p;
                tail = p;
            }
            else{
                head = p;
                tail = p;
            }

        }

        // this method will add after the value given

        void add_after(obj n, obj in){
            // this function will look for the n and then insert the in inside 
            node *s;
            for(current = head ; current->next!=null; current = current->next){
                if(current->data == n){
                    // then i have to add the node after this
                    s = new node(in, current->next);
                    current-> next = s;
                    return;
                }
            }
            
            add_to_end(n); // if the obj n was not found then the object is added at the end of the list 
        }

        void add_before(obj n, obj in){
            node *s;

            if(head == null){
                return;
            }

            // also handle if the desired value is at the head then 
            if(head->data == n){
                s = new node(in, head);
                head = s;
                return;
            }

            for(current = head ; current->next !=null; current = current->next){
                if(current->next->data == n){
                    s = new node(in, current->next);
                    current->next = s;
                    return;
                }
            }
        }

        // now i have to do the delete fucntion:

        // this function handles all the remove cases for the remove by the object name:
        int remove (obj n){
            if(head == null){
                return -1;
            }
            // to handle the case where you have to delete the head;
            else if(head -> data == n){
                node *p = head;
                head = head -> next;
                if(head == null){
                    tail = null;
                }
                delete p;
                return 0;
            }

            else{
                node *p;
                for(current = head; current-> next!= null ;current = current -> next){
                    if(current -> next -> data == n && current -> next -> next == null){
                        // this means the user is trying to delte the data at the tail node:
                        p = tail;
                        current->next= null;
                        tail = current;
                        delete p;
                        return 0;

                    }
                    if(current -> next -> data == n){
                        p = current->next;
                        current-> next= current ->next->next;
                        delete p; 
                        return 0; // success
                    }
                }
            }
            return -1; // in this case the data to be remove was not found in the list
        }

        // now i have to make the remove functions for the first and the last obj:

        void remove_start(){
            // this will remove the entry from the start if exists:
            if(head == null){
                return;
            }

            node * p;
            p = head;
            head = head->next;
            delete p;

            if(head == null){
                tail = null;
            }

        }


        int size(){
            // this function will give the size of the list:
            int s = 0;
            for(current = head; current-> next!= null ;current = current -> next){
                size++;
            }
            return size;

        }
       // create a function to reverse the list :
       void display_reverse_list(){
            // i have to display all the value in the list in reverse:
            // using for loop:
            int j = size();
            obj arr[j];
            for(current = head ; current ->next != null && j>0; current = current ->next){
                j--;
                arr[j-1] = current -> data;
            }

            for(int i = 0; i<j ; i++){
                cout<<arr[i]<<endl;
            }
       }



};

int main(){




    return 0;
}