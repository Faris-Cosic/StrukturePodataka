#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("move constructor moves elements from source list") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2{std::move(list1)};

  CHECK(list1.empty());
  CHECK(list1.size() == 0);
  CHECK(list2.size() == 3);
  CHECK(list2.front() == 1);
  CHECK(list2.back() == 3);
}

TEST_CASE("moved from list can append elements") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2{std::move(list1)};

  CHECK(list1.empty());
  CHECK(list1.size() == 0);

  list1.push_back(4);
  CHECK(list1.size() == 1);
  CHECK(list1.front() == 4);
  CHECK(list1.back() == 4);

  list1.push_front(5);
  CHECK(list1.size() == 2);
  CHECK(list1.front() == 5);
  CHECK(list1.back() == 4);
}
