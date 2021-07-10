//============================================================================
// Name        : Maksima.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "function_maxima.h"


class Secret
{
public:
  int
  get() const
  {
    return value;
  }
  bool
  operator<(const Secret &a) const
  {
    return value < a.value;
  }
  static Secret
  create(int v)
  {
    return Secret(v);
  }

private:
  Secret(int v)
    : value(v)
  {}
  int value;
};

template <typename A, typename V>
struct same
{
  bool
  operator()(const typename FunctionMaxima<A, V>::point_type &p,
             const std::pair<A, V> &                          q)
  {
    return !(p.arg() < q.first) && !(q.first < p.arg()) &&
           !(p.value() < q.second) && !(q.second < p.value());
  }
};

template <typename A, typename V>
bool
fun_equal(const FunctionMaxima<A, V> &                  F,
          const std::initializer_list<std::pair<A, V>> &L)
{
  return F.size() == L.size() &&
         std::equal(F.begin(), F.end(), L.begin(), same<A, V>());
}

template <typename A, typename V>
bool
fun_mx_equal(const FunctionMaxima<A, V> &                  F,
             const std::initializer_list<std::pair<A, V>> &L)
{
  return static_cast<typename FunctionMaxima<A, V>::size_type>(
           std::distance(F.mx_begin(), F.mx_end())) == L.size() &&
         std::equal(F.mx_begin(), F.mx_end(), L.begin(), same<A, V>());
}



int
main()
{
  FunctionMaxima<int, int> fun;
  int                      a = 0, b = 1;
  fun.set_value(a, b);
  fun.set_value(2, 4);
  fun.set_value(1, 4);
  fun.set_value(-1, 4);
  FunctionMaxima<int, int> F(fun);
  for (const auto &p : F)
    {
      std::cout << p.arg() << " -> " << p.value() << std::endl;
    }
  fun.set_value(0, 1);
  assert(fun_equal(fun, {{0, 1}}));
  assert(fun_mx_equal(fun, {{0, 1}}));

  //  [[maybe_unused]] auto newIter = funa.begin();
  //  int                   zmienna;
  //  zmienna = 9;
  //  ++zmienna;
  //  fun();
  return 0;
}
