#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Mixed push operations - push_back first") {
  DoubleLinkedList<int> list;

  list.push_back(1);
  CHECK(list.size() == 1);
  CHECK(list.front() == 1);
  CHECK(list.back() == 1);

  list.push_front(2);
  CHECK(list.size() == 2);
  CHECK(list.front() == 2);
  CHECK(list.back() == 1);

  list.push_back(3);
  CHECK(list.size() == 3);
  CHECK(list.front() == 2);
  CHECK(list.back() == 3);

  list.push_front(4);
  CHECK(list.size() == 4);
  CHECK(list.front() == 4);
  CHECK(list.back() == 3);
}

TEST_CASE("Mixed push operations - push_front first") {
  DoubleLinkedList<int> list;

  list.push_front(1);
  CHECK(list.size() == 1);
  CHECK(list.front() == 1);
  CHECK(list.back() == 1);

  list.push_back(2);
  CHECK(list.size() == 2);
  CHECK(list.front() == 1);
  CHECK(list.back() == 2);

  list.push_front(3);
  CHECK(list.size() == 3);
  CHECK(list.front() == 3);
  CHECK(list.back() == 2);

  list.push_back(4);
  CHECK(list.size() == 4);
  CHECK(list.front() == 3);
  CHECK(list.back() == 4);
}
