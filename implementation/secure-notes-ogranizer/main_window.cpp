#include "main_window.h"
#include "sidebar_vlayout.h"
#include "custom_widget.h"
#include <QHBoxLayout>

main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(0, 0, 800, 600);
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);

    // horizontal layout, now add right hand side of window
    QHBoxLayout *hLayout = new QHBoxLayout(centralWidget);
    sidebar_vlayout *sidebar = new sidebar_vlayout();

    CustomWidget *customWidget = new CustomWidget(centralWidget);
    centralLayout->addLayout(sidebar);
    centralLayout->addLayout(customWidget);

    setCentralWidget(centralWidget);
}

