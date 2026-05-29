#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Rvalue insert method") {
  DoubleLinkedList<int> list;
  
  for (int i = 1; i <= 4; ++i) {
    list.push_back(i);
  }

  SUBCASE("Insert rvalue at the beginning") {
    auto it = list.begin();
    auto newIt = list.insert(it, std::move(0));
    CHECK(*newIt == 0);
    CHECK(list.size() == 5);
    CHECK(list.front() == 0);

    // Verify forward: [0, 1, 2, 3, 4]
    it = list.begin();
    CHECK(*it == 0);
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(it == list.end());
  }

  SUBCASE("Insert rvalue in the middle") {
    auto it = list.begin();
    ++it;
    ++it;
    auto newIt = list.insert(it, std::move(5));
    CHECK(*newIt == 5);
    CHECK(list.size() == 5);

    // Verify forward: [1, 2, 5, 3, 4]
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(it == list.end());
  }

  SUBCASE("Insert rvalue at the end") {
    auto it = list.end();
    auto newIt = list.insert(it, std::move(9));
    CHECK(*newIt == 9);
    CHECK(list.size() == 5);
    CHECK(list.back() == 9);

    // Verify forward: [1, 2, 3, 4, 9]
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(*it == 9);
    ++it;
    CHECK(it == list.end());
  }
}

TEST_CASE("Insert rvalue into empty list") {
  DoubleLinkedList<int> list;
  
  auto it = list.begin();
  auto newIt = list.insert(it, std::move(42));
  CHECK(*newIt == 42);
  CHECK(list.size() == 1);
  CHECK(list.front() == 42);
  CHECK(list.back() == 42);
}
