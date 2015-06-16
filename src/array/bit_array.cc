#include <math.h>
#include <assert.h>
#include "bit_array.hh"
#include "../util/memory.hh"

const int BITS_IN_BYTE = 8;
const int LONG_BITS = BITS_IN_BYTE * sizeof(unsigned long);

/*
 * Construct a BitArray.
 *
 * Params:
 *  num_bits: The number of bits in the array.
 */
BitArray::BitArray(long num_bits) {
  last_set_bit_ind = -1;
  capacity = ceil((double) num_bits / LONG_BITS);
  // TODO(smilli): check to make sure get memory
  bits = (unsigned long*) checked_malloc(capacity * sizeof(unsigned long));
  for (int i = 0; i < capacity; i++) {
    bits[i] = 0;
  }
}

BitArray::~BitArray() {
  free(bits);
}

int BitArray::get_capacity() {
  return capacity;
}

/*
 * Add the n least significant bits of new_bits to bit array.
 *
 * Params:
 *   new_bits: The new bits.
 *   n: The number of new bits to append.
 */
void BitArray::append(long new_bits, int n) {
  // TODO(smilli): Check to make sure it doesn't go out of bounds
  // Should I make this indices ints or longs?  How big will it go?
  assert(n <= LONG_BITS);
  int long_ind = bit_ind_to_long_ind(last_set_bit_ind + 1);
  int num_bits_set = 
    (last_set_bit_ind < 0) ? 0 : bit_offset(last_set_bit_ind) + 1;
  int num_bits_left = LONG_BITS - num_bits_set;
  if (num_bits_left < n) {
    bits[long_ind] = bits[long_ind] | (new_bits >> (n - num_bits_left));
    if (long_ind + 1 >= capacity) {
      resize();
    }
    bits[long_ind + 1] = bits[long_ind + 1] | (
      new_bits << (LONG_BITS - (n - num_bits_left)));
  } else if (num_bits_left >= n) {
    bits[long_ind] = bits[long_ind] | (new_bits << (num_bits_left - n));
  }
  last_set_bit_ind += n;
}

void BitArray::resize() {
  unsigned long* old_bits = bits;
  int old_capacity = capacity;
  capacity = old_capacity * 3 / 2;
  // TODO(smilli): check to make sure get memory
  bits = (unsigned long*) checked_malloc(capacity * sizeof(unsigned long));
  for (int i = 0; i < old_capacity; i++) {
    bits[i] = old_bits[i];
  }
  for (int i = old_capacity; i < capacity; i++) {
    bits[i] = 0;
  }
  free(old_bits);
}

/*
 * Shrink the size of the array to only hold the bits that are currently set.
 */
void BitArray::shrink_to_fit() {
  // TODO(smilli): check to make sure works
  int size = bit_ind_to_long_ind(last_set_bit_ind) + 1;
  bits = (unsigned long*) checked_realloc(bits, size);
  capacity = size;
}

/*
 * Convert index of bit to index of long that bit is in.
 */
int BitArray::bit_ind_to_long_ind(long bit_ind) {
  return floor((double) bit_ind / LONG_BITS);
}

/*
 * Get index of bit within a long.
 */
int BitArray::bit_offset(long bit_ind) {
  return bit_ind % LONG_BITS;
}

/*
 * Return a long with the n bits starting at bit index i as the least sig bits.
 *
 * Params:
 *   i: The index of the first bit to access.
 *   n: The number of bits to get.
 */
unsigned long BitArray::get(long i, int n) {
  assert(n < LONG_BITS);
  assert(i + n - 1 <= last_set_bit_ind);
  int long_ind = bit_ind_to_long_ind(i);
  int start_bit = bit_offset(i);
  int bits_past_start = LONG_BITS - start_bit;
  unsigned long ret = bits[long_ind];
  if (n <= bits_past_start) {
    ret = ret >> (bits_past_start - n);
    ret = ret & ((1 << n) - 1);
  } else {
    int num_bits_left = n - bits_past_start;
    ret = (ret & ((1 << bits_past_start) - 1)) << (num_bits_left);
    long bits_left = bits[long_ind + 1] >> (LONG_BITS - num_bits_left);
    bits_left = bits_left & ((1 << num_bits_left) - 1);
    ret = ret | bits_left;
  }
  return ret;
}
