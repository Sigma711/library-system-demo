/**
 * @file painting.cc
 * @brief Implementation of class "Painting".
 *
 */

#include "painting.h"

#include "item.h"

using namespace core;

Painting::Painting(
    unsigned long long number, const std::string& title,
    const std::string& author, Rate rate,
    const std::string& nationality_of_producing,
    const std::pair<unsigned short, unsigned short>& length_and_width)
    : Item(number, title, author, rate),
      nationality_of_producing_(nationality_of_producing),
      length_and_width_(length_and_width) {}

std::string Painting::GetInfoStr() const {
  std::string main_str{Item::GetInfoStr()};
  int extra_str_len =
      ::snprintf(nullptr, static_cast<size_t>(0), "%s\t%hu,%hu",
                 nationality_of_producing_.c_str(), length_and_width_.first,
                 length_and_width_.second);
  char* new_extra_str = new char[static_cast<size_t>(extra_str_len)];
  ::snprintf(new_extra_str, static_cast<size_t>(extra_str_len), "%s\t%hu,%hu",
             nationality_of_producing_.c_str(), length_and_width_.first,
             length_and_width_.second);
  std::string extra_str{new_extra_str};
  delete[] new_extra_str;
  return main_str + extra_str;
}

ItemType Painting::GetItemType() const { return ItemType::kPainting; }
