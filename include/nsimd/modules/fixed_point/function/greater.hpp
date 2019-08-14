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

#ifndef NSIMD_MODULES_FUNCTION_GREATER_HPP
#define NSIMD_MODULES_FUNCTION_GREATER_HPP

#include "fixed_point/fixed.hpp"

namespace nsimd
{
namespace fixed_point
{

template <uint8_t _lf, uint8_t _rt>
bool gt(const fp_t<_lf, _rt> &a, const fp_t<_lf, _rt> &b)
{
  using raw_type = typename fp_t<_lf, _rt>::value_type;
  constexpr int shift_size = 8 * sizeof(raw_type) - _lf - _rt;
  const raw_type max = -1;
  const raw_type mask = (max << (shift_size));
  return ((a._raw & mask) > (b._raw & mask));
}

template <uint8_t _lf, uint8_t _rt>
bool operator>(const fp_t<_lf, _rt> &a, const fp_t<_lf, _rt> &b)
{
  return gt(a, b);
}

template <uint8_t _lf, uint8_t _rt, typename T>
bool operator>(const fp_t<_lf, _rt> &a, const T &b)
{
  return gt(a, fp_t<_lf, _rt>(b));
}

template <uint8_t _lf, uint8_t _rt, typename T>
bool operator>(const T &a, const fp_t<_lf, _rt> &b)
{
  return gt(fp_t<_lf, _rt>(a), b);
}

template <uint8_t _lf, uint8_t _rt>
bool gte(const fp_t<_lf, _rt> &a, const fp_t<_lf, _rt> &b)
{
  using raw_type = typename fp_t<_lf, _rt>::value_type;
  constexpr int shift_size = 8 * sizeof(raw_type) - _lf - _rt;
  const raw_type max = -1;
  const raw_type mask = (max << (shift_size));
  return ((a._raw & mask) >= (b._raw & mask));
}

template <uint8_t _lf, uint8_t _rt>
bool operator>=(const fp_t<_lf, _rt> &a, const fp_t<_lf, _rt> &b)
{
  return gte(a, b);
}

template <uint8_t _lf, uint8_t _rt, typename T>
bool operator>=(const fp_t<_lf, _rt> &a, const T &b)
{
  return gte(a, fp_t<_lf, _rt>(b));
}

template <uint8_t _lf, uint8_t _rt, typename T>
bool operator>=(const T &a, const fp_t<_lf, _rt> &b)
{
  return gte(fp_t<_lf, _rt>(a), b);
}

} // namespace fixed_point
} // namespace nsimd

#endif
