#pragma once
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

template<class T, unsigned int d = 2, class Compare = std::less<T>>
class heap {
private:
	Compare less;
	vector<T> data;
public:
	heap(const T* _data, size_t size, Compare _less = Compare()) :heap(_less) {
		data.resize(size);
		for (int i = 0; i < size; i++) data[i] = _data[i];
		createHeap();
	}

	size_t size() {
		return data.size();
	}

	heap(Compare _less = Compare()) {
		less = _less;
	}

	heap(const vector<T>& _data, Compare _less = Compare()) :heap(_less) {
		data = _data;
		createHeap();
	}

	bool empty() {
		return size() == 0;
	}

	const T& front(){
		if (!empty()) { return data[0]; }
		throw string("heap is empty");
	}

	void pop() {
		if (!empty()) {
			swap(data[0], data.back());
			data.pop_back();
			if (!empty()) heapity(0);
			return;
		}
		throw string("heap is empty");
	}

	template<unsigned int _d>
	void merge(const heap<T>& other) {
		int size1 = data.size();
		int size2 = size1 + other.size();
		data.resize(size2);
		for (int i = size1; i < size2; i++) {
			data[i] = other.data[i];
		}
		createHeap();
	}
	void push(const T& elem) {
		data.push_back(elem);
		int i = size() - 1;
		int parent = (i - 1) / d;
		while (i != 0 && less(data[i], data[parent])) {
			swap(data[parent], data[i]);
			i = parent;
			parent = (i - 1) / d;
		}
	}

private:

	void heapity(int i) {
		//if ((i < 0) || (i >= data.size()))return;
		const int _size = data.size();
		T* max_elem = &data[i];
		int next = -1, begin, end;
		while (i != next) {
			next = i, begin = d * i + 1, end = d * (i + 1);
			for (int child = begin; (child <= end) && (child < _size); child++) {
				T* elem = &data[child];
				if (less((*elem), (*max_elem))) {
					next = child;
					max_elem = elem;
				}
			}
			if (i != next) {
				swap(data[i], *max_elem);
				max_elem = &data[next];
				swap(i, next);
			}
		}
	}

	void createHeap() {
		for (int i = (h.size() - 2) / 2; i >= 0; i--) heapity(i);
	}
};