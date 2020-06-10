/*
 One-way list(non-cyclic)
 Nosov Viktor
 44440
*/
#include<iostream>
#include <fstream>
#include <time.h>
using namespace std;
struct fields {
    int i;
    double d;
    char ch;
    fields* next;
};
class lista {
    int amount = 0;
    fields* first;
public:
    bool add(int key) {
        fields* el = new fields;
        el->i = key;
        int i;
        fields* temp1 = first, *temp2 = NULL;
        if (amount == 0) {
            first = el;
            el->next = NULL;
        }
        else {
            for (i = 0; i < amount && temp1->i <= el->i; i++) {
                if (temp1->i == el->i) {
                    delete el;
                    return false;
                }
                temp2 = temp1;
                temp1 = temp1->next;
            }
            if (temp2 == NULL) {
                el->next = first;
                first = el;
            }
            else {
                temp2->next = el;
                el->next = temp1;
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
        fields* temp = first;
        cout << "Display first " << num << " elements or all(if " << num << " < " << amount
            <<") :" << endl;
        for (int i = 0; i < amount && num > 0; i++, num--) {
            cout << i + 1 << ") " << temp->i << "  " << temp->d << "  " << temp->ch << endl;
            temp = temp->next;
        }
    }
    void display_last(int num) {
        if (amount == 0) {
            cout << "List is empty." << endl;
            return;
        }
        fields** arr = new fields*[amount], * temp = first;
        cout << "Display last " << num << " elements or all(if " << num << " < " << amount
            << ") :" << endl;
        for (int i = 0; i < amount; i++) {
            arr[i] = temp;
            temp = temp->next;
        }
        for (int i = amount - 1; i >= 0 && num > 0; i--, num--) {
            cout << i + 1 << ") " << arr[i]->i << "  " << arr[i]->d << "  " << arr[i]->ch << endl;
        }
        delete[] arr;
    }
    bool delete_element(int key) {
        fields* temp1 = first, *temp2;
        if (first->i == key) {
            first = first->next;
            delete temp1;
            amount--;
            return true;
        }
        temp2 = temp1;
        temp1 = temp1->next;
        if (temp1 != NULL) {
            for (int i = 0; i < amount && temp1->i <= key; i++) {
                    if (temp1->i == key) {
                        temp2->next = temp1->next;
                        delete temp1;
                        amount--;
                        return true;
                    }
                    temp2 = temp1;
                    temp1 = temp1->next;
                }
        }
        cout << "Element with this value is absent in our list." << endl;
        return false;
    }
    void delete_all_elements() {
        fields* temp1 = first, *temp2;
        for (int i = 0; i < amount; i++) {
            temp2 = temp1->next;
            delete temp1;
            temp1 = temp2;
        }
        amount = 0;
        first = NULL;
        cout << "List is empty." << endl;
    }
    void display_count() {
        cout << "List have " << amount << " elements." << endl;
    }
    void find_element(int key) {
        fields* temp = first;
        for (int i = 0; i < amount && temp->i <= key; i++) {
            if (temp->i == key) {
                cout << "Element with key " << key << "has next values: " << temp->i << "  "
                    << temp->d << "  " << temp->ch << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Element with this value is absent in our list." << endl;
    }
};
int main() {
    srand(time(NULL));
    unsigned int start_time = clock();
    ifstream file("inlab02.txt");
    int k1, k2, k3, k4, k5, x;
	// file: 2001 13666 4 7 -1 100001
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