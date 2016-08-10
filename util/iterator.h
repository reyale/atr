#ifndef _ATR_ITERATOR__H
#define _ATR_ITERATOR__H

namespace atr {

  template < typename T >
  class rand_access_iterator_i {
    public:
      typedef rand_access_iterator_i<T> self_type;
      typedef T value_type;
      typedef std::forward_iterator_tag iterator_category;
      typedef std::ptrdiff_t difference_type;

      rand_access_iterator_i(T* ptr) : _ptr(ptr) { }
      self_type operator++() {  _ptr++; return *this; }
      self_type operator++(int junk) { self_type i = *this; _ptr++; return i; }
      T& operator*() { return *_ptr; }
      T* operator->() { return _ptr; }
      bool operator==(const self_type& rhs) { return _ptr == rhs._ptr; }
      bool operator!=(const self_type& rhs) { return _ptr != rhs._ptr; }

     private:
      T* _ptr;
  };

  template < typename T >
  class rand_access_const_iterator_i {
    public:
      typedef rand_access_const_iterator_i<T> self_type;
      typedef T value_type;
      typedef std::ptrdiff_t difference_type;
      typedef std::forward_iterator_tag iterator_category;

      rand_access_const_iterator_i(const T* ptr) : _ptr(ptr) { }
      self_type operator++() { _ptr++; return *this; } 
      self_type operator++(int junk) { self_type i = *this; _ptr++; return i; } 
      const T& operator*() { return *_ptr; }
      const T* operator->() { return _ptr; }
      bool operator==(const self_type& rhs) { return _ptr == rhs._ptr; }
      bool operator!=(const self_type& rhs) { return _ptr != rhs._ptr; }

    private:
      const T* _ptr;
  };

}

#endif
