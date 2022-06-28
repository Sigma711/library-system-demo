/**
 * @file manager.h
 * @brief Declaration of class "Manager".
 *
 */

#ifndef LIBRARY_CORE_MANAGER_H_
#define LIBRARY_CORE_MANAGER_H_

#include <array>
#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "book.h"
#include "non_copyable_movable.h"
#include "painting.h"
#include "video_cd.h"

#define START_THE_LIBRARY_SYSTEM()          \
  do {                                      \
    core::Manager::GetManager()->Execute(); \
  } while (false);

namespace core {

/**
 * @brief "Manager" is the main controller of the whole system.
 *
 */
class Manager : NonCopyableMovable {
 public:
  static Manager* GetManager();

  void Execute();

 private:
  typedef std::map<unsigned long long, std::shared_ptr<Item>> Indexer;
  typedef std::array<Indexer, 3> Indexers;
  typedef std::unordered_map<std::string, std::string> UserPasswords;
  typedef std::unordered_set<unsigned long long> ItemOrderNumbers;
  typedef std::unordered_map<std::string, ItemOrderNumbers> UserItems;

  void ExecuteForUsers();
  void ExecuteForAdmins();

  void BrowseAllItems() const;
  void BrowseItemsByAType(const std::string& user_name) const;

  void BorrowAnItem(const std::string& user_name);
  void ReturnAnItem(const std::string& user_name);

  void AddAnItem();
  void DeleteAnItem();

  Indexers indexers_;

  UserPasswords user_passwords_;
  UserItems user_items_;
};

}  // namespace core

#endif  // !LIBRARY_CORE_MANAGER_H_
