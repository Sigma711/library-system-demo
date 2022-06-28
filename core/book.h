/**
 * @file book.h
 * @brief Declaration of class "Book".
 *
 */

#ifndef LIBRARY_CORE_BOOK_H_
#define LIBRARY_CORE_BOOK_H_

#include "item.h"

namespace core {

/**
 * @brief Book entity.
 *
 */
class Book : public Item {
 public:
  explicit Book(unsigned long long number, const std::string& title,
                const std::string& author, Rate rate,
                const std::string& publishing_house,
                const std::string& isbn_number, unsigned int number_of_pages);

  std::string GetInfoStr() const;

  ItemType GetItemType() const;

 private:
  std::string publishing_house_;
  std::string isbn_number_;
  unsigned int number_of_pages_;
};

}  // namespace core

#endif  // !LIBRARY_CORE_BOOK_H_
