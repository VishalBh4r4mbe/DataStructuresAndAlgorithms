#include "bits/stdc++.h"

char scanc() {
  static char buf[1 << 15], *ptr = std::end(buf);
  if (ptr == std::end(buf)) fread(buf, 1, std::size(buf), stdin), ptr = buf;
  return *ptr++;
}
void printc(char c) {
  static char buf[1 << 15], *ptr = buf;
  if (ptr == std::end(buf) || c == -1) fwrite(buf, 1, ptr - buf, stdout), ptr = buf;
  *ptr++ = c;
}
__attribute__((destructor)) void print_destructor() { printc(-1); }
template <class T> T scan() {
  char c = scanc();
  bool neg = c == '-';
  T res = neg ? 0 : c & 0xf;
  while ((c = scanc()) >= '0') (res *= 10) += c & 0xf;
  return neg ? -res : res;
}
template <class T> void print(T a, char delimiter = '\n') {
  if (a < 0) printc('-'), a = -a;
  char buf[40], *ptr = buf;
  do *ptr++ = '0' | a % 10;
  while (a /= 10);
  while (ptr-- > buf) printc(*ptr);
  printc(delimiter);
}

template <class T, class Int> T power(T a, Int n, T e = 1) {
  __glibcxx_assert(n >= 0);
  if (n == 0) return e;
  for (; ~n & 1; n >>= 1) a *= a;
  T res = a;
  while (n >>= 1) {
    a *= a;
    if (n & 1) res *= a;
  }
  return res;
}

namespace ntt {

template <class T> T get_root(int n) {
  __glibcxx_assert(n && (n & (n - 1)) == 0 && (T::mod() - 1) % n == 0);
  T r = 3;
  while (power(r, (T::mod() - 1) / 2) != -1) ++r;
  return power(r, (T::mod() - 1) / n);
}
template <class T> std::array<std::vector<T>, 2> roots;
template <class T> void reserve(int n) {
  for (auto&& v : roots<T>) v.reserve(n / 2);
  if (std::empty(roots<T>[0])) roots<T>.fill({1});
  for (int sz = std::size(roots<T>[0]); sz < n / 2; sz *= 2) {
    T r = get_root<T>(4 * sz);
    for (int i = 0; i < sz; ++i) roots<T>[0].push_back(roots<T>[0][i] * r);
    r = 1 / r;
    for (int i = 0; i < sz; ++i) roots<T>[1].push_back(roots<T>[1][i] * r);
  }
}
template <class T, class RandomAccessIterator> void dit(RandomAccessIterator a, int n) {
  __glibcxx_assert(n && (n & (n - 1)) == 0 && (T::mod() - 1) % n == 0);
  reserve<T>(n);
  for (int step = n; step /= 2;)
    for (int start = 0, k = 0; start < n; start += 2 * step, ++k)
      for (int i0 = start, i1 = i0 + step; i0 < start + step; ++i0, ++i1) {
        auto t = a[i1] * roots<T>[0][k];
        a[i1] = a[i0] - t;
        a[i0] += t;
      }
}
template <class RandomAccessIterator> void dit(RandomAccessIterator a, int n) {
  dit<typename std::iterator_traits<RandomAccessIterator>::value_type>(a, n);
}
template <class T, class RandomAccessIterator> void dif(RandomAccessIterator a, int n) {
  __glibcxx_assert(n && (n & (n - 1)) == 0 && (T::mod() - 1) % n == 0);
  reserve<T>(n);
  for (int step = 1; step < n; step *= 2)
    for (int start = 0, k = 0; start < n; start += 2 * step, ++k)
      for (int i0 = start, i1 = i0 + step; i0 < start + step; ++i0, ++i1) {
        auto t = a[i1];
        a[i1] = (a[i0] - a[i1]) * roots<T>[1][k];
        a[i0] += t;
      }
}
template <class RandomAccessIterator> void dif(RandomAccessIterator a, int n) {
  dif<typename std::iterator_traits<RandomAccessIterator>::value_type>(a, n);
}
template <class T> std::vector<T> convolution(const std::vector<T>& a, const std::vector<T>& b) {
  if (std::empty(a) || std::empty(b)) return {};
  if (std::min(std::size(a), std::size(b)) <= 50) {
    std::vector<T> res(std::size(a) + std::size(b) - 1);
    for (int i = 0; i < int(std::size(a)); ++i)
      for (int j = 0; j < int(std::size(b)); ++j) res[i + j] += a[i] * b[j];
    return res;
  }
  int sz = std::size(a) + std::size(b) - 1, n = 1 << std::__lg(2 * sz - 1);
  std::vector<T> fa(n);
  std::copy(std::begin(a), std::end(a), std::begin(fa));
  dit(std::begin(fa), n);
  if (&a == &b) {
    for (auto&& e : fa) e *= e;
  } else {
    std::vector<T> fb(n);
    std::copy(std::begin(b), std::end(b), std::begin(fb));
    dit(std::begin(fb), n);
    for (int i = 0; i < n; ++i) fa[i] *= fb[i];
  }
  dif(begin(fa), n);
  fa.resize(sz);
  T inv_n = 1 / T(n);
  for (auto&& e : fa) e *= inv_n;
  return fa;
}
template <class T> std::vector<T> middle_product(const std::vector<T>& a, const std::vector<T>& b) {
  __glibcxx_assert(std::size(a) >= std::size(b) && !std::empty(b));
  if (std::min(std::size(b), std::size(a) - std::size(b) + 1) <= 50) {
    std::vector<T> res(std::size(a) - std::size(b) + 1);
    for (int i = 0; i < int(std::size(res)); ++i)
      res[i] = std::inner_product(std::begin(b), std::end(b), std::begin(a) + i, T(0));
    return res;
  }
  int n = 1 << std::__lg(2 * std::size(a) - 1);
  std::vector<T> fa(n), fb(n);
  std::copy(std::begin(a), std::end(a), std::begin(fa));
  std::copy(std::rbegin(b), std::rend(b), std::begin(fb));
  dit(std::begin(fa), n);
  dit(std::begin(fb), n);
  for (int i = 0; i < n; ++i) fa[i] *= fb[i];
  dif(std::begin(fa), n);
  fa.resize(std::size(a));
  fa.erase(std::begin(fa), std::begin(fa) + (std::size(b) - 1));
  T inv_n = 1 / T(n);
  for (auto&& e : fa) e *= inv_n;
  return fa;
}

}  // namespace ntt

