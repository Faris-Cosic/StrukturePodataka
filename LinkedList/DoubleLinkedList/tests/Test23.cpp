#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Const overload for front and back") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  SUBCASE("Test const front()") {
    const DoubleLinkedList<int>& constList = list;
    CHECK(constList.front() == 1);
    
    // Verify front returns const reference
    const int& frontRef = constList.front();
    CHECK(frontRef == 1);
  }

  SUBCASE("Test const back()") {
    const DoubleLinkedList<int>& constList = list;
    CHECK(constList.back() == 4);
    
    // Verify back returns const reference
    const int& backRef = constList.back();
    CHECK(backRef == 4);
  }

  SUBCASE("Test both const front and back") {
    const DoubleLinkedList<int>& constList = list;
    CHECK(constList.front() == 1);
    CHECK(constList.back() == 4);
    
    // Verify we can't modify through const reference
    const int& frontRef = constList.front();
    const int& backRef = constList.back();
    CHECK(frontRef == 1);
    CHECK(backRef == 4);
  }

  SUBCASE("Test const front and back on single element list") {
    DoubleLinkedList<int> singleList;
    singleList.push_back(42);
    
    const DoubleLinkedList<int>& constList = singleList;
    CHECK(constList.front() == 42);
    CHECK(constList.back() == 42);
    CHECK(constList.front() == constList.back());
  }
}
