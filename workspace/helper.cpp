#include "helper.h"
#include "ui_helper.h"

Helper::Helper(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Helper)
{
  ui->setupUi(this);
  ui->recordBrowser->setMarkdown(tr(R"(
- 按下 `Start` 后按旋律节奏按下键盘按键即可。
> 数字键、小键盘均可。字母键后续处理步骤较多。
)"));
  ui->editBrowser->setMarkdown(tr(R"(
### 显示说明

- 旋律框显示的为键盘录制时记录到的内容。
- 空格长度一定程度反映了按键间的时间间隔。
- 左上角标用于表示升降
- 右上角标用于表示**提升**的八度数
- 右下角标用于表示**降低**的八度数
- 无角标 `1` 表示 **中央C**
- 无角标 `6` 对应 **440 Hz** 的 A 音

### 操作流程

1. 选中要操作的音符
1. 填入筛选、指令字段
1. 执行

### 筛选

在选中的音符中进一步筛选要操作的内容。

### 指令

指令为一串字符。从左至右依次执行。

|指令|说明|
|-|-|
|b|标记为降|
|#|标记为升|
|0|取消升降标记|
|+|向上移动一个八度|
|-|向下移动一个八度|
|r_|将操作对象替换为 `_`。 `_` 为一任意字符|


)"));
}

Helper::~Helper()
{
  delete ui;
}
