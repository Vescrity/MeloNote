#include "Midi_Writer.h"
std::vector<unsigned char> VLQ_encode(unsigned long ticks);
void Midi_Writer::open(const string &filename)
{
  outfile = ofstream(filename, std::ios::binary);
  outfile.write("MThd", 4);
  writer.append(0, 1, 0, 2, 0, TPQN);
  writer.flush(outfile);
}
void Midi_Writer::set_bpm(const long double &bpm)
{
  microsec_per_beat = 60000000ul / bpm;
  // TODO: 写入文件
  outfile.write("MTrk", 4);
  writer.append(0);
  writer.append(0xFF, 0x58, 0x04);
  writer.append(numerator, power2, 1, 96);
  writer.append(0);
  writer.append(0xFF, 0x51, 0x03);
  writer.append((microsec_per_beat >> 16) & 0xFF);
  writer.append((microsec_per_beat >> 8) & 0xFF);
  writer.append((microsec_per_beat >> 0) & 0xFF);
  writer.append(1);
  writer.append(0xFF, 0x2F, 0x00);
  writer.flush(outfile);
  // 开始接受第一音轨
  outfile.write("MTrk", 4);
}

void Midi_Writer::addnote(const uint8_t &notenumber, const uint32_t &tick)
{
  if (notenumber == 0xFF)
  {
    auto delays = VLQ_encode(tick);
    for (const auto &i : delays)
      writer.append(i);
    writer.append(0x80, 0x01, 0x64); // TODO?
    return;
  }
  // NUM(69)=440Hz
  // NOTEON
  writer.append(0x00, 0x90, notenumber, 0x64); // Delay=0 NoteON, Channel0, Pitch, vel=0x64
  auto delays = VLQ_encode(tick);

  for (const auto &i : delays)
    writer.append(i);
  // NOTEOFF
  writer.append(0x80, notenumber, 0x64);
}
void Midi_Writer::close()
{
  writer.append(1);
  writer.append(0xFF, 0x2F, 0x00);
  writer.flush(outfile);
  outfile.close();
}
Midi_Writer::Midi_Writer()
{
  TPQN = 120;
  numerator = 4;
  power2 = 2;
}

std::vector<unsigned char> VLQ_encode(unsigned long ticks)
{
  std::vector<unsigned char> encodedBytes;
  unsigned char buffer;
  do
  {
    buffer = ticks & 0x7F;
    buffer |= 0x80;
    encodedBytes.insert(encodedBytes.begin(), buffer);
    ticks >>= 7;
  } while (ticks);
  encodedBytes.back() &= 0x7F;
  return encodedBytes;
}

uint32_t Midi_Writer::msec2tick(const uint32_t &msec)
{
  auto tick_time = microsec_per_beat / TPQN;
  return msec * 1000 / tick_time;
}

void Midi_Writer::set_signature(const uint8_t &nn, const uint8_t &p2)
{
  numerator = nn;
  power2 = p2;
}