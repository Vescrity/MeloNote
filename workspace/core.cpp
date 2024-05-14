#include "core.h"
#include "Midi_Writer.h"
#include "Jiemeng_LogIO.hpp"
#include <stdint.h>

#include <math.h>
using namespace std;

void NoteList::key_log(const string &s, const ull &t) { push_back(NoteEvent(s, t)); }

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
  calc_dtime();
  for (int i = 0; i < n - 1; i++)
  {
    writer.addnote(list[i].get_number(), writer.msec2tick(dtime[i]));
  }
  writer.addnote(list[n - 1].get_number(), 120);
  writer.close();
}

double NoteList::get_bpm() const
{
  if (bpm_ready)
    return bpm;
  return calc_bpm();
}
void NoteEvent::show() const { dout << prefix << " " << time << "\n"; }

uint8_t NoteEvent::get_number() const
{
  if (prefix[0] > '0' || prefix[0] >= '8')
  {
    uint8_t keys[] = {60, 62, 64, 65, 67, 69, 71, 72};
    return keys[prefix[0] - '1'] + 12 * octave + sharp_flat;
  }
  return 0xFF;
}
string NoteEvent::html() const
{
  string rt;

  rt +=
      "<sup>"s +
      (sharp_flat == 1
           ? "#"
       : sharp_flat == -1
           ? "b"
           : "&nbsp;") +
      "</sup>";

  rt += prefix;

  if (octave > 0)
    rt += "<sup>"s + to_string(octave) + "</sup>";
  else if (octave < 0)
    rt += "<sub>"s + to_string(-octave) + "</sub>";
  else
    rt += "<sup>&nbsp;</sup>";
  return rt;
}

std::vector<unsigned> NoteList::get_nindex() const
{
  if (!nindex_ready)
    calc_nindex();
  return nindex;
}

std::string NoteList::html() const
{
  get_nindex();
  string rt;
  auto n = nindex.size();
  for (size_t i = 0; i < n - 1; i++)
  {
    rt += list[i].html();
    auto m = nindex[i + 1] - nindex[i] - 3;
    for (unsigned j = 0; j < m; j++)
      rt += "&nbsp;";
  }
  rt += list[n - 1].html();
  return rt;
}
void NoteList::operate(const unsigned &st, const unsigned &ed, const string &pattern, const string &oper)
{
  unsigned i = 0;
  while (nindex[i] < st)
    i++;
  for (; nindex[i] < ed; i++)
  {
    if (pattern != "*" && (pattern.find(list[i].prefix) == string::npos))
      continue;
    unsigned it = 0;
    while (it < oper.length())
    {
      auto o = oper[it];
      switch (o)
      {
      case 'b':
        list[i].sharp_flat = -1;
        break;
      case '#':
        list[i].sharp_flat = 1;
        break;
      case '0':
        list[i].sharp_flat = 0;
        break;
      case '+':
        list[i].octave++;
        break;
      case '-':
        list[i].octave--;
        break;
      case 'r':
        it++;
        if (it >= oper.length())
        {
          throw std::invalid_argument("Invalid...");
        }
        list[i].prefix = oper[it];
        break;
      default:
        throw std::invalid_argument("Invalid...");
        break;
      }
      it++;
    }
  }
}
