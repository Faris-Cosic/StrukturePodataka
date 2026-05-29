#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Push back and pop back with iterator verification") {
  DoubleLinkedList<int> list;

  SUBCASE("Push back and check with iterators") {
    // First insert
    list.push_back(1);
    auto it = list.begin();
    CHECK(*it == 1);
    auto rit = list.end();
    --rit;
    CHECK(*rit == 1);

    // Second insert
    list.push_back(2);
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    rit = list.end();
    --rit;
    CHECK(*rit == 2);
    --rit;
    CHECK(*rit == 1);

    // Third insert
    list.push_back(3);
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    rit = list.end();
    --rit;
    CHECK(*rit == 3);
    --rit;
    CHECK(*rit == 2);
    --rit;
    CHECK(*rit == 1);

    // Fourth insert
    list.push_back(4);
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    rit = list.end();
    --rit;
    CHECK(*rit == 4);
    --rit;
    CHECK(*rit == 3);
    --rit;
    CHECK(*rit == 2);
    --rit;
    CHECK(*rit == 1);
  }

  SUBCASE("Pop back and check with iterators") {
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    // First pop
    list.pop_back();
    auto it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    auto rit = list.end();
    --rit;
    CHECK(*rit == 3);
    --rit;
    CHECK(*rit == 2);
    --rit;
    CHECK(*rit == 1);

    // Second pop
    list.pop_back();
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    rit = list.end();
    --rit;
    CHECK(*rit == 2);
    --rit;
    CHECK(*rit == 1);

    // Third pop
    list.pop_back();
    it = list.begin();
    CHECK(*it == 1);
    rit = list.end();
    --rit;
    CHECK(*rit == 1);

    // Fourth pop - list becomes empty
    list.pop_back();
    CHECK(list.begin() == list.end());
  }
}

TEST_CASE("Push front and pop front with iterator verification") {
  DoubleLinkedList<int> list;

  SUBCASE("Push front and check with iterators") {
    // First insert
    list.push_front(1);
    auto it = list.begin();
    CHECK(*it == 1);
    auto rit = list.end();
    --rit;
    CHECK(*rit == 1);

    // Second insert
    list.push_front(2);
    it = list.begin();
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
    rit = list.end();
    --rit;
    CHECK(*rit == 1);
    --rit;
    CHECK(*rit == 2);

    // Third insert
    list.push_front(3);
    it = list.begin();
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
    rit = list.end();
    --rit;
    CHECK(*rit == 1);
    --rit;
    CHECK(*rit == 2);
    --rit;
    CHECK(*rit == 3);

    // Fourth insert
    list.push_front(4);
    it = list.begin();
    CHECK(*it == 4);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
    rit = list.end();
    --rit;
    CHECK(*rit == 1);
    --rit;
    CHECK(*rit == 2);
    --rit;
    CHECK(*rit == 3);
    --rit;
    CHECK(*rit == 4);
  }

  SUBCASE("Pop front and check with iterators") {
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);

    // First pop
    list.pop_front();
    auto it = list.begin();
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
    auto rit = list.end();
    --rit;
    CHECK(*rit == 1);
    --rit;
    CHECK(*rit == 2);
    --rit;
    CHECK(*rit == 3);

    // Second pop
    list.pop_front();
    it = list.begin();
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
    rit = list.end();
    --rit;
    CHECK(*rit == 1);
    --rit;
    CHECK(*rit == 2);

    // Third pop
    list.pop_front();
    it = list.begin();
    CHECK(*it == 1);
    rit = list.end();
    --rit;
    CHECK(*rit == 1);

    // Fourth pop - list becomes empty
    list.pop_front();
    CHECK(list.begin() == list.end());
  }
}