template <class T> class NumberBase {
 public:
  T& operator++() { return self() += T(1); }
  T& operator--() { return self() -= T(1); }
  T operator++(int) { return std::exchange(self(), ++self()); }
  T operator--(int) { return std::exchange(self(), --self()); }
  T operator+() const { return self(); }
  T operator-() const { return T{} - self(); }
  bool operator!() const { return self() == T{}; }
  explicit operator bool() const { return !!self(); }
  friend T operator+(const T& a, const T& b) { return T(a) += b; }
  friend T operator-(const T& a, const T& b) { return T(a) -= b; }
  friend T operator*(const T& a, const T& b) { return T(a) *= b; }
  friend T operator/(const T& a, const T& b) { return T(a) /= b; }
  friend bool operator>(const T& a, const T& b) { return b < a; }
  friend bool operator<=(const T& a, const T& b) { return !(a > b); }
  friend bool operator>=(const T& a, const T& b) { return !(a < b); }
  friend bool operator!=(const T& a, const T& b) { return !(a == b); }

 private:
  T& self() { return *static_cast<T*>(this); }
  const T& self() const { return *static_cast<const T*>(this); }
};

template <auto P> struct FpStaticPolicy {
  using U = std::make_unsigned_t<decltype(P)>;
  using D = std::conditional_t<std::is_same_v<U, uint32_t>, uint64_t, __uint128_t>;
  static_assert(2 <= P && P <= U(-1) / 4);
  static constexpr U p = P;
  static constexpr U inv_p = [] {
    U res = p;
    for (int _ = 5; _--;) res *= 2 - p * res;
    return p == 2 ? U(-1) / 2 + 1 : res;
  }();
  static constexpr U r2 = p == 2 ? 1 : -D(p) % p;
};
template <class T, int Id> struct FpDynamicPolicy {
  using U = std::make_unsigned_t<T>;
  using D = std::conditional_t<std::is_same_v<U, uint32_t>, uint64_t, __uint128_t>;
  static inline U p, inv_p, r2;
};
template <class Policy = FpStaticPolicy<998244353>> class Fp : public NumberBase<Fp<Policy>> {
  using U = typename Policy::U;
  using D = typename Policy::D;
  static_assert(std::is_same_v<U, uint32_t> || std::is_same_v<U, uint64_t>);

 public:
  using T = std::make_signed_t<U>;
  static inline std::vector<Fp> fact, ifact, inv;
  static constexpr T mod() { return Policy::p; }
  static void mod(T mod) {
    __glibcxx_assert(2 <= mod && mod <= T(U(-1) / 4));
    fact.clear(), ifact.clear(), inv.clear();
    Policy::p = mod, Policy::inv_p = Policy::p, Policy::r2 = -D(Policy::p) % Policy::p;
    for (int _ = 5; _--;) Policy::inv_p *= 2 - Policy::p * Policy::inv_p;
    if (Policy::p == 2) Policy::inv_p = U(-1) / 2 + 1, Policy::r2 = 1;
  }
  static void reserve(T n) {
    __glibcxx_assert(0 <= n && n < mod());
    fact.resize(n + 1), ifact.resize(n + 1), inv.resize(n + 1);
    fact[0] = 1;
    for (T i = 1; i <= n; ++i) fact[i] = i * fact[i - 1];
    ifact[n] = power(fact[n], Policy::p - 2);
    for (T i = n; i; --i) ifact[i - 1] = ifact[i] * i, inv[i] = fact[i - 1] * ifact[i];
  }
  static Fp binom(T n, T k) {
    if (n >= 0) return 0 <= k && k <= n ? fact[n] * ifact[k] * ifact[n - k] : 0;
    if (k >= 0) return k & 1 ? -binom(k + ~n, k) : binom(k + ~n, k);
    return (n ^ k) & 1 ? -binom(~k, ~n) : binom(~k, ~n);
  }
  Fp() : v(0) {}
  template <class Int, std::enable_if_t<std::is_integral_v<Int> && std::is_signed_v<Int>>* = nullptr> Fp(Int x) {
    v = -mod() <= x && x < mod() ? x : x % mod();
    v = reduce(D(v + Policy::p) * Policy::r2);
  }
  template <class Int, std::enable_if_t<std::is_integral_v<Int> && std::is_unsigned_v<Int>>* = nullptr> Fp(Int x) {
    v = x < 2 * Policy::p ? x : x % Policy::p;
    v = reduce(D(v) * Policy::r2);
  }
  T val() const {
    T res = reduce(v) - Policy::p;
    return res < 0 ? res + Policy::p : res;
  }
  Fp& operator+=(const Fp& o) {
    v = T(v += o.v - 2 * Policy::p) < 0 ? v + 2 * Policy::p : v;
    return *this;
  }
  Fp& operator-=(const Fp& o) {
    v = T(v -= o.v) < 0 ? v + 2 * Policy::p : v;
    return *this;
  }
  Fp& operator*=(const Fp& o) {
    v = reduce(D(v) * o.v);
    return *this;
  }
  Fp& operator/=(const Fp& o) {
    __glibcxx_assert(o);
    if (o.val() < T(std::size(inv))) return *this *= inv[o.val()];
    if ((-o).val() < T(std::size(inv))) return *this *= -inv[(-o).val()];
    return *this *= power(o, Policy::p - 2);
  }
  friend bool operator==(const Fp& a, const Fp& b) {
    return a.v == b.v || a.v + Policy::p == b.v || a.v == b.v + Policy::p;
  }
  friend std::ostream& operator<<(std::ostream& os, const Fp& a) { return os << a.val(); }

 private:
  static U reduce(D x) { return (x + D(U(x) * -Policy::inv_p) * Policy::p) >> std::numeric_limits<U>::digits; }
  U v;
};

