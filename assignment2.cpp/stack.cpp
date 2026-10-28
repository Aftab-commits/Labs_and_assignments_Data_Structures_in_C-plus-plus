// i have to make a converter and an evaluator for the infix
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class stack
{
    // in the stack we delete the element from the last and also insert at the last
    int top;
    std::vector<char> arr;

    // top will be the index of the last one:

public:
    stack()
    {
        top = -1;
    }

    void push(char d)
    {
        arr.push_back(d);
        top++;
    }
    char pop()
    {
        // this will remove the last element and also remove it
        char d = '0';
        if (top == -1)
        {
            return d;
        }
        d = arr.at(top);
        arr.pop_back();
        top--;
        return d;
    }

    char show()
    {
        char d = '0';
        if (top == -1)
        {
            return d;
        }
        d = arr.at(top);
        return d;
    }

    int empty()
    {
        if (top == -1)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    int size()
    {
        return top + 1;
    }
};

class stack_int
{
    // in the stack we delete the element from the last and also insert at the last
    int top;
    std::vector<char> arr;

    // top will be the index of the last one:

public:
    stack_int()
    {
        top = -1;
    }

    void push(int d)
    {
        arr.push_back(d);
        top++;
    }
    int pop()
    {
        // this will remove the last element and also remove it
        int d = -1;
        if (top == -1)
        {
            return d;
        }
        d = arr.at(top);
        arr.pop_back();
        top--;
        return d;
    }

    int show()
    {
        int d = -1;
        if (top == -1)
        {
            return d;
        }
        d = arr.at(top);
        return d;
    }

    int empty()
    {
        if (top == -1)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    int size()
    {
        return top + 1;
    }
};

int prior(char d)
{
    // this function will give us the priority of the operatoors:
    if (d == '+')
    {
        return 1;
    }
    else if (d == '-')
    {
        return 2;
    }
    else if (d == '*' || d == '/' || d == '%')
    {
        return 3;
    }
    else if (d == '(' || d == ')')
    {
        return 4;
    }
    else if (d == '[' || d == ']')
    {
        return 5;
    }
    else if (d == '{' || d == '}')
    {
        return 6;
    }
    return -1;
}

int prior_brace(char d)
{
    if (d == '(' || d == ')')
    {
        return 1;
    }
    if (d == '[' || d == ']')
    {
        return 2;
    }
    if (d == '{' || d == '}')
    {
        return 3;
    }
}
int balance(string exp)
{
    stack brackets;
    string braces;
    int i = 0;

    while (i < exp.size())
    {
        if (exp[i] == '{' || exp[i] == '[' || exp[i] == '(' ||
            exp[i] == '}' || exp[i] == ']' || exp[i] == ')')
        {
            braces += exp[i];
            brackets.push(exp[i]);
        }
        i++;
    }

    if (brackets.size() % 2 != 0)
        return -1;
    int k = 0;
    while (k < brackets.size() / 2)
    {
        if (braces[k] == '{')
        {
            if (brackets.pop() != '}')
            {

                return -1; // not balance;
            }
            if (k >= 1)
                if (prior_brace(braces[k - 1]) < prior_brace(braces[k]))
                {
                    return -1;
                }
        }
        if (braces[k] == '[')
        {
            if (brackets.pop() != ']')
            {

                return -1; // not balance;
            }
            if (k >= 1)
                if (prior_brace(braces[k - 1]) < prior_brace(braces[k]))
                {
                    return -1;
                }
        }

        if (braces[k] == '(')
        {
            if (brackets.pop() != ')')
            {

                return -1; // not balance;
            }
            if (k >= 1)
                if (prior_brace(braces[k - 1]) < prior_brace(braces[k]))
                {
                    return -1;
                }
        }

        k++;
    }
    return 0; // the exp is balanced
}

std::string convert(std::string inf)
{
    // this is the converter function for the postfix conversion:
    stack out;
    stack oper;

    int i = 0;

    if (balance(inf) == -1)
    {
        return "Balance Error";
    }
    do
    {
        if (inf[i] >= '0' && inf[i] <= '9')
        {
            out.push(inf[i]);
        }
        else if (inf[i] == '(' || inf[i] == '[' || inf[i] == '{')
        {
            oper.push(inf[i]);
        }
        else if (inf[i] == '+' || inf[i] == '-' || inf[i] == '*' || inf[i] == '/' || inf[i] == '%')
        {
            if (oper.empty() == 0)
            {
                oper.push(inf[i]);
            }
            else
            {
                int coming;
                int last;
                coming = prior(inf[i]);
                last = prior(oper.show());
                while (coming <= last && last < 4)
                {
                    out.push(oper.pop());
                    last = prior(oper.show());
                }
                oper.push(inf[i]);
            }
        }

        else if (inf[i] == ')')
        {
            while (oper.show() != '(')
            {
                if (oper.empty() == 0)
                {
                    return "Error";
                }
                out.push(oper.pop());
            }
            oper.pop();
        }
        else if (inf[i] == ']')
        {
            while (oper.show() != '[')
            {
                if (oper.empty() == 0)
                {
                    return "Error";
                }
                out.push(oper.pop());
            }
            oper.pop();
        }

        else if (inf[i] == '}')
        {
            while (oper.show() != '{')
            {
                if (oper.empty() == 0)
                {
                    return "Error";
                }
                out.push(oper.pop());
            }
            oper.pop();
        }

        else
        {
            return "Error";
        }
        i++;
    } while (i < inf.size());

    while (oper.empty() != 0)
    {
        out.push(oper.pop());
    }

    if (oper.empty() != 0 || out.empty() == 0)
    {
        return "Error";
    }
    string s;
    while (out.empty() != 0)
    {
        s += out.pop();
    }

    string res;
    int k = s.size() - 1;
    while (k >= 0)
    {
        res += s[k];
        k--;
    }
    return res;
}

int cal(string post)
{
    // this gives the result after calculating from the postfix exp
    // the function will return -9999 in case of error
    stack_int res;
    int i = 0;
    int first;
    int second;
    int rs;
    while (i < post.size())
    {
        if (post[i] <= '9' && post[i] >= '0')
        {
            res.push(post[i] - '0');
        }
        else if (post[i] == '+' || post[i] == '-' || post[i] == '*' || post[i] == '/' || post[i] == '%')
        {
            if (res.empty() == 0)
            {
                return -9999;
            }
            else
            {
                second = res.pop();
            }
            if (res.empty() == 0)
            {
                return -9999;
            }
            else
            {
                first = res.pop();
            }
            if (post[i] == '+')
            {
                rs = first + second;
            }
            else if (post[i] == '-')
            {
                rs = first - second;
            }
            else if (post[i] == '*')
            {
                rs = first * second;
            }
            else if (post[i] == '/')
            {
                if (second != 0)
                    rs = first / second;
                else
                    return -9999;
            }
            else if (post[i] == '%')
            {
                if (second != 0)
                    rs = first % second;
                else
                    return -9999;
            }
            res.push(rs);
        }
        else
        {
            return -9999;
        }
        i++;
    }
    if (res.empty() == 0 || res.size() > 1)
    {
        return -9999;
    }
    else
    {
        return res.pop();
    }
}

int main()
{

    std::string inf = "{[(5+6)*7]/2}";
    string con;
    con = convert(inf);
    std::cout << con << std::endl;
    if (con != "Error" && con != "Balance Error")
    {
        int res = cal(con);
        cout << res << endl;
    }
}