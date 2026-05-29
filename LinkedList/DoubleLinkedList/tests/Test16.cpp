#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Mixed push and pop operations with iterator validation") {
  DoubleLinkedList<int> list;

  SUBCASE("push_back followed by iterator verification") {
    list.push_back(1);
    
    // Verify forward
    auto it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(it == list.end());
    
    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
    
    list.push_back(2);
    
    // Verify forward
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(it == list.end());
    
    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
    
    list.push_back(3);
    
    // Verify forward
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(it == list.end());
    
    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 3);
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
  }

  SUBCASE("pop_back followed by iterator verification") {
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    list.pop_back();
    
    // Verify forward
    auto it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(it == list.end());
    
    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
    
    list.pop_back();
    
    // Verify forward
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(it == list.end());
    
    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
    
    list.pop_back();
    
    // Verify empty list
    CHECK(list.begin() == list.end());
  }

  SUBCASE("push_front followed by iterator verification") {
    list.push_front(1);
    
    // Verify forward
    auto it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(it == list.end());
    
    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
    
    list.push_front(2);
    
    // Verify forward
    it = list.begin();
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(it == list.end());
    
    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(it == list.end());
    
    list.push_front(3);
    
    // Verify forward
    it = list.begin();
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(it == list.end());
    
    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(*it == 3);
    --it;
    CHECK(it == list.end());
  }

  SUBCASE("pop_front followed by iterator verification") {
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    
    list.pop_front();
    
    // Verify forward
    auto it = list.begin();
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(it == list.end());
    
    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(it == list.end());
    
    list.pop_front();
    
    // Verify forward
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(it == list.end());
    
    // Verify backward
    it = list.end();
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
    
    list.pop_front();
    
    // Verify empty list
    CHECK(list.begin() == list.end());
  }

  SUBCASE("Mixed operations with iterator verification") {
    list.push_back(1);
    
    // Verify: [1]
    auto it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(it == list.end());
    it = list.end();
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
    
    list.push_front(2);
    
    // Verify: [2, 1]
    it = list.begin();
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(it == list.end());
    it = list.end();
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(it == list.end());
    
    list.push_back(3);
    
    // Verify: [2, 1, 3]
    it = list.begin();
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(it == list.end());
    it = list.end();
    --it;
    CHECK(*it == 3);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(*it == 2);
    --it;
    CHECK(it == list.end());
    
    list.pop_front();
    
    // Verify: [1, 3]
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(it == list.end());
    it = list.end();
    --it;
    CHECK(*it == 3);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
    
    list.pop_back();
    
    // Verify: [1]
    it = list.begin();
    CHECK(*it == 1);
    ++it;
    CHECK(it == list.end());
    it = list.end();
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(it == list.end());
    
    list.push_front(4);
    list.push_back(5);
    
    // Verify: [4, 1, 5]
    it = list.begin();
    CHECK(*it == 4);
    ++it;
    CHECK(*it == 1);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(it == list.end());
    it = list.end();
    --it;
    CHECK(*it == 5);
    --it;
    CHECK(*it == 1);
    --it;
    CHECK(*it == 4);
    --it;
    CHECK(it == list.end());
  }
}
