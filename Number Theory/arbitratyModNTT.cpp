#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <queue>
#include <random>
#include <vector>

template <std::uint32_t P> struct ModInt32 {
public:
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;
  using m32 = ModInt32;

private:
  u32 v;

  static constexpr u32 get_r() {
    u32 iv = P;
    for (u32 i = 0; i != 4; ++i) iv *= 2U - P * iv;
    return -iv;
  }
  static constexpr u32 r = get_r(), r2 = -u64(P) % P;
  static_assert((P & 1) == 1);
  static_assert(-r * P == 1);
  static_assert(P < (1 << 30));
  static constexpr u32 pow_mod(u32 x, u64 y) {
    u32 res = 1;
    for (; y != 0; y >>= 1, x = u64(x) * x % P)
      if (y & 1) res = u64(res) * x % P;
    return res;
  }
  static constexpr u32 reduce(u64 x) { return x + u64(u32(x) * r) * P >> 32; }
  static constexpr u32 norm(u32 x) { return x - (P & -(x >= P)); }

public:
  static constexpr u32 get_pr() {
    u32 tmp[32] = {}, cnt = 0;
    const u64 phi = P - 1;
    u64 m = phi;
    for (u64 i = 2; i * i <= m; ++i)
      if (m % i == 0) {
        tmp[cnt++] = i;
        while (m % i == 0) m /= i;
      }
    if (m != 1) tmp[cnt++] = m;
    for (u64 res = 2; res != P; ++res) {
      bool flag = true;
      for (u32 i = 0; i != cnt && flag; ++i) flag &= pow_mod(res, phi / tmp[i]) != 1;
      if (flag) return res;
    }
    return 0;
  }
  ModInt32() = default;
  ~ModInt32() = default;
  constexpr ModInt32(u32 v) : v(reduce(u64(v) * r2)) {}
  constexpr ModInt32(const m32 &rhs) : v(rhs.v) {}
  constexpr u32 get() const { return norm(reduce(v)); }
  explicit constexpr operator u32() const { return get(); }
  explicit constexpr operator i32() const { return i32(get()); }
  constexpr m32 &operator=(const m32 &rhs) { return v = rhs.v, *this; }
  constexpr m32 operator-() const {
    m32 res;
    return res.v = (P << 1 & -(v != 0)) - v, res;
  }
  constexpr m32 inv() const { return pow(-1); }
  constexpr m32 &operator+=(const m32 &rhs) {
    return v += rhs.v - (P << 1), v += P << 1 & -(v >> 31), *this;
  }
  constexpr m32 &operator-=(const m32 &rhs) { return v -= rhs.v, v += P << 1 & -(v >> 31), *this; }
  constexpr m32 &operator*=(const m32 &rhs) { return v = reduce(u64(v) * rhs.v), *this; }
  constexpr m32 &operator/=(const m32 &rhs) { return this->operator*=(rhs.inv()); }
  friend m32 operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs) += rhs; }
  friend m32 operator-(const m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }
  friend m32 operator*(const m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }
  friend m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }
  friend bool operator==(const m32 &lhs, const m32 &rhs) { return norm(lhs.v) == norm(rhs.v); }
  friend bool operator!=(const m32 &lhs, const m32 &rhs) { return norm(lhs.v) != norm(rhs.v); }
  friend std::istream &operator>>(std::istream &is, m32 &rhs) {
    return is >> rhs.v, rhs.v = reduce(u64(rhs.v) * r2), is;
  }
  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return os << rhs.get(); }
  constexpr m32 pow(i64 y) const {
    if ((y %= P - 1) < 0) y += P - 1; // phi(P) = P - 1, assume P is a prime number
    m32 res(1), x(*this);
    for (; y != 0; y >>= 1, x *= x)
      if (y & 1) res *= x;
    return res;
  }
};

template <std::uint32_t P1, std::uint32_t P2, std::uint32_t P3> struct CRT3 {
public:
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  static_assert(P1 != P2);
  static_assert(P1 != P3);
  static_assert(P2 != P3);

  static constexpr u32 pow_mod(u32 a, i64 b, u32 P) {
    u32 res = 1;
    if ((b %= P - 1) < 0) b += P - 1;
    for (; b != 0; b >>= 1, a = u64(a) * a % P)
      if (b & 1) res = u64(res) * a % P;
    return res;
  }

private:
  static constexpr u64 P1_inv_P2 = pow_mod(P1 % P2, -1, P2),
                       P1P2_inv_P3 = pow_mod(u64(P1) * P2 % P3, -1, P3);
  const u32 m, P1P2_mod_m;

public:
  // assume P1 and P2 and P3 are different prime numbers
  constexpr CRT3(std::uint32_t m) : m(m), P1P2_mod_m(u64(P1) * P2 % m) {}
  ~CRT3() = default;
  u32 operator()(u32 a, u32 b, u32 c) const {
    u64 d;
    if constexpr (P2 < P1) { // a = a mod P1
      d = ((u64(b) + P2 - a % P2) * P1_inv_P2 % P2) * P1 + a;
    } else { // if P2 > P1: a mod P2 = a mod P1
      d = ((u64(b) + P2 - a) * P1_inv_P2 % P2) * P1 + a;
    }
    // assume (b + P2 - a) * P1_inv_P2 < 2^{64}
    // assume (c + P3 - d % P3) * P1P2_inv_P3 % P3 * P1P2_mod_m + d < 2^{63}
    return ((u64(c) + P3 - d % P3) * P1P2_inv_P3 % P3 * P1P2_mod_m + d) % m;
  }
};

