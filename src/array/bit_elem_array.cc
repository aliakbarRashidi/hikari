#include <memory>
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
unsigned long BitElemArray::get(int i) {
  return bit_array->get((long) i * bits_in_elem, bits_in_elem);
}

/*
 * Swap i-th and j-th element.
 */
void BitElemArray::swap(int i, int j) {
  bit_array->swap(
    (long) i * bits_in_elem, (long) j * bits_in_elem, bits_in_elem); 
}

/*
 * Sort array.  Array is shrunk before sorting.
 */
void BitElemArray::sort() {
  bit_array->shrink_to_fit();
  quicksort(0, size() - 1);
}

void BitElemArray::quicksort(int lo, int hi) {
  if (hi - lo < 1) {
    return;
  }
  int pivot_ind = partition(lo, hi);
  quicksort(lo, pivot_ind - 1);
  quicksort(pivot_ind + 1, hi);
}

int BitElemArray::partition(int lo, int hi) {
  int pivot_ind = rand_in_range(lo, hi);
  long pivot_val = get(pivot_ind);
  swap(pivot_ind, hi);
  int new_pivot_ind = lo;
  for (int i = lo; i < hi; i++) {
    if (get(i) < pivot_val) {
      swap(i, new_pivot_ind);
      new_pivot_ind++;
    }
  } 
  swap(new_pivot_ind, hi);
  return new_pivot_ind;
}

/*
 * Generates a random integer in the given range (inclusive).
 *
 * Params:
 *  min: The start of the range.
 *  max: The end of the range.
 */
int BitElemArray::rand_in_range(int min, int max) {
  return min + (rand() % (max - min + 1));
}
