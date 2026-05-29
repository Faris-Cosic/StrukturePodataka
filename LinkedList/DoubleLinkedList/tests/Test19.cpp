#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Test remove_if function") {
  DoubleLinkedList<int> list;

  for (int i = 1; i <= 10; ++i) {
    list.push_back(i);
  }

  // Remove all even elements from the list
  list.remove_if([](const int& x) { return x % 2 == 0; });

  // Check the size of the list
  REQUIRE(list.size() == 5);

  // Verify forward: [1, 3, 5, 7, 9]
  auto it = list.begin();
  CHECK(*it == 1);
  ++it;
  CHECK(*it == 3);
  ++it;
  CHECK(*it == 5);
  ++it;
  CHECK(*it == 7);
  ++it;
  CHECK(*it == 9);
  ++it;
  CHECK(it == list.end());

  // Verify backward
  it = list.end();
  --it;
  CHECK(*it == 9);
  --it;
  CHECK(*it == 7);
  --it;
  CHECK(*it == 5);
  --it;
  CHECK(*it == 3);
  --it;
  CHECK(*it == 1);
  --it;
  CHECK(it == list.end());
}
