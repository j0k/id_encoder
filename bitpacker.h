#include <vector>
#include <bitset>
#include <bits/stdc++.h>

#include "pack_types.h"

using std::vector;
using std::cout;
using std::endl;
using std::bitset;

class membuf : public std::basic_streambuf<char> {
public:
  membuf(const uint8_t *p, size_t l) {
    setg((char*)p, (char*)p, (char*)p + l);
  }
};

class memstream : public std::istream {
public:
  memstream(const uint8_t *p, size_t l) :
    std::istream(&_buffer),
    _buffer(p, l) {
    rdbuf(&_buffer);
  }

private:
  membuf _buffer;
};

typedef char bit;
typedef vector<bit> bits;

bitset<8> to_bitset(unsigned char byte);
bits code2bits(tcode code);
bits codes2bits(vector<tcode> codes);
