#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <ios>

class StreamSaver
{
public:
  StreamSaver(std::ios_base&);
  ~StreamSaver();

private:
  std::locale locale_;
  std::ios_base::fmtflags flags_;
  std::ios_base* stream_ptr_;
};

#endif // STREAMGUARD_H
