#include "laboptions.h"

#include <map>
#include <algorithm>
#include <functional>
#include <sstream>
#include <iterator>
#include "queuewithpriority.h"

#include <iostream>

template <typename T>
using handler = std::function<void (QueueWithPriority<T>&, std::ostream&)>;

void invalid(QueueWithPriority<std::string>&, std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

handler<std::string> parseAdd(std::istream& in)
{
  using queue = QueueWithPriority<std::string>;

  using str_priority = std::pair<std::string, queue::ElementPriority>;

  static const std::map<std::string, queue::ElementPriority> priority_map({str_priority("high", queue::HIGH),
      str_priority("normal", queue::NORMAL), str_priority("low", queue::LOW)});
  
  std::string priority_str;
  in >> priority_str >> std::ws;

  std::string data;
  std::getline(in, data);
  
  if(data.empty())
  {
    return &invalid;
  }
  
  try
  {
    queue::ElementPriority priority = priority_map.at(priority_str);
    return handler<std::string>([priority, data](QueueWithPriority<std::string>& queue_str, std::ostream&)
      {
        queue_str.put(data, priority);
      });
  }
  catch(const std::out_of_range&)
  {
    return &invalid;
  }
}

handler<std::string> parseGet(std::istream& in)
{
  if(!in.eof())
  {
    return &invalid;
  }
  return handler<std::string>([](QueueWithPriority<std::string>& queue_str, std::ostream& out)
    {
      if(!queue_str.process([&out](const std::string& item)
          {
            out << item << '\n';
          }))
      {
        out << "<EMPTY>\n";
      }
    });
}

handler<std::string> parseAccelerate(std::istream& in)
{
  if(!in.eof())
  {
    return &invalid;
  }
  return handler<std::string>([](QueueWithPriority<std::string>& queue_str, std::ostream&)
    {
      queue_str.accelerate();
    });
}

template <typename T>
std::istream& operator>>(std::istream& in, handler<T>& operation)
{
  using parser = handler<std::string>(*)(std::istream&);
  
  const struct
  {
    const char * name;
    const parser parse;
  } parsers[] = 
      {
        {"add", &parseAdd},
        {"get", &parseGet},
        {"accelerate", &parseAccelerate}
      };
  

  in >> std::ws;

  std::string command_str;
  std::getline(in, command_str);

  std::stringstream command(command_str);

  std::string name_command;
  std::getline(command, name_command, ' ');

  auto iter = std::find_if(std::begin(parsers), std::end(parsers),
      [&name_command](const auto & item)
      {
        return item.name == name_command;
      });

  if(iter == std::end(parsers))
  {
    operation = &invalid;
  }
  else
  {
    operation = iter->parse(command);
  }

  return in;
}

void doPart1(std::ostream& out, std::istream & in)
{
  QueueWithPriority<std::string> queue;

  std::for_each(std::istream_iterator<handler<std::string>>(in),
      std::istream_iterator<handler<std::string>>(), 
      [&out, &queue](const handler<std::string>& action)
      {
        action(queue, out);
      });
}
