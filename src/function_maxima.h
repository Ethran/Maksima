#include <bits/stdc++.h>
template <typename A, typename V>
class FunctionMaxima;

using InvalidArg = std::runtime_error;
template <typename A, typename V>
class FunctionMaxima
{
public:
  class point_type;

private:
  struct cmp;
  struct cmpMax;

  using Data_t     = std::multiset<point_type, cmp>;
  using Data_max_t = std::set<point_type, cmpMax>;

  using A_ptr = std::shared_ptr<const A>;
  using V_ptr = std::shared_ptr<const V>;

  Data_t     valueSet;
  Data_max_t maxValueSet;

public:
  using iterator    = typename Data_t::iterator;
  using mx_iterator = typename Data_max_t::iterator;
  using size_type   = typename Data_t::size_type;

private:
  // check and change maxima;
  void
  check(iterator it) noexcept;

public:
  FunctionMaxima();

  FunctionMaxima(const FunctionMaxima &element);


  FunctionMaxima<A, V> &
  operator=(const FunctionMaxima<A, V> &element);


  // Zwraca wartość w punkcie a, rzuca wyjątek InvalidArg, jeśli a nie
  // należy do dziedziny funkcji. Złożoność najwyżej O(log n).
  V const &
  value_at(A const &a) const;


  // Zmienia funkcję tak, żeby zachodziło f(a) = v. Jeśli a nie należy do
  // obecnej dziedziny funkcji, jest do niej dodawany. Najwyżej O(log n).
  void
  set_value(A const &arg, V const &val);


  // Usuwa a z dziedziny funkcji. Jeśli a nie należało do dziedziny funkcji,
  // nie dzieje się nic. Złożoność najwyżej O(log n).
  void
  erase(A const &a);

  // iterator wskazujący na pierwsze lokalne maksimum
  iterator
  mx_begin() const;


  // iterator wskazujący za ostatnie lokalne maksimum
  iterator
  mx_end() const;


  // iterator wskazujący na pierwszy punkt
  iterator
  begin() const;

  // iterator wskazujący za ostatni punkt
  iterator
  end() const;


  // Iterator, który wskazuje na punkt funkcji o argumencie a lub end(),
  // jeśli takiego argumentu nie ma w dziedzinie funkcji.
  iterator
  find(A const &a) const;

  // Typ size_type reprezentujący rozmiar dziedziny i funkcja zwracająca ten
  // rozmiar:
  size_type
  size() const;
};


template <typename A, typename V>
class FunctionMaxima<A, V>::point_type
{
private:
  friend class FunctionMaxima;
  A_ptr a;
  V_ptr v;
  point_type(const A_ptr &_arg)
    : a(_arg)

  {}
  point_type(const A_ptr &_arg, const V_ptr &_value)
    : a(_arg)
    , v(_value)
  {}

public:
  // Zwraca argument funkcji.
  const A &
  arg() const
  {
    return *a;
  }

  // Zwraca wartość funkcji w tym punkcie.
  const V &
  value() const
  {
    return *v;
  }
};


template <typename A, typename V>
struct FunctionMaxima<A, V>::cmp
{
  bool
  operator()(const point_type &a, const point_type &b) const noexcept
  {
    a.arg();
    b.arg();
    if (a.arg() < b.arg())
      return true;
    return false;
  }
};


template <typename A, typename V>
struct FunctionMaxima<A, V>::cmpMax
{
  bool
  operator()(const point_type &a, const point_type &b) const noexcept
  {
    // kiedy jest wieksze:
    if ((b.value() < a.value()))
      return true;

    // kiedy jest mniejsze:
    if (a.value() < b.value())
      return false;

    // kiedy jest równe:
    if (a.arg() < b.arg())
      return true;
    return false;
  }
};


template <typename A, typename V>
void
FunctionMaxima<A, V>::check(iterator it) noexcept
{
  // clang-format off
//	  Powiemy, że x jest lokalnym maksimum funkcji f, gdy spełnione są dwa warunki:
//	  1) x jest najmniejszym (względem <) elementem dziedziny funkcji f lub
//	     f(x) nie jest mniejsze niż f(l), gdzie l jest największym elementem
//	     elementem dziedziny f, takim że l < x.
//	  2) x jest największym (względem <) elementem dziedziny funkcji f lub
//	     f(x) nie jest mniejsze niż f(r), gdzie r jest najmniejszym elementem
//	     dziedziny f, takim że x < r.
  // clang-format on


  if (valueSet.size() == 0)
    {
      maxValueSet.clear();
      return;
    }
  if (valueSet.size() == 1)
    {
      assert(maxValueSet.size() == 1);
      return;
    }
  auto next     = valueSet.upper_bound(*it);
  auto previous = valueSet.lower_bound(*it);
  ;
  if (previous != valueSet.begin())
    {
      --previous;
      if (it->value() < previous->value())
        maxValueSet.erase(*it);
    }

  if (next != valueSet.end())
    {
      auto tmp = next;
      ++tmp;
      // jesli nastepne jest podwojone;
      if (tmp != valueSet.end())
        {
          if (!(next->arg() < tmp->arg()) && !(tmp->arg() < next->arg()))
            {
              next = tmp;
            }
        }
      if (it->value() < next->value())
        maxValueSet.erase(*it);
    }
}


template <typename A, typename V>
FunctionMaxima<A, V>::FunctionMaxima()
{}


template <typename A, typename V>
FunctionMaxima<A, V>::FunctionMaxima(const FunctionMaxima &element)
{
  try
    {
      valueSet    = element.valueSet;
      maxValueSet = element.maxValueSet;
    }
  catch (...)
    {
      valueSet.clear();
      maxValueSet.clear();
      throw;
    }
}


