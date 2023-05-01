#pragma once 

#include <random>

/*
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 10.0);
*/

namespace atr {

namespace stats {

    template < typename Distribution, typename Source = std::mt19937 >
    class random_ng {
    public:
      random_ng(Distribution& d) : source(rd()), distribution(d) { }

      auto next() { return distribution(source); }

      std::random_device rd;  
      Source source;
      Distribution& distribution;
    };

    template < typename T, typename Source = std::mt19937 >
    class uniform_real_distribution : public random_ng<std::uniform_real_distribution<T>, Source> {
    using distribution_t = std::uniform_real_distribution<T>;
    using base_t = random_ng<distribution_t, Source>;
    

    public:
      uniform_real_distribution(T one, T two) : dist(one, two), base_t(dist) { }
      distribution_t dist; 
    };

}

}
