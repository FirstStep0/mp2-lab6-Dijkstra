#include <iostream>
#include <string>
#include "heap.h"
#include "binomial_heap.h"
#define i(x,y) (x)*n+(y)
using namespace std;
typedef unsigned int uint;
const int Exit = 10;
const int max_size = 1000;
int arr[max_size][max_size];
int was[max_size];
int last[max_size];
int n;
bool connected = false;

void clear_graph() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = -1;
		}
	}
}

void clear_was() {
	for (int i = 0; i < n; i++) {
		was[i] = INT_MAX;
	}
	for (int i = 0; i < n; i++) {
		last[i] = -1;
	}
}

void show_graph() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
}

void show_was() {
	for (int i = 0; i < n; i++) {
		cout << was[i] << " ";
	}
}

void shuffle(int* arr, int size) {
	for (int i = 0; i < n; i++) {
		swap(arr[i], arr[rand() % n]);
	}
}

void noise() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)continue;
			if (rand() % 3 == 0) {
				arr[i][j] = arr[j][i] = (rand() % 50) + 1;
			}
		}
	}
};

void run_with_heap(int x) {
	heap<pair<int, int>> h;
	clear_was();
	was[x] = 0;
	h.push({ 0,x });
	while (!h.empty()) {
		pair<int,int> p = h.front();
		int i = p.second;
		h.pop();
		for (int j = 0; j < n; j++) {
			int val = arr[i][j];
			if (val != -1) {
				int path = was[i] + val;
				if (path < was[j]) {
					was[j] = path;
					last[j] = i;
					h.push({ val,j });
				}
			}
		}
	}
}

void run_with_bheap(int x) {
	binomial_heap<pair<int, int>> h;
	clear_was();
	was[x] = 0;
	h.push({ 0,x });
	while (!h.empty()) {
		pair<int, int> p = h.front();
		int i = p.second;
		h.pop();
		for (int j = 0; j < n; j++) {
			int val = arr[i][j];
			if (val != -1) {
				int path = was[i] + val;
				if (path < was[j]) {
					was[j] = path;
					last[j] = i;
					h.push({ val,j });
				}
			}
		}
	}
}



void run_with_array(int x) {
	vector<pair<int,int>> v;
	clear_was();
	was[x] = 0;
	v.push_back({ 0,x });
	while (!v.empty()) {
		pair<int,int> p = v[0];
		int index = 0;
		for (int k = 1; k < v.size(); k++) {
			if (p.first < v[k].first) {
				p = v[k];
				index = k;
			}
		}
		swap(v[index], v.back());
		v.pop_back();

		int i = p.second;
		for (int j = 0; j < n; j++) {
			int val = arr[i][j];
			if (val != -1) {
				int path = was[i] + val;
				if (path < was[j]) {
					was[j] = path;
					last[j] = i;
					v.push_back({ val,j });
				}
			}
		}
	}
}

bool connected_graph() {
	clear_was();
	run_with_heap(0);
	for (int i = 0; i < n; i++) {
		if (was[i] == INT_MAX) {
			connected = false;
			return false;
		}
	}
	connected = true;
	return true;
}

void random_graph() {
	clear_graph();
	int* index = new int[n];
	for (int i = 0; i < n; i++) { index[i] = i; }
	shuffle(index, n);
	for (int i = 1; i < n; i++) {
		arr[index[i - 1]][index[i]] = arr[index[i]][index[i - 1]] = (rand() % 50) + 1;
	}
	delete index;
	noise();
	connected_graph();
};

void enter_graph() {
	cout << "Enter list of edge in format (i,j), value. Example 1,2,5 enter edge (1,2) with weight = 5.\n";
	cout << "If edge (i,j) not exist enter weight = -1.\n";
	cout << "For exit enter -1\n";
	int i = 0, j, val;
	while (i != -1) {
		cin >> i;
		if (i == -1)break;
		cin >> j >> val;
		if (i >= 0 && i < n && j >= 0 && j < n && (val == -1 || val >= 0)) {
			arr[i][j] = arr[j][i] = val;
		}
	}
	connected_graph();
}

