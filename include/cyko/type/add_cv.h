#ifndef CYKO_TYPE_ADD_CV_H
#define CYKO_TYPE_ADD_CV_H

#include <cyko/type/add_const.h>
#include <cyko/type/add_volatile.h>

namespace cyko {
namespace type
{

  template <typename T>
    using add_cv = type::add_const<type::add_volatile<T>>;

} // namespace cyko::type
} // namespace cyko

#endif
