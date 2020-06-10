/*
 * Kruskal algorithm, Union_Find Structure
 * Nosov Viktor
 * nv44440@zut.ede.pl
 * */
#include <iostream>
#include <time.h>
#include <ctime>
#include <fstream>
using namespace std;
struct Wezel {
    double x;
    double y;
};
struct Krawedz {
    int a;
    int b;
    double length;
};
struct Graf {
    int liczba_wezlow;
    int liczba_krawedzi;
    Wezel* arr;
    Krawedz* krawedz;
};

class UnionFind {
    int count;
    int* parent;
    int* rank;
public:
    UnionFind(int amount) {
        count = amount;
        parent = new int[amount];
        rank = new int[amount];
        for (int i = 0; i < amount; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }

    int	find(int number) {
        if(parent[number] == number){
            return parent[number];
        }
        else{
            int f = find(parent[number]);
            if(f != parent[number]){
                parent[number] = f;
            }
            return f;
        }
    }

    void union_(int i_root, int j_root) {
        if (rank[i_root] < rank[j_root]) {
            parent[i_root] = parent[j_root];
        }
        else {
            if (rank[i_root] > rank[j_root]) {
                parent[j_root] = parent[i_root];
            }
            else {
                parent[i_root] = parent[j_root];
                rank[j_root]++;
            }
        }
    }
};

template <class T>
void insertion_sort(T* arr, int count) {
    for (int i = 1; i < count; i++) {
        T temp = arr[i];
        int j = i - 1;
        for (; j >= 0 && arr[j].length > temp.length; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}

template <class T>
void bucket_sorting(T* arr, int count, int range) {
    T** temp = new T * [10];
    double block = (double)range / 10, board = block, bottom = 0;
    int *index = new int[10];
    for (int i = 0; i < 10; i++) {
        index[i] = 0;
        temp[i] = new T[count];
        for (int j = 0; j < count; j++) {
            if (arr[j].length < board && arr[j].length >= bottom) {
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

Krawedz** algorytm_Kruskala(Graf* graf) {
    int index = 0, i_root, j_root;
    Krawedz** result = new Krawedz*[graf->liczba_wezlow - 1];

    UnionFind* uf = new UnionFind(graf->liczba_wezlow);

    bucket_sorting(graf->krawedz, graf->liczba_krawedzi, 1);

    for (int i = 0; i < graf->liczba_krawedzi && index < graf->liczba_wezlow - 1; i++) {
        i_root = uf->find(graf->krawedz[i].a);
        j_root = uf->find(graf->krawedz[i].b);
        if (i_root != j_root) {
            result[index] = new Krawedz(graf->krawedz[i]);
            index++;
            uf->union_(i_root, j_root);
        }
    }
    delete uf;
    return result;
}

int main()
{
    ifstream file("g1.txt");
    int num;
    file >> num;
    Graf* graf = new Graf();
    graf->liczba_wezlow = num;
    Wezel* g = new Wezel[num];
    for (int i = 0; i < num; i++) {
        g[i] = Wezel();
        file >> g[i].x >> g[i].y;
    }

    file >> num;
    Krawedz* k = new Krawedz[num];
    for (int i = 0; i < num; i++) {
        k[i] = Krawedz();
        file >> k[i].a >> k[i].b >> k[i].length;
    }
    graf->liczba_krawedzi = num;
    graf->krawedz = k;
    graf->arr = g;

    Krawedz** result = algorytm_Kruskala(graf);
    for (int i = 0; i < graf->liczba_wezlow - 1; i++) {
        cout << result[i]->a + 1 << "  " << result[i]->b + 1 << "  " << result[i]->length << endl;
        delete result[i];
    }
    delete[] result;
    delete[] k;
    delete[] g;
    delete graf;
    return 0;
}
