#ifndef CYKO_TYPE_REMOVE_EXTENT_H
#define CYKO_TYPE_REMOVE_EXTENT_H

namespace cyko {
namespace type {
namespace internal
{

  template <typename T>
    struct remove_extent_impl
    {
      using result = T;
    };

  template <typename T>
    struct remove_extent_impl<T[]>
    : remove_extent_impl<T>
    { };

  template <typename T, cyko::size_t I>
    struct remove_extent_impl<T[I]>
    : remove_extent_impl<T>
    { };

} // namespace cyko::type::internal

  template <typename T>
    using remove_extent = typename internal::remove_extent_impl<T>::result;

} // namespace cyko::type
} // namespace cyko

#endif
