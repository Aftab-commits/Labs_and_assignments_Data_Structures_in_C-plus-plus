// i have to be doing the singly linked list here:
// for that i have to be creating my own list class
// i may also be using the template to create a generic class list

// add functionality to display the Link List in reverse (both using loops and using recursive approach)
#include <iostream>

using namespace std;

// fist i have to create the list class

template <typename obj>
class List
{
    struct node
    {
        obj data;
        node *next;

        node(obj d, node *n) : data(d), next(n)
        {
        }
    };

    void display_recursive(node *cur)
    {
        if (cur == nullptr)
        {
            return;
        }
        display_recursive(cur->next); // go to the end first, then print while coming back
        cout << cur->data << endl;
    }

public:
    node *head; // this is a single linked list
    node *current;
    node *tail;

    List()
    {
        head = nullptr; // the list is empty
        current = head;
        tail = nullptr;
    }

    List(obj d)
    {
        head = new node(d, nullptr);
        tail = head;
        current = head;
    }

    int size()
    {
        // this function will give the size of the list:
        int s = 0;
        for (current = head; current != nullptr; current = current->next)
        {
            s++;
        }
        return s;
    }

    //now i have to create functions to add and then remove the data and then i have to move the pointer
    // current accordingly

    // this function will add the data to the end
    void add_to_end(obj n)
    {
        node *p = new node(n, nullptr);

        // this will be normal if the list is not empty
        if (head != nullptr)
        {
            tail->next = p;
            tail = p;
        }
        else
        {
            head = p;
            tail = p;
        }
    }

    // this function will add the data at the start of the list
    void add_to_start(obj n)
    {
        node *p = new node(n, head);
        if (head == nullptr)
        {
            tail = p; // list was empty so the new node is also the last one
        }
        head = p;
    }

    // this method will add after the value given
    void add_after(obj n, obj in)
    {
        // this function will look for the n and then insert the in inside
        node *s;
        for (current = head; current != nullptr; current = current->next)
        {
            if (current->data == n)
            {
                // then i have to add the node after this
                s = new node(in, current->next);
                current->next = s;
                if (current == tail)
                {
                    tail = s; // the new node became the last one
                }
                return;
            }
        }

        add_to_end(in); // if the obj n was not found then the new object is added at the end of the list
    }

    void add_before(obj n, obj in)
    {
        node *s;

        if (head == nullptr)
        {
            return;
        }

        // also handle if the desired value is at the head then
        if (head->data == n)
        {
            s = new node(in, head);
            head = s;
            return;
        }

        for (current = head; current->next != nullptr; current = current->next)
        {
            if (current->next->data == n)
            {
                s = new node(in, current->next);
                current->next = s;
                return;
            }
        }
    }

    // now i have to do the delete fucntion:

    // this function handles all the remove cases for the remove by the object name:
    int remove(obj n)
    {
        if (head == nullptr)
        {
            return -1;
        }
        // to handle the case where you have to delete the head;
        else if (head->data == n)
        {
            node *p = head;
            head = head->next;
            if (head == nullptr)
            {
                tail = nullptr;
            }
            delete p;
            return 0;
        }

        else
        {
            node *p;
            for (current = head; current->next != nullptr; current = current->next)
            {
                if (current->next->data == n && current->next->next == nullptr)
                {
                    // this means the user is trying to delte the data at the tail node:
                    p = tail;
                    current->next = nullptr;
                    tail = current;
                    delete p;
                    return 0;
                }
                if (current->next->data == n)
                {
                    p = current->next;
                    current->next = current->next->next;
                    delete p;
                    return 0; // success
                }
            }
        }
        return -1; // in this case the data to be remove was not found in the list
    }

    // now i have to make the remove functions for the first and the last obj:

    void remove_start()
    {
        // this will remove the entry from the start if exists:
        if (head == nullptr)
        {
            return;
        }

        node *p;
        p = head;
        head = head->next;
        delete p;

        if (head == nullptr)
        {
            tail = nullptr;
        }
    }

    void remove_last()
    {
        // this will remove the last entry if exists:
        if (head == nullptr)
        {
            return;
        }

        // only one node in the list
        if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }

