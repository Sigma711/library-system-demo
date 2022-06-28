/**
 * @file item.cc
 * @brief Implementation of class "Item".
 *
 */

#include "item.h"

#include <stdio.h>

using namespace core;

Item::Item(unsigned long long number, const std::string& title,
           const std::string& author, Rate rate)
    : number_(number),
      title_(title),
      author_(author),
      rate_(rate),
      is_borrowed_(false) {}

Item::~Item() {}

std::string Item::GetInfoStr() const {
  int str_len = ::snprintf(nullptr, static_cast<size_t>(0),
                           "%llu\t%s\t%s\t%s\ts", number_, title_.c_str(),
                           author_.c_str(), GetRateStr(rate_).c_str());
  char* new_str = new char[static_cast<size_t>(str_len)];
  ::snprintf(new_str, static_cast<size_t>(str_len), "%lld\t%s\t%s\t%s\t",
             number_, title_.c_str(), author_.c_str(),
             GetRateStr(rate_).c_str());
  std::string info_str{new_str};
  delete[] new_str;
  return info_str;
}

ItemType Item::GetItemType() const { return ItemType::kUnknown; }

unsigned long long Item::GetOrderNumber() const { return number_; }

void Item::SetBorrowedFlag(bool is_borrowed) { is_borrowed_ = is_borrowed; }
bool Item::IsBorrowed() const { return is_borrowed_; }
