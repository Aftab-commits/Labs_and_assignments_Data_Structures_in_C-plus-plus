// there are three programs in the lab one. i will skip the problem one and 
// then sove the problem 2 and 3
// for the problem 2 and 3 i will be making array list manually. i will not be using the vectors

//---------Lab 2 question: -----------

// Write the computer program to apply the concepts of Array List. The array list will include the following 
// functions:
// 1. Insert the value at end of the list
// 2. Insert the value at start of the list
// 3. Insert the value after specific value
// 4. Insert the value before specific value
// 5. Display the array list
// 6. Delete the value from end of the list
// 7. Delete the value from start of the list
// 8. Delete specific value

#include <iostream>
using namespace std;

class array_list{
    public:
        // three attributes:
        int size;
        int cap;
        int *data;

        // constructor:
        array_list(){
            size = 0;
            cap = 4;
            data = new int[cap];
        }

        // destructor:
        ~array_list(){
            delete [] data;
        }
        // function for adding the value at the end of the array list:


        void resize(){
            cap = cap*2;
            int *newData = new int[cap];
            for(int i = 0 ; i<size; i++){
                newData[i] = data[i];
            }
            delete [] data;
            data = newData;
        }

        void add_at_end(int value){
            if(size>=cap){
                resize();
            }
            data [size] = value;
            size++;
        }

        // create a function to add the value at the start of the list:
        void add_at_start(int value){
            if(size>=cap){
                resize();
            }
            for(int i = size; i > 0; i--){
                data[i] = data[i-1];    
            }
            data[0] = value;
            size++;
        }
        // create function for deletion. deletion at the start:
        void delete_start(){
            for(int i = 0; i>size-1 ;i--){
                data[i] = data[i+1];
            }
            size--;
        }

        void delete_end(){
            if(size == 0){
                return ;
            }
            size--;
        }

        void display(){
            for(int i =0; i<size; i++){
                cout<<data[i]<<endl;
            }
        }

        // insert the value before a specific value:

        void add_before(int value){
            // this will find the first occurance of the vaue and add a element before that
            int find =1;
            int ind;
            for(int i = 0; i<size; i++){
                if(data[i] == value){
                    find =0;
                    ind = i;
                    break;
                }
            }

            if(find == 1){
                return;
            }

            else{
                // add the value before the given value;
                // the before value has to be inserted at the ind-1
                // the values after the ind-1 have to move one step right
                if(size>=cap){
                    resize();
                }
                for(int i=size ; i>ind  ; i--){
                    data[i] = data[i-1];
                }
                data[ind] = value;
                size++;
            }
        }


        void add_after(int value){
            int find =1;
            int ind;
            for(int i = 0; i<size; i++){
                if(data[i] == value){
                    find =0;
                    ind = i;
                    break;
                }
            }

            if(find == 1){
                return;
            }

            else{
                if(size>=cap){
                    resize();
                }
                for(int i=size ; i>ind+1  ; i--){
                    data[i] = data[i-1];
                }
                data[ind+1] = value;
                size++;
            }
        }

        void spec_delete(int value){
            // this function will delete the first occurance of the vlaue
                        int find =1;
            int ind;
            for(int i = 0; i<size; i++){
                if(data[i] == value){
                    find =0;
                    ind = i;
                    break;
                }
            }

            if(find == 1){
                return;
            }

            else{
                // we have to note the index of the value and move the array to the left
                for(int i=ind; i<size-1; i++){
                    data[i] = data[i+1];
                }
                size--;
            }
        }

        int find(int value){
            for(int i=0 ;i<size; i++){
                if(data[i] == value){
                    return 0;
                }
            }
            return 1;
        } 

};


int main(){
    array_list *sup = new array_list();
    (*sup).add_at_end(10);
    (*sup).add_at_end(11); //or sup ->. it is actaully the same as *sup 
    (*sup).add_at_end(12);
    (*sup).add_at_end(13);
    (*sup).add_at_end(14);
    (*sup).add_at_end(15);
    (*sup).add_at_end(16);
    (*sup).add_at_end(17);
    (*sup).add_at_end(18);
    (*sup).add_at_end(19);
    (*sup).add_at_start(20);

    (*sup).display();

    int key;
    cout<<"Enter the value you want to find: "<<endl;
    cin>>key;

    (*sup).find(key) == 0 ? cout<<"Value found!"<<endl : cout<<"Value not found!"<<endl; // this will give the first occurance of the key




    return 0;
}