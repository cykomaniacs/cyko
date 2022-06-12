//#include <iostream>
import <iostream>;
import neta;

auto main()
  -> int
{
  mods::neta::testa<int>::type vhfjfe = 87;
  cyko::size_t x = 1337;
  cyko::size_t z = 1337;
  using namespace cyko::type;

  add_const<int> a = 1;
  add_volatile<char> b = 'c';
  add_cv<int[]> c = { 33, 44, 55 };

  remove_pointer<int*> pa = 1;
  remove_pointer<int**> pb = nullptr;
  remove_pointer<int const*const> pc = NULL;
  remove_pointer<int const*const*volatile*const volatile> pd = nullptr;
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

  std::cout << "Hello World!" << std::endl;

  std::cout
    << std::endl << ":   int   : "
    << sizeof(int)
    << std::endl << ":   int_t : "
    << sizeof(cyko::int_t)
    << std::endl << ":  byte_t : "
    << sizeof(cyko::byte_t)
    << std::endl << ":  word_t : "
    << sizeof(cyko::word_t)
    << std::endl << ": dword_t : "
    << sizeof(cyko::dword_t)
    << std::endl << ": qword_t : "
    << sizeof(cyko::qword_t);

  std::cout
    << std::endl << "qf = { &pa }" << qf[0]
    << std::endl
    << std::endl << size<int>::value
    << std::endl << size<char>::value
    << std::endl << size<int, int>::value
    << std::endl << size<int[3]>::value
    << std::endl << size<int[3][4]>::value
    << std::endl << size<int[1][1][1][1]>::value
    << std::endl << size<int[2][6][4]>::value
    << std::endl << size<int[5]>::value
    << std::endl;
}
