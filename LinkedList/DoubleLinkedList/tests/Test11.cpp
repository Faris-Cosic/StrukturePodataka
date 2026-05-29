#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("clear method removes all elements from list") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.clear();

  CHECK(list.empty());
  CHECK(list.size() == 0);

  SUBCASE("add elements with push_front after clear") {
    list.push_front(10);
    CHECK(list.size() == 1);
    CHECK(list.front() == 10);
    CHECK(list.back() == 10);

    list.push_front(20);
    CHECK(list.size() == 2);
    CHECK(list.front() == 20);
    CHECK(list.back() == 10);
  }

  SUBCASE("add elements with push_back after clear") {
    list.push_back(10);
    CHECK(list.size() == 1);
    CHECK(list.front() == 10);
    CHECK(list.back() == 10);

    list.push_back(20);
    CHECK(list.size() == 2);
    CHECK(list.front() == 10);
    CHECK(list.back() == 20);
  }
}
