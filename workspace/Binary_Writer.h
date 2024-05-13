#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
class Binary_Writer
{
public:

  template <typename... Bytes>
  void append(Bytes... bytes)
  {
    (..., (buffer_.put(static_cast<char>(bytes)), ++length_));
  }
  void flush(std::ostream &os)
  {
    // Write the length in 4 bytes (big endian format).
    uint32_t len = length_;
    std::vector<uint8_t> lenBytes = {
        static_cast<uint8_t>((len >> 24) & 0xFF),
        static_cast<uint8_t>((len >> 16) & 0xFF),
        static_cast<uint8_t>((len >> 8) & 0xFF),
        static_cast<uint8_t>(len & 0xFF)};
    for (uint8_t byte : lenBytes)
    {
      os.put(static_cast<char>(byte));
    }
    // Now write the actual data.
    os << buffer_.rdbuf();
    buffer_.str(""); // Clear the buffer
    buffer_.clear(); // Clear any error flags
    length_ = 0;     // Reset the length
  }

private:
  std::ostringstream buffer_;
  uint32_t length_ = 0;
};
// 你可以使用这样的一个类来储存字节，并最终写入到一个二进制文件中。
/*int main()
{
  BinaryDataWriter writer;
  // 假设我们添加了一些字节
  writer.append(0x45);
  writer.append(0x23);
  writer.append(0x56);
  // ... 按需继续追加更多字节
  // 打开文件并写入数据和长度信息
  std::ofstream outfile("example.bin", std::ios::binary | std::ios::out);
  if (outfile.is_open())
  {
    writer.write(outfile);
    outfile.close();
  }
  return 0;
}*/