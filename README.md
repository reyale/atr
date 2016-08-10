#ATR

ATR is a general purpose c++ utility library designed to reduce common c++ operations. 

##Requirements

* google test - if you want to compile the test suite
* gcc (g++) - I've been developing against 4.9.2, but C++11 compliant compilers should work

##pstring

pstring_i is a templated class that allows you to wrap string classes conforming to std::string.  This template provides the string functionality similar to that of python strings.  pstring_i is not designed to be fast but should not be overally inefficient.  Internally pstring_i does not allocate on the heap. Future work should extend pstring_i to expose custom allocators.

examples:

```
  #include <iostream>
  #include <util/pstring.h>

  atr::util::pstring test("abc_123");
  auto tokens = test.split('_');
  for(auto & token : tokens)
    std::cout << token << std::endl;
```

##tokenizer

tokenizer is a simple tokenizer akin to boost::tokenizer.  It's designed to be lightweight, returning tokens in the format requested.  As such tokens can be returned in native types or as lightweight (T::value_type* T::size_type) pairs with zero copy.  pstring_i internally uses tokenizer. 

examples:
```

  #include <string>
  #include <util/tokenizer.h>

  atr::util::string_tokenizer tokenizer('_');
  auto lightweight_tokens = tokenizer.tokenize<atr::util::string_tokenizer::token>("abc_123");
  auto string_tokens = tokenizer.tokenize<std::string>("abc_123");

```

##Dedication

Dedicated to my wife, because she asked me to while we were watching the Olympics.

##License

No warranty, no restrictions.  You can use this for private or commercial use, I don't care.
