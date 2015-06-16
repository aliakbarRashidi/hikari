#ifndef ARRAY_BIT_ARRAY_H
#define ARRAY_BIT_ARRAY_H

class BitArray {
  int capacity;
  long last_set_bit_ind;
  unsigned long* bits;
  int bit_ind_to_long_ind(long);
  int bit_offset(long);
  void resize();
  public:
    BitArray (long);
    ~BitArray();
    int get_capacity();
    void append(long, int);
    unsigned long get(long, int);
    void shrink_to_fit();
};

#endif // ARRAY_BIT_ARRAY_H
