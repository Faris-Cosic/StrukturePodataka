#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Test reverse() method") {
  DoubleLinkedList<int> l;
  
  for (int i = 1; i <= 10; ++i) {
    l.push_back(i);
  }

  l.reverse();

  // Verify forward: [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
  auto it = l.begin();
  CHECK(*it == 10);
  ++it;
  CHECK(*it == 9);
  ++it;
  CHECK(*it == 8);
  ++it;
  CHECK(*it == 7);
  ++it;
  CHECK(*it == 6);
  ++it;
  CHECK(*it == 5);
  ++it;
  CHECK(*it == 4);
  ++it;
  CHECK(*it == 3);
  ++it;
  CHECK(*it == 2);
  ++it;
  CHECK(*it == 1);
  ++it;
  CHECK(it == l.end());

  // Verify backward: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
  it = l.end();
  --it;
  CHECK(*it == 1);
  --it;
  CHECK(*it == 2);
  --it;
  CHECK(*it == 3);
  --it;
  CHECK(*it == 4);
  --it;
  CHECK(*it == 5);
  --it;
  CHECK(*it == 6);
  --it;
  CHECK(*it == 7);
  --it;
  CHECK(*it == 8);
  --it;
  CHECK(*it == 9);
  --it;
  CHECK(*it == 10);
  --it;
  CHECK(it == l.end());
}
