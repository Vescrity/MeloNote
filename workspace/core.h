#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <utility>
#define ull unsigned long long
using namespace std;
class NoteEvent
{
  string prefix;
  short sharp_flat;
  // prefix,octave = 6,0 -> 440Hz
  short octave;
  ull time;
  friend class NoteList;

public:
  NoteEvent(const string &str, const ull &t)
      : prefix(str), time(t), sharp_flat(0), octave(0){};
  void show() const;
  string html() const;
  uint8_t get_number() const;
};
class NoteList
{
  vector<NoteEvent> list;
  mutable bool dtime_ready;
  mutable vector<ull> dtime;
  mutable bool nindex_ready;
  mutable vector<unsigned> nindex;
  void calc_nindex() const;
  ull time_try() const;
  void calc_dtime() const;
  mutable bool bpm_ready;
  mutable double bpm;
  double calc_bpm() const;

public:
  NoteList()
  {
    bpm = -1;
    nindex_ready = dtime_ready = bpm_ready = 0;
  }
  void save_midi(const string &filename, uint8_t numerator, uint8_t power2) const;
  std::string html() const;
  std::vector<unsigned> get_nindex() const;
  void push_back(const NoteEvent &e) { list.push_back(e); }
  double get_bpm() const;
  void set_bpm(const double &b)
  {
    bpm_ready = 1;
    nindex_ready = 0;
    bpm = b;
  };
  void key_log(const string &s, const ull &t);
  void operate(const unsigned &st,const unsigned &ed,const string &pattern,const string &oper);
  void show() const;
  void clear();
};
