#ifndef ARRAY_BIT_ARRAY_H
#define ARRAY_BIT_ARRAY_H

class BitArray {
  long arr_long_capacity;
  long last_set_bit_ind = -1;
  unsigned long* bits;
  int bit_ind_to_long_ind(long);
  int bit_offset(long);
  void resize();
  public:
    BitArray (long);
    ~BitArray();
    long long_capacity();
    long bit_capacity();
    long size();
    void append(long, int);
    unsigned long get(long, int);
    void shrink_to_fit();
};

#endif // ARRAY_BIT_ARRAY_H
