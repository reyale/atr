#ifndef _ATR_DATA_VEC__H
#define _ATR_DATA_VEC__H

#include <string>
#include <vector>
#include <unordered_set>
#include <typeinfo>
#include <initializer_list>

namespace atr {

namespace collections {

namespace data {

  enum dtype {
    INT,
    DOUBLE,
    OBJ
  };

  class vec_generic {
    public:
      vec_generic(const std::type_info& in) : _info(in) { }
 
      dtype type;

    private:
      const std::type_info& _info;
  };

  template < typename T >
  class vec_i : public vec_generic, public std::vector<T> {
    typedef std::vector<T> ParentVec;

    public:
      vec_i() : vec_generic(typeid(T)), ParentVec() { }
      vec_i(size_t size) : vec_generic(typeid(T)), ParentVec(size) { }
      vec_i(std::initializer_list<T> l) : vec_generic(typeid(T)), ParentVec(l) { }

      template < typename W >
      vec_i<bool> operator==(const W & w) const {
        vec_i<bool> result(ParentVec::size());
        for(size_t i = 0; i < result.size(); ++i)
          result[i] = w == ParentVec::operator[](i);
        return result;
      }

      template < typename W >
      vec_i<bool> isin(const W & w) const {
        std::unordered_set<typename W::value_type> compare; 
        for(size_t i = 0; i < w.size(); ++i)
          compare.insert(w[i]); 

        vec_i<bool> result(ParentVec::size());
        for(size_t i = 0; i < ParentVec::size(); ++i) {
          if(compare.find(ParentVec::operator[](i)) != compare.end())         
            result[i] = true;
          else
            result[i] = false;
        }
        return result;
      }

    private:
  };

  typedef vec_i<int> vec_int;
  typedef vec_i<double> vec_double;
  typedef vec_i<std::string> vec_obj;
  typedef vec_i<bool> vec_bool;

} //end data

} //end collections 

} //end atr

#endif
