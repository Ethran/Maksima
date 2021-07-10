#include <bits/stdc++.h>
template <typename A, typename V>
class FunctionMaxima;

template <typename A, typename V>
class FunctionMaxima
{
public:
  class point_type;

private:
  class size_type
  {
  public:
    size_type(const unsigned long long int &a)
      : roz(a)
    {}
    friend bool
    operator==(const size_type &a, const size_type &b)
    {
      return a.roz == b.roz;
    };
    unsigned long long int roz;
  };
  struct cmp
  {
    bool
    operator()(const point_type &a, const point_type &b) const
    {
      a.arg();
      b.arg();
      if (a.arg() < b.arg())
        return true;
      return false;
    }
  };

  struct cmpMax
  {
    bool
    operator()(const point_type &a, const point_type &b) const
    {
      a.arg();
      b.arg();
      // nie mamy gwaracji że jest ==
      if (a.value() > b.value())
        return true;
      if ((a.value() < b.value()))
        return false;

      if (a.arg() < b.arg())
        return true;
      return false;
    }
  };
  using Data_t = std::multiset<point_type, cmp>;
  Data_t valueSet;
  Data_t maxValueSet;

public:
  FunctionMaxima();

  FunctionMaxima(const FunctionMaxima &element);

  FunctionMaxima<A, V>
  operator=(FunctionMaxima<A, V> &element);

  // Zwraca wartość w punkcie a, rzuca wyjątek InvalidArg, jeśli a nie
  // należy do dziedziny funkcji. Złożoność najwyżej O(log n).
  V const &
  value_at(A const &a) const;

  // Zmienia funkcję tak, żeby zachodziło f(a) = v. Jeśli a nie należy do
  // obecnej dziedziny funkcji, jest do niej dodawany. Najwyżej O(log n).
  void
  set_value(A const &a, V const &v);
  // Usuwa a z dziedziny funkcji. Jeśli a nie należało do dziedziny funkcji,
  // nie dzieje się nic. Złożoność najwyżej O(log n).
  void
  erase(A const &a);

  // iterator wskazujący na pierwsze lokalne maksimum
  typename Data_t::iterator const
  mx_begin() const
  {
    return maxValueSet.begin();
  }
  // iterator wskazujący za ostatnie lokalne maksimum
  typename Data_t::iterator const
  mx_end() const
  {
    return maxValueSet.end();
  }



  typename Data_t::iterator
  begin()
  {
    return valueSet.begin();
  }
  typename Data_t::iterator
  end()
  {
    return valueSet.end();
  }

  class point_type
  {
  private:
    friend class FunctionMaxima;
    A a;
    V v;
    point_type(const A &_arg)
      : a(_arg)
    {}
    point_type(const A &_arg, const V &_value)
      : a(_arg)
      , v(_value)
    {}
    bool isMax = false;
    // Zwraca argument funkcji. referencja do mod
    A &
    arg()
    {
      return a;
    }

    // Zwraca wartość funkcji w tym punkcie.
    V &
    value()
    {
      return v;
    }

  public:
    // Zwraca argument funkcji.
    const A &
    arg() const
    {
      return a;
    }

    // Zwraca wartość funkcji w tym punkcie.
    const V &
    value() const
    {
      return v;
    }
  };

  size_type
  size() const
  {
    return size_type(valueSet.size());
  }
};

template <typename A, typename V>
FunctionMaxima<A, V>::FunctionMaxima()
{
  try
    {}
  catch (std::exception &e)
    {
      throw e;
    }
}

template <typename A, typename V>
FunctionMaxima<A, V>::FunctionMaxima(const FunctionMaxima &element)
  : valueSet(element.valueSet)
{}

template <typename A, typename V>
FunctionMaxima<A, V>
FunctionMaxima<A, V>::operator=(FunctionMaxima<A, V> &element)
{}

template <typename A, typename V>
V const &
FunctionMaxima<A, V>::value_at(A const &a) const
{
  return valueSet.at(point_type(a));
}

template <typename A, typename V>
void
FunctionMaxima<A, V>::set_value(A const &a, V const &v)
{
  valueSet.insert(point_type(a, v));
}

template <typename A, typename V>
void
FunctionMaxima<A, V>::erase(A const &a)
{
  valueSet.erase(valueSet.find(point_type(a)));
}

template <typename A, typename V>
bool
operator<(FunctionMaxima<A, V> first, FunctionMaxima<A, V> second)
{
  if (true)
    return true;
  else
    return false;
}
