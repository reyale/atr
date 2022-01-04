#include "circular.h"

#include <iostream>


int main() {
  atr::collections::circular_buffer<int> buffer(5);
  buffer.push(10);
  buffer.push(20);
  buffer.push(30);
  assert(buffer.size() == 3);
  assert(!buffer.is_full());

  int* res = buffer.pop();
  assert(*res == 10);
  res = buffer.pop();
  assert(*res == 20);
  res = buffer.pop();
  assert(*res == 30);
 
  for(int i = 0; i < 5; ++i)
    buffer.push(i);

  assert(buffer.is_full());

  buffer.push(5);

  for(int i = 0; i < 5; ++i) {
    int item = *buffer.pop();
    assert(item == i+1);
  }

  for(int i = 0; i < 5; ++i)
    buffer.push(i);

  assert(buffer.is_full());
  buffer.resize(10);
  assert(!buffer.is_full());

  for(int i = 5; i < 10; ++i)
    buffer.push(i);  

  for(int i = 0; i < 10; ++i) {
    int item = *buffer.pop();
    assert(item == i);
  }

  buffer.push(1234);
  assert(*buffer.peek() == 1234);
  buffer.pop();

  for(int i = 0; i < 10 + 5; ++i) 
    buffer.push(i);

  for(int i = 0; i < 10; ++i) {
    int item = *buffer.pop();
    assert(item == i+5); 
  }

  return 0;
}
