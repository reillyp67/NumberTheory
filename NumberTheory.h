#pragma once

#include <optional>
#include <set>
#include <vector>


class NumberTheory
{
public:


template <typename T>
bool is_a_group(std::vector<T> const & elements,
T (*op)(T const & lhs, T const & rhs));




// Calculate extended GCD of a and b.  x and y are out
// parameters and useful to find multiplicative inverses
static int gcdExtended(int a, int b, int & x, int & y);


// return multiplcative inverse of a mod m, if it exists
static auto multiplcativeInverse(int a, int m)
  -> std::optional<int>;


// return all nubers coprime with \param composite_number
static
std::vector<std::size_t> coprimes(std::size_t composite_number);


// Write to stdout the roots of the @param prime_number
static void draw_primitive_root(int prime_number);
static
void draw_primitive_root2(int composite_number);

static
void draw_primitive_root3(int composite_number);
static
void draw_primitive_root4(int const number);

static
void diffie_hellman_example(int(*func)(unsigned int, unsigned int, int));


// Calculates base^exponent mod modulo.
static
int modExp(unsigned int base, unsigned int exponent, int modulo);


static // Calculates b^e mod m
int modExp(int b, int e, int m);


static
void test_el_gammal();

// Iterative Function to calculate (x^y) % p in O(log y) time
static
int power(int x, unsigned int y, int p);




static
std::set<int> multiplicative_group(int elem, int mod);


static
std::vector<int> multiplicative_vector(int elem, int mod);


template <typename T>
static
void display(T const & multiplicative_group_residues);


static
void display_multiplicative_group_19();


static void display_multiplicative_group(int prime);




private:

};
