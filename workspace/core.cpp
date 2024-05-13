#include "core.h"
#include <algorithm>
#include "Midi_Writer.h"
#include "Jiemeng_LogIO.hpp"
#include <stdint.h>
using namespace std;
void NoteList::calc_dtime() const
{
  if (dtime_ready)
    return;

  dtime.clear();
  for (int i = 1; i < list.size(); i++)
  {
    auto dt = list[i].time - list[i - 1].time;
    dtime.push_back(dt);
  }
  dtime_ready = 1;
}
double time2bpm(const ull &t, int as = 16)
{
  return 240000.0 / t / as;
}
ull TIME_1 = 10;
ull TIME_2 = 25;
ull TIME_3 = 50;
ull NoteList::time_try() const
{
  calc_dtime();
  auto stime = dtime;
  sort(stime.begin(), stime.end());
  unsigned head, tail;
  head = 0;
  tail = 0;
  auto q_push = [&]
  {
    tail++;
    if (tail > stime.size())
      tail = stime.size();
  };
  auto q_pop = [&]
  {
    head++;
    if (head > tail)
      head = tail;
  };
  auto q_size = [&]
  { return tail - head; };
  auto q_empty = [&]
  { return head == tail; };
  // 队列加入第一元素
  q_push();
  auto n = stime.size();
  while (tail < n)
  {
    bool b_1 = stime[tail] - stime[tail - 1] < TIME_1;
    // bool b_2 = stime[tail] - stime[tail - 1] < TIME_2;
    bool bh_1 = (head + 1 >= tail) ? 1 : stime[head + 1] - stime[head] < TIME_1;
    bool b_3 = stime[tail] - stime[head] < TIME_3;
    if (b_1)
    {
      // 新时长更贴近时更新掉队头并重新考察
      if (!bh_1)
      {
        q_pop();
        continue;
      }
      else
      {
        if (!b_3)
        {
        nob3:
          if (q_size() >= 5) // 直接进行结算
            break;
          else // 清空队列后重新推入新元素
          {
            head = tail;
            q_push();
            continue;
          }
        }
        // 正常入队
        q_push();
        continue;
      }
    }
    else if (!b_3)
    {
      goto nob3;
    }
    else
    {
      q_push();
      continue;
    }
  }
  if (q_size() < 5)
    return 0;
  ull sum = 0;
  for (int i = head; i < tail; i++)
  {
    sum += stime[i];
  }
  return sum / q_size();
}
double NoteList::calc_bpm() const
{
  // 若开头存在4个以上0则使用其计算bpm
  unsigned cnt;
  for (cnt = 0; cnt < list.size(); cnt++)
  {
    if (list[cnt].prefix != "0")
      break;
  }
  if (cnt >= 4)
  {
    auto &t1 = list[cnt - 4].time;
    auto &t2 = list[cnt - 1].time;
    auto dt = t2 - t1;
    bpm = 60000.0 / dt * 4.0;
    bpm_ready = 1;
    return bpm;
  }
  // 否则使用后续的操作猜测bpm
  calc_dtime();
  auto dt = time_try();
  bpm = time2bpm(dt);
  bpm_ready = 1;
  return bpm;
}
void NoteList::key_log(const string &s, const ull &t)
{
  push_back(NoteEvent(s, t));
}

void NoteList::show() const
{
  for (auto &i : list)
  {
    i.show();
  }
  get_bpm();
  dout << "bpm=" << get_bpm() << "\n";
}
void NoteList::clear()
{
  list.clear();
  dtime_ready = 0;
  dtime.clear();
  bpm_ready = 0;
  bpm = 0;
}
void NoteList::save_midi(const string &filename, uint8_t numerator, uint8_t power2) const
{
  Midi_Writer writer;
  writer.open(filename);
  writer.set_signature(numerator, power2);
  writer.set_bpm(get_bpm());
  auto n = list.size();
  for (int i = 0; i < n - 1; i++)
  {
    // writer.addnote();
  }
}

double NoteList::get_bpm() const
{
  if (bpm_ready)
    return bpm;
  return calc_bpm();
}
void NoteEvent::show() const
{
  dout << prefix << " " << time << "\n";
}

uint8_t NoteEvent::get_number() const
{
  
}