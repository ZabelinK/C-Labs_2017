#include "actionsformarks.h"

#include <algorithm>

#include "errors.h"

bool checkMark(const std::string& mark_name)
{
  return std::find_if(mark_name.begin(), mark_name.end(), [](char c)
      {
        return !(std::isalnum(c, std::locale()) || (c == '-'));
      }) == mark_name.end();
}


StoreAction::StoreAction(const std::string& old_makr, const std::string& new_mark):
  Action(),
  old_mark_(old_makr),
  new_mark_(new_mark),
  target_(nullptr)
{}

std::string StoreAction::exec(PhoneBook&, marks_map& map, list_of_actions& stack, list_of_actions& re_stack)
{
  if(!done_)
  {
    auto it = map.find(old_mark_);
    if(it != map.end() && checkMark(new_mark_))
    {
      map.insert(std::pair<std::string, PhoneBook::const_robust_iterator>(new_mark_, it->second));
      target_ = &map;
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

void StoreAction::rollback()
{
  if(done_)
  {
    target_->erase(new_mark_);
    done_ = false;
  }
}

MoveAction::MoveAction(const std::string& mark, const std::string& step):
  Action(),
  mark_(mark),
  step_(step),
  diff_(0),
  target_(nullptr)
{}

std::string MoveAction::exec(PhoneBook& book, marks_map& map, list_of_actions& stack, list_of_actions& re_stack)
{
  if(!done_)
  {
    auto it = map.find(mark_);
    if(it != map.end())
    {
      if(step_ == "first")
      {
        diff_ = -std::distance(book.cbegin(), it->second);
        it->second = book.cbegin();
      }
      else if(step_ == "last")
      {
        diff_ = std::distance(it->second, book.empty() ? book.cend() : --book.cend());
        it->second = book.empty() ? book.cend() : --book.cend();
      }
      else
      {
        size_t pos = 0;
        int step_int = 0;
        try
        {
          step_int = std::stoi(step_, &pos);
        }
        catch(const std::invalid_argument&)
        {
          throw StepError();
        }

        if(pos != step_.size())
        {
          throw StepError();
        }

        diff_ = step_int;
        it->second += step_int;
      }
      target_ = &map;
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

void MoveAction::rollback()
{
  if(done_)
  {
    target_->at(mark_) += (-diff_);
    done_ = false;
  }
}

ShowAction::ShowAction(const std::string& mark):
  mark_(mark)
{}

std::string ShowAction::exec(PhoneBook &, marks_map& map, list_of_actions &, list_of_actions &)
{
  auto it = map.find(mark_);
  if(it != map.end())
  {
    if(it->second->name == PhoneBook::invalid)
    {
      throw EmptyError();
    }
    return it->second->phone_number + " " + it->second->name +  "\n";
  }
  else
  {
    throw BookMarkError();
  }
}

void ShowAction::rollback()
{}
