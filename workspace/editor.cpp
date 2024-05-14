#include "editor.h"
#include "ui_editor.h"
#include <QFileDialog>
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
    numerator = ui->numeratorSpinBox->value();
    power2 = ui->power2Box->currentIndex();
    ui->statusBar->showMessage(tr("初始化已完成"));
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
    QString fname=QFileDialog::getSaveFileName(this,tr("保存文件"),QDir::currentPath(),tr("MIDI 文件(*.mid)"));
    if(!fname.isEmpty()){
        current_list.save_midi(fname.toStdString(), numerator, power2);
        ui->statusBar->showMessage(tr("文件已导出"));
    }
    else{
        ui->statusBar->showMessage(tr("导出已取消"));
    }
}

void Editor::on_power2Box_currentIndexChanged(int index)
{
    power2 = index;
}
