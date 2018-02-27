#include "actionsforbook.h"
#include "book.h"
#include "errors.h"

InsertActionBefore::InsertActionBefore(const std::string& mark, const note_t& note):
  Action(),
  mark_(mark),
  note_(note),
  target_(nullptr),
  target_it_(nullptr)
{}

std::string InsertActionBefore::exec(PhoneBook& book, marks_map& marks, list_of_actions& stack, list_of_actions& re_stack)
{
  if(!done_)
  {
    auto it = marks.find(mark_);
    if(it != marks.end())
    {
      book.insert(it->second, note_);
      target_it_ = &it->second;
      target_ = &book;
      stack.push_back(shared_from_this());
      if(shared_from_this() != re_stack.back())
      {
        re_stack.clear();
      }
      done_ = true;
    }
    else
    {
      throw BookMarkError();
    }
  }
  return std::string();
}

void InsertActionBefore::rollback()
{
  if(done_)
  {
    target_->erase(--(*target_it_));
    ++(*target_it_);
    done_ = false;
  }
}

InsertActionAfter::InsertActionAfter(const std::string& mark, const note_t& note):
  Action(),
  mark_(mark),
  note_(note),
  target_(nullptr),
  target_it_(nullptr)
{}

std::string InsertActionAfter::exec(PhoneBook& book, marks_map& map, list_of_actions& stack, list_of_actions& re_stack)
{
  if(!done_)
  {
    auto it = map.find(mark_);
    if(it != map.end())
    {
      auto tmp = it->second + 1;
      book.insert(tmp, note_);
      target_it_ = &it->second;
      target_ = &book;
      stack.push_back(shared_from_this());
      if(shared_from_this() != re_stack.back())
      {
        re_stack.clear();
      }
      done_ = true;
    }
    else
    {
      throw BookMarkError();
    }
  }
  return std::string();
}

void InsertActionAfter::rollback()
{
  if(done_)
  {
    target_->erase(++(*target_it_));
    --(*target_it_);
    done_ = false;
  }
}

AddAction::AddAction(const note_t& note):
  Action(),
  note_(note),
  target_(nullptr)
{}

std::string AddAction::exec(PhoneBook& book, marks_map&, list_of_actions& stack, list_of_actions& re_stack)
{
  if(!done_)
  {
    book.add(note_);
    target_ = &book;
    stack.push_back(shared_from_this());
    if(shared_from_this() != re_stack.back())
    {
      re_stack.clear();
    }
    done_ = true;
  }
  return std::string();
}

void AddAction::rollback()
{
  if(done_)
  {
    target_->erase(--(target_->end()));
    done_ = false;
  }
}

EraseAction::EraseAction(const std::string& mark):
  Action(),
  mark_(mark),
  note_({std::string(), std::string()}),
  target_(nullptr),
  target_it_(nullptr),
  last_elem_(false)
{}

std::string EraseAction::exec(PhoneBook& book, marks_map& map, list_of_actions& stack, list_of_actions& re_stack)
{
  if(!done_)
  {
    if(book.empty())
    {
      throw EmptyError();
    }

    auto it = map.find(mark_);
    if(it != map.end())
    {
      note_ = *it->second;
      book.erase(it->second);
      last_elem_ = std::distance(it->second, book.cend()) == 1;
      target_it_ = &it->second;
      target_ = &book;
      stack.push_back(shared_from_this());
      if(shared_from_this() != re_stack.back())
      {
        re_stack.clear();
      }
      done_ = true;
    }
    else
    {
      throw BookMarkError();
    }
  }
  return std::string();
}

void EraseAction::rollback()
{
  if(done_)
  {
    target_->insert(*target_it_ + last_elem_, note_);
    *target_it_ += last_elem_;
    done_ = false;
  }
}

std::string InvalidAction::exec(PhoneBook &, marks_map &, list_of_actions &, list_of_actions &)
{
  return "<INVALID COMMAND>\n";
}

void InvalidAction::rollback()
{}
