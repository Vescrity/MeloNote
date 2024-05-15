#include "version.h"
#include "editor.h"
#include <QMessageBox>
void Editor::on_actionQt_triggered()
{
  QMessageBox::aboutQt(this);
}
void Editor::on_actionAboutThis_triggered()
{
  QMessageBox::about(
      this, "About MeloNote",
      tr(
          "<h1>%1</h1>"
          "<p>Version %2.%3.%4</p>"
          "<p>编译于 %5 %6</p>"
          "<p>更多信息请参考 <a href='https://github.com/Vescrity/MeloNote'>Github</a></p>")
          .arg(tr("MeloNote"))
          .arg(VERSION_1)
          .arg(VERSION_2)
          .arg(VERSION_3)
          .arg(__DATE__)
          .arg(__TIME__));
}
