#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "core.h"
#include "editor.h"
#include "Jiemeng_DebugIO.hpp"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start_time = 0;
    is_Recording = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_stop_button_clicked()
{
    // cout << "Called!" << endl;
    if (!is_Recording)
    {
        is_Recording = 1;
        ui->start_stop_button->setText("Stop");
        current_list.clear();
        start_time = QDateTime::currentMSecsSinceEpoch();
    }
    else
    {
        is_Recording = 0;
        ui->start_stop_button->setText("Start");
        current_list.show();
        ui->bpmNumber->display(current_list.get_bpm());
        debug_lable("[Click]");
        debug_puts("creating editor window.");
        Editor *editor = new Editor(this, current_list);
        editor->show();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (is_Recording && !event->isAutoRepeat())
    {                                                                        // 判定是否在记录，忽略长按时的自动重复
        qint64 timestamp = QDateTime::currentMSecsSinceEpoch() - start_time; // 获取当前时间戳
        current_list.key_log(QString(event->text().at(0)).toStdString(), timestamp);
    }
    QWidget::keyPressEvent(event); // 保证正常的按键事件处理
}
