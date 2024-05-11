#include "core.h"
#include <iostream>
using namespace std;
void NoteList::calc_dtime()
{
  for (int i = 1; i < list.size(); i++)
  {
    auto dt = list[i].time - list[i - 1].time;
    dtime.push_back(dt);
  }
  dtime_ready = 1;
}
double time_try(const ull &dt)
{
  // TODO
}
double NoteList::calc_bpm()
{
  // 若开头存在4个以上0则使用其计算bpm
  unsigned cnt;
  for (cnt = 0; cnt < list.size(); cnt++)
  {
    if (list[cnt].name != "0")
      break;
  }
  if (cnt >= 4)
  {
    auto t1 = list[cnt - 4].time;
    auto t2 = list[cnt - 1].time;
    // TODO: 计算
    bpm_ready = 1;
    return bpm;
  }
  // 否则使用后续的操作猜测bpm
  if (dtime_ready)
    calc_dtime();
  // TODO: sort(dtime)
}
void NoteList::key_log(const string &s, const ull &t)
{
  push_back(NoteEvent(s, t));
}

void NoteEvent::show() const
{
  cout << name << " " << time << endl;
}
void NoteList::show() const
{
  for (auto &i : list)
  {
    i.show();
  }
}
void NoteList::clear() { list.clear(); }