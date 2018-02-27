#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <regex>

struct DataStruct
{
  int         key1;
  int         key2;
  std::string str;
};

std::istream& operator>>(std::istream& in, DataStruct& data)
{
  std::string line_str;
  std::getline(in, line_str);
  static const std::regex condition("^\\s*([-+]?\\d+)\\s*,\\s*([+-]?\\d+)\\s*,\\s*(.+)\\s*$");
  if(!line_str.empty())
  {
    std::match_results<std::string::const_iterator> result;
    if(std::regex_match(line_str, result, condition))
    {
      data.key1 = std::stoi(result[1]);
      data.key2 = std::stoi(result[2]);
      data.str = result[3];
    }
    else
    {
      in.setstate(std::ios_base::badbit);
    }
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
  out << data.key1 << "," << data.key2 << "," << data.str;
  return out;
}

class less
{
public:
  bool operator()(const DataStruct& a, const DataStruct& b)
  {
    return a.key1 != b.key1 ? a.key1 < b.key1
        : a.key2 != b.key2 ? a.key2 < b.key2
        : a.str.size() < b.str.size();
  }
};

const DataStruct& validateDataStruct(const DataStruct& data)
{
  if((data.key1 > 5) || (data.key1 < -5) || (data.key2 > 5) || (data.key2 < -5) || data.str.empty())
  {
    throw std::invalid_argument("Invalid data struct");
  }
  return data;
}

int main()
{
  std::vector<DataStruct> vector_of_data;

  try
  {
    std::transform(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>(),
        std::back_insert_iterator<std::vector<DataStruct>>(vector_of_data), &validateDataStruct);
  }
  catch(const std::invalid_argument& err)
  {
    std::cerr << "Invalid data\n";
    return 1;
  }

  if(std::cin.bad())
  {
    std::cerr << "Input error\n";
    return 1;
  }

  std::sort(vector_of_data.begin(), vector_of_data.end(), less());

  std::copy(vector_of_data.begin(), vector_of_data.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  return 0;
}
