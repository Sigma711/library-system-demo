/**
 * @file manager.h
 * @brief Implementation of class "Manager".
 *
 */

#include "manager.h"

#include <vector>

#include "item.h"
#include "painting.h"
#include "video_cd.h"

#define PASSWORD "1234"

using namespace core;

Manager* Manager::GetManager() {
  static Manager manager;
  return &manager;
}

void Manager::Execute() {
  if (::system("clear") != 0) {
    ::exit(-1);
  }
  bool should_quit = false;
  while (!should_quit) {
    ::printf(
        "Welcome to this library management system!!!\nThis is the main "
        "menu.\nYou have three operation options:\n(1) Login as a user;\n(2) "
        "Login as an administrator;\n(3) Quit.\n");
    unsigned int operation_option;
    if (::scanf("%u", &operation_option) == EOF) {
      ::exit(-1);
    }
    ::getchar();
    if (::system("clear") != 0) {
      ::exit(-1);
    }
    switch (operation_option) {
      case 1:
        ExecuteForUsers();
        break;
      case 2:
        ExecuteForAdmins();
        break;
      case 3:
        should_quit = true;
        break;
      default:
        ::printf(
            "You input wrong info.\nPlease press any key to return the main "
            "menu.\n");
        ::getchar();
        should_quit = true;
    }
    if (::system("clear") != 0) {
      ::exit(-1);
    }
  }
}
void Manager::ExecuteForUsers() {
  std::string name;
  {
    ::printf("Please input user's name:\n");
    char nm[100];
    name = ::fgets(nm, 100, stdin);
    name.substr(0, name.size() - 1);
    bool is_new = true;
    if (user_passwords_.count(name) != 0) {
      is_new = false;
    }
    ::printf("Please input user's 4-digit password:\n");
    char passwd[100];
    if (::scanf("%s", passwd) == EOF) {
      ::exit(-1);
    }
    ::getchar();
    passwd[4] = '\0';
    std::string password{passwd};
    if (is_new) {
      user_passwords_.insert({name, password});
      user_items_.insert({name, {}});
    } else {
      if (password != user_passwords_[name]) {
        ::printf(
            "The password you input is wrong!\nPlease press any key to "
            "return.\n");
        ::getchar();
        return;
      }
    }
  }
  if (::system("clear") != 0) {
    ::exit(-1);
  }
  bool should_quit = false;
  while (!should_quit) {
    ::printf(
        "This is the menu for users.\nYou have four operation options:\n(1) "
        "Browse all items;\n(2) Borrow an item by its order number;\n(3) "
        "Return an item by its order number;\n(4) Browse iterms I borrowed by "
        "a specific type;\n(5) Quit.\n");
    unsigned int operation_option;
    if (::scanf("%u", &operation_option) == EOF) {
      ::exit(-1);
    }
    ::getchar();
    if (::system("clear") != 0) {
      ::exit(-1);
    }
    switch (operation_option) {
      case 1:
        BrowseAllItems();
        break;
      case 2:
        BorrowAnItem(name);
        break;
      case 3:
        ReturnAnItem(name);
        break;
      case 4:
        BrowseItemsByAType(name);
        break;
      case 5:
        should_quit = true;
        break;
      default:
        ::printf(
            "You input wrong info.\nPlease press any key to return the main "
            "menu.\n");
        ::getchar();
        should_quit = true;
    }
    if (::system("clear") != 0) {
      ::exit(-1);
    }
  }
}
void Manager::ExecuteForAdmins() {
  {
    ::printf("Please input administrators' 4-digit password:\n");
    char passwd[5];
    if (::scanf("%s", passwd) == EOF) {
      ::exit(-1);
    }
    ::getchar();
    passwd[4] = '\0';
    std::string password{passwd};
    if (PASSWORD != password) {
      ::printf(
          "The password you typed is false!\nPlease press any key to "
          "return.\n");
      ::getchar();
      return;
    }
  }
  if (::system("clear") != 0) {
    ::exit(-1);
  }
  bool should_quit = false;
  while (!should_quit) {
    ::printf(
        "This is the menu for administrators.\nYou have four operation "
        "options:\n(1) Browse all items;\n(2) Add an item by its order "
        "number;\n(3) Delete an item by its order number;\n(4) Quit.\n");
    unsigned int operation_option;
    if (::scanf("%u", &operation_option) == EOF) {
      ::exit(-1);
    }
    ::getchar();
    if (::system("clear") != 0) {
      ::exit(-1);
    }
    switch (operation_option) {
      case 1:
        BrowseAllItems();
        break;
      case 2:
        AddAnItem();
        break;
      case 3:
        DeleteAnItem();
        break;
      case 4:
        should_quit = true;
        break;
      default:
        ::printf("You input wrong info.\nPlease press any key to return.\n");
        ::getchar();
        should_quit = true;
    }
    if (::system("clear") != 0) {
      ::exit(-1);
    }
  }
}

