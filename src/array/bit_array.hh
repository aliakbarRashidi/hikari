#ifndef ARRAY_BIT_ARRAY_H
#define ARRAY_BIT_ARRAY_H

class BitArray {
  private:
    long arr_long_capacity;
    long last_set_bit_ind = -1;
    unsigned long* bits;
    int bit_ind_to_long_ind(long);
    int bit_offset(long);
    void set(unsigned long, int, int);
    unsigned long set_bits_in_long(unsigned long, unsigned long, int, int);
    void resize();
  public:
    BitArray (long);
    ~BitArray();
    long long_capacity();
    long bit_capacity();
    long size();
    void append(unsigned long, int);
    void swap(long, long, int);
    unsigned long get(long, int);
    void shrink_to_fit();
};

#endif // ARRAY_BIT_ARRAY_H
