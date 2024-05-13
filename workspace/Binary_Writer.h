#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include "Jiemeng_DebugIO.hpp"
class Binary_Writer
{
public:
  template <typename... Bytes>
  void append(Bytes... bytes)
  {
    (..., (buf.push_back(static_cast<uint8_t>(bytes))));
  }
  void flush(std::ostream &os)
  {
    // Write the length in 4 bytes (big endian format).
    uint32_t len = buf.size();
    std::vector<uint8_t> lenBytes = {
        static_cast<uint8_t>((len >> 24) & 0xFF),
        static_cast<uint8_t>((len >> 16) & 0xFF),
        static_cast<uint8_t>((len >> 8) & 0xFF),
        static_cast<uint8_t>(len & 0xFF)};
    for (const uint8_t &byte : lenBytes)
      os.put(static_cast<char>(byte));
    for (const auto &i : buf)
      os.put(i);
    buf.clear();
  }

private:
  vector<uint8_t> buf;
};
