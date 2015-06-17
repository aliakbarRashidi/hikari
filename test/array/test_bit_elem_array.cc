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
}

