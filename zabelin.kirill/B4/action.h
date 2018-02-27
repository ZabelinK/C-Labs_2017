#ifndef ACTION_H
#define ACTION_H

#include <list>
#include <map>
#include <memory>

#include "book.h"

class Action;

using marks_map = std::map<std::string, PhoneBook::const_robust_iterator>;

using list_of_actions = std::list<std::shared_ptr<Action>>;

class Action : public std::enable_shared_from_this<Action>
{
public:
  virtual ~Action() = default;
  virtual std::string exec(PhoneBook&, marks_map&, list_of_actions&, list_of_actions&) = 0;
  virtual void rollback() = 0;

protected:
  bool done_;
};

#endif // ACTION_H
