#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent, const NoteList &l)
    : QMainWindow(parent), ui(new Ui::Editor), current_list(l)
{
    ui->setupUi(this);
    auto bpm = current_list.get_bpm();
    if (bpm > 9999 || bpm <= 0)
    {
        current_list.set_bpm(100);
    }
    ui->bpmSpinBox->setValue(current_list.get_bpm());
}

Editor::~Editor()
{
    delete ui;
}
/*
void Editor::set_list(const NoteList &l)
{
    current_list = l;
}*/

void Editor::on_actionMidi_triggered()
{
    current_list.save_midi("temp.mid", numerator, power2);
}

void Editor::on_power2Box_currentIndexChanged(int index)
{
    power2 = index;
}
