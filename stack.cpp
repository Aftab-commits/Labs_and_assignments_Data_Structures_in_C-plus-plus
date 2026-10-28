// here is the task for the stack:
// Write an application using Stack that checks whether the entered 
//string of brackets is balanced, e.g.
// [{( )}] is Balanced while {[( )] } is not Balanced because the 
//priority of the pranthesis is not maintained.

#include <iostream>
#include<string>
using namespace std;


template<typename obj>
class stack{
    // for the stack i would be using the array lis:
    int cap;
    int size;
    int top;
    obj * arr;

    void resize(){
        if(size == cap){
            cap = cap*2;
            obj * data;
            data = new obj[cap];
            // now the size of the array has been increased:
            for(int i = 0; i<size; i++){
                data[i] = arr[i];
            }
            arr = data;
            delete data;
        }
    }

    // now i have to be making the pop, push and the show top fucntion:
    // the push will insert at the end and the pop will return the last and then remove it

    public:

    stack(){
        cap = 10;
        size = 0;
        top = -1;
        arr = new obj[cap];
    }
    void push(obj data){
        if(size == cap){
            resize();
            arr[size] = data;
            size++;
        }
        else{
            arr[size] = data;
            size++; 
        }
        top = size -1;
    }

    obj * pop(){
        if(size == 0){
            return nullptr;
        }
        else{
            size--;
            top = size-1;
            return & arr[size];// this is the last element returned

        }

    }

    int empty(){
        // return 0 if the stack is empty and -1 other wise:
        if(size == 0){
            return 0;
        }
        else{
            return -1;
        }
    }

    obj * show(){
        if(size == 0){
            return nullptr;
        }
        else{
            return & arr[top];
        }
    }

    // int size_stack(){
    //     return top+1;
    // }
    
    int check_prior(char b){
        // this function will give a number according to the braces passed.
        // this will help us determine the priority:
        if(b == '[' || b == ']'){
            return 1;
        }
        else if(b == '{' || b == '}'){
            return 2;
        }
        else if(b == '(' || b == ')'){
            return 3;
        }
        return -1;

    }




    public:
    int check_balance(string braces){
        // this will return 0 if successfull and return -1 is not
        // this function will receive a char array of the brackets:
        char b;
        int i = 0;
        int p;
        int n;
        stack<char> brac;
        if(braces.length() == 0){
            return -1;
        }
        do{
            b = braces[i];
            if(b == '(' || b=='[' || b =='{'){
                if(brac.show() == nullptr){
                    // the list is empty:
                    brac.push(b);
                }
                else{
                    p = check_prior(*(brac.show()));
                    n = check_prior(b);
                    if(n>=p){
                        brac.push(b);    
                    }
                    else{
                        return -1;
                    }    
                }
            }
            else if(b == ')' || b == ']' || b == '}'){
                if(brac.show() == nullptr){
                    return -1;
                }
                char n;
                if(brac.show() != nullptr)n = *brac.pop();
                int l;
                int r;
                l = check_prior(n);
                r = check_prior(b);
                if(r != l){
                    // this means that either the the most close left brace is
                    // high or low in priority
                    return -1;
                }

            }

            i++;
        }while(i<braces.length());

        if(brac.empty() == 0){
            return 0;
        }
        return -1;
    }

    // now i have to make a function to evaluate the result from the postfix expression:
    
    int cal(string exp){
        // if there is a operand that will be pushed to the stack and
        // if there is a operator then two value will be poped from the stack and
        // the operator will be applied between them then the result will pushed to the 
        // stack and the loop continues until the expression is finsihed. there should
        // remain only one value in the stack and that will be the result and if ther are more
        // then one value on the remaining stack this means that something has gone wrong

        int i = 0;
        stack<int> calc;
        char get;
        int first;
        int second;
        int result;
        if(exp.length() == 0){
            return -1;
        }
        do{
            get = exp[i];
            if(get == '+' || get == '-' || get == '*' || get == '/' || get == '%'){
                if(calc.empty() == 0 || i ==1 || i== 0 ){
                    return -1;
                }
                else{
                    second = * calc.pop();
                }
                if(calc.empty() == 0 || i ==1 || i== 0 ){
                    return -1;
                }
                else{
                    first = * calc.pop();
                }
                if(get == '+'){
                    result = first+second;
                }
                
                else if(get == '-'){
                    result = first-second;
                }
                
                else if(get == '*'){
                    result = first*second;
                }

                if(second !=  0){
                    if(get == '/'){
                        result = first/second;
                    }
                
                    if(get == '%'){
                        result = first%second;
                    }
                }
                // then push this result to the top of the stack:
                calc.push(result);
            }
            
            else if(get>='0' && get<='9'){
                // if it is a operand and it is a digit
                calc.push(int(get-'0'));
            }
            i++;

        }while(i<exp.length());
        if(calc.empty() == 0){
            return -1;
        }
        return * calc.pop();
    }

    // now i have to make the converter from the infinix to the postfix:
    // first i will try to make for the one digit numbers:
    // what is the plan: i will first take the infinix string and then
    // the operands will be pushed to a stack as it is and i will make a seperate stack for the 
    // operators. if the oprator coming has higher precdence then it is pushed as it is
    // if the operator coming is having less precdence then the list will be poped until the list
    // is empty or the top is having a operator of low precedence. if the incoming operator
    // has the same precende then the list will be poped until found an operator with the 
    // lower precedence.each time you pop a operator pop two operands from the 
    // operand stack
    

    int check_prior_op(char b){
        // this function will give a number according to the braces passed.
        // this will help us determine the priority:
        if(b == '+'){
            return 1;
        }
        else if(b == '-'){
            return 2;
        }
        else if(b == '*' || b == '/' || b == '%'){
            return 3;
        }
        return -1;

    }
    string converter(string inf){
        // the function receives a one digit number infinix expression:
        
        
        stack<char> postfix;
        stack<char> operator;
        int i = 0;
        char b;
        char tmp;
        int first;
        int second;
        int k=0;
        if(inf.length() == 0){
            return "error";
        }
        do{
            b = inf[i];
            if(b>=0 && b=<9){
                postfix.push(b);
            }
            if(b == '+' || b == '-' || b == '*' || b == '/' || b == '%'){
                k++;
                if(postfix.empty() == 0){
                    return "error";
                }
                // a function returns the size of the postix stack and it should
                // be equal to the k*2
                if(postfix.size() < k*2){
                    return "error";
                }
                
                if(operator.empty == 0){
                    operator.push(b);    
                }
                else{
                    tmp = * operator.show();
                    first = check_prior_op(tmp);
                    second = check_prior_op(b);
                    if(b>tmp){
                        operator.push(b);
                    } 
                    else if(b==tmp){
                        postfix.push(* operator.pop());
                    }
                    else if(b<tmp){
                        postfix.push(* operator.pop());
                    }
                }
            }
            i++;
        }while(i<inf.length());
        if(operator.empty != 0){
            return "error";
        }
        char exp [postfix.size()];
        int j = postfix. - 1;
        
        while(j>=0){
            exp[j] = postfix.pop();
        }
        string f_exp = exp;
        return f_exp;
    }
};


int main(){

    stack<int> n;
    // int check = n.check_balance("[{()}]");
    // cout<<check<<endl;
    string t = n.converter("5+4");
    cout<< t<<endl;


}