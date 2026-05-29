#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("find") {
  DoubleLinkedList<int> lst;
  
  for (int i = 1; i <= 10; ++i) {
    lst.push_back(i);
  }

  SUBCASE("element exists") {
    auto it = lst.find(2);
    REQUIRE(*it == 2);
  }

  SUBCASE("element doesn't exist") {
    auto it = lst.find(15);
    REQUIRE(it == lst.end());
  }
}
