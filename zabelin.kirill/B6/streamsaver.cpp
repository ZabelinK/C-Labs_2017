#include "streamsaver.h"

StreamSaver::StreamSaver(std::ios_base& stream):
  locale_(stream.getloc()),
  flags_(stream.flags()),
  stream_ptr_(&stream)
{}

StreamSaver::~StreamSaver()
{
  stream_ptr_->imbue(locale_);
  stream_ptr_->flags(flags_);
}
