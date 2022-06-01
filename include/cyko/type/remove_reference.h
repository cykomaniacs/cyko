#ifndef CYKO_TYPE_REMOVE_REFERENCE_H
#define CYKO_TYPE_REMOVE_REFERENCE_H

namespace cyko {
namespace type {
namespace internal
{

  template <typename T>
    struct remove_reference_impl
    {
      using result = T;
    };

  template <typename T>
    struct remove_reference_impl<T&>
    {
      using result = T;
    };

  template <typename T>
    struct remove_reference_impl<T&&>
    {
      using result = T;
    };

} // namespace cyko::type::internal

  template <typename T>
    using remove_reference = typename internal::remove_reference_impl<T>::result;

} // namespace cyko::type
} // namespace cyko

#endif
