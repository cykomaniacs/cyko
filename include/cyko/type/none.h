#ifndef CYKO_TYPE_NONE_H
#define CYKO_TYPE_NONE_H

namespace cyko {
namespace type
{

  /**
   * @brief std::void_t implementation.
   * @tparam X ignored.
   */

  template <typename... X>
    using none = cyko::void_t;

} // namespace cyko::type
} // namespace cyko

#endif