void Manager::BrowseAllItems() const {
  ::printf(
      "Info below shows the status of records of three different types of "
      "items:\n\n(1) There are all books (Order Number, Title, Author, Rate, "
      "Publishing House, ISBN Number, Number of Pages, Is Borrowed):\n");
  for (const auto& index : indexers_[0]) {
    printf("%s\n", std::string{index.second->GetInfoStr() + "\t" +
                               (index.second->IsBorrowed() ? "true" : "flase")}
                       .c_str());
  }
  ::printf(
      "\n(2) There are all Video CDs (Order Number, Title, Author, Rate, "
      "Producer, Year of Producing, Length of Video, Is Borrowed):\n");
  for (const auto& index : indexers_[1]) {
    printf("%s\n", std::string{index.second->GetInfoStr() + "\t" +
                               (index.second->IsBorrowed() ? "true" : "flase")}
                       .c_str());
  }
  ::printf(
      "\n(3) There are all Paitings (Order Number, Title, Author, Rate, "
      "Nationality of Producing, Length and Width, Is Borrowed):\n");
  for (const auto& index : indexers_[2]) {
    printf("%s\n", std::string{index.second->GetInfoStr() + "\t" +
                               (index.second->IsBorrowed() ? "true" : "flase")}
                       .c_str());
  }
  ::printf("\nYou can press any key to return.\n");
  ::getchar();
}
void Manager::BrowseItemsByAType(const std::string& user_name) const {
  std::array<std::vector<std::shared_ptr<Item>>, 3> items;
  for (const auto& number : user_items_.at(user_name)) {
    for (const auto& indexer : indexers_) {
      if (indexer.count(number) != 0) {
        switch (indexer.at(number)->GetItemType()) {
          case ItemType::kBook:
            items[0].push_back(indexer.at(number));
            break;
          case ItemType::kVideoCd:
            items[1].push_back(indexer.at(number));
            break;
          case ItemType::kPainting:
            items[2].push_back(indexer.at(number));
            break;
          default:;
        }
        break;
      }
    }
  }
  ::printf(
      "There are all books you borrowed (Order Number, Title, Author, Rate, "
      "Publishing House, ISBN Number, Number of Pages):\n");
  for (const auto& item : items[0]) {
    ::printf("%s\n", item->GetInfoStr().c_str());
  }
  ::printf(
      "\nThere are all Video CDs you borrowed (Order Number, Title, Author, "
      "Rate, Producer, Year of Producing, Length of Video):\n");
  for (const auto& item : items[1]) {
    ::printf("%s\n", item->GetInfoStr().c_str());
  }
  ::printf(
      "\nThere are all Paitings (Order Number, Title, Author, Rate, "
      "Nationality of Producing, Length and Width):\n");
  for (const auto& item : items[2]) {
    ::printf("%s\n", item->GetInfoStr().c_str());
  }
  ::printf("\nYou can press any key to return.\n");
  ::getchar();
}

void Manager::BorrowAnItem(const std::string& user_name) {
  ::printf("Please input the order number:\n");
  unsigned long long number;
  if (::scanf("%llu", &number) == EOF) {
    ::exit(-1);
  }
  ::getchar();
  for (auto& indexer : indexers_) {
    if (indexer.count(number) != 0 && !indexer.at(number)->IsBorrowed()) {
      indexer.at(number)->SetBorrowedFlag(true);
      user_items_.at(user_name).insert(number);
      return;
    }
  }
  ::printf("You could not borrow the item!\nPlease press any key to return.\n");
  ::getchar();
}
void Manager::ReturnAnItem(const std::string& user_name) {
  ::printf("Please input the order number:\n");
  unsigned long long number;
  if (::scanf("%llu", &number) == EOF) {
    ::exit(-1);
  }
  ::getchar();
  for (auto& indexer : indexers_) {
    if (indexer.count(number) != 0 &&
        user_items_.at(user_name).count(number) != 0) {
      user_items_.at(user_name).erase(number);
      indexer.at(number)->SetBorrowedFlag(false);
      return;
    }
  }
  ::printf("You could not return the item!\nPlease press any key to return.\n");
  ::getchar();
}

