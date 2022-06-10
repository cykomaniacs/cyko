#ifndef CYKO_META_EXPRESSION_H
#define CYKO_META_EXPRESSION_H

namespace cyko {
namespace meta {
namespace internal
{

  struct expression_tag { };
  template <typename T, T V>
    struct constant
    {
      using type = T;
      using tag  = expression_tag;

      static constexpr T value = V;

      constexpr explicit operator T()      { return value; }
      constexpr auto     operator()() -> T { return value; }
    };

} // namespace cyko::meta::internal

  template <typename, typename...> struct plus;
  template <typename, typename...> struct minus;
  template <typename, typename...> struct multiply;
  template <typename, typename...> struct divide;


  template <typename...> struct eller;
  template <typename...> struct och;

  template <typename, typename, typename> struct conditional;


  template <typename, typename> struct equal;
  template <typename>           struct zero;
  template <typename, typename> struct greater;
  template <typename, typename> struct less;

  template <typename> struct increase;
  template <typename> struct decrease;
  template <typename> struct negate;



  template <typename T, T V>
    struct expression
    : internal::constant<T, V>
    { /*
      using type = T;
      using tag  = internal::expression_tag;
      using self = expression<T, V>;


      static constexpr T value = V;

      constexpr      operator T()      { return value; }
      constexpr auto operator()() -> T { return value; }
      */

     using self = expression<T, V>;

      /*
       + ----------
       | UTILITIES
       + -----
       */

      /// @b 1:unary @e arithmetic
      using decrease = cyko::meta::decrease <self>;
      using increase = cyko::meta::increase <self>;
      /// @b 1:unary @e logical
      using negate   = cyko::meta::negate   <self>;
      using zero     = cyko::meta::zero     <self>;

      /// @b 2:binary @e logical
      template <typename B> using equal    = cyko::meta::equal    <self, B>;
      template <typename B> using less     = cyko::meta::less     <self, B>;
      template <typename B> using greater  = cyko::meta::greater  <self, B>;
      /// @b 2:binary @e arithmetic @todo @b test
      template <typename B, typename... Pack> using plus     = cyko::meta::plus     <self, B, Pack...>;
      template <typename B, typename... Pack> using minus    = cyko::meta::minus    <self, B, Pack...>;
      template <typename B, typename... Pack> using multiply = multiply <self, B, Pack...>;
      template <typename B, typename... Pack> using divide   = cyko::meta::divide   <self, B, Pack...>;

      /// @b 3:ternary @e logical
      template <typename B, typename C> using conditional = cyko::meta::conditional <self, B, C>;

      /// @b #:variadic @e logical
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
   * @todo implement @b number and @b boolean expressions.
   */

  template <cyko::bool_t V>
    struct boolean
    : meta::expression<cyko::bool_t, V>
    {
      using self = boolean<V>;
    };

  template <cyko::int_t V>
    struct number
    : meta::expression<cyko::int_t, V>
    {
      using self = number<V>;
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
    {
      static_assert(false, "unimplemented!");
    };
    #endif


} // namespace cyko::meta
} // namespace cyko

#endif
