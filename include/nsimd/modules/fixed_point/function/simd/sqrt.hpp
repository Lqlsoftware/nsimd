/*

Copyright (c) 2019 Agenium Scale

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef NSIMD_MODULES_FIXED_POINT_FUNCTION_SIMD_SQRT_HPP
#define NSIMD_MODULES_FIXED_POINT_FUNCTION_SIMD_SQRT_HPP

#include "nsimd/modules/fixed_point/fixed.hpp"

namespace nsimd {
namespace fixed_point {
template <unsigned char _lf, unsigned char _rt>
NSIMD_INLINE fpsimd_t<_lf, _rt> simd_sqrt(const fpsimd_t<_lf, _rt> &a) {
  typedef typename fp_t<_lf, _rt>::value_type val_t;
  typedef typename fp_t<_lf, _rt>::simd_logical log_t;
  fpsimd_t<_lf, _rt> x0, x1;
  fpsimd_t<_lf, _rt> two;
  two._raw = nsimd::set1(constants::two<_lf, _rt>()._raw, val_t());
  x0 = a;
  // For the few cases tested, 10 iterations is more than enough to converge
  fpsimd_t<_lf, _rt> zero;
  zero._raw = nsimd::xorb( zero._raw , zero._raw , val_t() );
  fpsimdl_t<_lf,_rt> zero_output = simd_eq(two , zero );
  fpsimd_t<_lf, _rt> res;
  for (int i = 0; i < 10; ++i) {
    fpsimdl_t<_lf,_rt> is_zero = simd_eq(x0 , zero );
    zero_output = simd_orl( zero_output , is_zero );
    x0 = simd_if_else1( is_zero , two , x0 );
    x1 = (x0 + (a / x0));
    x1._raw = nsimd::shr( x1._raw , 1 , val_t() );
    x0 = x1;
  }

  x0 = simd_if_else1( zero_output , zero , x0 );
  return x0;
}

} // namespace fixed_point
} // namespace nsimd

#endif
