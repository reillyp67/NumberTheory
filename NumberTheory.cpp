
#include "NumberTheory.h"
#include "Matrix.h"
#include "polynomial.h"


#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <optional>
#include <set>
#include <vector>






template <typename T>
bool NumberTheory::is_a_group(std::vector<T> const & elements,
T (*op)(T const & lhs, T const & rhs))
{
  // 1) Each element must have inverse
  // 2) There must be an identity member for each element
  // 3) Must be associative for all elements

  // 4) If commutative i.e. ab == ba then is an abelian
  // group.


  return T{};
}




// Calculate extended GCD of a and b.  x and y are out
// parameters and useful to find multiplicative inverses
int NumberTheory::gcdExtended(int a, int b, int & x, int & y)
{
    if (a == 0) // Base Case
    {
        x = 0;
        y = 1;
        return b;
    }

    int x1{}, y1{}; // To store results of recursive call
    int gcd = gcdExtended(b%a, a, x1, y1);

    // Update x and y using results of recursive call
    x = y1 - (b/a) * x1;
    y = x1;

    return gcd;
}




// Function to find modulo inverse of a mod m
auto NumberTheory::multiplcativeInverse(int a, int m)
  -> std::optional<int>
{
    int x{0}, y{0};
    const int gcd = gcdExtended(a, m, x, y);
    if (gcd != 1) // if gcd(a, m) != 1
    {
        std::cout << "Inverse of " << a << " mod " << m << " doesn't exist";
        std::cout << ".  GCD(" << a << ", " << m << ") != 1\n";
        return std::nullopt;
    }
    else
    {
        std::cout << "x is: " << x << "\n";
        std::cout << "y is: " << y << "\n";
        // m is added to handle negative x
        //int res = ((x % m) + m) % m;

        return gcd;
    }
}


/*
// A naive method to find modulor multiplicative inverse of
// 'a' under modulo 'm'
int NumberTheory::modInverse(int a, int m)
{
    a = a%m;
    for (int x=1; x<m; x++)
    {
       if ((a*x) % m == 1)
       {
          return x;
       }
    }

    return -1;
}
*/


// Iterative Function to calculate (x^y) % p in O(log y) time
int NumberTheory::power(int x, unsigned int y, int p)
{
    int res = 1;      // Initialize result

    x = x % p;  // Update x if it is more than or equal to p

    while (y > 0)
    {
        if (y & 0x01) // If y is odd, multiply x with result
        {
            res = (res*x) % p;
        }

        // y must be even now
        y = y>>1; // equivalent to: y = y/2
        x = (x*x) % p;
    }
    return res;
}



void draw_table(int prime_number)
{
  std::cout << "Primitive root for " << prime_number << '\n';
  std::cout << "\t<--- Powers horizontally---> \n";
  std::cout << "  ";
  for (int p = 1; p < prime_number; ++p)
  {
    std::cout <<  std::setw(3) << std::setfill(' ') << p << ' ';
  }
  std::cout << std::endl;

  for (int p = 0; p < prime_number; ++p)
  {
    std::cout << "====";
  }
  std::cout << std::endl;
}


void draw_table2(std::vector<std::size_t> const & values,
  std::size_t composite_number)
{
  std::cout << "Primitive root for " << composite_number << '\n';
  std::cout << "\t<--- Powers horizontally---> \n";
  for (auto p : values)
  {
    std::cout <<  std::setw(2) << p << ' ';
  }
  std::cout << std::endl;

  for (unsigned int p = 1; p < values.size(); ++p)
  {
    std::cout << "===";
  }
  std::cout << "==" << std::endl;
}


