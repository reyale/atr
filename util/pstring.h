#ifndef _PSTRING__H
#define _PSTRING__H

#include <string>
#include <algorithm>
#include <vector>

namespace atr {

namespace util {

  template < typename T >
  class pstring_i : public T {
  public:
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
 
    std::vector< pstring_i<T> > split() const {

    }

  protected:
  };

  typedef pstring_i<std::string> pstring;

}

}

#endif
