/**
 * @file book.cc
 * @brief Implementation of class "Book".
 *
 */

#include "book.h"

#include "item.h"

using namespace core;

Book::Book(unsigned long long number, const std::string& title,
           const std::string& author, Rate rate,
           const std::string& publishing_house, const std::string& isbn_number,
           unsigned int number_of_pages)
    : Item(number, title, author, rate),
      publishing_house_(publishing_house),
      isbn_number_(isbn_number),
      number_of_pages_(number_of_pages) {}

std::string Book::GetInfoStr() const {
  std::string main_str{Item::GetInfoStr()};
  int extra_str_len = ::snprintf(nullptr, static_cast<size_t>(0), "%s\t%s\t%u",
                                 publishing_house_.c_str(),
                                 isbn_number_.c_str(), number_of_pages_);
  char* new_extra_str = new char[static_cast<size_t>(extra_str_len)];
  ::snprintf(new_extra_str, static_cast<size_t>(extra_str_len), "%s\t%s\t%u",
             publishing_house_.c_str(), isbn_number_.c_str(), number_of_pages_);
  std::string extra_str{new_extra_str};
  delete[] new_extra_str;
  return main_str + extra_str;
}

ItemType Book::GetItemType() const { return ItemType::kBook; }
