#ifndef HELPER_H
#define HELPER_H

#include <QMainWindow>

namespace Ui {
class Helper;
}

class Helper : public QMainWindow
{
    Q_OBJECT

public:
    explicit Helper(QWidget *parent = nullptr);
    ~Helper();

private:
    Ui::Helper *ui;
};

#endif // HELPER_H
