#include "../../lib/catch.hpp"
#include "../../src/array/bit_elem_array.hh"

TEST_CASE("BitElemArray constructs correct size array", "[bit_elem_array]") {
  BitElemArray bit_elem_array (8, 24);
  REQUIRE(bit_elem_array.capacity() == 24);
  REQUIRE(bit_elem_array.size() == 0);
}

TEST_CASE("BitElemArray can append and get elements", "[bit_elem_array]") {
  BitElemArray bit_elem_array (13, 8);
  bit_elem_array.append(458);
  REQUIRE(bit_elem_array.size() == 1);
  REQUIRE(bit_elem_array.get(0) == 458);
  bit_elem_array.append(8191);
  REQUIRE(bit_elem_array.size() == 2);
  REQUIRE(bit_elem_array.get(1) == 8191);
  REQUIRE(bit_elem_array.get(0) == 458);
}

TEST_CASE("BitElemArray::swap", "[bit_elem_array]") {
  BitElemArray bit_elem_array(26, 14);
  bit_elem_array.append(41840);
  bit_elem_array.append(31804);
  bit_elem_array.append(14014801);
  bit_elem_array.append(14180);
  bit_elem_array.swap(0, 3);
  REQUIRE(bit_elem_array.get(0) == 14180);
  REQUIRE(bit_elem_array.get(3) == 41840);
  bit_elem_array.swap(1, 2);
  REQUIRE(bit_elem_array.get(1) == 14014801);
  REQUIRE(bit_elem_array.get(2) == 31804);
}

TEST_CASE("BitElemArray::sort", "[bit_elem_array]") {
  BitElemArray bit_elem_array(18, 10);
  bit_elem_array.append(4108);
  bit_elem_array.append(14014);
  bit_elem_array.append(5106);
  bit_elem_array.append(3104);
  bit_elem_array.append(9056);
  bit_elem_array.sort();
  REQUIRE(bit_elem_array.size() == 5);
  REQUIRE(bit_elem_array.get(0) == 3104);
  REQUIRE(bit_elem_array.get(1) == 4108);
  REQUIRE(bit_elem_array.get(2) == 5106);
  REQUIRE(bit_elem_array.get(3) == 9056);
  REQUIRE(bit_elem_array.get(4) == 14014);
}

TEST_CASE("BitElemArray::index_of", "[bit_elem_array]") {
  BitElemArray bit_elem_array(18, 10);
  bit_elem_array.append(4108);
  bit_elem_array.append(14014);
  bit_elem_array.append(5106);
  bit_elem_array.append(3104);
  bit_elem_array.append(9056);
  bit_elem_array.sort();
  REQUIRE(bit_elem_array.index_of(3104) == 0);
  REQUIRE(bit_elem_array.index_of(4108) == 1);
  REQUIRE(bit_elem_array.index_of(5106) == 2);
  REQUIRE(bit_elem_array.index_of(9056) == 3);
  REQUIRE(bit_elem_array.index_of(14014) == 4);
}
