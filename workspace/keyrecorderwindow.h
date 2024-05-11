#ifndef KEYRECORDERWINDOW_H
#define KEYRECORDERWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class KeyRecorderWindow;
}
QT_END_NAMESPACE

class KeyRecorderWindow : public QWidget
{
    Q_OBJECT

public:
    KeyRecorderWindow(QWidget *parent = nullptr);
    ~KeyRecorderWindow();

private:
    Ui::KeyRecorderWindow *ui;
};
#endif // KEYRECORDERWINDOW_H
