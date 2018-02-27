#include "actionsforactions.h"

std::string UndoAction::exec(PhoneBook &, marks_map &, list_of_actions& from, list_of_actions& to)
{
  if(!from.empty())
  {
    std::shared_ptr<Action> action(from.back());
    from.pop_back();
    action->rollback();
    to.push_back(action);
  }
  return std::string();
}

void UndoAction::rollback()
{}

std::string RedoAction::exec(PhoneBook& book, marks_map& map, list_of_actions& to, list_of_actions& from)
{
  if(!from.empty())
  {
    std::shared_ptr<Action> action(from.back());
    action->exec(book, map, to, from);
    from.pop_back();
    to.push_back(action);
  }
  return std::string();
}

void RedoAction::rollback()
{}
