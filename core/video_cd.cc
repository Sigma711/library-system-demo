/**
 * @file video_cd.cc
 * @brief Implementation of class "VideoCd".
 *
 */

#include "video_cd.h"

#include "item.h"

using namespace core;

VideoCd::VideoCd(unsigned long long number, const std::string& title,
                 const std::string& author, Rate rate,
                 const std::string& producer, unsigned short year_of_producing,
                 unsigned long length_of_video)
    : Item(number, title, author, rate),
      producer_(producer),
      year_of_producing_(year_of_producing),
      length_of_video_(length_of_video) {}

std::string VideoCd::GetInfoStr() const {
  std::string main_str{Item::GetInfoStr()};
  int extra_str_len =
      ::snprintf(nullptr, static_cast<size_t>(0), "%s\t%u\t%lu",
                 producer_.c_str(), year_of_producing_, length_of_video_);
  char* new_extra_str = new char[static_cast<size_t>(extra_str_len)];
  ::snprintf(new_extra_str, static_cast<size_t>(extra_str_len), "%s\t%u\t%lu",
             producer_.c_str(), year_of_producing_, length_of_video_);
  std::string extra_str{new_extra_str};
  delete[] new_extra_str;
  return main_str + extra_str;
}

ItemType VideoCd::GetItemType() const { return ItemType::kVideoCd; }
