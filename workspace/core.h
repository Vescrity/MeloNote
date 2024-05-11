#pragma once

#include <string>
#include <vector>
#define ull unsigned long long
using namespace std;
class NoteEvent
{
  string name;
  int prefix;
  string suffix;
  ull time;
  friend class NoteList;

public:
  NoteEvent(const string &str, const ull &t)
      : name(str), time(t){};
  void show() const;
};
class NoteList
{
  vector<NoteEvent> list;
  bool dtime_ready;
  vector<ull> dtime;
  double time_try(const ull &);
  void calc_dtime();
  bool bpm_ready;
  double bpm;
  double calc_bpm();

public:
  void push_back(const NoteEvent &e) { list.push_back(e); }
  double get_bpm();
  double set_bpm();
  void key_log(const string &s, const ull &t);
  void show() const;
  void clear();
};
