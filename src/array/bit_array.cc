#include <math.h>
#include <assert.h>
#include "bit_array.hh"
#include "../util/memory.hh"

const int BITS_IN_BYTE = 8;
const int LONG_BITS = BITS_IN_BYTE * sizeof(long);

/*
 * Construct a BitArray.
 *
 * Params:
 *  num_bits: The number of bits in the array.
 */
BitArray::BitArray(long num_bits) {
  arr_long_capacity = ceil((double) num_bits / LONG_BITS);
  bits = (unsigned long*) checked_malloc(
      arr_long_capacity * sizeof(unsigned long));
  for (int i = 0; i < arr_long_capacity; i++) {
    bits[i] = 0;
  }
}

BitArray::~BitArray() {
  free(bits);
}

/*
 * Get number of longs array can currently store.
 */
long BitArray::long_capacity() {
  return arr_long_capacity;
}

/*
 * Get number of bits array can currently store.
 */
long BitArray::bit_capacity() {
  return arr_long_capacity * LONG_BITS;
}

/*
 * Get number of bits set in array.
 */
long BitArray::size() {
  return last_set_bit_ind + 1;
}

/*
 * Add the n least significant bits of new_bits to bit array.
 *
 * Params:
 *   new_bits: The new bits.
 *   n: The number of new bits to append.
 */
void BitArray::append(unsigned long new_bits, int n) {
  set(new_bits, last_set_bit_ind + 1, n);
  last_set_bit_ind += n;
}

/*
 * Set n bits in the array.
 *
 * Params:
 *  new_bits: The values of the bits to set.
 *  start: The bit index to start in the array.
 *  n: Number of least sig bits to take form new_bits and set in array.
 */
void BitArray::set(unsigned long new_bits, int start, int n) {
  assert(n <= LONG_BITS);
  int long_ind = bit_ind_to_long_ind(start);
  if (long_ind >= arr_long_capacity) {
    resize();
  }
  int num_bits_set = bit_offset(start);
  int num_bits_left = LONG_BITS - num_bits_set;
  if (num_bits_left < n) {
    bits[long_ind] = set_bits_in_long(
        bits[long_ind], new_bits, num_bits_set, num_bits_left);
    if (long_ind + 1 >= arr_long_capacity) {
      resize();
    }
    bits[long_ind + 1] = set_bits_in_long(
        bits[long_ind + 1], new_bits, 0, n - num_bits_left);
  } else if (num_bits_left >= n) {
    bits[long_ind] = set_bits_in_long(
        bits[long_ind], new_bits, num_bits_set, n);
  }
}

/*
 * Return a new long with a range of bits set.
 *
 * Params:
 *  bits: The long to set bits in.
 *  new_bits: The values of the bits to set.
 *  offset: The index of the bit in the long to start setting at.
 *  n: Number of least sig bits to take from new_bits and set in bits.
 */
unsigned long BitArray::set_bits_in_long(
    unsigned long bits, unsigned long new_bits, int offset, int n) {
  // TODO(smilli): rename start to offset
  assert(offset + n - 1 < LONG_BITS);
  unsigned long start_mask = ((1 << offset) - 1) << (LONG_BITS - offset);
  int num_bits_left_at_end = LONG_BITS - offset - n;
  unsigned long end_mask = (1 << num_bits_left_at_end) - 1;
  unsigned long mask = start_mask + end_mask;
  bits = (bits & mask) | (new_bits << (LONG_BITS - n  - offset));
  return bits;
}

void BitArray::resize() {
  unsigned long* old_bits = bits;
  int old_capacity = arr_long_capacity;
  arr_long_capacity = old_capacity * 3 / 2;
  bits = (unsigned long*) checked_malloc(arr_long_capacity * sizeof(unsigned long));
  for (int i = 0; i < old_capacity; i++) {
    bits[i] = old_bits[i];
  }
  for (int i = old_capacity; i < arr_long_capacity; i++) {
    bits[i] = 0;
  }
  free(old_bits);
}

/*
 * Shrink the size of the array to only hold the bits that are currently set.
 */
void BitArray::shrink_to_fit() {
  int size = bit_ind_to_long_ind(last_set_bit_ind) + 1;
  bits = (unsigned long*) checked_realloc(bits, size);
  arr_long_capacity = size;
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
  // Check b/c last_set_bit_ind is less than 0 at start.
  // Prob a better way to do this.
  // TODO(smilli): I don't need this
  return (bit_ind < 0) ? 0 : bit_ind % LONG_BITS;
}

/*
 * Return a long with the n bits starting at bit index i as the least sig bits.
 *
 * Params:
 *   i: The index of the first bit to access.
 *   n: The number of bits to get.
 */
unsigned long BitArray::get(long i, int n) {
  assert(n <= LONG_BITS);
  assert(i + n - 1 <= last_set_bit_ind);
  int long_ind = bit_ind_to_long_ind(i);
  int start_bit = bit_offset(i);
  int bits_past_start = LONG_BITS - start_bit;
  unsigned long ret = bits[long_ind];
  if (n <= bits_past_start) {
    if (n < LONG_BITS) {
      ret = ret >> (bits_past_start - n);
      ret = ret & ((1 << n) - 1);
    }
  } else {
    int num_bits_left = n - bits_past_start;
    ret = (ret & ((1 << bits_past_start) - 1)) << (num_bits_left);
    long bits_left = bits[long_ind + 1] >> (LONG_BITS - num_bits_left);
    bits_left = bits_left & ((1 << num_bits_left) - 1);
    ret = ret | bits_left;
  }
  return ret;
}
