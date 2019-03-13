#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

#include <queue>
#include <functional>
#define M32 32
#define M8 8

using namespace std;

#define MIN(a,b) (a <= b) ? a : b;

#define FOR_IT(it,argv) \
for ( auto it = argv.begin(); it != argv.end(); it++ )

#define FOREACH_CHAR(ch, chars) \
char * ch = (char*) chars; \
while (* ch != 0)

#define CONCAT(AB,A,B) \
vector<int> AB;        \
AB.reserve( A.size() + B.size() );         \
AB.insert( AB.end(), A.begin(), A.end() ); \
AB.insert( AB.end(), B.begin(), B.end() );

#define PDEBUG_CODE(code) \
FOR_IT(it, code){ \
  cout << (char) (*it + (int)'0'); \
};

#define FOR(i,start,stop) for(int i=start; i<stop; i++)
//typedef pair<char, int> tcode;
struct symbol {
    int   w;
    vector<int> ref_code;
    bool operator> (const symbol &ref) const {return w > ref.w;}
};

typedef vector<char> tcode;
struct pair_code{
  char letter; // first
  tcode code;
};

struct t_code_desc{
  int len;
  int num;
  bool operator< (const t_code_desc &ref) const {
    return (len < ref.len) & (num < ref.num);
  }
};


//typedef pair<char, vector<char>> pair_code;
typedef vector<pair_code> huffman_codes;
typedef priority_queue<symbol, std::deque<symbol>, std::greater<symbol> > djikstra_heap;

class Huffman{
  map<char,int> weights;

  map<t_code_desc, char> mdecode;
  map<char,tcode> mcode, mcodeR;
  huffman_codes codes;
  huffman_codes codesR;

  public:
    void calc_weight(const char * text){
      FOREACH_CHAR(c, text){
        if (weights.count(*c) > 0)
          weights[*c] ++;
        else
          weights[*c] = 1;

        c++;
      }
    }

    void print_weights(){
      FOR_IT(it, weights)
      {
        cout << it->first
             << ':'
             << it->second
             << std::endl ;
      }
    }

    void create_dict(){
      djikstra_heap heap;
      int i = 0;

      FOR_IT(it, weights)
      {
        vector<int> v = {i++};
        symbol s{it->second, v};
        heap.push(s);

        tcode seq; // empty sequence
        pair_code code = {it->first, seq};
        codes.push_back(code);
      }

      if (heap.size() == 1){
        // only one symbol

      }
      while(heap.size() > 1){
        symbol lo = heap.top(); heap.pop();
        symbol hi = heap.top(); heap.pop();

        for (int i: lo.ref_code)
          codes[i].code.push_back(0);

        for (int i: hi.ref_code)
          codes[i].code.push_back(1);

        CONCAT(vec, lo.ref_code, hi.ref_code);
        heap.push({lo.w + hi.w, vec});
      }

      //codesR = codes.copy();
      copy(codes.begin(), codes.end(), back_inserter(codesR));

      FOR_IT(it,codesR){
       reverse((*it).code.begin(), (*it).code.end());
      }

      FOR_IT(it,codes){
       reverse((*it).code.begin(),(*it).code.end());
      }
    }

    void print_codes(){
      FOR_IT(it, codes){
        cout << it->letter << " : " << weights[it->letter] << "\t: ";
        cout << code2num( it->code ).num << "\t: ";
        FOR_IT(itc, it->code)
        {
          cout << (char) (*itc+(int)'0');
        }
        cout << endl;
      }
      cout << "reversed" << endl;
      FOR_IT(it, codesR){
        cout << it->letter << " : " << weights[it->letter] << "\t: ";
        cout << code2num( it->code ).num << "\t: ";
        FOR_IT(itc, it->code)
        {
          cout << (char) (*itc+(int)'0');
        }
        cout << endl;
      }
    }

    void table2file(ofstream & file){
      FOR_IT(it, codes){
        file << it->letter << "";
        FOR_IT(itc, it->code)
        {
          file << (char) (*itc + (int)'0');
        }
        file << endl;
      }
    }

    void file2table(ifstream & file){
    }

    void encode(ifstream & fin, ofstream & fout){
      vector<bitset<M8>> bitseq;
      string line;
      vector<char> enc;

      FOR_IT(it, codes){
        mcode[it->letter] = it->code; // mcode['a'] = {0,1,1,0,1}
      }

      FOR_IT(it, codesR){
        mcodeR[it->letter] = it->code; // mcode['a'] = {0,1,1,0,1}
      }

      tcode rawcode;
      int i = 0;
      fout.write((char*)(&i), sizeof(i));

      while ( getline (fin, line) ){
        const char * chars = line.c_str();
        cout << chars << endl;

        FOREACH_CHAR(c, chars){
          tcode code = mcode[*c];
          i++;
          cout << "code " << *c << " " ;
          PDEBUG_CODE(code);
          cout << endl;
          FOR_IT(it, code){
            rawcode.push_back(*it);
          }

          if (rawcode.size()>=8)
            bits2file(fout, rawcode, M8);
          c++;
        }
        bits2file(fout, rawcode, rawcode.size());
        fout.seekp(0);
        //i *= 256;
        fout.write((char*)(&i), sizeof(i));
      }
    }

    void bits2file(ofstream & fout, tcode & rawcode, const char codesize){
      if (rawcode.size()>=codesize){
        bitset<M8> bits;
        FOR(i, 0, codesize){
          bits[i] = rawcode[i];
        }
        cout << bits << "~" << bits.to_ulong() << endl;
        char bytechunk = (char) bits.to_ulong();
        rawcode.erase (rawcode.begin(), rawcode.begin()+codesize);

        fout.write(&bytechunk, sizeof(bytechunk));
      }
    }

    t_code_desc code2num(vector<char> code){
      int num = 0;
      FOR_IT(it, code){
        num <<= 1;
        num |= *it;
      }

      return {code.size(), num};
    }

    //mdecode << mcodeR;
    void prepare_decode_tbl(){
      // dict[(len, int (binary form 10101011 of code)] -> {char}
      for (auto pair_code: mcodeR){
        t_code_desc ln = code2num(pair_code.second);
        mdecode[ln] = pair_code.first;
      }

      //mdecode
    }

    void decode(ifstream & file){
      prepare_decode_tbl();
      unsigned int n;

      tcode buffer;
      file.read((char *) &n, sizeof(int));

      cout << n << endl;

      char raw  = 0;
      int  i    = 0;
      unsigned int num = 0;
      unsigned int mask = 0x00000000;

      char memblock2[4];
      while(!file.eof() && i!=n ){
        char raw  = 0;
        file.read(&raw, sizeof(char));

        FOR(j,0,8){
          char dig = 1;
          buffer.push_back(((dig << j) & raw) > 0);
        }
        //cout << raw << endl;
      }


      unsigned int code = 0, iw = 0;
      FOR_IT(it,buffer){
        iw ++ ;
        code <<= 1;
        code |= *it;
        const t_code_desc desc = {(int) iw, code};
        if(mdecode.count(desc)>0){
          cout << mdecode[desc];
          i ++ ;
          code = 0;
          iw   = 0;
          //break;
        }
        if(i == n)
          break;
      }
      cout << endl;

      //PDEBUG_CODE(buffer);
      int pos;
      FOR_IT(it, buffer){ \
        pos ++;
        cout << (char) (*it + (int)'0'); \
        if (pos % 8 == 0)
          cout << " ";
      };
    }

};