void Initialize() {
	srand(time(0));
	cout.precision(10);
	n = 5;
}

void change_size() {
	cout << "max size is " << max_size << "\n";
	cout << "enter size:\n";
	cout << ">";
	int new_size;
	cin >> new_size;
	cin.clear();
	cin.ignore(10000, '\n');
	if (new_size <= 0 || new_size > max_size)throw string("error: (size <= 0) or (size > max size)");
	else {
		n = new_size;
	}
	connected_graph();
}

void shortest_way(int x) {
	if (x < 0 || x >= n)throw string("incorrect value");
	vector<int> v;
	while (x != -1) {
		v.push_back(x);
		x = last[x];
	}
	for (int i = 0, j = v.size() - 1; i < j; i++, j--) {
		swap(v[i], v[j]);
	}
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
}

int main()
{
	Initialize();
	int code = 0;
	while (code != Exit) {
		system("cls");
		cout << "+-------------------------------+\n";
		cout << "|program for working with tables|\n";
		cout << "+-------------------------------+\n";
		cout << "[command for graph]\n";
		cout << " graph is " << (connected ? "" : "not ") << "connected\n";
		cout << "  1.Change size (size: " << n << ")\n";
		cout << "  2.Change edge\n";
		cout << "  3.Random\n";
		cout << "  4.Show\n";
		cout << "  5.Clear\n";
		cout << "[command for Dijksta]\n";
		cout << "  6.Run with heap\n";
		cout << "  7.Run with binomial heap\n";
		cout << "  8.Run with array\n";
		cout << "\n";
		cout << "10.Exit\n";
		cout << ">";
		cin >> code;
		cin.clear();
		cin.ignore(10000, '\n');
		try {
			switch (code) {
			case 1: {
				change_size();
				clear_graph();
				connected_graph();
				break;
			}
			case 2: {
				enter_graph();
				break;
			}
			case 3: {
				random_graph();
				break;
			}
			case 4: {
				show_graph();
				break;
			}
			case 5: {
				clear_graph();
				connected_graph();
				break;
			}
			case 6: {
				cout << "Enter start vertex\n";
				int x;
				cin >> x;
				run_with_heap(x);
				cout << "shortest way:\n";
				show_was();
				cout << "\n";
				cout << "Enter the number of the vertex for which you want to know the path.\n";
				cout << "If you want exit then enter -1\n";
				int d = -2;
				while (true) {
					cin >> d;
					if (d == -1)break;
					shortest_way(d);
					cout << "\n";
				}
				break;
			}
			case 7: {
				cout << "Enter start vertex\n";
				int x;
				cin >> x;
				run_with_bheap(x);
				cout << "shortest way:\n";
				show_was();
				cout << "\n";
				cout << "Enter the number of the vertex for which you want to know the path.\n";
				cout << "If you want exit then enter -1\n";
				int d = -2;
				while (true) {
					cin >> d;
					if (d == -1)break;
					shortest_way(d);
					cout << "\n";
				}
				break;
			}
			case 8: {
				cout << "Enter start vertex\n";
				int x;
				cin >> x;
				run_with_array(x);
				cout << "shortest way:\n";
				show_was();
				cout << "\n";
				cout << "Enter the number of the vertex for which you want to know the path.\n";
				cout << "If you want exit then enter -1\n";
				int d = -2;
				while (true) {
					cin >> d;
					if (d == -1)break;
					shortest_way(d);
					cout << "\n";
				}
				break;
			}
			case 10: {
				break;
			}
			default: {
				cout << "command not found\n";
			}
			}
		}
		catch (string s) {
			cout << s << "\n";
		}
		catch (...) {
			cout << "undefined error\n";
		}
		system("pause");
	}
}