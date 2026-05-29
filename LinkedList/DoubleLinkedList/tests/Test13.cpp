#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator prefix increment operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the first element of the list
  auto it = list.begin();

  // Increment the iterator and check that it points to the second element
  ++it;
  CHECK(*it == 2);

  // Increment the iterator again and check that it points to the third element
  ++it;
  CHECK(*it == 3);

  // Increment the iterator again and check that it is equal to the end iterator
  ++it;
  CHECK(it == list.end());
}

TEST_CASE("Iterator postfix increment operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the first element of the list
  auto it = list.begin();

  // Use the postfix increment operator and check that the original iterator is
  // unchanged
  auto old_it = it++;
  CHECK(*old_it == 1);

  // Check that the new iterator points to the second element
  CHECK(*it == 2);

  // Use the postfix increment operator again and check that the original
  // iterator is unchanged
  old_it = it++;
  CHECK(*old_it == 2);

  // Check that the new iterator points to the third element
  CHECK(*it == 3);

  // Use the postfix increment operator again and check that the original
  // iterator is unchanged
  old_it = it++;
  CHECK(*old_it == 3);

  // Check that the new iterator is equal to the end iterator
  CHECK(it == list.end());
}

TEST_CASE("Iterator decrement operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the last element of the list
  auto it = list.begin();
  ++it;
  ++it;

  // Use the decrement operator and check that the iterator now points to the
  // second element
  --it;
  CHECK(*it == 2);

  // Use the decrement operator again and check that the iterator now points to
  // the first element
  --it;
  CHECK(*it == 1);

  // Use the decrement operator again and check that the iterator is now equal
  // to the end iterator
  --it;
  CHECK(it == list.end());
}

TEST_CASE("Iterator post-decrement operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the last element of the list
  auto it = list.begin();
  ++it;
  ++it;

  // Use the post-decrement operator and check that the iterator still points to
  // the last element
  auto it2 = it--;
  CHECK(*it2 == 3);
  CHECK(*it == 2);

  // Use the post-decrement operator again and check that the iterator still
  // points to the second element
  it2 = it--;
  CHECK(*it2 == 2);
  CHECK(*it == 1);
  CHECK(it == list.begin());

  // Use the post-decrement operator again and check that the iterator still
  // points to the first element
  it2 = it--;
  CHECK(*it2 == 1);
}