std::uint64_t get_len(std::uint64_t n) { // if n=0, boom
  return --n, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8, n |= n >> 16, n |= n >> 32, ++n;
}

struct ArbitaryModuloArithmetic {
public:
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  static constexpr u32 P1 = 985661441, P2 = 943718401, P3 = 935329793;

  using m1 = ModInt32<P1>;
  using m2 = ModInt32<P2>;
  using m3 = ModInt32<P3>;

  static inline m1 r1[1 << 20], ir1[1 << 20];
  static inline m2 r2[1 << 20], ir2[1 << 20];
  static inline m3 r3[1 << 20], ir3[1 << 20];

  static void init(i32 n) {
    static i32 lim = 0;
    static constexpr m1 G1(m1::get_pr());
    static constexpr m2 G2(m2::get_pr());
    static constexpr m3 G3(m3::get_pr());
    if (lim == 0) {
      r1[1 << 19] = G1.pow(P1 - 1 >> 21), ir1[1 << 19] = G1.pow(-i32(P1 - 1 >> 21));
      r2[1 << 19] = G2.pow(P2 - 1 >> 21), ir2[1 << 19] = G2.pow(-i32(P2 - 1 >> 21));
      r3[1 << 19] = G3.pow(P3 - 1 >> 21), ir3[1 << 19] = G3.pow(-i32(P3 - 1 >> 21));
      for (i32 i = 18; i != -1; --i) {
        r1[1 << i] = r1[1 << i + 1] * r1[1 << i + 1];
        ir1[1 << i] = ir1[1 << i + 1] * ir1[1 << i + 1];

        r2[1 << i] = r2[1 << i + 1] * r2[1 << i + 1];
        ir2[1 << i] = ir2[1 << i + 1] * ir2[1 << i + 1];

        r3[1 << i] = r3[1 << i + 1] * r3[1 << i + 1];
        ir3[1 << i] = ir3[1 << i + 1] * ir3[1 << i + 1];
      }
      lim = 1;
    }
    while ((lim << 1) < n) {
      for (i32 i = lim + 1, e = lim << 1; i < e; ++i) {
        r1[i] = r1[i - lim] * r1[lim], ir1[i] = ir1[i - lim] * ir1[lim];
        r2[i] = r2[i - lim] * r2[lim], ir2[i] = ir2[i - lim] * ir2[lim];
        r3[i] = r3[i - lim] * r3[lim], ir3[i] = ir3[i - lim] * ir3[lim];
      }
      lim <<= 1;
    }
  }

