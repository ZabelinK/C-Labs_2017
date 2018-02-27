#ifndef ACTIONSFORBOOK_H
#define ACTIONSFORBOOK_H

#include "action.h"
#include "book.h"

class InsertActionBefore : public Action
{
public:
  InsertActionBefore(const std::string&, const note_t&);
  std::string exec(PhoneBook&, marks_map&, list_of_actions&, list_of_actions&) override;
  void rollback() override;

private:
  std::string mark_;
  const note_t note_;
  PhoneBook* target_;
  PhoneBook::const_robust_iterator* target_it_;
};

class InsertActionAfter : public Action
{
public:
  InsertActionAfter(const std::string&, const note_t&);
  std::string exec(PhoneBook&, marks_map&, list_of_actions&, list_of_actions&) override;
  void rollback() override;

private:
  std::string mark_;
  const note_t note_;
  PhoneBook* target_;
  PhoneBook::const_robust_iterator* target_it_;
};

class AddAction : public Action
{
public:
  AddAction(const note_t&);
  std::string exec(PhoneBook&, marks_map&, list_of_actions&, list_of_actions&) override;
  void rollback() override;

private:
  const note_t note_;
  PhoneBook* target_;
};

class EraseAction : public Action
{
public:
  EraseAction(const std::string&);
  std::string exec(PhoneBook&, marks_map&, list_of_actions&, list_of_actions&) override;
  void rollback() override;

private:
  std::string mark_;
  note_t note_;
  PhoneBook* target_;
  PhoneBook::const_robust_iterator* target_it_;
  bool last_elem_;
};

class InvalidAction : public Action
{
  std::string exec(PhoneBook &, marks_map &, list_of_actions &, list_of_actions &);
  void rollback();
};

#endif // ACTIONSFORBOOK_H
