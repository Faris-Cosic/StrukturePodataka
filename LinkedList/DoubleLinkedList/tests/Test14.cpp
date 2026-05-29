#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator equality operator") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2;
  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(3);

  DoubleLinkedList<int> list3;
  list3.push_back(4);
  list3.push_back(5);
  list3.push_back(6);

  auto it1 = list1.begin();
  auto it2 = list1.begin();
  CHECK(it1 == it2);

  // Test equality of iterators pointing to different elements
  it1 = list1.begin();
  it2 = list1.end();
  CHECK_FALSE(it1 == it2);

}

TEST_CASE("Iterator inequality operator") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2;
  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(3);

  DoubleLinkedList<int> list3;
  list3.push_back(4);
  list3.push_back(5);
  list3.push_back(6);

  // Test inequality of iterators pointing to the same element
  auto it1 = list1.begin();
  auto it2 = list1.begin();
  CHECK_FALSE(it1 != it2);

  // Test inequality of iterators pointing to different elements
  it1 = list1.begin();
  it2 = list1.end();
  CHECK(it1 != it2);
}

TEST_CASE("Iterator begin function") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Test begin function
  auto it = list.begin();
  CHECK(*it == 1);

  // Test begin function with empty list
  DoubleLinkedList<int> emptyList;
  auto emptyIt = emptyList.begin();
  CHECK(emptyIt == emptyList.end());
}

TEST_CASE("Iterator end function") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Test end function
  auto it = list.end();
  CHECK(it == nullptr);

  // Test end function with non-empty list
  auto beginIt = list.begin();
  auto endIt = list.end();
  CHECK(beginIt != endIt);

  // Test end function with empty list
  DoubleLinkedList<int> emptyList;
  auto emptyIt = emptyList.end();
  CHECK(emptyIt == nullptr);
}
