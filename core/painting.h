/**
 * @file painting.h
 * @brief Declaration of class "Painting".
 *
 */

#ifndef LIBRARY_CORE_PAINTING_H_
#define LIBRARY_CORE_PAINTING_H_

#include <utility>

#include "item.h"

namespace core {

/**
 * @brief Painting entity.
 *
 */
class Painting : public Item {
 public:
  explicit Painting(
      unsigned long long number, const std::string& title,
      const std::string& author, Rate rate,
      const std::string& nationality_of_producing,
      const std::pair<unsigned short, unsigned short>& length_and_width);

  std::string GetInfoStr() const;

  ItemType GetItemType() const;

 private:
  std::string nationality_of_producing_;
  std::pair<unsigned short, unsigned short> length_and_width_;
};

}  // namespace core

#endif  // !LIBRARY_CORE_PAINTING_H_
