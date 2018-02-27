#include "impl.h"
#include <vector>
#include <stdexcept>
#include <memory>
#include <cstdio>

void doPart2(int argc, char *argv[])
{
  if(argc != 3)
  {
    throw std::invalid_argument("Not correct parameters\n./lab 2 file_name");
  }
  
  std::unique_ptr<FILE, decltype(&fclose)> file(fopen(argv[2], "r"), &fclose);

  if(!file.get())
  {
    throw std::invalid_argument("Missing file");
  }
  
  const size_t size_block = 4096;

  std::unique_ptr<char[], decltype(&free)> arr_c(static_cast<char*>(malloc(size_block)), &free);
  size_t size = fread(&arr_c[0], sizeof(char), size_block, file.get());

  if(size != 0)
  {
    while(size % size_block == 0)
    {
      std::unique_ptr<char[], decltype(&free)> new_arr(static_cast<char*>(realloc(arr_c.get(), size + size_block)), &free);
      if(!new_arr)
      {
        throw std::bad_alloc();
      }
      arr_c.release();
      arr_c.swap(new_arr);
      size += fread(&arr_c[size], sizeof(char), size_block, file.get());
    }
  }

  std::vector<char> data_vector(&arr_c[0], &arr_c[size]);
  detail::print(data_vector.begin(), data_vector.end(), false);
}
