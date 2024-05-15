#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include "core.h"
namespace Ui
{
    class Editor;
}

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent, const NoteList &);
    // void set_list(const NoteList&);
    ~Editor();

private slots:
    void on_actionMidi_triggered();

    void on_power2Box_currentIndexChanged(int index);
    void on_executeButton_clicked();
    

    void on_actionHelp_triggered();

    void on_updateButton_clicked();

    void on_x05Button_clicked();

    void on_x2Button_clicked();

    void on_actionText_triggered();

    void on_actionQt_triggered();

    void on_actionAboutThis_triggered();

private:
    Ui::Editor *ui;
    NoteList current_list;
    uint8_t numerator, power2;
    void editor_update();
};

#endif // EDITOR_H
