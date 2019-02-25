# id_encoder
generate dict, then encode and decode

!!! in work stage !!!
# run
```
$ g++ decoder.cpp -o decoder
$ ./decoder text_examples/text_01.txt table.tbl file.out
  : 6   : 14    : 1110
a : 3   : 25    : 11001
c : 1   : 106   : 1101010
d : 1   : 49    : 110001
e : 3   : 30    : 11110
f : 3   : 27    : 11011
g : 1   : 107   : 1101011
h : 2   : 63    : 111111
i : 8   : 4     : 100
l : 1   : 42    : 101010
m : 2   : 23    : 10111
n : 35  : 0     : 0
o : 2   : 22    : 10110
p : 1   : 124   : 1111100
r : 1   : 125   : 1111101
s : 2   : 20    : 10100
t : 1   : 43    : 101011
u : 1   : 52    : 110100
x : 1   : 48    : 110000
this is annnnnnnnnnnnnnnniiiiinnnnnnnnnnnnnnnn example for huffman encoding
code t 101011
code h 111111
11110101~245
code i 100
code s 10100
10011111~159
code   1110
01110010~114
code i 100
code s 10100
00101001~41
code   1110
code a 11001
00110111~55
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
00000001~1
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
00000000~0
code n 0
code i 100
code i 100
code i 100
10010010~146
code i 100
code i 100
00100100~36
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
00000000~0
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
code n 0
00000000~0
code   1110
code e 11110
11110111~247
code x 110000
code a 11001
10000110~134
code m 10111
11011001~217
code p 1111100
00111111~63
code l 101010
code e 11110
11010101~213
code   1110
code f 11011
10111011~187
code o 10110
11011101~221
code r 1111101
10111110~190
code   1110
code h 111111
11110111~247
code u 110100
00101111~47
code f 11011
code f 11011
01111011~123
code m 10111
code a 11001
11110111~247
code n 0
code   1110
11101001~233
code e 11110
code n 0
code c 1101010
10011110~158
code o 10110
01010101~85
code d 110001
00011011~27
code i 100
code n 0
code g 1101011
01100011~99
00001101~13
75
this is annnnnnnnnnnnnnnniiiiinnnnnnnnnnnnnnnn example for huffman encoding
101011111111100101001110100101001110110010000000000000000100100100100100000000000000000011101111011000011001101111111100101010111101110110111011011111011110111111110100110111101110111110010111011110011010101011011000110001101011000000000000

```
