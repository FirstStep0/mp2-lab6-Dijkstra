#include <gtest.h>
#include "heap.h"
#include "binomial_heap.h"

//heap
TEST(heap, can_create_heap) {
	EXPECT_NO_THROW(heap<int> h);
}

TEST(heap, can_push_elem_into_heap) {
	heap<int> h;
	EXPECT_NO_THROW(h.push(2));
}

TEST(heap, can_pop_elem_from_heap) {
	heap<int> h;
	h.push(2);
	EXPECT_NO_THROW(h.pop());
}

TEST(heap, front_elem_is_minimum) {
	heap<int> h;
	h.push(2);
	h.push(3);
	h.push(-1);
	EXPECT_EQ(h.front(), -1);
}

TEST(heap, order_of_element_is_correct) {
	for (int i = 0; i < 10; i++) {
		heap<int> h;
		for (int j = 0; j < 10; j++) h.push(rand());
		int last = -1;
		for (int k = 0; k < 10; k++) {
			EXPECT_TRUE(last <= h.front());
			last = h.front();
			h.pop();
		}
	}
}

//binomial_heap
TEST(binomial_heap, can_create_heap) {
	EXPECT_NO_THROW(binomial_heap<int> h);
}

TEST(binomial_heap, can_push_elem_into_heap) {
	binomial_heap<int> h;
	EXPECT_NO_THROW(h.push(2));
}

TEST(binomial_heap, can_pop_elem_from_heap) {
	binomial_heap<int> h;
	h.push(2);
	EXPECT_NO_THROW(h.pop());
}

TEST(binomial_heap, front_elem_is_minimum) {
	binomial_heap<int> h;
	h.push(2);
	h.push(3);
	h.push(-1);
	EXPECT_EQ(h.front(), -1);
}

TEST(binomial_heap, order_of_element_is_correct) {
	for (int i = 0; i < 10; i++) {
		binomial_heap<int> h;
		for (int j = 0; j < 10; j++) h.push(rand());
		int last = -1;
		for (int k = 0; k < 10; k++) {
			EXPECT_TRUE(last <= h.front());
			last = h.front();
			h.pop();
		}
	}
}