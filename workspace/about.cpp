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
          "<p>许可：GPL-3.0 License</p>"
          "<p>此程序是自由软件，您可以以自由软件基金会发布的 GNU通用公共许可协议第三版或(您可以选择)更高版方式重新发布它和/或修改它。</p>"
          "<p>此程序是希望其会有用而发布，但没有任何担保</p>"
          "<p>更多信息请参考 <a href='https://github.com/Vescrity/MeloNote'>Github</a></p>")
          .arg(tr("MeloNote"))
          .arg(VERSION_1)
          .arg(VERSION_2)
          .arg(VERSION_3)
          .arg(__DATE__)
          .arg(__TIME__));
}
