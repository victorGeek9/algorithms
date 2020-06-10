/*
 * hash table
 * Nosov Viktor
 */
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
enum type { adresowanie = 0, mieszanie = 1};
class HashingTable {
	int* arr;
	int count;
	bool is_full;
	type mode;
	bool add_element_adresowanie(int key) {
		if (is_full) return false;
		if (find_element(key) != -1) return false;
		int index = find_index_first(key);
		while (index < count && arr[index] != -1) index++;
		if (index > count) return false;
		if (arr[index] == -1) {
			arr[index] = key;
			return true;
		}
		return false;
	}
	bool add_element_mieszanie(int key) {
		if (is_full) return false;
		if (find_element(key) != -1) return false;
		int index = find_index_first(key), iter = find_index_second(key),
			temp = index;
		for (int i = 1; index < count && arr[index] != -1; i++) {
			index = temp;
			index += (i * iter);
		}
		if (index > count) return false;
		if (arr[index] == -1) {
			arr[index] = key;
			return true;
		}
		return false;
	}
	int find_index_first(int key) {
		int index = (key % 1000) + 1, pow = 1;
		for (int i = key % 10; i > 0; i--) {
			pow *= 2;
		}
		index += pow;
		return index;
	}
	int find_index_second(int key) {
		int index = (3 * key) % 19 + 1;
		return index;
	}
	void check_table() {
		int i;
		for (i = 0; i < count && arr[i] != -1; i++);
		if (i == count) is_full = true;
	}
	void initialization(int amount) {
		for (int i = 0; i < amount; i++) {
			arr[i] = -1;
		}
	}
public:
	HashingTable(int amount, type m = adresowanie) {
		mode = m;
		is_full = false;
		count = amount;
		arr = new int[amount];
		initialization(amount);
	}
	HashingTable(type mode = adresowanie): HashingTable(997, mode){}
	~HashingTable() {
		delete[] arr;
	}
	
	bool add_element(int key) {
		if (mode == adresowanie) {
			return add_element_adresowanie(key);
		}
		else {
			return add_element_mieszanie(key);
		}
	}
	bool remove_element(int key) {
		int index = find_element(key);
		if (index != -1) {
			arr[index] = -1;
			return true;
		}
		else {
			return false;
		}
	}
	bool add_all_elements(int amount) {
		int counter = 0, key;
		bool temp;
		for (; counter < amount; counter++) {
			key = (rand() % 20000) + 20000;
			temp = add_element(key);
			if (!temp) {
				counter--;
				check_table();
				if (is_full) break;
			}
		}
		if (counter == amount) return true;
		return false;
	}
	int find_element(int key) {
		// zwraca index elementu lub -1(jak tablica nie zawira takigo elementu)
		int index = find_index_first(key);
		if (mode == adresowanie) {
			for (; index < count && arr[index] != key; index++);
		}
		else {
			int iter = find_index_second(key), temp = index;
			for (int i = 0; index < count && arr[index] != key; i++) {
				index = temp + i * iter;
			}
		}
		if (index >= count) {
			return -1;
		}
		else {
			return index;
		}
	}
	void display_from_to(int start, int end) {
		for (int i = start; i <= end && i < count; i++) {
			if(arr[i] !=-1)
				cout << i << ") " << arr[i] << endl;
		}
	}
};
int main()
{
	srand(time(NULL));
	unsigned int start_time = clock();
	ifstream file("inlab07.txt");
	int x, k1, k2, k3, k4;
	//file: 500 25013 29511 37013 32511
	file >> x >> k1 >> k2 >> k3 >> k4;
	type tryb = adresowanie;
	HashingTable* ht = new HashingTable(tryb);
	cout << ht->remove_element(k1) << endl;
	cout << ht->add_element(k1) << endl;
	ht->display_from_to(0, 100);
	ht->add_all_elements(x);
	ht->display_from_to(0, 100);
	cout << ht->add_element(k2) << endl;
	cout << ht->add_element(k3) << endl;
	cout << ht->add_element(k4) << endl;
	ht->display_from_to(0, 100);
	ht->display_from_to(500, 600);
	ht->remove_element(k3);
	ht->remove_element(k4);
	ht->display_from_to(0, 100);
	ht->display_from_to(500, 600);
	delete ht;
	unsigned int end_time = clock();
	cout << "Time : " << (end_time - start_time) / (double)1000 << " seconds." << endl;
	start_time = clock();
	tryb = mieszanie;
	ht = new HashingTable(tryb);
	cout << ht->remove_element(k1) << endl;
	cout << ht->add_element(k1) << endl;
	ht->display_from_to(0, 100);
	ht->add_all_elements(x);
	ht->display_from_to(0, 100);
	cout << ht->add_element(k2) << endl;
	cout << ht->add_element(k3) << endl;
	cout << ht->add_element(k4) << endl;
	ht->display_from_to(0, 100);
	ht->display_from_to(500, 600);
	ht->remove_element(k3);
	ht->remove_element(k4);
	ht->display_from_to(0, 100);
	ht->display_from_to(500, 600);
	delete ht;
	end_time = clock();
	cout << "Time : " << (end_time - start_time) / (double)1000 << " seconds." << endl;
	return 0;
}
