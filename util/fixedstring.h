#ifndef _ATR_FIXEDSTRING__H
#define _ATR_FIXEDSTRING__H

#include <string>
#include <assert.h>

#include "util/iterator.h"

namespace atr {

namespace util {

  template < std::size_t SIZE >
  class fixed_string {
  public:
    typedef char value_type;
    typedef std::size_t size_type;

    typedef atr::rand_access_iterator_i<value_type> iterator;
    typedef atr::rand_access_const_iterator_i<value_type> const_iterator;
    
    static const std::size_t npos = std::string::npos;
    static const std::size_t max_size = SIZE;

    fixed_string() : _size(0) { static_assert(max_size > 0, "size must be > 0"); }
    fixed_string(const value_type* data) : _size(0) {
      do {
        if(data[_size] == '\0' || _size >= max_size)
          break;
        _data[_size] = data[_size];
        ++_size;
      } while(true);
    }

    fixed_string(const fixed_string & other) : _size(other._size) {
      ::strncpy(_data, other._data, _size);
    }

    fixed_string(fixed_string && other) {
      _size = other._size;
      ::strncpy(_data, other._data, _size); 
    }

    fixed_string(const value_type* start, size_type len) {
      len = std::min(len, SIZE);
      ::strncpy(_data, start, len);
      _size = len;
    }

    fixed_string& operator=(const fixed_string & other) {
      _size = other._size;
      ::strncpy(_data, other._data, _size);
      return *this;
    }

    fixed_string& operator=(fixed_string && other) {
      _size = other._size;
      ::strncpy(_data, other._data, _size);
      return *this;
    }

    size_type size() const { return _size; } 

    value_type& operator[](size_type index) {
      return _data[index];
    }
   
    const value_type& operator[](size_type index) const {
      return _data[index];
    }

    bool operator==(const fixed_string& other) const {
      if(size()!=other.size()) 
        return false;

      for(fixed_string::size_type i = 0; i < size(); ++i) {
        if(_data[i] != other[i])
          return false;
      }

      return true;
    }

    iterator begin() {
      return iterator(&_data[0]);
    }

    iterator end() {
      return iterator(&_data[_size]);
    }

    const_iterator begin() const {
      return const_iterator(&_data[0]);
    }

    const_iterator end() const {
      return const_iterator(&_data[_size]);
    }

  private:
    friend std::ostream& operator<<(std::ostream &os, const fixed_string& fs) {
      for(auto & f : fs)
         os << f;
      return os;
    }
    value_type _data[SIZE];
    size_type        _size;
  };

}

}

#endif
