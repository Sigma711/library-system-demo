/**
 * @file video_cd.h
 * @brief Declaration of class "VideoCd".
 *
 */

#ifndef LIBRARY_CORE_VIDEO_CD_H_
#define LIBRARY_CORE_VIDEO_CD_H_

#include "item.h"

namespace core {

/**
 * @brief Video CD entity.
 *
 */
class VideoCd : public Item {
 public:
  explicit VideoCd(unsigned long long number, const std::string& title,
                   const std::string& author, Rate rate,
                   const std::string& producer,
                   unsigned short year_of_producing,
                   unsigned long length_of_video);

  std::string GetInfoStr() const;

  ItemType GetItemType() const;

 private:
  std::string producer_;
  unsigned short year_of_producing_;
  unsigned long length_of_video_;
};

}  // namespace core

#endif  // !LIBRARY_CORE_VIDEO_CD_H_
