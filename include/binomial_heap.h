#pragma once
#include "list.h"

template<class T>
class binomial_heap {
	class Node {
	public:
		int deg;
		list<Node*> childs;
		T value;
		Node(const T& value = T()) :value(value) {}
		void clear() {
			for (auto it = childs.begin(); it != childs.end(); ++it) {
				(*it)->clear();
				delete (*it);
			}
		}
	};
	list<Node*> root_list;
public:
	binomial_heap() {}
	~binomial_heap() {
		for (auto it = root_list.begin(); it != root_list.end(); ++it) {
			(*it)->clear();
			delete (*it);
		}
	}
	void push(const T& value) {
		binomial_heap<T> b;
		b.root_list.push_back(new Node(value));
		merge(b);
	}
	const T& front() {
		return (*_minimum())->value;
	}

	bool empty() {
		return root_list.size() == 0;
	}

	void pop() {
		if (!root_list.empty()) {
			auto it = _minimum();
			binomial_heap<T> b;
			b.root_list = (*it)->childs;
			root_list.erase(it);
			merge(b);
		}
	}
	/*void show() {
		int numb = 1;
		for (auto it = root_list.begin(); it != root_list.end(); ++it, numb++) {
			cout << numb << ": ";
			show(*it);
			cout << "\n";
		}
	}
	void show(Node* node) {
		cout << node->value << "\n";
		for (auto it = node->childs.begin(); it != node->childs.end(); ++it) {
			for (int i = 0; i < deep; i++)cout << "  ";
			deep++;
			show((*it));
			deep--;
		}
	}*/
private:
	list<Node*>::iterator<Node*> _minimum() {
		if (!root_list.empty()) {
			auto mi = root_list.begin();
			for (auto it = root_list.begin(); it != root_list.end(); ++it) {
				if (((*it)->value) < ((*mi)->value)) {
					mi = it;
				}
			}
			return mi;
		}
		else {
			throw string("binomial_heap is empty");
		}
	}
	Node* merge_heap(Node* a, Node* b) {
		if (a->value < b->value) {
			a->childs.push_back(b);
			a->deg *= 2;
			return a;
		}
		else {
			b->childs.push_back(a);
			b->deg *= 2;
			return b;
		}
	}

	void merge(binomial_heap<T>& heap) {
		root_list.merge(heap.root_list, [](Node* a, Node* b) {return (*a).deg < (*b).deg; });
		auto it = root_list.begin();
		while (it != root_list.end()) {
			auto next = it;
			++next;
			if (next != root_list.end() && (*it)->deg == (*next)->deg) {
				it = next;
			}
			else {
				auto last = it;
				--last;
				if (last != root_list.end() && (*last)->deg == (*it)->deg) {
					Node* n = merge_heap((*last), (*it));
					auto ins_elem = root_list.insert(it, n);
					root_list.erase(it);
					root_list.erase(last);
					it = ins_elem;
				}
				else {
					it++;
				}
			}
		}
	}
};