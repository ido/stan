#ifndef STAN__MATH__MIX__MAT__FUNCTOR__GRAD_TR_MAT_TIMES_HESSIAN_HPP
#define STAN__MATH__MIX__MAT__FUNCTOR__GRAD_TR_MAT_TIMES_HESSIAN_HPP

#include <stan/math/fwd/core.hpp>
#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <stan/math/rev/core.hpp>
#include <stan/math/mix/mat/functor/gradient_dot_vector.hpp>
#include <vector>

namespace stan {

  namespace agrad {

    using Eigen::Dynamic;

    // FIXME: add other results that are easy to extract
    // // N * (fwd(2) + bk)
    template <typename F>
    void
    grad_tr_mat_times_hessian(const F& f,
                              const Eigen::Matrix<double, Dynamic, 1>& x,
                              const Eigen::Matrix<double, Dynamic, Dynamic>& M,
                              Eigen::Matrix<double, Dynamic, 1>& grad_tr_MH) {
      using Eigen::Matrix;
      start_nested();
      try {
        grad_tr_MH.resize(x.size());

        Matrix<var, Dynamic, 1> x_var(x.size());
        for (int i = 0; i < x.size(); ++i)
          x_var(i) = x(i);

        Matrix<fvar<var>, Dynamic, 1> x_fvar(x.size());

        var sum(0.0);
        Matrix<double, Dynamic, 1> M_n(x.size());
        for (int n = 0; n < x.size(); ++n) {
          for (int k = 0; k < x.size(); ++k)
            M_n(k) = M(n, k);
          for (int k = 0; k < x.size(); ++k)
            x_fvar(k) = fvar<var>(x_var(k), k == n);
          fvar<var> fx;
          fvar<var> grad_fx_dot_v;
          gradient_dot_vector<fvar<var>, double>(f, x_fvar, M_n, fx,
                                                 grad_fx_dot_v);
          sum += grad_fx_dot_v.d_;
        }

        stan::agrad::grad(sum.vi_);
        for (int i = 0; i < x.size(); ++i)
          grad_tr_MH(i) = x_var(i).adj();
      } catch (const std::exception& e) {
        stan::agrad::recover_memory_nested();
        throw;
      }
      stan::agrad::recover_memory_nested();
    }


  }  // namespace agrad
}  // namespace stan
#endif
