#include <bits/stdc++.h>
template <typename A, typename V>
class FunctionMaxima;

template <typename A, typename V>
class FunctionMaxima
{
public:
  FunctionMaxima();

  FunctionMaxima(FunctionMaxima &element);

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

  struct iterator
  {
    struct Iterator
    {
      using iterator_category = std::bidirectional_iterator_tag;
      using difference_type   = std::ptrdiff_t;
      using value_type        = V;
      using pointer           = value_type *;
      using reference         = value_type &;
    };
  };

  class point_type
  {
    // Zwraca argument funkcji.
    A const &
    arg() const;

    // Zwraca wartość funkcji w tym punkcie.
    V const &
    value() const;
  };

private:
  struct cmp
  {
    bool
    operator()(std::pair<A, V> &a, std::pair<A, V> &b) const
    {
      if (a.first < b.first)
        return true;
      return false;
    }
  };

  using Data = std::map<A, V, cmp>;
  Data valueSet;
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
FunctionMaxima<A, V>::FunctionMaxima(FunctionMaxima &element)
{
  valueSet = element;
}

template <typename A, typename V>
FunctionMaxima<A, V>
FunctionMaxima<A, V>::operator=(FunctionMaxima<A, V> &element)
{}

template <typename A, typename V>
V const &
FunctionMaxima<A, V>::value_at(A const &a) const
{
  try
    {
      if (valueSet.find(a) == valueSet.end())
        throw std::exception("value does not exist");
      return valueSet.at(a);
    }
  catch (std::exception &e)
    {
      throw e;
    }
  catch (...)
    {
      std::cout << "Default Exception\n";
    }
}

template <typename A, typename V>
void
FunctionMaxima<A, V>::set_value(A const &a, V const &v)
{
  try
    {
      if (valueSet.find(a) != valueSet.end())
        throw std::exception("value already exist");
      valueSet[a] = v;
    }
  catch (std::exception &e)
    {
      throw e;
    }
  catch (...)
    {
      throw;
    }
}

template <typename A, typename V>
void
FunctionMaxima<A, V>::erase(A const &a)
{
  try
    {
      if (valueSet.find(a) == valueSet.end())
        throw std::exception("value does not exist");

      valueSet.erase(valueSet.find(a));
    }
  catch (std::exception &e)
    {
      throw e;
    }
  catch (...)
    {
      throw;
    }
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

int
fun()
{
  printf("%dhello", 1);
  return 0;
}
