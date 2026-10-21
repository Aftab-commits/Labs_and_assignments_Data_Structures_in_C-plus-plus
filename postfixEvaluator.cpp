// here i would be making the infix to postfix conversion using stack
#include<iostream>
#include<vector>
#include<string>
#include<optional>
using namespace std;


// i am making this stack for the evaluation of answer from the given postfix expression
class stack{
    // i would be using the array one
    int top; // this is the index of the last element
    vector<int> arr;
    
    
    public:
    stack(){
        top = -1;
    }

    void push(int data){
        arr.push_back(data);
        top++;
    }
    int pop(){
        int i;
        if(top>-1){
            i = arr.at(top);
            arr.pop_back();// this removes the element from the end
            top--;
            return i;
        }
        return -9999;
    }
    int show(){
        if(top>-1){
            return arr.at(top);    
        }
        return -9999;
    }
    
    int empty(){
        // this returns 0 if the stack is empty:
        if(top == -1){
            return 0;
        }
        return -1;
    }

    int size(){
        if(top == -1){
            return 0;
        }
        return arr.size();
    }
};

int evaluate(string post){
    if(post.size() == 0){
        return -9999; // this means that something has went wrong
    }

    int i = 0;
    stack st;
    while(i<post.size()){
        if(post[i] == ' ') {
            i++;
            continue;
        }
        if(post[i]>='0' && post[i]<='9'){
            int num = 0;
            while((post[i]>='0' && post[i]<='9')&&i<post.size()){
                num = num*10 + (post[i] - '0'); 
                i++;    
            }
            st.push(num);
            continue;
        }
        else if(post[i] == '+' || post[i] == '-' ||
            post[i] == '*' || post[i] == '/' ||
            post[i] == '%'){
                if(st.size()<2){
                    return -9999; // issue
                }

                int first = st.pop();
                int second = st.pop();
                int res;

                if(post[i] == '+'){
                    res = second + first;
                }
                else if(post[i] == '-'){
                    res = second - first;
                }
                else if(post[i] == '*'){
                    res = second * first;
                }
                else if(post[i] == '/'){
                    if(first == 0){
                    return -9999;
                }
                    res = second / first;
                }
                else if(post[i] == '%'){
                    if(first == 0){
                    return -9999;
                }
                    res = second % first;
                }
                st.push(res);
            }
            else{
                return -9999;
            }  
            i++;
        }
        if(st.size() != 1){
            return -9999;
        }

        return st.pop();
}



int main(){

    string e = "78 99 * 90 +";
    int i = evaluate(e);
    if(i != -9999) cout<<i<<endl;
    else cout<<"Error in the question!";

    return 0;
}




