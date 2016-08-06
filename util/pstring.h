#ifndef _ATR_PSTRING__H
#define _ATR_PSTRING__H

#include <string>
#include <algorithm>
#include <vector>

#include "tokenizer.h"

namespace atr {

namespace util {

  template < typename T >
  class pstring_i : public T {
  public:
    pstring_i() : T() { }
    pstring_i(const char* in) : T(in) { }
    pstring_i(const char* in, typename T::size_type sz) : T(in, sz) { }
 
    pstring_i<T> lower() const {
      auto str_copy = *this;
      std::transform(str_copy.begin(), str_copy.end(), str_copy.begin(), ::tolower);  
      return str_copy;
    }

    pstring_i<T> upper() const {
      auto str_copy = *this;
      std::transform(str_copy.begin(), str_copy.end(), str_copy.begin(), ::toupper);
      return str_copy;
    }

    pstring_i<T> lstrip(typename T::value_type val) const {
      const auto loc = T::find_first_not_of(val);
      if (loc==T::npos)
        return pstring_i<T>();
      return operator()(loc, T::size());
    }
 
    std::vector< pstring_i<T> > split(char delim) const {
      tokenizer< pstring_i<T> > tokenizer(delim);
      auto tokens = tokenizer.tokenize(*this);
      
      std::vector< pstring_i<T> > result;
      for(auto & token : tokens)
        result.push_back(pstring_i<T>(token.start, token.len)); 

      return result;
    }

    auto operator[](long index) const { 
      if(index >= 0)
        return T::operator[](index);
      return T::operator[](T::size() + index);
    }

    auto operator()(long index) const {
      return operator[](index);
    }

    auto operator()(long start, long end) const {
      start = start >=0 ? start : T::size() + start;
      end = end >= 0 ? end : T::size() + end;

      if(start >= T::size() || end < 0 || end <= start)
        return pstring_i<T>();

      return pstring_i<T>(&T::operator[](start), end - start); 
    }

  };

  typedef pstring_i<std::string> pstring;

}

}

#endif
