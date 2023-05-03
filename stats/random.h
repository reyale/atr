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
      random_ng(Distribution& d, Distribution::result_type seed = std::random_device()()) : source(seed), distribution(d) { }

      auto next() { return distribution(source); }

      Source source;
      Distribution& distribution;
    };


    template < typename T, typename Source = std::mt19937 >
    class uniform_real_distribution : public random_ng<std::uniform_real_distribution<T>, Source> {
    public:
      using dist_t = std::uniform_real_distribution<T>;
      using base_t = random_ng<dist_t, Source>;

      uniform_real_distribution(T one, T two) : dist(one, two), base_t(dist) { }
      uniform_real_distribution(T one, T two, T seed) : dist(one, two), base_t(dist, seed) { }
      dist_t dist; 
    };


    class standard_uniform_distribution : public uniform_real_distribution<double> {
      using base_t = uniform_real_distribution<double>;

    public:
      standard_uniform_distribution() : base_t(0.0, 1.0) { }
      standard_uniform_distribution(dist_t::result_type seed) : base_t(0.0, 1.0, seed) { }
    };


    template < auto T, auto W, int prob = 50 > 
    class choice {
      static_assert(prob >= 0); 
      static_assert(prob <= 100); 

      using dist_t = standard_uniform_distribution;

    public:
      static constexpr double PROBABILITY = prob / 100.0;

      choice() : _dist() { }
      choice(dist_t::dist_t::result_type seed) : _dist(seed) { }

      auto choose() {
        if(_dist.next() > PROBABILITY)
          return W;

        return T;
      }

    private:
      dist_t _dist;
    };
}

}
