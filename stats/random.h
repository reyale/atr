#pragma once 

#include <random>

/*
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 10.0);
*/

namespace atr {

namespace stats {

    namespace source {
      using mersenne_twister = std::mt19937;
    }

    template < typename Distribution, typename Source = source::mersenne_twister > 
    class random_ng {
    public:
      random_ng(Distribution& d, Distribution::result_type seed = std::random_device()()) : source(seed), distribution(d) { }

      auto next() { return distribution(source); }

      Source source;
      Distribution& distribution;
    };


    template < typename T = double, typename Source = source::mersenne_twister > 
    class uniform_real_distribution : public random_ng<std::uniform_real_distribution<T>, Source> {
    public:
      using dist_t = std::uniform_real_distribution<T>;
      using base_t = random_ng<dist_t, Source>;

      uniform_real_distribution(T one, T two) : dist(one, two), base_t(dist) { }
      uniform_real_distribution(T one, T two, T seed) : dist(one, two), base_t(dist, seed) { }

      dist_t dist; 
    };


    template < typename T = double, typename Source = source::mersenne_twister > 
    class standard_uniform_distribution : public uniform_real_distribution<T, Source> {
      using base_t = uniform_real_distribution<T>;

    public:
      standard_uniform_distribution() : base_t(0.0, 1.0) { }
      standard_uniform_distribution(base_t::dist_t::result_type seed) : base_t(0.0, 1.0, seed) { }
    };

  
    template < typename T = double, typename Source = source::mersenne_twister > 
    class normal_distribution : public random_ng<std::normal_distribution<T>, Source> {
    public:
      using dist_t = std::normal_distribution<T>;
      using base_t = random_ng<dist_t, Source>;

      normal_distribution(T mean, T mu) : dist(mean, mu), base_t(dist) { }
      normal_distribution(T mean, T mu, T seed) : dist(mean, mu), base_t(dist, seed) { }

      dist_t dist; 
    };
    
    template < typename T = double, typename Source = source::mersenne_twister > 
    class standard_normal_distribution : public normal_distribution<T, Source> {
      using base_t = normal_distribution<T, Source>;

      standard_normal_distribution() : base_t(0.0, 1.0) { }
      standard_normal_distribution(base_t::dist_t::result_type seed) : base_t(0.0, 1.0, seed) { }
    };


    //start distribution utils

    template < auto T, auto W, int prob = 50 > 
    class choice {
      static_assert(prob >= 0); 
      static_assert(prob <= 100); 

      using dist_t = standard_uniform_distribution<double>;

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