// In modular arithmetic, a branch of number theory, a number g is a primitive
// root modulo n if every number a coprime to n is congruent to a power of g
// modulo n. That is, for every integer a coprime to n, there is an integer k
// such that gk ≡ a (mod n). Such k is called the index or discrete logarithm
// of a to the base g modulo n.
//
// In other words, g is a generator of the multiplicative group of integers
// modulo n.
void NumberTheory::draw_primitive_root(int prime_number)
{
  draw_table(prime_number);

  for (int i = 1; i < prime_number; ++i)
  {
    int x{}, y{};
    // Candidates must be coprimewith prime_number
    if (gcdExtended(i, prime_number, x, y) != 1)
    {
      continue;
    }
    std::vector<int> residues{};
    for (int j = 1; j < prime_number; ++j)
    {
      residues.push_back(power(i, j, prime_number));
      std::cout <<  std::setw(2) << residues.back() << " ";
    }

    auto residues_copy{ residues };
    std::sort(residues_copy.begin(), residues_copy.end());
    auto copy_iter = std::unique( residues_copy.begin(), residues_copy.end());
    auto distance = std::distance(residues_copy.begin(), copy_iter);

    if ( distance == (prime_number - 1))
    {
      std::cout << " Primitive root";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}


std::vector<std::size_t> NumberTheory::coprimes(std::size_t composite_number)
{
  std::vector<std::size_t> coprimes{};

  int x{}, y{}; // Unused
  for (std::size_t i = 0; i < composite_number; ++i)
  {
    if (gcdExtended(i, composite_number, x, y) == 1)
    {
      coprimes.push_back(i);
    }
  }

  return coprimes;
}


std::size_t phi(std::size_t number)
{

  return 12;
}


template <typename T>
void display(std::vector<T> const & elements)
{
  for (auto & elem : elements)
  {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

// a number g is a primitive root modulo n if every number a coprime to n is
// congruent to a power of g modulo n. That is, for every integer a coprime to
// n, there is an integer k such that gk ≡ a (mod n). Such k is called the index
// or discrete logarithm of a to the base g modulo n.
// In other words, g is a generator of the multiplicative group of integers
// modulo n
void NumberTheory::draw_primitive_root4(int const number)
{
  auto const coprime_values = coprimes(number);
  //display(coprime_values);

  draw_table(number); // todo hanle coprimes

  std::vector<std::size_t> residues{};

  for (auto an_element_from_residues : coprime_values)
  {
      for (auto exponent = 1; exponent < number; ++exponent)
      {
        residues.emplace_back(power(an_element_from_residues, exponent, number));
        //std::cout <<  std::setw(2) << residues.back() << " ";
      }


      auto residues_copy{ residues };
      std::sort(residues_copy.begin(), residues_copy.end());
      auto new_end = std::unique(residues_copy.begin(), residues_copy.end());
      residues_copy.erase(new_end, residues_copy.end());


      if (residues_copy == coprime_values)
      {
        std::cout << std::setw(2) << std::setfill(' ') << an_element_from_residues
          << ": ";
        for (auto elem : residues)
        {
          std::cout << std::setw(2) << std::setfill(' ') << elem << "  ";
        }

        auto iter = std::find(residues.begin(), residues.end(), 1);
        auto order{std::distance(residues.begin(), iter)};
        std::cout << "Primitive root, of order " << (order + 1) << "\n";
      }
      else
      {
        //std::cout << "Not a primitve root\n";
      }
      residues.clear();
  }
}


void NumberTheory::draw_primitive_root3(int composite_number)
{
  auto const coprime_values = coprimes(composite_number);
  //draw_table2(coprime_values, composite_number);

  draw_table(composite_number);

  for (int i = 1; i < composite_number; ++i)
  {
    int x{}, y{};
    // Candidates must be coprimewith prime_number
    if (gcdExtended(i, composite_number, x, y) != 1)
    {
      continue;
    }
    std::vector<int> residues{};
    for (int j = 1; j < composite_number; ++j)
    {
      residues.push_back(power(i, j, composite_number));
      std::cout <<  std::setw(2) << residues.back() << " ";
    }

    auto residues_copy{ residues };
    std::sort(residues_copy.begin(), residues_copy.end());
    auto copy_iter = std::unique( residues_copy.begin(), residues_copy.end());
    auto distance = std::distance(residues_copy.begin(), copy_iter);

    if ( distance == (composite_number - 1))
    {
      std::cout << " Primitive root";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}




void NumberTheory::draw_primitive_root2(int composite_number)
{
  auto const coprime_values = coprimes(composite_number);
  draw_table2(coprime_values, composite_number);

  for (auto const value : coprime_values) // Each coprime
  {
    std::vector<std::size_t> residues{};
    for (auto coprime_value : coprime_values)
    {
      residues.push_back(power(value, coprime_value, composite_number));
      if (value == 15)
        std::cout << value << " ^ " << coprime_value << " mod " << composite_number << " = " <<
          residues.back() << ", ";
      else
        std::cout <<  std::setw(2) << residues.back() << " ";
    }

    auto residues_copy{ residues };
    std::sort(residues_copy.begin(), residues_copy.end());

    if ( residues_copy == coprime_values)
    {
      std::cout << " Primitive root";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}


/*
void NumberTheory::diffie_hellman_example(int(*func)(int, int, int))
{
  int prime = 941;
  int generator = 627; // A primitive root of 941
  std::cout << "Freely publish the generator " << generator << " and prime " << prime << ".  In "
  "the real world, these are hundreds of digits long\n";

  int alice_private = 347;
  int alice_public = power(generator, alice_private, prime);
  int bob_private = 781;
  int bob_public = power(generator, bob_private, prime);


  std::cout << "Alice public is " << alice_public << '\n';
  std::cout << "Bob public is " << bob_public << '\n';

  std::cout << "Now, some time later ...\n";

  std::cout << "Alice computes " << power(bob_public, alice_private, prime) << '\n';
  std::cout << "Bob computes " << power(alice_public, bob_private, prime) << '\n';
}
*/

void NumberTheory::diffie_hellman_example(int(*func)(unsigned int, unsigned int, int))
{
  unsigned int prime = 941;
  unsigned int generator = 627; // A primitive root of 941
  std::cout << "Freely publish the generator " << generator << " and prime " << prime << ".  In "
  "the real world, these are hundreds of digits long\n";

  int alice_private = 347;
  int alice_public = func(generator, alice_private, prime);
  int bob_private = 781;
  int bob_public = func(generator, bob_private, prime);


  std::cout << "Alice public is " << alice_public << '\n';
  std::cout << "Bob public is " << bob_public << '\n';

  std::cout << "Now, some time later ...\n";

  std::cout << "Alice computes " << func(bob_public, alice_private, prime) << '\n';
  std::cout << "Bob computes " << func(alice_public, bob_private, prime) << '\n';
}


// Calculates b^e mod m
int NumberTheory::modExp(unsigned int b, unsigned int e, int m)
{
  int remainder{};
  int x = 1;

  while (e != 0)
  {
    remainder = e % 2;
    e/= 2;

    if (remainder == 1)
    {
      x = (x * b) % m;
    }

    b= (b * b) % m; // New base equal b^2 % m
  }
  return x;
}


void NumberTheory::test_el_gammal()
{
  //unsigned int g{47};
  //unsigned int prime{31};
  //int el_gammal_value = power(g, p, prime);
  //int inverse = g ^ (p - 1 - a) mod p
}



// Calculates b^e mod m
int NumberTheory::modExp(int b, int e, int m)
{
  int remainder{};
  int x = 1;

  while (e != 0)
  {
    remainder = e % 2;
    e/= 2;

    if (remainder == 1)
    {
      x = (x * b) % m;
    }

    b= (b * b) % m; // New base equal b^2 % m
  }
  return x;
}


std::set<int> NumberTheory::multiplicative_group(int elem, int mod)
{
    std::set<int> result{};
    for(int y = 0; y < mod; ++y)
    {
        auto val = modExp(elem, y, mod);
        auto pair = result.insert(val);

        constexpr bool debug{false};
        if constexpr (debug)
        {
            if (pair.second)
            {
                std::cout << "Inserted " << val << '\n';
            }
            else
            {
                std::cout << "Failed with " << val << '\n';
            }
        }
    }

    return result;
}



std::vector<int> NumberTheory::multiplicative_vector(int elem, int mod)
{
    std::vector<int> result{};
    for(int y = 1; y < mod; ++y)
    {
        auto val = modExp(elem, y, mod);
        result.push_back(val);
    }

    return result;
}



template <typename T>
void NumberTheory::display(T const & multiplicative_group_residues)
{
    std::size_t counter{0u};
    auto display_func = [&counter] (std::set<int>::value_type elem) -> void
    {
        std::cout << elem << ' ';
        ++counter;
        if (counter % 32 == 0)
            std::cout << '\n';
    };


    std::for_each(multiplicative_group_residues.cbegin(), multiplicative_group_residues.cend(), display_func);
    std::cout << '\n';
}


void NumberTheory::display_multiplicative_group_19()
{
    auto prime = 19;
    for (int i = 0; i < prime; ++i)
    {
        auto result = multiplicative_group(i, prime);
        //std::cout << "The size of the group is " << result.size() << std::endl;
        std::cout << "G(" << i << "):: ";
        display(result);
    }
}



void NumberTheory::display_multiplicative_group(int prime)
{
    for (int i = 1; i < prime; ++i)
    {
        auto result = multiplicative_group(i, prime);

        //std::cout << "The size of the group is " << result.size() << std::endl;

        //auto result = multiplicative_vector(i, prime);
        std::cout << "G(" << i << "):: ";

        display(result);
    }
}




int main()
{
  /*
  auto res47 = NumberTheory::multiplcativeInverse(7, 31); // -> std::optional<int>
  if (res47)
  {
    std::cout << "The GCD(7, 31) = " << res47.value() << '\n';
  }
  */
  NumberTheory::draw_primitive_root(7);
  NumberTheory::draw_primitive_root(9);
  NumberTheory::draw_primitive_root(11);
  NumberTheory::draw_primitive_root(13);
  NumberTheory::draw_primitive_root(17);
  NumberTheory::draw_primitive_root(19);

  //  return 0;
  //NumberTheory::draw_primitive_root2(26);

  //NumberTheory::draw_primitive_root4(26);

  auto res_gcd = NumberTheory::multiplcativeInverse(7814, 17449);
  std::cout << "Res GCD: " << res_gcd.value() << '\n';
  auto second_res = NumberTheory::modExp(7814, -1, 17449);
  std::cout << "2nd Res GCD: " << second_res << '\n';

//return 0;
  for (int i = 2; i < 20; ++i)
  NumberTheory::draw_primitive_root4(i);

  //NumberTheory::draw_primitive_root(14);
  //NumberTheory::draw_primitive_root(23);
  //NumberTheory::draw_primitive_root(24);
  //NumberTheory::draw_primitive_root(16);
  //NumberTheory::draw_primitive_root(17);

return 0;
  NumberTheory::display_multiplicative_group(7);
  NumberTheory::display_multiplicative_group(7+12);
  return 0;


    NumberTheory::test_el_gammal();
    return 1;


    NumberTheory::diffie_hellman_example(NumberTheory::modExp);
    return 1;

    NumberTheory::draw_primitive_root(19);
    return 1;

    // x and y are the multiplcative inverses
    int a{27}, b{2}, x{}, y{};
    auto res = NumberTheory::gcdExtended(a, b, x, y);
    std::cout << "The CGD(" << a << ", " << b << ") is " << res << "\n";
    std::cout << "The multiplcative inverses are " << x << " and " << y << '\n';
    return 0;
    /*
      int a = 3, m = 11;
      std::cout << "The mod inverse of " << a << " and modulus " << m << " is ";
      modInverse(a, m);
      std::cout << '\n';
    */




    NumberTheory::display_multiplicative_group_19();
    return 0;


    auto result = NumberTheory::multiplicative_group(2, 1031);
    std::cout << "The size of the group is " << result.size() << std::endl;
    //display(result);
    return 0;


/*
    int a = 3, m = 11;
    std::cout << "The mod inverse of " << a << " and modulus " << m << " is ";
    modInverse(a, m);
    std::cout << '\n';
*/
}
