#include "impl.h"

#include <stack>
#include <sstream>
#include <algorithm>
#include <map>
#include <functional>
#include <utility>
#include <memory>
#include <locale>

#include "book.h"
#include "actionsforbook.h"
#include "actionsformarks.h"
#include "actionsforactions.h"
#include "errors.h"

#include <iostream>

struct name_t
{
  std::string name;
};

std::istream& operator>>(std::istream& in, name_t& name)
{
  in >> std::ws;

  char now = '\0', prev = '\\';
  now = in.get();
  while(!in.eof())
  {
    if(prev == '\\')
    {
      name.name.push_back(now);
    }
    else
    {
      if(now != '\\')
      {
        name.name.push_back(now);
      }
    }
    prev = now;
    now = in.get();
  }

  in.clear();
  if((name.name.size() < 2) || ((name.name.front() != '"') || (name.name.back() != '"')))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  name.name.erase(name.name.begin());
  name.name.pop_back();
  return in;
}

std::ostream& operator<<(std::ostream& out, const note_t& note)
{
  out << note.phone_number << ' ' << note.name;
  return out;
}

std::istream& operator>>(std::istream& in, note_t& note)
{
  name_t name;
  in >> note.phone_number >> name;
  note.name = name.name;
  return in;
}

std::shared_ptr<Action> parseAdd(std::istream& in)
{
  note_t note;
  in >> note;

  if(note.phone_number.empty() || note.name.empty() || in.fail())
  {
    return std::make_shared<InvalidAction>();
  }

  return std::make_shared<AddAction>(note);
}

std::shared_ptr<Action> parseStore(std::istream& in)
{
  std::string old_mark, new_mark;
  in >> old_mark >> new_mark;

  if(old_mark.empty() || new_mark.empty() || !in.eof())
  {
    return std::make_shared<InvalidAction>();
  }

  return std::make_shared<StoreAction>(old_mark, new_mark);
}

std::shared_ptr<Action> parseInsert(std::istream& in)
{
  std::string type, mark_name;
  note_t note;
  in >> type >> mark_name >> note;

  if(type.empty() || mark_name.empty() || note.phone_number.empty() || note.name.empty() || in.fail())
  {
    return std::make_shared<InvalidAction>();
  }

  if(type == "before")
  {
    return std::make_shared<InsertActionBefore>(mark_name, note);
  }
  else if(type == "after")
  {
    return std::make_shared<InsertActionAfter>(mark_name, note);
  }
  else
  {
    return std::make_shared<InvalidAction>();
  }
}

std::shared_ptr<Action> parseDelete(std::istream& in)
{
  std::string mark_name;
  in >> mark_name;

  if(mark_name.empty() || !in.eof())
  {
    return std::make_shared<InvalidAction>();
  }

  return std::make_shared<EraseAction>(mark_name);
}

std::shared_ptr<Action> parseShow(std::istream& in)
{
  std::string mark_name;
  in >> mark_name;

  if(mark_name.empty() || !in.eof())
  {
    return std::make_shared<InvalidAction>();
  }

  return std::make_shared<ShowAction>(mark_name);
}

std::shared_ptr<Action> parseMove(std::istream& in)
{
  std::string mark_name, step;
  in >> mark_name >> step;

  if(mark_name.empty() || step.empty() || !in.eof())
  {
    return std::make_shared<InvalidAction>();
  }

  return std::make_shared<MoveAction>(mark_name, step);
}

std::shared_ptr<Action> parseBack(std::istream& in)
{
  if(!in.eof())
  {
    return std::make_shared<InvalidAction>();
  }
  return std::make_shared<UndoAction>();
}

std::shared_ptr<Action> parseForward(std::istream& in)
{
  if(!in.eof())
  {
    return std::make_shared<InvalidAction>();
  }
  return std::make_shared<RedoAction>();
}

std::istream& operator>>(std::istream& in, std::shared_ptr<Action>& action)
{
  using parser = std::shared_ptr<Action>(*)(std::istream&);

  static const struct
  {
    const char* name;
    const parser parse;
  } parsers[] =
    {
      {"add", &parseAdd},
      {"store", &parseStore},
      {"insert", &parseInsert},
      {"delete", &parseDelete},
      {"show", &parseShow},
      {"move", &parseMove},
      {"back", &parseBack},
      {"forward", &parseForward}
    };

  in >> std::ws;

  std::string command_str;
  std::getline(in, command_str);

  std::stringstream command(command_str);

  std::string command_name;
  std::getline(command, command_name, ' ');

  auto iter = std::find_if(std::begin(parsers), std::end(parsers),
      [&command_name](const auto& item)
      {
        return item.name == command_name;
      });

  if(iter == std::end(parsers))
  {
    action = std::make_shared<InvalidAction>();
  }
  else
  {
    action = iter->parse(command);
  }

  return in;
}

int doPart1(std::istream& in, std::ostream& out)
{
  PhoneBook book;

  list_of_actions stack;
  list_of_actions stack_rollback;
  marks_map marks({std::pair<std::string, PhoneBook::const_robust_iterator>("current", book.cbegin())});

  std::for_each(std::istream_iterator<std::shared_ptr<Action>>(in), std::istream_iterator<std::shared_ptr<Action>>(),
      [&book, &stack, &stack_rollback, &marks, &out](const std::shared_ptr<Action>& action)
      {
        try
        {
          out << action->exec(book, marks, stack, stack_rollback);
        }
        catch(const std::exception& err)
        {
          out << err.what() << '\n';
        }
      });

  if(!in.eof())
  {
    std::cerr << "Input error\n";
    return 2;
  }

  return 0;
}
