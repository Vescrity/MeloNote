#pragma once
#include <stdint.h>
#include <string>
#include "Binary_Writer.h"
#include <fstream>
using namespace std;

class Midi_Writer
{
  uint8_t TPQN;
  uint8_t numerator;
  uint8_t power2;
  uint32_t microsec_per_beat;
  std::ofstream outfile;
  Binary_Writer writer;

public:
  Midi_Writer();
  // 打开并写入文件头
  void open(const string &filename);
  // Midi_Writer(const string &filename){}
  void set_bpm(const long double &bpm);
  void addnote(const uint8_t &notenumber, const uint32_t &tick);
  void set_signature(const uint8_t &nn, const uint8_t &p2);
  uint32_t msec2tick(const uint32_t &msec);
};