/**
 * @file item.h
 * @brief Declaration of class "Item".
 *
 */

#ifndef LIBRARY_CORE_ITEM_H_
#define LIBRARY_CORE_ITEM_H_

#include <string>

#include "non_copyable_movable.h"

namespace core {

/**
 * @brief Type of items.
 *
 */
enum ItemType {
  kUnknown = -1,
  kBook = 0,
  kVideoCd,
  kPainting,
};

/**
 * @brief Rate-level of items.
 *
 */
enum Rate {
  kUnrated = 0,
  kNormal,
  kAdult,
  kKid,
};

inline std::string GetRateStr(Rate rate) {
  switch (rate) {
    case Rate::kUnrated:
      return "unrated";
    case Rate::kNormal:
      return "normal";
    case Rate::kAdult:
      return "adult";
    case Rate::kKid:
      return "kid";
    default:
      return {};
  }
}

/**
 * @brief Base class of all 'item's ("Book", "VideoCd", "Painting").
 *
 */
class Item : NonCopyableMovable {
 public:
  explicit Item(unsigned long long number, const std::string& title,
                const std::string& author, Rate rate);
  virtual ~Item();

  virtual std::string GetInfoStr() const;

  virtual ItemType GetItemType() const;

  unsigned long long GetOrderNumber() const;

  void SetBorrowedFlag(bool is_borrowed);
  bool IsBorrowed() const;

 private:
  unsigned long long number_;
  std::string title_;
  std::string author_;
  Rate rate_;
  bool is_borrowed_;
};

}  // namespace core

#endif  // !LIBRARY_CORE_ITEM_H_
