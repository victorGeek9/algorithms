/*
  skip list
  Nosov Viktor
*/
#include<iostream>
#include <fstream>
#include <time.h>
using namespace std;
struct fields {
    int i;
    double d;
    char ch;
    fields** next;
};
int generate_height(int max);
class lista {
    int max_height;
    int amount = 0;
    fields* first;
    fields* last;
public:
    lista(int height = 10) {
        max_height = height;
        first = new fields();
        last = new fields();
        first->next = new fields * [max_height];
        last->next = new fields * [max_height];
        for (int i = 0; i < max_height; i++) {
            first->next[i] = last;
            last->next[i] = nullptr;
        }
    }
    bool add(int key) {
        int height;
        fields* el = new fields;
        el->i = key;
        height = generate_height(max_height);
        el->next = new fields * [height];
        if (amount == 0) {
            for (int i = 0; i < height; i++) {
                first->next[i] = el;
                el->next[i] = last;
            }
        }
        else {
            fields* temp, * start = first;
            for (int i = height - 1; i >= 0; i--) {
                temp = start->next[i];
                if (temp != last) {
                    if (temp->i < key) {
                        start = temp;
                        i++;
                    }
                    else {
                        if (temp->i == key) {
                            temp->ch = 'T';
                            temp->d = rand() + ((double)rand() / RAND_MAX);
                            delete[] el->next;
                            delete el;
                            return false;
                        }
                    }
                }
            }
            start = first;
            for (int i = height - 1; i >= 0; i--) {
                temp = start->next[i];
                if (temp != last) {
                    if (temp->i < key) {
                        start = temp;
                        i++;
                    }
                    else {
                        el->next[i] = start->next[i];
                        start->next[i] = el;
                    }
                }
                else {
                    el->next[i] = last;
                    start->next[i] = el;
                }
            }
        }
        el->ch = 'T';
        el->d = rand() + ((double)rand() / RAND_MAX);//rand() zwraca int + ulamek
        amount++;
        return true;
    }
    void add_elements(int num) {
        int temp;
        for (; num > 0; num--) {
            temp = rand() % 100000;
            if (temp < 99) {
                temp += 100;
            }
            if (!add(temp)) {
                num++;
            }
        }
    }
    void display_first(int num) {
        if (amount == 0) {
            cout << "List is empty." << endl;
            return;
        }
        fields* temp = first->next[0];
        cout << "Display first " << num << " elements or all(if " << num << " < " << amount
            <<") :" << endl;
        for (int i = 0; i < amount && num > 0; i++, num--) {
            cout << i + 1 << ") " << temp->i << "  " << temp->d << "  " << temp->ch << endl;
            temp = temp->next[0];
        }
    }
    void display_last(int num) {
        if (amount == 0) {
            cout << "List is empty." << endl;
            return;
        }
        fields** arr = new fields*[amount], * temp = first->next[0];
        cout << "Display last " << num << " elements or all(if " << num << " < " << amount
            << ") :" << endl;
        for (int i = 0; i < amount; i++) {
            arr[i] = temp;
            temp = temp->next[0];
        }
        for (int i = amount - 1; i >= 0 && num > 0; i--, num--) {
            cout << i + 1 << ") " << arr[i]->i << "  " << arr[i]->d << "  " << arr[i]->ch << endl;
        }
        delete[] arr;
    }
    bool delete_element(int key) {
        bool flag = false;
        fields* temp = nullptr, * start = first;
        for (int i = max_height - 1; i >= 0; i--) {
            temp = start->next[i];
            if (temp != last) {
                if (temp->i < key) {
                    start = temp;
                    i++;
                }
                else {
                    if (temp->i == key) {
                        start->next[i] = temp->next[i];
                        flag = true;
                    }
                }
            }
        }
        if (!flag) {
            cout << "Element with this (" << key << ") value is absent in our list." << endl;
        }
        else {
            delete[] temp->next;
            delete temp;
            amount--;
            cout << "Element with this (" << key << ") value was deleted." << endl;
        }
        return flag;
    }
    void delete_all_elements() {
        fields* temp1 = first->next[0], *temp2;
        for (int i = 0; i < amount; i++) {
            temp2 = temp1->next[0];
            delete[] temp1->next;
            delete temp1;
            temp1 = temp2;
        }
        amount = 0;
        for (int i = 0; i < max_height; i++) first->next[i] = last;
        cout << "List is empty." << endl;
    }
    void display_count() {
        cout << "List have " << amount << " elements." << endl;
    }
    void find_element(int key) {
        if (amount > 0) {
            fields* temp, * start = first;
            for (int i = max_height - 1; i >= 0; i--) {
                temp = start->next[i];
                if (temp != last) {
                    if (temp->i < key) {
                        start = temp;
                        i++;
                    }
                    else {
                        if (temp->i == key) {
                            cout << "Element with key " << key << "has next values: " << temp->i << "  "
                                << temp->d << "  " << temp->ch << endl;
                            return;
                        }
                    }
                }
            }
        }
        cout << "Element with this value is absent in our list." << endl;
    }
};
int generate_height(int max) {
    return rand() % max + 1;
}
int main() {
    srand(time(NULL));
    unsigned int start_time = clock();
    ifstream file("inlab03.txt");
    int k1, k2, k3, k4, k5, x;
    file >> x >> k1 >> k2 >> k3 >> k4 >> k5;
    lista l;
    l.find_element(k1);
    l.add_elements(x);
    l.display_count();
    l.display_first(20);
    l.add(k2);
    l.display_first(20);
    l.add(k3);
    l.display_first(20);
    l.add(k4);
    l.display_first(20);
    l.add(k5);
    l.delete_element(k3);
    l.display_first(20);
    l.delete_element(k2);
    l.display_first(20);
    l.delete_element(k5);
    l.display_count();
    l.find_element(k5);
    l.display_last(11);
    l.display_count();
    l.delete_all_elements();
    unsigned int end_time = clock();
    cout << "Time : " << (end_time - start_time) / (double)1000 << " seconds." << endl;
}