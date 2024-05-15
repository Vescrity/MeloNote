#ifndef JIEMENG_DEBUGIO
#define JIEMENG_DEBUGIO

#include "Jiemeng_IO.hpp"
#include <string>
using namespace std;
extern bool Debug_Mode;
class DoutStream
{
public:
  template <typename T>
  DoutStream &operator<<(const T &value)
  {
    if (Debug_Mode)
      dprint(std::to_string(value));
    return *this;
  }
  DoutStream &operator<<(const char *value)
  {
    if (Debug_Mode)
      dprint(value);
    return *this;
  }
  DoutStream &operator<<(const string &value)
  {
    if (Debug_Mode)
      dprint(value);
    return *this;
  }

private:
  void dprint(const string &message) { debug_print(message); }
};
extern DoutStream dout;

#endif