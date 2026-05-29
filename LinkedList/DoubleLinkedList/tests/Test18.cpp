#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Test DoubleLinkedList erase") {
  DoubleLinkedList<int> list;

  for (int i = 1; i <= 10; ++i) {
    list.push_back(i);
  }

  SUBCASE("Erase single element") {
    auto pos = list.begin();
    ++pos;
    ++pos;
    auto it = list.erase(pos);
    CHECK(*it == 4);
    CHECK(list.size() == 9);
    CHECK(list.front() == 1);
    CHECK(list.back() == 10);

    // Verify forward: [1, 2, 4, 5, 6, 7, 8, 9, 10]
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 6);
    ++it;
    CHECK(*it == 7);
    ++it;
    CHECK(*it == 8);
    ++it;
    CHECK(*it == 9);
    ++it;
    CHECK(*it == 10);
    ++it;
    CHECK(it == list.end());

    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 10);
    --it;
    CHECK(*it == 9);
    --it;
    CHECK(*it == 8);
    --it;
    CHECK(*it == 7);
    --it;
    CHECK(*it == 6);
    --it;
    CHECK(*it == 5);
    --it;
    CHECK(*it == 4);
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
  }

  SUBCASE("Erase range of elements") {
    auto start = list.begin();
    ++start;
    auto end = list.begin();
    --end;
    --end;
    --end;
    --end;
    auto it = list.erase(start, end);
    CHECK(*it == 8);
    CHECK(list.size() == 4);
    CHECK(list.front() == 1);
    CHECK(list.back() == 10);

    // Verify forward: [1, 8, 9, 10]
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 8);
    ++it;
    CHECK(*it == 9);
    ++it;
    CHECK(*it == 10);
    ++it;
    CHECK(it == list.end());

    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 10);
    --it;
    CHECK(*it == 9);
    --it;
    CHECK(*it == 8);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
  }
}
