#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../DoubleLinkedList.hpp"
#include "doctest.h"

#include <concepts>

TEST_CASE("An newly created list is empty") {
  SUBCASE("empty list returns true") {
    DoubleLinkedList<int> list;
    CHECK(list.size() == 0);
    CHECK(list.empty());
  }
}

TEST_CASE("push_front adds element to empty list") {
  DoubleLinkedList<int> list;
  list.push_front(1);

  CHECK(list.size() == 1);
  CHECK(list.front() == 1);
  CHECK(list.back() == 1);
}

TEST_CASE("push_front adds element to front of list") {
  DoubleLinkedList<int> list;
  list.push_front(1);
  CHECK(list.size() == 1);
  CHECK(!list.empty());
  CHECK(list.front() == 1);
  CHECK(list.back() == 1);

  list.push_front(2);
  CHECK(list.size() == 2);
  CHECK(list.front() == 2);
  CHECK(list.back() == 1);

  list.push_front(3);
  CHECK(list.size() == 3);
  CHECK(list.front() == 3);
  CHECK(list.back() == 1);
}

TEST_CASE("push_front can add string elements") {
  DoubleLinkedList<std::string> list;

  std::string str = "hello";
  list.push_front(str);
  list.push_front("world");

  CHECK(list.size() == 2);
  CHECK(list.front() == "world");
  CHECK(list.back() == "hello");
}

TEST_CASE("push_front can add rvalue elements") {
  DoubleLinkedList<std::string> list;
  list.push_front("hello");

  std::string str = "world";
  list.push_front(std::move(str));

  CHECK(list.size() == 2);
  CHECK(list.front() == "world");
  CHECK(str.size() == 0);
}
