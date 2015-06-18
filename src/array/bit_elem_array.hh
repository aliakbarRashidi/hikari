#ifndef ARRAY_BIT_ELEM_ARRAY_H
#define ARRAY_BIT_ELEM_ARRAY_H

#include "bit_array.hh"

/*
 * An array of elements that are all a specified number of bits.
 */
class BitElemArray {
  private:
    std::unique_ptr<BitArray> bit_array;
    bool sorted;
    long max_storable_num;
    void quicksort(int, int);
    int partition(int, int);
    int rand_in_range(int, int);
    int binary_search(unsigned long elem, int, int);
  public:
    int bits_in_elem;
    BitElemArray (int, long);
    long size();
    long capacity();
    void append(unsigned long);
    unsigned long get(int);
    void swap(int, int);
    void sort();
    int index_of(unsigned long elem);
};

#endif // ARRAY_BIT_ELEM_ARRAY_H