std::vector<uint64_t> convolution(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b) {
  constexpr uint32_t P0 = 119 << 23 | 1;
  constexpr uint32_t P1 = 107 << 23 | 1;
  constexpr uint32_t P2 = 105 << 23 | 1;
  constexpr uint32_t P3 = 483 << 21 | 1;
  constexpr uint32_t P4 = 479 << 21 | 1;
  using M0 = Fp<FpStaticPolicy<P0>>;
  using M1 = Fp<FpStaticPolicy<P1>>;
  using M2 = Fp<FpStaticPolicy<P2>>;
  using M3 = Fp<FpStaticPolicy<P3>>;
  using M4 = Fp<FpStaticPolicy<P4>>;
  static const M1 inv10 = 1 / M1(P0);
  static const M2 inv21 = 1 / M2(P1), inv20 = inv21 / P0;
  static const M3 inv32 = 1 / M3(P2), inv31 = inv32 / P1, inv30 = inv31 / P0;
  static const M4 inv43 = 1 / M4(P3), inv42 = inv43 / P2, inv41 = inv42 / P1, inv40 = inv41 / P0;
  auto a0 = ntt::convolution<M0>({std::begin(a), std::end(a)}, {std::begin(b), std::end(b)});
  auto a1 = ntt::convolution<M1>({std::begin(a), std::end(a)}, {std::begin(b), std::end(b)});
  auto a2 = ntt::convolution<M2>({std::begin(a), std::end(a)}, {std::begin(b), std::end(b)});
  auto a3 = ntt::convolution<M3>({std::begin(a), std::end(a)}, {std::begin(b), std::end(b)});
  auto a4 = ntt::convolution<M4>({std::begin(a), std::end(a)}, {std::begin(b), std::end(b)});
  std::vector<uint64_t> res(std::size(a0));
  for (int i = 0; i < int(size(res)); ++i) {
    auto x0 = a0[i].val();
    auto x1 = ((a1[i] - x0) * inv10).val();
    auto x2 = ((a2[i] - x0) * inv20 - x1 * inv21).val();
    auto x3 = ((a3[i] - x0) * inv30 - x1 * inv31 - x2 * inv32).val();
    auto x4 = ((a4[i] - x0) * inv40 - x1 * inv41 - x2 * inv42 - x3 * inv43).val();
    res[i] = x0 + P0 * (x1 + P1 * (x2 + P2 * (x3 + P3 * uint64_t(x4))));
  }
  return res;
}

int main() {
  using namespace std;
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = scan<int>();
  int m = scan<int>();
  vector<uint64_t> a(n), b(m);
  generate(begin(a), end(a), scan<uint64_t>);
  generate(begin(b), end(b), scan<uint64_t>);
  a = convolution(a, b);
  for (int i = 0; i < int(size(a)); ++i) print(a[i], " \n"[i + 1 == int(size(a))]);
}