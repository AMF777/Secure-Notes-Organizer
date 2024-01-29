#include "main_window.h"
#include "sidebar_vlayout.h"
#include <QHBoxLayout>

main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    // horizontal layout, now add right hand side of window
    QHBoxLayout *hLayout = new QHBoxLayout(centralWidget);
    sidebar_vlayout *sidebar = new sidebar_vlayout();
    hLayout->addLayout(sidebar);
    setCentralWidget(centralWidget);
}