template <typename A, typename V>
FunctionMaxima<A, V> &
FunctionMaxima<A, V>::operator=(const FunctionMaxima<A, V> &element)
{
  Data_t     first  = element.valueSet;
  Data_max_t second = element.maxValueSet;
  valueSet          = std::move(first);
  maxValueSet       = std::move(second);


  return *this;
}


template <typename A, typename V>
V const &
FunctionMaxima<A, V>::value_at(A const &a) const
{
  auto it = valueSet.find(point_type(std::make_shared<const A>(a)));
  if (it == valueSet.end())
    throw InvalidArg("invalid argument value");

  return it->value();
}


template <typename A, typename V>
void
FunctionMaxima<A, V>::set_value(A const &arg, V const &val)
{
  point_type toInsert =
    point_type(std::make_shared<const A>(arg), std::make_shared<const V>(val));
  if (valueSet.size() == 0)
    {
      valueSet.insert(toInsert);
      maxValueSet.clear();
      maxValueSet.insert(toInsert);
      return;
    }


  point_type tmp         = point_type(std::make_shared<const A>(arg));
  bool       toRemove    = false;
  bool       toRemoveMax = false;

  if (valueSet.find(tmp) != valueSet.end())
    {
      tmp = *valueSet.find(tmp);
      if (maxValueSet.find(tmp) != maxValueSet.end())
        toRemoveMax = true;

      toRemove = true;
    }


  iterator previous;
  iterator next;
  iterator present;
  bool     a = false, b = false, c = false, d = false;
  try
    {
      present = valueSet.insert(toInsert);
      a       = true;
      maxValueSet.insert(toInsert);
      b        = true;
      next     = valueSet.upper_bound(toInsert);
      previous = valueSet.lower_bound(toInsert);
      check(present);



      if (previous != valueSet.begin())
        {
          --previous;

          if (maxValueSet.find(*previous) == maxValueSet.end())
            {
              maxValueSet.insert(*previous);
              c = true;
            }
          check(previous);
        }


      if (next != valueSet.end())
        {
          if (maxValueSet.find(*next) == maxValueSet.end())
            {
              maxValueSet.insert(*next);
              d = true;
            }
          check(next);
        }
      if (toRemove)
        {
          valueSet.erase(valueSet.lower_bound(tmp));
          if (toRemoveMax)
            maxValueSet.erase(maxValueSet.find(tmp));
        }
    }
  catch (...)
    {
      if (a)
        {
          if (valueSet.find(toInsert) != valueSet.end())
            valueSet.erase(toInsert);
        }
      if (b)
        {
          if (maxValueSet.find(toInsert) != maxValueSet.end())
            maxValueSet.erase(toInsert);
        }
      if (c)
        {
          if (maxValueSet.find(*previous) != maxValueSet.end())
            maxValueSet.erase(*previous);
        }
      if (d)
        {
          if (maxValueSet.find(*next) != maxValueSet.end())
            maxValueSet.erase(*next);
        }
      throw;
    }
}


template <typename A, typename V>
void
FunctionMaxima<A, V>::erase(A const &a)
{
  iterator it = valueSet.find(point_type(std::make_shared<const A>(a)));
  if (it == valueSet.end())
    throw InvalidArg("invalid argument value");

  if (valueSet.size() == 1)
    {
      valueSet.clear();
      maxValueSet.clear();
      return;
    }



  point_type maxForErase = *it;
  auto       next        = it;
  ++next;
  auto previous      = it;
  bool isPreviousMax = false;
  bool isNextMax     = false;

  try
    {
      if (valueSet.begin() != it)
        {
          --previous;
          if (maxValueSet.find(*previous) == maxValueSet.end())
            {
              maxValueSet.insert(*previous);
              isPreviousMax = true;
            }
        }
      if (next != valueSet.end())
        {
          if (maxValueSet.find(*next) == maxValueSet.end())
            {
              maxValueSet.insert(*next);
              isNextMax = true;
            }
        }
      valueSet.erase(it);
      if (valueSet.begin() != it)
        {
          check(previous);
        }
      if (next != valueSet.end())
        {
          check(next);
        }

      // usunac element
      if (maxValueSet.find(maxForErase) != maxValueSet.end())
        maxValueSet.erase(maxForErase);
    }
  catch (...)
    {
      if (isPreviousMax)
        maxValueSet.erase(*previous);
      if (isNextMax)
        maxValueSet.erase(*next);
      throw;
    }


  return;
}


template <typename A, typename V>
typename FunctionMaxima<A, V>::iterator
FunctionMaxima<A, V>::mx_begin() const
{
  return maxValueSet.begin();
}


template <typename A, typename V>
typename FunctionMaxima<A, V>::iterator
FunctionMaxima<A, V>::mx_end() const
{
  return maxValueSet.end();
}


template <typename A, typename V>
typename FunctionMaxima<A, V>::iterator
FunctionMaxima<A, V>::begin() const
{
  return valueSet.begin();
}


template <typename A, typename V>
typename FunctionMaxima<A, V>::iterator
FunctionMaxima<A, V>::end() const
{
  return valueSet.end();
}


template <typename A, typename V>
typename FunctionMaxima<A, V>::iterator
FunctionMaxima<A, V>::find(A const &a) const
{
  point_type tmp = point_type(std::make_shared<const A>(a));

  return valueSet.find(tmp);
}


template <typename A, typename V>
typename FunctionMaxima<A, V>::size_type
FunctionMaxima<A, V>::size() const
{
  return size_type(valueSet.size());
}