        // stop at the node just before the tail
        for (current = head; current->next != tail; current = current->next)
        {
        }
        delete tail;
        current->next = nullptr;
        tail = current;
    }

    void display()
    {
        for (current = head; current != nullptr; current = current->next)
        {
            cout << current->data << endl;
        }
    }

    // this will print the position of every match, not just the first one
    void search_all(obj n)
    {
        int pos = 0;
        bool found = false;
        for (current = head; current != nullptr; current = current->next)
        {
            if (current->data == n)
            {
                cout << n << " found at position " << pos << endl;
                found = true;
            }
            pos++;
        }
        if (!found)
        {
            cout << n << " not found in the list" << endl;
        }
    }

    // this will return the pointer of the node if the value is found otherwise nullptr
    node *search(obj key)
    {
        node *p = head;
        while (p != nullptr && p->data != key)
        {
            p = p->next;
        }
        return p;
    }

    // this will make a third new list which has all of l1 and then all of l2
    // it is static because both the lists are passed as parameters
    static List<obj> merge(List<obj> &l1, List<obj> &l2)
    {
        List<obj> merged;
        for (node *p = l1.head; p != nullptr; p = p->next)
        {
            merged.add_to_end(p->data);
        }
        for (node *p = l2.head; p != nullptr; p = p->next)
        {
            merged.add_to_end(p->data);
        }
        return merged;
    }

    void clear()
    {
        // delete every node and then the list is empty again
        while (head != nullptr)
        {
            remove_start();
        }
    }

    // create a function to reverse the list :
    void display_reverse_list()
    {
        // i have to display all the value in the list in reverse:
        // using for loop:
        int s = size();
        if (s == 0)
        {
            return;
        }
        obj *arr = new obj[s];
        int j = s;
        for (current = head; current != nullptr; current = current->next)
        {
            j--;
            arr[j] = current->data; // first node goes to the last place of the array
        }

        for (int i = 0; i < s; i++)
        {
            cout << arr[i] << endl;
        }
        delete[] arr;
    }
    void display_rec()
    {
        display_recursive(head);
    }
};

int main()
{
    List<int> list1(10);
    list1.add_to_end(20);
    list1.add_to_end(30);
    list1.add_to_end(40);

    List<int> list2(50);
    list2.add_to_end(60);
    list2.add_to_end(70);
    list2.add_to_end(60);

    List<int> l = List<int>::merge(list1, list2);

    int choice = 0;
    while (choice != 15)
    {
        cout << "\n========== LINKED LIST MENU ==========\n";
        cout << "1. Display list\n";
        cout << "2. Add after value\n";
        cout << "3. Add before value\n";
        cout << "4. Add to end\n";
        cout << "5. Remove value\n";
        cout << "6. Remove from start\n";
        cout << "7. Remove from last\n";
        cout << "8. Display reverse (loop)\n";
        cout << "9. Display reverse (recursive)\n";
        cout << "10. Search all occurrences\n";
        cout << "11. Size\n";
        cout << "12. Clear list\n";
        cout << "13. Add to start\n";
        cout << "14. Search a value (node pointer)\n";
        cout << "15. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int a, b;
        switch (choice)
        {
        case 1:
            l.display();
            break;
        case 2:
            cout << "Existing value, then new value: ";
            cin >> a >> b;
            l.add_after(a, b);
            l.display();
            break;
        case 3:
            cout << "Existing value, then new value: ";
            cin >> a >> b;
            l.add_before(a, b);
            l.display();
            break;
        case 4:
            cout << "Value: ";
            cin >> a;
            l.add_to_end(a);
            l.display();
            break;
        case 5:
            cout << "Value to remove: ";
            cin >> a;
            if (l.remove(a) == -1)
            {
                cout << "Value not found\n";
            }
            l.display();
            break;
        case 6:
            l.remove_start();
            l.display();
            break;
        case 7:
            l.remove_last();
            l.display();
            break;
        case 8:
            l.display_reverse_list();
            break;
        case 9:
            l.display_rec();
            break;
        case 10:
            cout << "Value to search: ";
            cin >> a;
            l.search_all(a);
            break;
        case 11:
            cout << "Size: " << l.size() << endl;
            break;
        case 12:
            l.clear();
            cout << "List cleared\n";
            break;
        case 13:
            cout << "Value: ";
            cin >> a;
            l.add_to_start(a);
            l.display();
            break;
        case 14:
            cout << "Value to search: ";
            cin >> a;
            if (l.search(a) == nullptr)
            {
                cout << "Value not found\n";
            }
            else
            {
                cout << "Node found at address " << l.search(a) << endl;
            }
            break;
        case 15:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    }

    return 0;
}
