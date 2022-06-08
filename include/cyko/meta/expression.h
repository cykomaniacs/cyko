#ifndef CYKO_META_EXPRESSION_H
#define CYKO_META_EXPRESSION_H

namespace cyko {
namespace meta {
namespace internal
{

  struct expression_tag { };

} // namespace cyko::meta::internal

  template <typename...>
    struct eller;
  template <typename...>
    struct och;
  template <typename, typename, typename>
    struct conditional;
  template <typename, typename>
    struct divide;
  template <typename, typename>
    struct equal;
  template <typename, typename>
    struct greater;
  template <typename, typename>
    struct less;
  template <typename, typename>
    struct minus;
  template <typename, typename>
    struct multiply;
  template <typename, typename>
    struct plus;
  template <typename>
    struct increase;
  template <typename>
    struct decrease;
  template <typename>
    struct zero;
  template <typename>
    struct negate;



  template <typename T, T V>
    struct expression
    : internal::expression_tag
    {
      using type = T;
      using tag  = internal::expression_tag;
      using self = expression<T, V>;


      static constexpr T value = V;

      constexpr   operator T() { return value; }
      constexpr T operator()() { return value; }

      /*
       + ----------
       | UTILITIES
       + -----
       */

      /// @b 1:unary
      using decrease = cyko::meta::decrease <self>;
      using increase = cyko::meta::increase <self>;
      using negate   = cyko::meta::negate   <self>;
      using zero     = cyko::meta::zero     <self>;

      /// @b 2:binary
      template <typename B> using equal    = cyko::meta::equal    <self, B>;
      template <typename B> using less     = cyko::meta::less     <self, B>;
      template <typename B> using greater  = cyko::meta::greater  <self, B>;
      /// @b 2:binary
      template <typename B> using divide   = cyko::meta::divide   <self, B>;
      template <typename B> using minus    = cyko::meta::minus    <self, B>;
      template <typename B> using multiply = cyko::meta::multiply <self, B>;
      template <typename B> using plus     = cyko::meta::plus     <self, B>;

      /// @b 3:ternary
      template <typename B, typename C> using conditional = cyko::meta::conditional <self, B, C>;

      /// @b X:variadic
      template <typename... Pack> using eller = cyko::meta::eller <self, Pack...>;
      template <typename... Pack> using och   = cyko::meta::och   <self, Pack...>;
    };

  template <cyko::bool_t V>
    struct bool_t
    : meta::expression<cyko::bool_t, V>
    {
      using self = bool_t<V>;
    };

  template <cyko::int_t V>
    struct int_t
    : meta::expression<cyko::int_t, V>
    {
      using self = int_t<V>;
    };

  template <cyko::size_t V>
    struct size_t
    : meta::expression<cyko::size_t, V>
    {
      using self = size_t<V>;
    };

  /**
   * @todo implement requirement / constraint / concept
   */

  template <typename T>
    struct is_expression
    #ifdef CYKO_BUILD_CXX_MSVC
    : meta::bool_t<__is_base_of(internal::expression_tag, T)>
    {
      using self = is_expression<T>;
    };
    #elif  CYKO_BUILD_CXX_LLVM
    : meta::bool_t<__is_base_of(internal::expression_tag, T)>
    {
      using self = is_expression<T>;
    };
    #else
    { static_assert(false, "unimplemented!"); };
    #endif


} // namespace cyko::meta
} // namespace cyko

#endif
