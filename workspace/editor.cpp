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
  ui->editorBrowser->setHtml(QString::fromStdString(current_list.html()));
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
void Editor::editor_update()
{
  ui->editorBrowser->setHtml(QString::fromStdString(current_list.html()));
}
void Editor::on_actionMidi_triggered()
{
  QString fname = QFileDialog::getSaveFileName(this, tr("保存文件"), QDir::currentPath(), tr("MIDI 文件(*.mid)"));
  if (!fname.isEmpty())
  {
    current_list.save_midi(fname.toStdString(), numerator, power2);
    ui->statusBar->showMessage(tr("文件已导出"));
  }
  else
  {
    ui->statusBar->showMessage(tr("导出已取消"));
  }
}

void Editor::on_power2Box_currentIndexChanged(int index)
{
  power2 = index;
}

void Editor::on_executeButton_clicked()
{
  QTextCursor cursor = ui->editorBrowser->textCursor();
  if (!cursor.hasSelection())
  {
    ui->statusBar->showMessage(tr("没有选中的内容"));
    return;
  }
  int st = cursor.selectionStart();
  int ed = cursor.selectionEnd();
  auto pat = ui->patternEdit->displayText().toStdString();
  auto com = ui->commandEdit->displayText().toStdString();
  try
  {
    current_list.operate(st, ed, pat, com);
  }
  catch (const invalid_argument &)
  {
    ui->statusBar->showMessage(tr("无效的指令"));
    return;
  }

  editor_update();
  ui->statusBar->showMessage(tr("操作完成"));
}
