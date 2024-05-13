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

private:
    Ui::Editor *ui;
    NoteList current_list;
    uint8_t numerator, power2;
};

#endif // EDITOR_H
