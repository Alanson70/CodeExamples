// Copyright (c) 2001-2006  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.7-branch/Number_types/src/CGAL/MP_Float.cpp $
// $Id: MP_Float.cpp 57004 2010-06-23 08:32:08Z afabri $
// 
//
// Author(s)     : Sylvain Pion

#include "StdAfx.h"

#define CGAL_NO_AUTOLINK
#define CGAL_NDEBUG
#define BOOST_ALL_NO_LIB

#include <CGAL/basic.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Quotient.h>
#include <CGAL/Root_of_2.h>
#include <functional>
#include <cmath>

namespace CGAL {

using std::pair;

typedef MP_Float::exponent_type       exponent_type;

const unsigned        log_limb         = 8 * sizeof(MP_Float::limb);
const MP_Float::limb2 base             = 1 << log_limb;
const MP_Float::V::size_type limbs_per_double = 2 + 53/log_limb;

const double trunc_max = double(base)*(base/2-1)/double(base-1);
const double trunc_min = double(-base)*(base/2)/double(base-1);


// We face portability issues with the ISO C99 functions "nearbyint",
// so I re-implement it for my need.
template < typename T >
int my_nearbyint(const T& d)
{
  int z = int(d);
  T frac = d - z;

  CGAL_assertion(CGAL::abs(frac) < T(1.0));

  if (frac > 0.5)
    ++z;
  else if (frac < -0.5)
    --z;
  else if (frac == 0.5 && (z&1) != 0) // NB: We also need the round-to-even rule.
    ++z;
  else if (frac == -0.5 && (z&1) != 0)
    --z;

  CGAL_assertion(CGAL::abs(T(z) - d) < T(0.5) ||
                 (CGAL::abs(T(z) - d) == T(0.5) && ((z&1) == 0)));
  return z;
}


template < typename T >
inline
void MP_Float::construct_from_builtin_fp_type(T d)
{
    if (d == 0)
      return;

    // Protection against rounding mode != nearest, and extended precision.
    Set_ieee_double_precision P;

    CGAL_assertion(is_finite(d));

    // This is subtle, because ints are not symetric against 0.

    // First, scale d, and adjust exp accordingly.
    exp = 0;
    while (d < trunc_min || d > trunc_max) {
      ++exp;
      d /= base;
    }

    while (d >= trunc_min/base && d <= trunc_max/base) {
      --exp;
      d *= base;
    }

    // Then, compute the limbs.
    // Put them in v (in reverse order temporarily).
    T orig = d, sum = 0;
    while (true) {
      int r = my_nearbyint(d);
      if (d-r >= T(base/2-1)/(base-1))
        ++r;
      v.push_back(r);
      // We used to do simply "d -= v.back();", but when the most significant
      // limb is 1 and the second is -32768, then it can happen that
      // |d - v.back()| > |d|, hence a bit of precision can be lost.
      //  Hence the need for sum/orig.
      sum += v.back();
      d = orig-sum;
      if (d == 0)
        break;
      sum *= base;
      orig *= base;
      d *= base;
      --exp;
    }

    // Reverse v.
    std::reverse(v.begin(), v.end());

    CGAL_assertion(v.back() != 0);
}

MP_Float::MP_Float(float d)
{
    construct_from_builtin_fp_type(d);
    CGAL_expensive_assertion(CGAL::to_double(*this) == d);
}

MP_Float::MP_Float(double d)
{
    construct_from_builtin_fp_type(d);
    CGAL_expensive_assertion(CGAL::to_double(*this) == d);
}

MP_Float::MP_Float(long double d)
{
    construct_from_builtin_fp_type(d);
    // CGAL_expensive_assertion(CGAL::to_double(*this) == d);
}

Comparison_result
INTERN_MP_FLOAT::compare (const MP_Float & a, const MP_Float & b)
{
  if (a.is_zero())
    return (Comparison_result) - b.sign();
  if (b.is_zero())
    return (Comparison_result) a.sign();

  for (exponent_type i = (std::max)(a.max_exp(), b.max_exp()) - 1;
                    i >= (std::min)(a.min_exp(), b.min_exp()); i--)
  {
    if (a.of_exp(i) > b.of_exp(i))
      return LARGER;
    if (a.of_exp(i) < b.of_exp(i))
      return SMALLER;
  }
  return EQUAL;
}

// Common code for operator+ and operator-.
template <class BinOp>
inline
MP_Float
Add_Sub(const MP_Float &a, const MP_Float &b, const BinOp &op)
{
  CGAL_assertion(!b.is_zero());

  exponent_type min_exp, max_exp;

  if (a.is_zero()) {
    min_exp = b.min_exp();
    max_exp = b.max_exp();
  }
  else {
    min_exp = (std::min)(a.min_exp(), b.min_exp());
    max_exp = (std::max)(a.max_exp(), b.max_exp());
  }

  MP_Float r;
  r.exp = min_exp;
  r.v.resize(static_cast<int>(max_exp - min_exp + 1)); // One more for carry.
  r.v[0] = 0;
  for(int i = 0; i < max_exp - min_exp; i++)
  {
    MP_Float::limb2 tmp = r.v[i] + op(a.of_exp(i+min_exp),
                                      b.of_exp(i+min_exp));
    MP_Float::split(tmp, r.v[i+1], r.v[i]);
  }
  r.canonicalize();
  return r;
}

MP_Float
operator+(const MP_Float &a, const MP_Float &b)
{
  if (a.is_zero())
    return b;
  if (b.is_zero())
    return a;

  return Add_Sub(a, b, std::plus<MP_Float::limb2>());
}

MP_Float
operator-(const MP_Float &a, const MP_Float &b)
{
  if (b.is_zero())
    return a;

  return Add_Sub(a, b, std::minus<MP_Float::limb2>());
}

MP_Float
operator*(const MP_Float &a, const MP_Float &b)
{
  if (a.is_zero() || b.is_zero())
    return MP_Float();

  // Disabled until square() is fixed.
  // if (&a == &b)
  //   return square(a);

  MP_Float r;
  r.exp = a.exp + b.exp;
  CGAL_assertion_msg(CGAL::abs(r.exp) < (1<<30)*1.0*(1<<23),
                     "Exponent overflow in MP_Float multiplication");
  r.v.assign(a.v.size() + b.v.size(), 0);
  for(unsigned i = 0; i < a.v.size(); ++i)
  {
    unsigned j;
    MP_Float::limb carry = 0;
    for(j = 0; j < b.v.size(); ++j)
    {
      MP_Float::limb2 tmp = carry + (MP_Float::limb2) r.v[i+j]
                        + std::multiplies<MP_Float::limb2>()(a.v[i], b.v[j]);
      MP_Float::split(tmp, carry, r.v[i+j]);
    }
    r.v[i+j] = carry;
  }
  r.canonicalize();
  return r;
}

// Squaring simplifies things and is faster, so we specialize it.
MP_Float
INTERN_MP_FLOAT::square(const MP_Float &a)
{
  // There is a bug here (see test-case in test/NT/MP_Float.C).
  // For now, I disable this small optimization.
  // See also the comment code in operator*().
  return a*a;
#if 0
  typedef MP_Float::limb limb;
  typedef MP_Float::limb2 limb2;

  if (a.is_zero())
    return MP_Float();

  MP_Float r;
  r.exp = 2*a.exp;
  r.v.assign(2*a.v.size(), 0);
  for(unsigned i=0; i<a.v.size(); i++)
  {
    unsigned j;
    limb2 carry = 0;
    limb carry2 = 0;
    for(j=0; j<i; j++)
    {
      // There is a risk of overflow here :(
      // It can only happen when a.v[i] == a.v[j] == -2^15 (log_limb...)
      limb2 tmp0 = std::multiplies<limb2>()(a.v[i], a.v[j]);
      limb2 tmp1 = carry + (limb2) r.v[i+j] + tmp0;
      limb2 tmp = tmp0 + tmp1;

      limb tmpcarry;
      MP_Float::split(tmp, tmpcarry, r.v[i+j]);
      carry = tmpcarry + (limb2) carry2;

      // Is there a more efficient way to handle this carry ?
      if (tmp > 0 && tmp0 < 0 && tmp1 < 0)
      {
        // If my calculations are correct, this case should never happen.
	CGAL_error();
      }
      else if (tmp < 0 && tmp0 > 0 && tmp1 > 0)
        carry2 = 1;
      else
        carry2 = 0;
    }
    // last round for j=i :
    limb2 tmp0 = carry + (limb2) r.v[i+i]
                       + std::multiplies<limb2>()(a.v[i], a.v[i]);
    MP_Float::split(tmp0, r.v[i+i+1], r.v[i+i]);
    r.v[i+i+1] += carry2;
  }
  r.canonicalize();
  return r;
#endif
}

// Division by Newton (code by Valentina Marotta & Chee Yap) :
/*
Integer reciprocal(const Integer A, Integer k) {
  Integer t, m, ld;
  Integer e, X, X1, X2, A1;
  if (k == 1)
    return 2;

  A1 = A >> k/2;   // k/2 most significant bits
  X1 = reciprocal(A1, k/2);
  // To avoid the adjustment :
  Integer E = (1 << (2*k - 1)) - A*X1;
  if (E > A)
    X1 = X1 + 1;

  e = 1 << 3*k/2; // 2^(3k/2)
  X2 = X1*e - X1*X1*A;
  X = X2 >> k-1;
  return X;
}
*/

MP_Float
approximate_division(const MP_Float &a, const MP_Float &b)
{
  CGAL_assertion_msg(! b.is_zero(), " Division by zero");
  return MP_Float(CGAL::to_double(a)/CGAL::to_double(b));
}

MP_Float
approximate_sqrt(const MP_Float &d)
{
  return MP_Float(CGAL_NTS sqrt(CGAL::to_double(d)));
}

// Returns (first * 2^second), an approximation of b.
pair<double, int>
to_double_exp(const MP_Float &b)
{
  if (b.is_zero())
    return std::make_pair(0.0, 0);

  exponent_type exp = b.max_exp();
  int steps = static_cast<int>((std::min)(limbs_per_double, b.v.size()));
  double d_exp_1 = std::ldexp(1.0, - static_cast<int>(log_limb));
  double d_exp   = 1.0;
  double d = 0;

  for (exponent_type i = exp - 1; i > exp - 1 - steps; i--) {
    d_exp *= d_exp_1;
    d += d_exp * b.of_exp(i);
  }

  CGAL_assertion_msg(CGAL::abs(exp*log_limb) < (1<<30)*2.0,
                     "Exponent overflow in MP_Float to_double");

  return std::make_pair(d, static_cast<int>(exp * log_limb));
}

// Returns (first * 2^second), an interval surrounding b.
pair<pair<double, double>, int>
to_interval_exp(const MP_Float &b)
{
  if (b.is_zero())
    return std::make_pair(pair<double, double>(0, 0), 0);

  exponent_type exp = b.max_exp();
  int steps = static_cast<int>((std::min)(limbs_per_double, b.v.size()));
  double d_exp_1 = std::ldexp(1.0, - (int) log_limb);
  double d_exp   = 1.0;

  Interval_nt_advanced::Protector P;
  Interval_nt_advanced d = 0;

  exponent_type i;
  for (i = exp - 1; i > exp - 1 - steps; i--) {
    d_exp *= d_exp_1;
    if (d_exp == 0) // Take care of underflow.
      d_exp = CGAL_IA_MIN_DOUBLE;
    d += d_exp * b.of_exp(i);
  }

  if (i >= b.min_exp() && d.is_point()) {
    if (b.of_exp(i) > 0)
      d += Interval_nt_advanced(0, d_exp);
    else if (b.of_exp(i) < 0)
      d += Interval_nt_advanced(-d_exp, 0);
    else
      d += Interval_nt_advanced(-d_exp, d_exp);
  }

#ifdef CGAL_EXPENSIVE_ASSERTION // force it always in early debugging
  if (d.is_point())
    CGAL_assertion(MP_Float(d.inf()) == b);
  else
    CGAL_assertion(MP_Float(d.inf()) <= b & MP_Float(d.sup()) >= b);
#endif

  CGAL_assertion_msg(CGAL::abs(exp*log_limb) < (1<<30)*2.0,
                     "Exponent overflow in MP_Float to_interval");
  return std::make_pair(d.pair(), static_cast<int>(exp * log_limb));
}

// to_double() returns, not the closest double, but a one bit error is allowed.
// We guarantee : to_double(MP_Float(double d)) == d.
double
INTERN_MP_FLOAT::to_double(const MP_Float &b)
{
  pair<double, int> ap = to_double_exp(b);
  return ap.first * std::ldexp(1.0, ap.second);
}

double
INTERN_MP_FLOAT::to_double(const Quotient<MP_Float> &q)
{
    pair<double, int> n = to_double_exp(q.numerator());
    pair<double, int> d = to_double_exp(q.denominator());
    double scale = std::ldexp(1.0, n.second - d.second);
    return (n.first / d.first) * scale;
}


double
INTERN_MP_FLOAT::to_double(const Root_of_2<MP_Float> &x)
{
  typedef MP_Float RT;
  typedef Quotient<RT> FT;
  typedef CGAL::Rational_traits< FT > Rational;
  Rational r;
  const RT r1 = r.numerator(x.alpha());
  const RT d1 = r.denominator(x.alpha());

  if(x.is_rational()) {
    std::pair<double, int> n = to_double_exp(r1);
    std::pair<double, int> d = to_double_exp(d1);
    double scale = std::ldexp(1.0, n.second - d.second);
    return (n.first / d.first) * scale;
  }

  const RT r2 = r.numerator(x.beta());
  const RT d2 = r.denominator(x.beta());
  const RT r3 = r.numerator(x.gamma());
  const RT d3 = r.denominator(x.gamma());

  std::pair<double, int> n1 = to_double_exp(r1);
  std::pair<double, int> v1 = to_double_exp(d1);
  double scale1 = std::ldexp(1.0, n1.second - v1.second);

  std::pair<double, int> n2 = to_double_exp(r2);
  std::pair<double, int> v2 = to_double_exp(d2);
  double scale2 = std::ldexp(1.0, n2.second - v2.second);

  std::pair<double, int> n3 = to_double_exp(r3);
  std::pair<double, int> v3 = to_double_exp(d3);
  double scale3 = std::ldexp(1.0, n3.second - v3.second);

  return ((n1.first / v1.first) * scale1) + 
         ((n2.first / v2.first) * scale2) *
         std::sqrt((n3.first / v3.first) * scale3);
}


// FIXME : This function deserves proper testing...
pair<double,double>
INTERN_MP_FLOAT::to_interval(const MP_Float &b)
{
  pair<pair<double, double>, int> ap = to_interval_exp(b);
  return ldexp(Interval_nt<>(ap.first), ap.second).pair();
}

// FIXME : This function deserves proper testing...
pair<double,double>
INTERN_MP_FLOAT::to_interval(const Quotient<MP_Float> &q)
{
  pair<pair<double, double>, int> n = to_interval_exp(q.numerator());
  pair<pair<double, double>, int> d = to_interval_exp(q.denominator());
  CGAL_assertion_msg(CGAL::abs(1.0*n.second - d.second) < (1<<30)*2.0,
                     "Exponent overflow in Quotient<MP_Float> to_interval");
  return ldexp(Interval_nt<>(n.first) / Interval_nt<>(d.first),
               n.second - d.second).pair();
}

std::ostream &
operator<< (std::ostream & os, const MP_Float &b)
{
  os << CGAL::to_double(b);
  return os;
}

std::ostream &
print (std::ostream & os, const MP_Float &b)
{
  // Binary format would be nice and not hard to have too (useful ?).
  if (b.is_zero())
    return os << 0 << " [ double approx == " << 0.0 << " ]";

  MP_Float::const_iterator i;
  exponent_type exp = b.min_exp() * log_limb;
  double approx = 0; // only for giving an idea.

  for (i = b.v.begin(); i != b.v.end(); i++)
  {
    os << ((*i > 0) ? " +" : " ") << *i;

    if (exp != 0)
      os << " * 2^" << exp;

    approx += std::ldexp(static_cast<double>(*i),
                                   static_cast<int>(exp));

    exp += log_limb;
  }

  os << "  [ double approx == " << approx << " ]";

  return os;
}

std::istream &
operator>> (std::istream & is, MP_Float &b)
{
  double d;
  is >> d;
  if (is)
    b = MP_Float(d);
  return is;
}

} //namespace CGAL