  static void dft(i32 n, m1 x1[], m2 x2[], m3 x3[]) {
    init(n);
    for (i32 j = 0, l = n >> 1; j != l; ++j) {
      m1 u1 = x1[j], v1 = x1[j + l];
      x1[j] = u1 + v1, x1[j + l] = u1 - v1;

      m2 u2 = x2[j], v2 = x2[j + l];
      x2[j] = u2 + v2, x2[j + l] = u2 - v2;

      m3 u3 = x3[j], v3 = x3[j + l];
      x3[j] = u3 + v3, x3[j + l] = u3 - v3;
    }
    for (i32 i = n >> 1; i >= 2; i >>= 1) {
      for (i32 j = 0, l = i >> 1; j != l; ++j) {
        m1 u1 = x1[j], v1 = x1[j + l];
        x1[j] = u1 + v1, x1[j + l] = u1 - v1;

        m2 u2 = x2[j], v2 = x2[j + l];
        x2[j] = u2 + v2, x2[j + l] = u2 - v2;

        m3 u3 = x3[j], v3 = x3[j + l];
        x3[j] = u3 + v3, x3[j + l] = u3 - v3;
      }
      for (i32 j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
        m1 root1 = r1[m];
        m2 root2 = r2[m];
        m3 root3 = r3[m];
        for (i32 k = 0; k != l; ++k) {
          m1 u1 = x1[j + k], v1 = x1[j + k + l] * root1;
          x1[j + k] = u1 + v1, x1[j + k + l] = u1 - v1;

          m2 u2 = x2[j + k], v2 = x2[j + k + l] * root2;
          x2[j + k] = u2 + v2, x2[j + k + l] = u2 - v2;

          m3 u3 = x3[j + k], v3 = x3[j + k + l] * root3;
          x3[j + k] = u3 + v3, x3[j + k + l] = u3 - v3;
        }
      }
    }
  }
  static void idft(i32 n, m1 x1[], m2 x2[], m3 x3[]) {
    for (i32 i = 2; i < n; i <<= 1) {
      for (i32 j = 0, l = i >> 1; j != l; ++j) {
        m1 u1 = x1[j], v1 = x1[j + l];
        x1[j] = u1 + v1, x1[j + l] = u1 - v1;

        m2 u2 = x2[j], v2 = x2[j + l];
        x2[j] = u2 + v2, x2[j + l] = u2 - v2;

        m3 u3 = x3[j], v3 = x3[j + l];
        x3[j] = u3 + v3, x3[j + l] = u3 - v3;
      }
      for (i32 j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
        m1 root1 = ir1[m];
        m2 root2 = ir2[m];
        m3 root3 = ir3[m];
        for (i32 k = 0; k != l; ++k) {
          m1 u1 = x1[j + k], v1 = x1[j + k + l];
          x1[j + k] = u1 + v1, x1[j + k + l] = (u1 - v1) * root1;

          m2 u2 = x2[j + k], v2 = x2[j + k + l];
          x2[j + k] = u2 + v2, x2[j + k + l] = (u2 - v2) * root2;

          m3 u3 = x3[j + k], v3 = x3[j + k + l];
          x3[j + k] = u3 + v3, x3[j + k + l] = (u3 - v3) * root3;
        }
      }
    }
    m1 iv1(P1 - (P1 - 1) / n);
    m2 iv2(P2 - (P2 - 1) / n);
    m3 iv3(P3 - (P3 - 1) / n);
    for (i32 j = 0, l = n >> 1; j != l; ++j) {
      m1 u1 = x1[j] * iv1, v1 = x1[j + l] * iv1;
      x1[j] = u1 + v1, x1[j + l] = u1 - v1;

      m2 u2 = x2[j] * iv2, v2 = x2[j + l] * iv2;
      x2[j] = u2 + v2, x2[j + l] = u2 - v2;

      m3 u3 = x3[j] * iv3, v3 = x3[j + l] * iv3;
      x3[j] = u3 + v3, x3[j + l] = u3 - v3;
    }
  }
};

std::vector<std::uint32_t> mul(const std::vector<std::uint32_t> &x,
                               const std::vector<std::uint32_t> &y, std::uint32_t modulo) {
  static ArbitaryModuloArithmetic::m1 a1[1 << 21], b1[1 << 21];
  static ArbitaryModuloArithmetic::m2 a2[1 << 21], b2[1 << 21];
  static ArbitaryModuloArithmetic::m3 a3[1 << 21], b3[1 << 21];

  using i32 = std::int32_t;
  using u32 = std::uint32_t;

  CRT3<ArbitaryModuloArithmetic::P1, ArbitaryModuloArithmetic::P2, ArbitaryModuloArithmetic::P3>
      crt(modulo);

  i32 len = get_len(x.size() + y.size() - 1);

  for (i32 i = 0, e = x.size(); i != e; ++i) a1[i] = x[i], a2[i] = x[i], a3[i] = x[i];
  for (i32 i = 0, e = y.size(); i != e; ++i) b1[i] = y[i], b2[i] = y[i], b3[i] = y[i];
  std::fill(a1 + x.size(), a1 + len, 0);
  std::fill(a2 + x.size(), a2 + len, 0);
  std::fill(a3 + x.size(), a3 + len, 0);
  std::fill(b1 + y.size(), b1 + len, 0);
  std::fill(b2 + y.size(), b2 + len, 0);
  std::fill(b3 + y.size(), b3 + len, 0);
  ArbitaryModuloArithmetic::dft(len, a1, a2, a3), ArbitaryModuloArithmetic::dft(len, b1, b2, b3);
  for (i32 i = 0; i != len; ++i) a1[i] *= b1[i], a2[i] *= b2[i], a3[i] *= b3[i];
  ArbitaryModuloArithmetic::idft(len, a1, a2, a3);
  std::vector<u32> res(x.size() + y.size() - 1);
  for (int i = 0, e = x.size() + y.size() - 1; i != e; ++i)
    res[i] = crt(u32(a1[i]), u32(a2[i]), u32(a3[i]));
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  std::cin >> n >> m;
  std::vector<uint32_t> a(n), b(m);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  for (auto i : mul(a, b, 1000000007)) std::cout << i << ' ';
  return 0;
}