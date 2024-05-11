#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>
#include <QDateTime>
#include "core.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_start_stop_button_clicked();

private:
    Ui::MainWindow *ui;
    bool is_Recording;
    qint64 start_time;
    NoteList current_list;
};
#endif // MAINWINDOW_H
