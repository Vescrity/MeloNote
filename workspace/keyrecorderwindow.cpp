#include "keyrecorderwindow.h"
#include "./ui_keyrecorderwindow.h"

KeyRecorderWindow::KeyRecorderWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::KeyRecorderWindow)
{
    ui->setupUi(this);
}

KeyRecorderWindow::~KeyRecorderWindow()
{
    delete ui;
}

void KeyRecorderWindow::on_pushButton_clicked()
{

}

