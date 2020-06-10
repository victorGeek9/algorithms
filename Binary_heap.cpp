/*
   binary heap 
 * Nosov Viktor
 */
#include <iostream>
#include <time.h>
#include <fstream>
#include <cmath>
using namespace std;
class fields {
public:
    int key;
    fields* left = nullptr;
    fields* right = nullptr;
};
template <class T>
class ArrConsequential {
public:
    T** arr;
    int index = 0;
    ArrConsequential(int num) {
        arr = new T * [num];
    }
    ~ArrConsequential() {
        delete[] arr;
    }
};
template <class T>
class sterta {
    T* root = nullptr;
    int amount = 0;
    int height = 0;
    void preorder(T* ptr) {
        if (ptr != nullptr) {
            cout << "Element : key = " << ptr->key << endl;
            preorder(ptr->left);
            preorder(ptr->right);
        }
    }
    T* scan(T* node, T* result, ArrConsequential<T>*& arr) {
        if (node != nullptr && result == nullptr) {
            arr->arr[arr->index] = node;
            arr->index++;
            result = scan(node->left, result, arr);
            result = scan(node->right, result, arr);
            if ((node->right == nullptr || node->left == nullptr) && arr->index == height - 1) {
                result = node;
            }
            arr->index--;
        }
        return result;
    }
    T* find_last_element(T* node, int num, bool left, T* result, int board) {
        if (node != nullptr && result == nullptr) {
            if (left) {
                num *= 2;
            }
            else {
                num *= 2;
                num++;
            }
            if (num == board) result = node;
            result = find_last_element(node->left, num, true, result, board);
            result = find_last_element(node->right, num, false, result, board);
            if (left) {
                num /= 2;
            }
            else {
                num--;
                num /= 2;
            }
        }
        return result;
    }
    void delete_element(T* node) {
        if (node != nullptr) {
            delete_element(node->left);
            delete_element(node->right);
            delete node;
        }
    }
public:
    void add(int key) {
        bool left = true;
        int temp = 1, max_amount = 1;
        if (root == nullptr) {
            root = new T();
            root->key = key;
            amount++;
            height++;
            return;
        }

        if (height != 1) {
            for (int i = height; i > 1; i--) {
                temp = 1;
                for (int j = i; j > 1; j--) {
                    temp *= 2;
                }
                max_amount += temp;
            }
        }

        T* ptr = root;
        ArrConsequential<T>* arr_temp = new ArrConsequential<T>(height + 1);
        if (max_amount == amount) {
            for (int i = height; i > 0; i--) {
                arr_temp->arr[arr_temp->index] = ptr;
                arr_temp->index++;
                ptr = ptr->left;
            }
            arr_temp->arr[arr_temp->index - 1]->left = new T();
            arr_temp->arr[arr_temp->index] = arr_temp->arr[arr_temp->index - 1]->left;
            arr_temp->arr[arr_temp->index]->key = key;
            height++;
        }
        else {
            scan(ptr, nullptr, arr_temp);
            arr_temp->index = height - 2;
            ptr = arr_temp->arr[arr_temp->index];
            if (ptr->left == nullptr) {
                ptr->left = new T();
                ptr->left->key = key;
                arr_temp->index++;
                arr_temp->arr[arr_temp->index] = ptr->left;
            }
            else {
                ptr->right = new T();
                ptr->right->key = key;
                arr_temp->index++;
                arr_temp->arr[arr_temp->index] = ptr->right;
                left = false;
            }
        }
        temp = arr_temp->index;
        for (int i = arr_temp->index - 1; i >= 0; i--) {
            if (arr_temp->arr[i]->key < arr_temp->arr[temp]->key) {
                if (left) {
                    ptr = arr_temp->arr[i]->right;
                    arr_temp->arr[i]->left = arr_temp->arr[temp]->left;
                    arr_temp->arr[i]->right = arr_temp->arr[temp]->right;
                    arr_temp->arr[temp]->right = ptr;
                    arr_temp->arr[temp]->left = arr_temp->arr[i];
                }
                else {
                    ptr = arr_temp->arr[i]->left;
                    arr_temp->arr[i]->left = arr_temp->arr[temp]->left;
                    arr_temp->arr[i]->right = arr_temp->arr[temp]->right;
                    arr_temp->arr[temp]->right = arr_temp->arr[i];
                    arr_temp->arr[temp]->left = ptr;
                }

                if (i - 1 >= 0) {
                    if (arr_temp->arr[i - 1]->left == arr_temp->arr[i]) {
                        arr_temp->arr[i - 1]->left = arr_temp->arr[temp];
                        left = true;
                    }
                    else {
                        arr_temp->arr[i - 1]->right = arr_temp->arr[temp];
                        left = false;
                    }

                }
                else {
                    if (i == 0) root = arr_temp->arr[temp];
                }
            }
        }
        amount++;
        delete arr_temp;
    }
    void delete_root() {
        if (root == nullptr) return;

        if (amount == 1) {//just root
            delete root;
            root = nullptr;
            amount--;
            height--;
            return;
        }
        //faza 1
        bool left = true;
        T* last = find_last_element(root, 0, false, nullptr, amount),
            * temp = find_last_element(root, 0, false, nullptr, amount / 2), * temp1;

        if (temp->left == last) {
            temp->left = nullptr;
        }
        else {
            temp->right = nullptr;
        }
        last->left = root->left;
        last->right = root->right;


        delete root;
        root = last;

        amount--;
        int var, max_amount = 1;
        for (int i = height - 1; i > 1; i--) {
            var = 1;
            for (int j = i; j > 1; j--) {
                var *= 2;
            }
            max_amount += var;
        }
        if (max_amount >= amount) height--;
        //faza 2
        for (int i = 1; i <= amount; i *= 2) {
            temp = nullptr;
            if (i != 0 && !left) i++;
            if (last->left != nullptr && last->right != nullptr) {
                if (last->left->key > last->key&& last->right->key > last->key) {
                    if (last->left->key > last->right->key) {
                        temp = last->left;
                        left = true;
                    }
                    else {
                        temp = last->right;
                        left = false;
                    }
                }
                else {
                    if (last->left->key < last->key && last->right->key < last->key) {
                        break;
                    }
                    else {
                        if (last->left->key > last->key) {
                            temp = last->left;
                            left = true;
                        }
                        else {
                            temp = last->right;
                            left = false;
                        }
                    }
                }
            }
            else {
                if (last->left != nullptr) {
                    if (last->left->key > last->key) {
                        temp = last->left;
                        left = true;
                    }
                    else {
                        break;
                    }
                }
                else {
                    if (last->right != nullptr) {
                        if (last->right->key > last->key) {
                            temp = last->right;
                            left = false;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
            }

            if (left) {
                temp1 = last->right;
                last->right = temp->right;
                last->left = temp->left;
                temp->right = temp1;
                temp->left = last;
            }
            else {
                temp1 = last->left;
                last->left = temp->left;
                last->right = temp->right;
                temp->left = temp1;
                temp->right = last;
            }
            if (i == 1) {
                root = temp;
            }
            else {
                temp1 = find_last_element(root, 0, false, nullptr, i / 2);
                if (temp1->left == last) {
                    temp1->left = temp;
                }
                else {
                    temp1->right = temp;
                }
            }
        }
    }
    void delete_all() {
        delete_element(root);
        root = nullptr;
        amount = 0;
        height = 0;
    }
    sterta(int key) {
        add(key);
    }
    sterta() {}
    ~sterta() {
        delete_all();
    }
    void display_preorder() {
        preorder(root);
        if (root == nullptr) cout << "Sterta jest pusta!" << endl;
    }
    int get_amount() {
        return amount;
    }
    int get_height() {
        return height;
    }
};
int main()
{
    srand(time(NULL));
    sterta <fields>* bh = new  sterta <fields>();
    const  int  MAX_ORDER = 5;
    for (int o = 1; o <= MAX_ORDER; o++) {
        const  int n = pow(10, o);
        clock_t  t1 = clock();
        for (int i = 0; i < n; i++) {
            bh->add(rand());
        }
        clock_t  t2 = clock();
        cout << "Height: " << bh->get_height() << endl;
        cout << "Amount: " << bh->get_amount() << endl;
        cout << "Time : " << (t2 - t1) / (double)1000 << " seconds." << endl;
        t1 = clock();
        for (int i = 0; i < n; i++) {
            bh->delete_root();
        }
        t2 = clock();
        cout << "Height: " << bh->get_height() << endl;
        cout << "Amount: " << bh->get_amount() << endl;
        cout << "Time : " << (t2 - t1) / (double)1000 << " seconds." << endl;
        bh->delete_all();
        cout << endl << endl;
    }
    delete bh;
}
