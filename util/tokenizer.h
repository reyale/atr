#ifndef _ATR_TOKENIZER__H
#define _ATR_TOKENIZER__H

#include <vector>

namespace atr {

namespace util {

  /* 
   * This tokenizer returns lightweight tokens...
   * we probably want a tokenizer that returns the native type T
   */

  template < typename T >
  class tokenizer {
  public:
    struct token {
      token(const typename T::value_type* s, const typename T::size_type l) : start(s), len(l) { }
      const typename T::value_type* start;
      const typename T::size_type len;
    };

    tokenizer(char delim) : _delim(delim) { }

    template < typename W >
    std::vector<W> tokenize(const T & t) const {
      std::vector<W> result;
      tokenize(t, result);
      return result;
    }

    template < typename W >
    void tokenize(const T & t, std::vector<W> & result) const {
      result.clear();    
      const typename T::value_type* start = 0;
      typename T::size_type len = 0;
      for(auto& c : t) {
        if(c==_delim) {
          if(!start)
            continue;
          result.push_back(W(start, len));
          start = 0;
          len = 0;
          continue;
        }

        if(!start) {
          start = &c;
          len = 1;
          continue;
        }
        ++len;
      }

      if(len > 0)
        result.push_back(W(start, len));
    }

  private:
    const char _delim;    
  };

  typedef tokenizer<std::string> string_tokenizer;

  template < typename T >
  std::string token_to_string(const T & t) {
    return std::string(t.start, t.len);
  }

}

}

#endif
