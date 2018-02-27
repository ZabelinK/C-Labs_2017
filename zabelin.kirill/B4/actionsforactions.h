#ifndef ACTIONSFORACTIONS_H
#define ACTIONSFORACTIONS_H

#include "action.h"

class UndoAction : public Action
{
public:
  std::string exec(PhoneBook&, marks_map&, list_of_actions&, list_of_actions&);
  void rollback();
};

class RedoAction : public Action
{
public:
  std::string exec(PhoneBook&, marks_map&, list_of_actions&, list_of_actions&);
  void rollback();
};

#endif // ACTIONSFORACTIONS_H
