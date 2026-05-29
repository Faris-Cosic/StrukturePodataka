#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("front returns reference to first element in list") {
  SUBCASE("front works with int") {
    DoubleLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    CHECK(list.front() == 1);
    list.front() = 4;
    CHECK(list.front() == 4);
  }
  SUBCASE("front works with std::string") {
    DoubleLinkedList<std::string> strList;
    strList.push_back("hello");
    strList.push_back("world");

    CHECK(strList.front() == "hello");
    strList.front() = "goodbye";
    CHECK(strList.front() == "goodbye");
  }
}

TEST_CASE("back returns reference to last element in list") {
  SUBCASE("back works with int") {
    DoubleLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    CHECK(list.back() == 3);
    list.back() = 5;
    CHECK(list.back() == 5);
  }
  SUBCASE("back works with std::string") {
    DoubleLinkedList<std::string> strList;
    strList.push_back("hello");
    strList.push_back("world");

    CHECK(strList.back() == "world");
    strList.back() = "universe";
    CHECK(strList.back() == "universe");
  }
}
