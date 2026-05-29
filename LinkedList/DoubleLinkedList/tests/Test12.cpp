#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator copy constructor") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the second element of the list
  auto it1 = list.begin();
  ++it1;

  // Copy the iterator using the copy constructor
  auto it2 = it1;

  // Check that the copy points to the same element as the original
  CHECK(*it2 == 2);

  // Check that advancing one iterator does not affect the other
  ++it1;
  CHECK(*it1 == 3);
  CHECK(*it2 == 2);
}

TEST_CASE("Iterator assignment operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the second element of the list
  auto it1 = list.begin();
  ++it1;

  // Create a new iterator and assign it the value of the first iterator
  auto it2 = DoubleLinkedList<int>::Iterator();
  it2 = it1;

  // Check that the new iterator points to the same element as the original
  CHECK(*it2 == 2);

  // Check that advancing one iterator does not affect the other
  ++it1;
  CHECK(*it1 == 3);
  CHECK(*it2 == 2);

  // Check that reassigning the first iterator does not affect the second
  it1 = list.begin();
  CHECK(*it1 == 1);
  CHECK(*it2 == 2);
}

TEST_CASE("Iterator dereference operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Test dereference operator
  auto it = list.begin();
  CHECK(*it == 1);

  // Test dereference operator with const iterator
  const auto& constList = list;
  auto cit = constList.begin();
  CHECK(*cit == 1);
}

TEST_CASE("Iterator arrow operator") {
  struct Data {
    int a = 20;
    int b = 30;
    char x = 'x';
    Data() = default;
    Data(int a1, int b1, char x1) : a{a1}, b{b1}, x{x1} {}
  };
  DoubleLinkedList<Data> list;
  list.push_back(Data{});
  list.push_back(Data{50, 70, 'a'});
  list.push_back(Data{-4, -2, 'A'});

  // Test arrow operator
  auto it = list.begin();
  CHECK(it->a == 20);
  CHECK(it->b == 30);
  CHECK(it->x == 'x');

  // Test arrow operator with const iterator
  const auto& constList = list;
  auto cit = constList.begin();
  CHECK(cit->a == 20);
  CHECK(cit->b == 30);
  CHECK(cit->x == 'x');
}
