#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator insert function") {
  DoubleLinkedList<int> list;

  for (int i = 1; i <= 4; ++i) {
    list.push_back(i);
  }

  SUBCASE("Test inserting at the beginning") {
    auto it = list.begin();
    auto newIt = list.insert(it, 0);
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

    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 4);
    --it;
    CHECK(*it == 3);
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(*it == 0);
    --it;
    CHECK(it == list.end());
  }

  SUBCASE("Test inserting in the middle") {
    auto it = list.begin();
    ++it;
    ++it;
    auto newIt = list.insert(it, 5);
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

    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 4);
    --it;
    CHECK(*it == 3);
    --it;
    CHECK(*it == 5);
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
  }

  SUBCASE("Test inserting at the end") {
    auto it = list.end();
    auto newIt = list.insert(it, 9);
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

    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 9);
    --it;
    CHECK(*it == 4);
    --it;
    CHECK(*it == 3);
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
  }
}

TEST_CASE("Insert into an empty list") {
  DoubleLinkedList<int> list;
  
  auto it = list.begin();
  auto newIt = list.insert(it, 42);
  CHECK(*newIt == 42);
  CHECK(list.size() == 1);
  CHECK(list.front() == 42);
  CHECK(list.back() == 42);

  // Verify forward
  it = list.begin();
  CHECK(*it == 42);
  ++it;
  CHECK(it == list.end());

  // Verify backward
  it = list.end();
  --it;
  CHECK(*it == 42);
  --it;
  CHECK(it == list.end());
}

TEST_CASE("Insert into a list with one value") {
  SUBCASE("Insert at the beginning") {
    DoubleLinkedList<int> list;
    list.push_back(5);
    
    auto it = list.begin();
    auto newIt = list.insert(it, 3);
    CHECK(*newIt == 3);
    CHECK(list.size() == 2);
    CHECK(list.front() == 3);
    CHECK(list.back() == 5);

    // Verify forward: [3, 5]
    it = list.begin();
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(it == list.end());

    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 5);
    --it;
    CHECK(*it == 3);
    --it;
    CHECK(it == list.end());
  }

  SUBCASE("Insert at the end") {
    DoubleLinkedList<int> list;
    list.push_back(5);
    
    auto it = list.end();
    auto newIt = list.insert(it, 7);
    CHECK(*newIt == 7);
    CHECK(list.size() == 2);
    CHECK(list.front() == 5);
    CHECK(list.back() == 7);

    // Verify forward: [5, 7]
    it = list.begin();
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 7);
    ++it;
    CHECK(it == list.end());

    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 7);
    --it;
    CHECK(*it == 5);
    --it;
    CHECK(it == list.end());
  }
}

TEST_CASE("Insert into a list with two values") {
  SUBCASE("Insert at the beginning") {
    DoubleLinkedList<int> list;
    list.push_back(5);
    list.push_back(10);
    
    auto it = list.begin();
    auto newIt = list.insert(it, 3);
    CHECK(*newIt == 3);
    CHECK(list.size() == 3);
    CHECK(list.front() == 3);

    // Verify forward: [3, 5, 10]
    it = list.begin();
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 10);
    ++it;
    CHECK(it == list.end());

    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 10);
    --it;
    CHECK(*it == 5);
    --it;
    CHECK(*it == 3);
    --it;
    CHECK(it == list.end());
  }

  SUBCASE("Insert at the end") {
    DoubleLinkedList<int> list;
    list.push_back(5);
    list.push_back(10);
    
    auto it = list.end();
    auto newIt = list.insert(it, 15);
    CHECK(*newIt == 15);
    CHECK(list.size() == 3);
    CHECK(list.back() == 15);

    // Verify forward: [5, 10, 15]
    it = list.begin();
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 10);
    ++it;
    CHECK(*it == 15);
    ++it;
    CHECK(it == list.end());

    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 15);
    --it;
    CHECK(*it == 10);
    --it;
    CHECK(*it == 5);
    --it;
    CHECK(it == list.end());
  }

  SUBCASE("Insert in the middle") {
    DoubleLinkedList<int> list;
    list.push_back(5);
    list.push_back(10);
    
    auto it = list.begin();
    ++it;
    auto newIt = list.insert(it, 7);
    CHECK(*newIt == 7);
    CHECK(list.size() == 3);

    // Verify forward: [5, 7, 10]
    it = list.begin();
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 7);
    ++it;
    CHECK(*it == 10);
    ++it;
    CHECK(it == list.end());

    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 10);
    --it;
    CHECK(*it == 7);
    --it;
    CHECK(*it == 5);
    --it;
    CHECK(it == list.end());
  }
}
