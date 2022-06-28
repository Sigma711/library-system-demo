/**
 * @file non_copyable_movable.h
 * @brief Base classes for disable Copy" semantics and "Move" semantics (can be
 * used to build "Singleton" patterns).
 *
 */

#ifndef LIBRARY_CORE_NON_COPYABLE_MOVABLE_H_
#define LIBRARY_CORE_NON_COPYABLE_MOVABLE_H_

namespace core {

/**
 * @brief "Copy" semantics and "Move" semantics of the class that inherits
 * it will be prohibited.
 *
 */
class NonCopyableMovable {
 protected:
  NonCopyableMovable() = default;
  ~NonCopyableMovable() = default;

 private:
  NonCopyableMovable(const NonCopyableMovable&) = delete;
  NonCopyableMovable& operator=(const NonCopyableMovable&) = delete;
  NonCopyableMovable(NonCopyableMovable&&) = delete;
};

}  // namespace core

#endif  // !LIBRARY_CORE_NON_COPYABLE_MOVABLE_H_
