#include "../../lib/catch.hpp"
#include "../../src/array/bit_array.hh"

const int BITS_IN_BYTE = 8;

TEST_CASE("BitArray constructs correct size array", "[bit_array]") {
  long num_bits = 51028;
  BitArray bit_array = BitArray(num_bits);
  int expected_capacity = ceil(num_bits / (sizeof(long) * 8.0));
  REQUIRE(bit_array.get_capacity() == expected_capacity);
}

TEST_CASE("BitArray::append appends when it can fit in 1 long", "[bit_array]") {
  BitArray bit_array = BitArray(sizeof(long) * BITS_IN_BYTE * 2);
  bit_array.append(25, 8);
  bit_array.append(135, 8);
  REQUIRE(bit_array.get(0, 2) == 0);
  REQUIRE(bit_array.get(2, 6) == 25);
  REQUIRE(bit_array.get(8, 8) == 135);
  // check when num_bits is greater than what's left in array
}

TEST_CASE("BitArray::append appends when it requires 2 longs", "[bit_array]") {
  BitArray bit_array = BitArray(sizeof(long) * BITS_IN_BYTE * 2);
  bit_array.append(138, sizeof(long) * BITS_IN_BYTE - 2);
  bit_array.append(24, 8);
  REQUIRE(bit_array.get(sizeof(long) * BITS_IN_BYTE - 2, 2) == 0);
  REQUIRE(bit_array.get(sizeof(long) * BITS_IN_BYTE, 6) == 24);
  REQUIRE(bit_array.get(sizeof(long) * BITS_IN_BYTE - 2, 8) == 24);
}

TEST_CASE("BitArray resizes when necessary", "[bit_array]") {
  BitArray bit_array = BitArray(sizeof(long) * BITS_IN_BYTE * 2);
  bit_array.append(138, sizeof(long) * BITS_IN_BYTE);
  bit_array.append(4552, sizeof(long) * BITS_IN_BYTE);
  bit_array.append(789, sizeof(long) * BITS_IN_BYTE);
  REQUIRE(bit_array.get_capacity() > 2);
}

TEST_CASE("BitArray::shrink_to_fit shrinks to minimum capacity necessary",
    "[bit_array]") {
  BitArray bit_array = BitArray(sizeof(long) * BITS_IN_BYTE * 2);
  bit_array.append(138, sizeof(long) * BITS_IN_BYTE);
  bit_array.append(4552, sizeof(long) * BITS_IN_BYTE);
  bit_array.append(789, sizeof(long) * BITS_IN_BYTE);
  bit_array.shrink_to_fit();
  REQUIRE(bit_array.get_capacity() == 3);
}