void Manager::AddAnItem() {
  ::printf(
      "Choose the type of item you want to add:\n(1) Book;\n(2) Video CD;\n(3) "
      "Painting.\n(If you press 4, you will quit.)\n");
  unsigned int operation_option;
  if (::scanf("%u", &operation_option) == EOF) {
    ::exit(-1);
  }
  ::getchar();
  if (::system("clear") != 0) {
    ::exit(-1);
  }
  unsigned long long number;
  std::string title;
  char ttl[100];
  std::string author;
  char atr[100];
  int rt;
  auto GetRate = [](int rate) -> Rate {
    switch (rate) {
      case 1:
        return Rate::kNormal;
      case 2:
        return Rate::kAdult;
      case 3:
        return Rate::kKid;
      default:
        return Rate::kUnrated;
    }
  };
  Rate rate;
  std::string publishing_house;
  std::string isbn_number;
  std::string producer;
  std::string nationality_of_producing;
  switch (operation_option) {
    case 1:
      ::printf(
          "Please input Order Number, Title, Author, Rate, Publishing House, "
          "ISBN Number and Number of Pages:\n(Each entry should use single one "
          "line)\n");
      if (::scanf("%llu", &number) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      for (const auto& indexer : indexers_) {
        if (indexer.count(number) != 0) {
          ::printf(
              "The order number you input is existed.\nPlease press any key to "
              "return.\n");
          ::getchar();
          return;
        }
      }
      title = ::fgets(ttl, 100, stdin);
      title = title.substr(0, title.size() - 1);
      author = ::fgets(atr, 100, stdin);
      author = author.substr(0, author.size() - 1);
      if (::scanf("%d", &rt) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      rate = GetRate(rt);
      char ph[100];
      publishing_house = ::fgets(ph, 100, stdin);
      publishing_house =
          publishing_house.substr(0, publishing_house.size() - 1);
      char in[100];
      isbn_number = ::fgets(in, 100, stdin);
      isbn_number = isbn_number.substr(0, isbn_number.size() - 1);
      unsigned int number_of_pages;
      if (::scanf("%u", &number_of_pages) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      indexers_[0].insert(
          {number,
           std::make_shared<Book>(number, title, author, rate, publishing_house,
                                  isbn_number, number_of_pages)});
      break;
    case 2:
      ::printf(
          "Please input Order Number, Title, Author, Rate, Producer, Year of "
          "Producing and Length of Video:\n(Each entry should use single one "
          "line)\n");
      if (::scanf("%llu", &number) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      for (const auto& indexer : indexers_) {
        if (indexer.count(number) != 0) {
          ::printf(
              "The order number you input is existed.\nPlease press any key to "
              "return.\n");
          ::getchar();
          return;
        }
      }
      title = ::fgets(ttl, 100, stdin);
      title = title.substr(0, title.size() - 1);
      author = ::fgets(atr, 100, stdin);
      author = author.substr(0, author.size() - 1);
      if (::scanf("%d", &rt) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      rate = GetRate(rt);
      char pd[100];
      producer = ::fgets(pd, 100, stdin);
      producer = producer.substr(0, producer.size() - 1);
      unsigned short year_of_producing;
      if (::scanf("%hu", &year_of_producing) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      unsigned long length_of_video;
      if (::scanf("%lu", &length_of_video) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      indexers_[1].insert({number, std::make_shared<VideoCd>(
                                       number, title, author, rate, producer,
                                       year_of_producing, length_of_video)});
      break;
    case 3:
      ::printf(
          "Please input Order Number, Title, Author, Rate, Nationality of "
          "Producing, Length and Width:\n(Each entry should use single "
          "one line)\n");
      if (::scanf("%llu", &number) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      for (const auto& indexer : indexers_) {
        if (indexer.count(number) != 0) {
          ::printf(
              "The order number you input is existed.\nPlease press any key to "
              "return.\n");
          ::getchar();
          return;
        }
      }
      title = ::fgets(ttl, 100, stdin);
      title = title.substr(0, title.size() - 1);
      author = ::fgets(atr, 100, stdin);
      author = author.substr(0, author.size() - 1);
      if (::scanf("%d", &rt) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      rate = GetRate(rt);
      char nop[100];
      nationality_of_producing = ::fgets(nop, 100, stdin);
      nationality_of_producing = nationality_of_producing.substr(
          0, nationality_of_producing.size() - 1);
      unsigned short lgt;
      if (::scanf("%hu", &lgt) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      unsigned short wdt;
      if (::scanf("%hu", &wdt) == EOF) {
        ::exit(-1);
      }
      ::getchar();
      indexers_[2].insert(
          {number, std::make_shared<Painting>(
                       number, title, author, rate, nationality_of_producing,
                       std::pair<unsigned short, unsigned short>{lgt, wdt})});
      break;
    case 4:
      break;
    default:
      ::printf("You input wrong info.\nPlease press any key to return.\n");
      ::getchar();
  }
}
void Manager::DeleteAnItem() {
  ::printf("Input the order number of the item you want to delete:\n");
  unsigned long long order_number;
  if (::scanf("%llu", &order_number) == EOF) {
    ::exit(-1);
  }
  ::getchar();
  for (auto& indexer : indexers_) {
    if (indexer.count(order_number) != 0) {
      if (indexer.at(order_number)->IsBorrowed()) {
        ::printf("The item is borrowed.\nPlease press any key to return.\n");
        ::getchar();
      } else {
        indexer.erase(order_number);
      }
      return;
    }
  }
  ::printf("The item does not exist.\nPlease press any key to return.\n");
  ::getchar();
}
