#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("push_back adds element to empty list") {
  DoubleLinkedList<int> list;
  list.push_back(1);

  CHECK(list.size() == 1);
  CHECK(list.front() == 1);
  CHECK(list.back() == 1);
}

TEST_CASE("push_back adds element to back of list") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  CHECK(list.size() == 1);
  CHECK(list.front() == 1);
  CHECK(list.back() == 1);

  list.push_back(2);
  CHECK(list.size() == 2);
  CHECK(list.front() == 1);
  CHECK(list.back() == 2);

  list.push_back(3);
  CHECK(list.size() == 3);
  CHECK(list.front() == 1);
  CHECK(list.back() == 3);
}

TEST_CASE("push_back adds string elements to list") {
  DoubleLinkedList<std::string> list;

  std::string str = "hello";
  list.push_back(str);
  list.push_back("world");

  CHECK(list.size() == 2);
  CHECK(list.front() == "hello");
  CHECK(list.back() == "world");
}

// TODO: Add a test for move semantics like we had for push_back

TEST_CASE("push_back can add rvalue elements") {
  DoubleLinkedList<std::string> list;
  list.push_back("hello");

  std::string str = "world";
  list.push_back(std::move(str));

  CHECK(list.size() == 2);
  CHECK(list.back() == "world");
  CHECK(str.size() == 0);
}
