#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), pushed_( 0 ), popped_( 0 ), buffer_( "" ), error_( false ), closed_( false ){}

bool Writer::is_closed() const
{
  return closed_;
}

void Writer::push( string data )
{
  int in_len = std::min(available_capacity(), data.size());
  buffer_ += data.substr(0, in_len);
  pushed_ += in_len;

  return;
}

void Writer::close()
{
  closed_ = true;
  return;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return pushed_;
}

bool Reader::is_finished() const
{
  return closed_ && (buffer_.size() == 0);
}

uint64_t Reader::bytes_popped() const
{
  return popped_;
}

string_view Reader::peek() const
{
  // Returns all bytes in buffer for peeking
  return string_view(buffer_);
}

void Reader::pop( uint64_t len )
{
  int out_len = std::min(len, bytes_buffered());
  buffer_.erase(0, out_len);
  popped_ += out_len;
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size();
}
