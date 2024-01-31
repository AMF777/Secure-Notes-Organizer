#include "main_window.h"
#include "sidebar_vlayout.h"
#include "custom_widget.h"
#include "constants.h"

#include <QHBoxLayout>

main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
{
    // setGeometry(0, 0, 800, 600);
    setMinimumSize(MAIN_WINDOW_MIN_WIDTH, MAIN_WINDOW_MIN_HEIGHT);
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);

    // horizontal layout, now add right hand side of window
    sidebar_vlayout *sidebar = new sidebar_vlayout();
    CustomWidget *customWidget = new CustomWidget();

    centralLayout->addLayout(sidebar);
    centralLayout->addLayout(customWidget);
    setCentralWidget(centralWidget);
}

