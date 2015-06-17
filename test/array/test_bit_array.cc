#include "../../lib/catch.hpp"
#include "../../src/array/bit_array.hh"

const int BITS_IN_BYTE = 8;
const int LONG_BITS = sizeof(long) * BITS_IN_BYTE;

TEST_CASE("BitArray constructs correct size array", "[bit_array]") {
  long num_bits = 51028;
  BitArray bit_array (num_bits);
  int expected_capacity = ceil((double) num_bits / LONG_BITS);
  REQUIRE(bit_array.long_capacity() == expected_capacity);
}

TEST_CASE("BitArray::append appends when it can fit in 1 long", "[bit_array]") {
  BitArray bit_array (LONG_BITS * 2);
  bit_array.append(25, 8);
  bit_array.append(135, 8);
  REQUIRE(bit_array.get(0, 2) == 0);
  REQUIRE(bit_array.get(2, 6) == 25);
  REQUIRE(bit_array.get(8, 8) == 135);
}

TEST_CASE("BitArray::append appends when it requires 2 longs", "[bit_array]") {
  BitArray bit_array (LONG_BITS * 2);
  bit_array.append(138, LONG_BITS - 2);
  bit_array.append(24, 8);
  REQUIRE(bit_array.get(LONG_BITS - 2, 2) == 0);
  REQUIRE(bit_array.get(LONG_BITS, 6) == 24);
  REQUIRE(bit_array.get(LONG_BITS - 2, 8) == 24);
}

TEST_CASE(
  "BitArray::append appends when new bits are start of new long",
  "[bit_array]") {
  BitArray bit_array (LONG_BITS * 4);
  bit_array.append(1480143, LONG_BITS);
  bit_array.append(2495, 15);
  REQUIRE(bit_array.get(0, LONG_BITS) == 1480143);
  REQUIRE(bit_array.get(LONG_BITS, 15) == 2495);
}

TEST_CASE("BitArray resizes when necessary", "[bit_array]") {
  BitArray bit_array (LONG_BITS * 2);
  bit_array.append(138, LONG_BITS);
  bit_array.append(4552, LONG_BITS);
  bit_array.append(789, LONG_BITS);
  REQUIRE(bit_array.long_capacity() > 2);
}

TEST_CASE(
  "BitArray::shrink_to_fit shrinks to minimum capacity necessary",
  "[bit_array]") {
  BitArray bit_array (LONG_BITS * 2);
  bit_array.append(138, LONG_BITS);
  bit_array.append(4552, LONG_BITS);
  bit_array.append(789, LONG_BITS);
  bit_array.shrink_to_fit();
  REQUIRE(bit_array.long_capacity() == 3);
}
