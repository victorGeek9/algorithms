/*
  tree rotation DSW
  Nosov Viktor
*/
#include <iostream>
#include <time.h>
#include <fstream>
#pragma comment(linker, "/STACK:200000000")
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
    int scan(fields* node, int height) {
        int max = 0, temp = 0;
        if (node != nullptr) {
            height++;
            temp = scan(node->left, height);
            if (max < temp) max = temp;
            temp = scan(node->right, height);
            if (max < temp) max = temp;
        }
        else {
            max = height;
        }
        return max;
    }
    void delete_current_element(fields* node) {
        if (node != nullptr) {
            delete_current_element(node->left);
            delete_current_element(node->right);
            delete[] node->arr;
            delete node;
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
    drzewo() {
        root = nullptr;
    }
    drzewo(fields* root) {
        this->root = root;
        root->left = nullptr;
        root->right = nullptr;
        generateCharArr(root);
    }
    void delete_all_elements() {
        delete_current_element(root);
        root = nullptr;
    }
    ~drzewo() {
        delete_all_elements();
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
    void display_inorder() {
        inorder(root);
    }
    void display_postorder() {
        postorder(root);
    }
    bool deleteELement(int key) {
        fields* ptr = root, * father = nullptr, * next = nullptr;
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
                    fields* temp_priv = ptr;
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
    bool rotate_right(fields* grandfather, fields* parent, fields* child) {
        if (child == root || child == nullptr) return false;
        if (grandfather != nullptr) {
            if (grandfather->right == parent) {
                grandfather->right = child;
            }
            else {
                grandfather->left = child;
            }
        }
        else {
            root = child;
        }
        parent->left = child->right;
        child->right = parent;
        return true;
    }
    bool rotate_right_by_key(int key) {
        fields* grandfather = nullptr, * parent = nullptr, * child = root;
        while (child->key != key && child != nullptr) {
            grandfather = parent;
            parent = child;
            if (child->key < key) {
                child = child->right;
            }
            else {
                child = child->left;
            }
        }
        return rotate_right(grandfather, parent, child);
    }
    bool rotate_left(fields* grandfather, fields* parent, fields* child) {
        if (child == root || child == nullptr) return false;
        if (grandfather != nullptr) {
            if (grandfather->right == parent) {
                grandfather->right = child;
            }
            else {
                grandfather->left = child;
            }
        }
        else {
            root = child;
        }
        parent->right = child->left;
        child->left = parent;
        return true;
    }
    bool rotate_left_by_key(int key) {
        fields* grandfather = nullptr, * parent = nullptr, * child = root;
        while (child->key != key && child != nullptr) {
            grandfather = parent;
            parent = child;
            if (child->key < key) {
                child = child->right;
            }
            else {
                child = child->left;
            }
        }
        return rotate_left(grandfather, parent, child);
    }
    void make_perfect_tree() {
        fields* grandfather = nullptr, * parent = root, * temp;
        //faza 1
        while (parent != nullptr) {
            temp = parent->left;
            if (parent->left != nullptr) {
                rotate_right(grandfather, parent, parent->left);
                parent = temp;
            }
            else {
                grandfather = parent;
                parent = parent->right;
            }
        }
        //faza 2
        int n, m = 1;
        n = find_height();
        for (int i = n + 1; i >= 2; i /= 2) m *= 2;
        m--;
        grandfather = nullptr;
        parent = root;
        for (int i = 0; i < (n - m); i++) {
            temp = parent->right;
            rotate_left(grandfather, parent, parent->right);
            grandfather = temp;
            parent = grandfather->right;
        }
        while (m != 0) {
            m /= 2;
            grandfather = nullptr;
            parent = root;
            for (int i = 0; i < m; i++) {
                temp = parent->right;
                rotate_left(grandfather, parent, parent->right);
                grandfather = temp;
                parent = grandfather->right;
            }
        }
    }
    int find_height() {
        fields* ptr = root;
        int height = 0;
        height = scan(root, height);
        return height;
    }
};
int main()
{
    srand(time(NULL));
    unsigned int start_time = clock();
    drzewo* d = new drzewo;
    int x1 = 127, x2 = 10000;
    d->addElemants(x1);
    cout << "height do DSW: " << d->find_height() << endl;
    d->make_perfect_tree();
    cout << "height po DSW: " << d->find_height() << endl;
    d->delete_all_elements();
    d->addElemants(x2);
    cout << "height do DSW: " << d->find_height() << endl;
    d->make_perfect_tree();
    cout << "height po DSW: " << d->find_height() << endl;
    unsigned int end_time = clock();
    cout << "Time : " << (end_time - start_time) / (double)1000 << " seconds." << endl;
    delete  d;
}