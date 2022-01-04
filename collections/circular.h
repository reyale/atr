#pragma once

#include <cassert>
#include <stddef.h>
#include <iostream>

#include <vector>


namespace atr {

namespace collections {

  template < typename T >
  class circular_buffer {
  public:
	  circular_buffer(size_t capacity) : _read_mark(0), _write_mark(0), _item_count(0) { _data.reserve(capacity); }

    void resize(size_t capacity) {
      if(_data.capacity() >= capacity)
        return;

      std::vector<T> copied;
      copied.reserve(capacity);
      while(size() > 0) {
        auto item = *pop();
        std::cout << "copying item: " << item << std::endl;
        copied.push_back(item);
      }

      _read_mark = 0;
      _write_mark = copied.size(); 
      _data.reserve(capacity); 
      _data = copied;
      _item_count = copied.size();
    }

    void push(const T & t) {
      _data[_write_mark] = t;
      increment_write();
    }

    void push(T && t) {
      _data[_write_mark] = std::move(t);
      increment_write();
    }

    void increment_write() {
      _write_mark = (_write_mark + 1) % _data.capacity();
      if(_item_count == _data.capacity()) {
        _read_mark = (_read_mark + 1) % _data.capacity();
      } else {
        ++_item_count;
      }
    }

    bool is_full() const {
      return _item_count >= _data.capacity();
    }

    size_t size() const {
      return _item_count;
    }

    bool empty() const {
        return _item_count == 0;
    }

    T* pop() {
      if(_item_count == 0)
        return nullptr;

      --_item_count;
      auto item = &_data[_read_mark];
      _read_mark = (_read_mark + 1) % _data.capacity();
      return item;
    }

    const T* peek() const {
      if(_item_count == 0)
        return nullptr;

      return &_data[_read_mark];
    }

  protected:
    std::vector<T> _data;
    size_t _read_mark;
    size_t _write_mark;
    size_t _item_count;
  };

}

}
