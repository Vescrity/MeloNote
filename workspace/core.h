#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#define ull unsigned long long
using namespace std;
class NoteEvent
{
  string prefix;
  // mutable uint8_t prefix;
  string suffix;
  ull time;
  friend class NoteList;

public:
  NoteEvent(const string &str, const ull &t)
      : prefix(str), time(t){};
  void show() const;
  uint8_t get_number() const;
};
class NoteList
{
  vector<NoteEvent> list;
  mutable bool dtime_ready;
  mutable vector<ull> dtime;
  ull time_try() const;
  void calc_dtime() const;
  mutable bool bpm_ready;
  mutable double bpm;
  double calc_bpm() const;

public:
  NoteList()
  {
    bpm = -1;
    dtime_ready = bpm_ready = 0;
  }
  void save_midi(const string &filename, uint8_t numerator, uint8_t power2) const;
  void push_back(const NoteEvent &e) { list.push_back(e); }
  double get_bpm() const;
  void set_bpm(const double &b)
  {
    bpm_ready = 1;
    bpm = b;
  };
  void key_log(const string &s, const ull &t);
  void show() const;
  void clear();
};
