/*
 * Sorting algorithms: heapsort, counting sort, bucket sort
 * Nosov Viktor
 * */
#include <iostream>
#include<ctime>
#include<fstream>
#include<cmath>
#include <string.h>
using namespace std;
class Person {
public:
    string name;
    double key;
    Person(int num = 0, string name = "-") {
        this->name = name;
        this->key = num;
    }
};
template <class T>
class Heap {
    void excavation_bottom_up(T** arr, int index) {
        int i = (index / 2);
        for (; i > 0 && arr[i - 1]->key < arr[index - 1]->key; i /= 2) {
            swap(arr, i - 1, index - 1);
            index = i;
        }
        if (i == 0 && arr[i]->key < arr[index - 1]->key) {
            swap(arr, i, index - 1);
        }
    }
    void excavation_up_down(T** arr) {
        int i = 1, j = 2;
        for (; j < amount && (arr[j] != nullptr || arr[j - 1] != nullptr); j *= 2) {
            if (arr[j] != nullptr && arr[j - 1] != nullptr) {
                if (arr[i - 1]->key < arr[j - 1]->key && arr[i - 1]->key < arr[j]->key) {
                    if (arr[j - 1]->key < arr[j]->key) {
                        swap(arr, i - 1, j);
                        i = j + 1;
                        j++;
                    }
                    else {
                        swap(arr, i - 1, j - 1);
                        i = j;
                    }
                }
                else {
                    if (arr[i - 1]->key < arr[j - 1]->key) {
                        swap(arr, i - 1, j - 1);
                        i = j;
                    }
                    else {
                        if (arr[i - 1]->key < arr[j]->key) {
                            swap(arr, i - 1, j);
                            i = j + 1;
                            j++;
                        }
                        else {
                            break;
                        }
                    }
                }
            }
            else {
                if (arr[j] != nullptr && arr[j]->key > arr[i - 1]->key) {
                    swap(arr, i - 1, j);
                    i = j + 1;
                    j++;
                }
                else {
                    if (arr[j - 1] != nullptr && arr[j - 1]->key > arr[i - 1]->key) {
                        swap(arr, i - 1, j - 1);
                        i = j;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        if (j - 1 < amount && arr[j - 1] != nullptr  && arr[j - 1]->key > arr[i - 1]->key) {
            swap(arr, i - 1, j - 1);
        }
    }
    void swap(T** arr, int i, int index) {
        int temp = arr[i]->key;
        arr[i]->key = arr[index]->key;
        arr[index]->key = temp;
    }
    void initialization(T** arr, int size) {
        for (int i = 0; i < size; i++) {
            arr[i] = nullptr;
        }
    }
public:
    int amount = 0;
    int size;
    T** arr;

    Heap(int count) {
        size = count;
        arr = new T*[count];
        initialization(arr, size);
    }

    Heap(T** ptr, int count, bool type) { // pamiec musi byc alokowana przez new
        // 0 = bottom - up
        // 1 = top - down
        arr = new T * [count];
        size = count;
        initialization(arr, size);
        sort(ptr, count, type);
    }

    ~Heap() {
        delete[] arr;
    }

    void sort(T** ptr, int size, bool type) {
        for (int i = 0; i < size; i++) {
            add(ptr[i]->key);
        }
        clear(ptr, size);
        if (type == true) {
            for (int i = size - 1; i >= 0; i--) {
                ptr[i] = new T(*(arr[0]));
                remove();
            }
            clear(arr, amount);
            for (int i = size - 1; i >= 0; i--) {
                add(ptr[i]->key);
            }
        }
        else {
            int index = 1;
            ptr[0] = new T(*(arr[amount - 1]));
            for (int i = amount - 2; i >= 0; i--, index++) {
                int j = index - 1, key = arr[i]->key;
                ptr[index] = new T(*(arr[i]));
                T* temp = ptr[index];
                for (; j >= 0 && ptr[j]->key > key; j--) {
                    ptr[j + 1] = ptr[j];
                }
                ptr[j + 1] = temp;
            }
        }

    }

    bool add(int key) {
        if (amount == size) return false;
        arr[amount] = new T();
        arr[amount]->key = key;
        amount++;
        if (amount != 1) {
            excavation_bottom_up(arr, amount);
        }
        return true;
    }

    bool remove() {
        if (amount == 0) return false;
        delete arr[0];
        arr[0] = arr[amount - 1];
        arr[amount - 1] = nullptr;
        amount--;
        excavation_up_down(arr);
        return true;
    }

    void clear(T** arr, int amount) {
        for (int i = 0; i < amount; i++) {
            delete arr[i];
        }
        initialization(arr, amount);
        if (this->arr == arr) this->amount = 0;
    }
    void display(T** arr, int amount) {
        for (int i = 0; i < amount; i++) {
            cout << i + 1 << ") " << arr[i]->key << endl;
        }
    }
};

template <class T>
void display_arr(T* arr, int amount) {
    for (int i = 0; i < amount; i++) {
        cout << i + 1 << ") " << arr[i] << endl;
    }
}
template <class T>
void display_arr(T** arr, int amount) {
    for (int i = 0; i < amount; i++) {
        cout << i + 1 << ") " << arr[i]->key << endl;
    }
}
void insertion_sort(int* arr, int count) {
    for (int i = 1; i < count; i++) {
        int temp = arr[i], j = i - 1;
        for (; j >= 0 && arr[j] > temp; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}
template <class T>
void insertion_sort(T* arr, int count) {
    for (int i = 1; i < count; i++) {
        double temp = arr[i].key;
        int j = i - 1;
        for (; j >= 0 && arr[j].key > temp; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}
bool equal(double a, double b) {
    if (a >= b) {
        return true;
    }
    return false;
}
template <class T>
double get_key(T* a) {
    return a->key;
}

template <class T>
void bucket_sorting(T* arr, int count, int range) {
    T** temp = new T * [10];
    int block = range / 10, board = block, bottom = 0, * index = new int[10];
    for (int i = 0; i < 10; i++) {
        index[i] = 0;
        temp[i] = new T[count];
        for (int j = 0; j < count; j++) {
            if (arr[j].key < board && arr[j].key >= bottom) {
                temp[i][index[i]] = arr[j];
                index[i]++;
            }
        }
        bottom = board;
        board += block;
    }

    board = 0;
    for (int i = 0; i < 10; i++) {
        insertion_sort(temp[i], index[i]);
        board += index[i];
        for (int j = board - index[i], k = 0; j < board; j++, k++) {
            arr[j] = temp[i][k];
        }
    }
    for (int i = 0; i < 10; i++) {
        delete[] temp[i];
    }
    delete[] index;
    delete[] temp;
}
void bucket_sorting(int* arr, int count, int range) {
    int** temp = new int*[10], block = range / 10, board = block, *index = new int[10];
    for (int i = 0; i < 10; i++) {
        index[i] = 0;
        temp[i] = new int[count];
        for (int j = 0; j < count; j++) {
            if (arr[j] < board) {
                temp[i][index[i]] = arr[j];
                arr[j] = range;
                index[i]++;
            }
        }
        board += block;
    }
    board = 0;
    for (int i = 0; i < 10; i++) {
        insertion_sort(temp[i], index[i]);
        board += index[i];
        for (int j = board - index[i], k = 0; j < board; j++, k++) {
            arr[j] = temp[i][k];
        }
    }
    for (int i = 0; i < 10; i++) {
        delete[] temp[i];
    }
    delete[] index;
    delete[] temp;
}
void sorting_by_counting(int* arr, int count, int range) {
    int* temp = new int[range], *result = new int[count];
    for (int j = 0; j < range; j++) {
        temp[j] = 0;
        for (int i = 0; i < count; i++) {
            if (arr[i] == j) {
                temp[j]++;
            }
        }
    }
    for (int i = 1; i < range; i++) {
        temp[i] += temp[i - 1];
    }
    for (int i = 0; i < count; i++) {
        result[temp[arr[i]] - 1] = arr[i];
        temp[arr[i]]--;
    }
    for (int i = 0; i < count; i++) {
        arr[i] = result[i];
    }
    delete[] result;
    delete[] temp;
}


int main()
{

    srand(0);
    const int MAX_ORDER = 5; // maksymalny rzad wielkosci sortowanych danych
    const int m = (int)pow(10,5); // sortowane liczby ze zbioru {0 , ... , m - 1}
    cout << m << endl;
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        cout << o << endl;
        const int n = (int)pow(10, o); // rozmiar tablicy z danymi
        int* array1 = new int[n];
        for (int i = 0; i < n; i++)
        {
            int rand_val = rand() % m;
            array1[i] = rand_val;
        }
        display_arr(array1, 10);
        cout << endl << endl;

        Person** array2 = new Person*[n];
        int* array3 = new int[n];
        for (int i = 0; i < n; i++) {// pierwsza kopia
            array2[i] = new Person(array1[i]);
        }
        memcpy(array3, array1, n * sizeof(int)); // druga kopia

        clock_t t1 = clock();
        sorting_by_counting(array1, n, m);
        clock_t t2 = clock();
        display_arr(array1, 10);
        cout << "Time : " << (t2 - t1) / (double)1000 << " seconds." << endl;

        t1 = clock();
        Heap<Person>* bh = new Heap<Person>(array2, n, false);
        display_arr(array2, 10);
        t2 = clock();
        cout << "Time : " << (t2 - t1) / (double)1000 << " seconds." << endl;

        t1 = clock();
        bucket_sorting(array3, n, m); // szczegolna wersja bucket sort tylko dla liczb calkowitych
        display_arr(array3, 10);
        t2 = clock();
        cout << "Time : " << (t2 - t1) / (double)1000 << " seconds." << endl;

        for (int i = 0; i < n; i++) {// pierwsza kopia
            delete array2[i];
        }
        for(int i = 0; i < 5; i++) cout << endl;
        delete[] array1;
        delete[] array2;
        delete[] array3;
    }
    return 0;
}

