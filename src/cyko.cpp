#include <iostream>
#include <cyko/env.h>

int main()
{
  cyko::size_t x = 1337;

  using namespace cyko::type;

  add_const<int> a = 1;
  add_volatile<char> b = 'c';
  add_cv<int[]> c = { 33, 44, 55 };

  remove_pointer<int*> pa = 1;
  remove_pointer<int**> pb = NULL;
  remove_pointer<int const*const> pc = NULL;
  remove_pointer<int const*const*volatile*const volatile> pd = NULL;
  remove_pointer<int*, true> qa = 1;
  remove_pointer<int**const, true> qb = NULL;
  remove_pointer<int const*const, true> qc = NULL;
  remove_pointer<int *const**, true> qd = NULL;
  remove_pointer<int volatile*const**const, true> qe = NULL;
  remove_pointer<int*[], true> qf = { &pa };
  cyko::type::add_const<int> xjj = 1;
  /*
  remove_const<int const volatile&&const volatile> e = 3;
  remove_const<int const volatile&const volatile> e = e;
  remove_const<int const volatile*const volatile> f = NULL;
  remove_const<int const volatile> g = 1;

  remove_volatile<int const volatile&&const volatile> e = 3;
  remove_volatile<int const volatile&const volatile> e = e;
  remove_volatile<int const volatile*const volatile> f = NULL;
  remove_volatile<int const volatile> g = 1;

  remove_pointer<int*> pa = 0;
  remove_pointer<int**> pb = 0;
  remove_pointer<int const*> pc = 0;
  remove_pointer<int const**> pd = 0;
  remove_pointer<int const*const volatile> pe = 0;
  remove_pointer<int const**> pf = 0;
  remove_pointer<int const*> pg = 0;
  remove_pointer<int const**> ph = 0;
  */
  std::cout << "Hello World!\n";
  std::cout << xjj
  << std::endl << ':'
  << sizeof(int)
  << std::endl << ':'
  << sizeof(cyko::int_t)
  << std::endl << ':'
  << sizeof(cyko::byte_t)
  << std::endl << ':'
  << sizeof(cyko::word_t)
  << std::endl << ':'
  << sizeof(cyko::dword_t)
  << std::endl << ':'
  << sizeof(cyko::qword_t);

  std::cout
  << std::endl
  << std::endl << size<int>::value
  << std::endl << size<char>::value
  << std::endl << size<int, int>::value
  << std::endl << size<int[]>::value
  << std::endl << size<int[3][4]>::value
  << std::endl << size<int[1][1][1][1]>::value
  << std::endl << size<int[][6][4]>::value
  << std::endl << size<int[5]>::value
  << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
