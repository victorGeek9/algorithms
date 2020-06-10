/*
  Binary Search Tree
  Nosov Viktor
*/
#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;
class fields {
public:
    int key;
    fields* left = nullptr;
    fields* right = nullptr;
    char* arr = new char[10];
};
class drzewo {
    fields* root;
    void postorder(fields* ptr) {
        if (ptr != nullptr) {
            postorder(ptr->left);
            postorder(ptr->right);
            cout << "Element : key = " << ptr->key << endl;
        }
    }
    void inorder(fields* ptr) {
        if (ptr != nullptr) {
            inorder(ptr->left);
            cout << "Element : key = " << ptr->key << endl;
            inorder(ptr->right);
        }
    }
    void preorder(fields* ptr) {
        if (ptr != nullptr) {
            cout << "Element : key = " << ptr->key << endl;
            preorder(ptr->left);
            preorder(ptr->right);
        }
    }
public:
    void generateCharArr(fields* ptr) {
        int amount = 0;
        for (int i = ptr->key; i > 0; amount++, i /= 10);
        for (int i = 9; i >= amount; i--) ptr->arr[i] = '-';
        for (int i = amount - 1, j = ptr->key; i >= 0; i--, j /= 10) {
            ptr->arr[i] = j % 10 + '0';
        }
    }
    drzewo(){
        root = nullptr;
    }
    drzewo(fields* root) {
        this->root = root;
        root->left = nullptr;
        root->right = nullptr;
        generateCharArr(root);
    }
    fields* find(int key) {
        fields* ptr = root;
        while (ptr != nullptr) {
            if (ptr->key == key) {
                return ptr;
            }
            else {
                if (ptr->key < key) {
                    ptr = ptr->right;
                }
                else {
                    ptr = ptr->left;
                }
            }
        }
        return nullptr;
    }
    bool add(int key) {
        if (root == nullptr) {
            root = new fields();
            root->key = key;
        }
        else {
            fields* ptr = root;
            fields* father = root;
            bool left = false;
            while (ptr != nullptr) {
                if (ptr->key == key) {
                    return false;
                }
                else {
                    if (ptr->key < key) {
                        father = ptr;
                        ptr = ptr->right;
                        left = false;
                    }
                    else {
                        father = ptr;
                        ptr = ptr->left;
                        left = true;
                    }
                }
            }
            if (left) {
                father->left = new fields();
                father->left->key = key;
                generateCharArr(father->left);
            }
            else {
                father->right = new fields();
                father->right->key = key;
                generateCharArr(father->right);
            }
        }
        return true;
    }
    void addElemants(int count) {
        int key;
        for (int i = 1; i <= count; i++) {
            key = rand() % 20001;
            key -= 10000;
            if (!add(key)) {
                i--;
            }
        }
    }
    void display_preorder() {
        preorder(root);
    }
    void disolay_inorder() {
        inorder(root);
    }
    void display_postorder() {
        postorder(root);
    }
    bool deleteELement(int key) {
        fields* ptr = root, * father = nullptr, *next = nullptr;
        bool flag = true, left = true;
        while (flag && ptr != nullptr) {
            if (ptr->key == key) {
                flag = false;
            }
            else {
                if (ptr->key < key) {
                    father = ptr;
                    ptr = ptr->right;
                    left = false;
                }
                else {
                    father = ptr;
                    ptr = ptr->left;
                    left = true;
                }
            }
        }
        if (ptr == nullptr) {
            return false;
        }
        else {
            if (ptr->left == nullptr && ptr->right == nullptr) {
                delete[] ptr->arr;
                delete ptr;
            }
            else {
                if (ptr->left != nullptr && ptr->right != nullptr) {
                    fields *temp_priv = ptr;
                    bool left = true;
                    next = ptr->left;
                    int count = 0;
                    do {
                        if (next->left != nullptr && next->right != nullptr) {
                            count = 2;
                        }
                        else {
                            if (next->left == nullptr && next->right == nullptr) {
                                count = 0;
                            }
                            else {
                                count = 1;
                            }
                        }
                        if (count == 2) {
                            temp_priv = next;
                            next = next->right;
                            left = false;
                        }
                    } while (count == 2);
                    if (left) {
                        if (next->left == nullptr) {
                            temp_priv->left = next->right;
                        }
                        else {
                            temp_priv->left = next->left;
                        }
                    }
                    else {
                        if (next->left == nullptr) {
                            temp_priv->right = next->right;
                        }
                        else {
                            temp_priv->right = next->left;
                        }
                    }
                    next->right = ptr->right;
                    next->left = ptr->left;
                    delete[] ptr->arr;
                    delete ptr;
                }
                else {
                    if (ptr->left != nullptr) {
                        next = ptr->left;
                    }
                    else {
                        next = ptr->right;
                    }
                    delete[] ptr->arr;
                    delete ptr;
                }
            }
            if (father != nullptr) {
                if (!left) {
                    father->right = next;
                }
                else {
                    father->left = next;
                }
            }
            else {
                root = next;
                if (root == nullptr) {
                    cout << "Ostriznie! Root = null!" << endl;
                }
            }
        }
        return true;
    }
};
int main()
{
    srand(time(NULL));
    unsigned int start_time = clock();
    ifstream file("inlab04.txt");
    int x, k1, k2, k3, k4;
	//file: 101 6000 2 20001 -6
    file >> x >> k1 >> k2 >> k3 >> k4;
    drzewo* d = new drzewo;
    unsigned int end_time = clock();
    d->deleteELement(k1);
    d->add(k1);
    d->addElemants(x);
    d->disolay_inorder();
    d->display_preorder();
    d->add(k2);
    d->disolay_inorder();
    d->add(k3);
    d->add(k4);
    d->deleteELement(k1);
    d->display_preorder();
    d->find(k1);
    d->deleteELement(k2);
    d->disolay_inorder();
    d->deleteELement(k3);
    d->deleteELement(k4);
    cout << "Time : " << (end_time - start_time) / (double)1000 << " seconds." << endl;
}