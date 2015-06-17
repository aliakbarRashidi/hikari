#include <memory>
#include <iostream>
#include <math.h>
#include <assert.h>
#include "bit_elem_array.hh"

/*
 * Construct a BitElemArray.
 *
 * Params:
 *  bits_per_elem: Number of bits in each element.
 *  num_elems: The number of elements to allocate space for.
 */
BitElemArray::BitElemArray(int bits_per_elem, long num_elems) {
  bits_in_elem = bits_per_elem;
  max_storable_num  = (1 << bits_per_elem) - 1;
  bit_array.reset(new BitArray(bits_in_elem * num_elems)); 
}

/*
 * The number of elements in the array.
 */
long BitElemArray::size() {
  return bit_array->size() / bits_in_elem; // should always be an int
}

/*
 * Returns the number of elements possible to store
 */
long BitElemArray::capacity() {
  return floor(bit_array->bit_capacity() / bits_in_elem);
}

/*
 * Appends the bits_in_elem least significant bits of element to array.
 *
 * Params:
 *  element: The element to append.
 */
void BitElemArray::append(long element) {
  assert(element <= max_storable_num);
  bit_array->append(element, bits_in_elem);
}

/*
 * Get the i-th element.
 *
 * Params:
 *  i: Index of element.
 */
unsigned long BitElemArray::get(long i) {
  return bit_array->get(i * bits_in_elem, bits_in_elem);
}
