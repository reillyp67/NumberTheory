#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>



bool unique(std::vector<std::size_t> const & vec)
{
  // deal with empty vectors or vector.size() == 1

  auto first = vec[0];
  for (auto iter = vec.cbegin() + 1; iter != vec.cend(); ++iter)
  {
    if (first == *iter)
    {
      return  false;
    }
    else
    {
      first = *iter;
    }
  }

  return true;
}


std::vector<std::size_t> generate_values(std::size_t const gen,
  std::size_t const modulus)
{
  std::vector<std::size_t> result{};

  for (auto i{1u}; i < modulus; ++i)
  {
    result.emplace_back( static_cast<std::size_t>(std::pow(gen, i)) % modulus);
  }

  return result;
}


template<typename T>
void display(std::vector<T> & vec)
{
  auto sort_crit = [](auto lhs, auto rhs) -> bool
  {
    return lhs < rhs;
  };
  std::sort(vec.begin(), vec.end(), sort_crit);


  for (auto i: vec)
  {
    std::cout << i << " ";
  }

  if (unique(vec))
  {
    std::cout << "And they are all unique\n";
  }
  else
  {
    std::cout << "And they are NOT all unique\n";
  }
}





int main()
{
  auto res = generate_values(3, 15);
  display( res );

  return 0;
}
