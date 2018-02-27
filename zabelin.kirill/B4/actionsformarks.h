#ifndef ACTIONFORMARKS_H
#define ACTIONFORMARKS_H

#include <memory>
#include <map>

#include "action.h"
#include "book.h"

class StoreAction : public Action
{
public:
  StoreAction(const std::string& old_mark, const std::string& new_mark);
  std::string exec(PhoneBook&, marks_map&, list_of_actions&, list_of_actions&);
  void rollback();

private:
  const std::string old_mark_;
  const std::string new_mark_;
  marks_map* target_;
};

class MoveAction : public Action
{
public:
  MoveAction(const std::string& mark, const std::string& step);
  std::string exec(PhoneBook&, marks_map&, list_of_actions&, list_of_actions&);
  void rollback();

private:
  const std::string mark_;
  const std::string step_;
  int diff_;
  marks_map* target_;
};

class ShowAction : public Action
{
public:
  ShowAction(const std::string&);
  std::string exec(PhoneBook&, marks_map&, list_of_actions&, list_of_actions&);
  void rollback();

private:
  std::string mark_;
};

#endif // ACTIONFORMARKS_H
