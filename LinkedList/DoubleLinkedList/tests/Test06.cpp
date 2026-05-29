#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("pop_back removes last element from list") {
  DoubleLinkedList<int> list;
  list.push_back(0);
  list.push_back(1);
  list.push_back(2);

  CHECK(list.size() == 3);
  CHECK(list.back() == 2);

  list.pop_back();

  CHECK(list.size() == 2);
  CHECK(list.back() == 1);

  list.pop_back();

  CHECK(list.size() == 1);
  CHECK(list.back() == 0);

  list.pop_back();

  CHECK(list.size() == 0);
}

TEST_CASE("push_back, pop_back, push_back sequence") {
  DoubleLinkedList<int> list;

  list.push_back(1);
  CHECK(list.size() == 1);
  CHECK(list.front() == 1);
  CHECK(list.back() == 1);

  list.pop_back();
  CHECK(list.size() == 0);
  CHECK(list.empty());

  list.push_back(2);
  CHECK(list.size() == 1);
  CHECK(list.front() == 2);
  CHECK(list.back() == 2);
}

TEST_CASE("push_front, pop_back, push_front sequence") {
  DoubleLinkedList<int> list;

  list.push_front(1);
  CHECK(list.size() == 1);
  CHECK(list.front() == 1);
  CHECK(list.back() == 1);

  list.pop_back();
  CHECK(list.size() == 0);
  CHECK(list.empty());

  list.push_front(2);
  CHECK(list.size() == 1);
  CHECK(list.front() == 2);
  CHECK(list.back() == 2);
}
