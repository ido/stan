#ifndef STAN__MATH__PRIM__ARR__FUN__REP_ARRAY_HPP
#define STAN__MATH__PRIM__ARR__FUN__REP_ARRAY_HPP

#include <vector>

#include <stan/math/prim/scal/err/check_nonnegative.hpp>

namespace stan {

  namespace math {

    template <typename T>
    inline std::vector<T>
    rep_array(const T& x, int n) {
      using stan::math::check_nonnegative;
      check_nonnegative("rep_array", "n", n);
      return std::vector<T>(n,x);
    }

    template <typename T>
    inline std::vector<std::vector<T> >
    rep_array(const T& x, int m, int n) {
      using std::vector;
      using stan::math::check_nonnegative;
      check_nonnegative("rep_array", "rows", m);
      check_nonnegative("rep_array", "cols", n);
      return vector<vector<T> >(m, vector<T>(n, x));
    }

    template <typename T>
    inline std::vector<std::vector<std::vector<T> > >
    rep_array(const T& x, int k, int m, int n) {
      using std::vector;
      using stan::math::check_nonnegative;
      check_nonnegative("rep_array", "shelfs", k);
      check_nonnegative("rep_array", "rows", m);
      check_nonnegative("rep_array", "cols", n);
      return vector<vector<vector<T> > >(k,
                                         vector<vector<T> >(m,
                                                            vector<T>(n, x)));
    }

  }
}

#endif
