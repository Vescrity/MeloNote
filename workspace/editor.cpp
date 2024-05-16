#include "editor.h"
#include "helper.h"
#include "ui_editor.h"
#include <QFileDialog>
#include "Jiemeng_DebugIO.hpp"
#include <QFile>
#include <QTextStream>

Editor::Editor(QWidget *parent, const NoteList &l)
    : QMainWindow(parent), ui(new Ui::Editor), current_list(l)
{
  ui->setupUi(this);
  auto bpm = current_list.get_bpm();
  if (bpm > 9999 || bpm <= 0)
  {
    current_list.set_bpm(100);
  }
  editor_update();
  ui->statusBar->showMessage(tr("初始化已完成"));
}

Editor::~Editor()
{
  delete ui;
}

void Editor::editor_update()
{
  ui->bpmSpinBox->setValue(current_list.get_bpm());
  numerator = ui->numeratorSpinBox->value();
  power2 = ui->power2Box->currentIndex();
  ui->editorBrowser->setHtml(QString::fromStdString(current_list.html()));
}
void Editor::on_actionMidi_triggered()
{
  QString fname = QFileDialog::getSaveFileName(
      this, tr("保存文件"),
      QDir::currentPath(),
      tr("MIDI 文件(*.mid)"));
  if (!fname.isEmpty())
  {
    current_list.save_midi(
        fname.toStdString(), numerator, power2,
        ui->quantizeCheckBox->isChecked(),
        ui->quantizeComboBox->currentIndex() + 2);
    ui->statusBar->showMessage(tr("文件已导出"));
  }
  else
  {
    ui->statusBar->showMessage(tr("导出已取消"));
  }
}

void Editor::on_actionText_triggered()
{
  QString fname = QFileDialog::getSaveFileName(
      this, tr("保存文件"),
      QDir::currentPath(),
      tr("HTML 文件(*.htm)"));
  if (!fname.isEmpty())
  {
    auto s = ui->editorBrowser->toHtml();
    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      ui->statusBar->showMessage(tr("无法写入，导出失败"));
      return;
    }
    QTextStream out(&file);
    out << s;
    file.close();
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

void Editor::on_actionHelp_triggered()
{
  Helper *helper = new Helper(this);
  helper->show();
}

void Editor::on_updateButton_clicked()
{
  current_list.set_bpm(ui->bpmSpinBox->value());
  editor_update();
}

void Editor::on_x05Button_clicked()
{
  current_list.set_bpm(ui->bpmSpinBox->value() * 0.5);
  editor_update();
}

void Editor::on_x2Button_clicked()
{
  current_list.set_bpm(ui->bpmSpinBox->value() * 2.0);
  editor_update();
}
