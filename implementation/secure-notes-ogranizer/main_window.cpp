#include "main_window.h"
#include "sidebar_vlayout.h"
#include "custom_widget.h"
#include "constants.h"

#include <QHBoxLayout>

main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(MAIN_WINDOW_MIN_WIDTH, MAIN_WINDOW_MIN_HEIGHT);

    // Create the central widget that contains all layouts and widgets
    QWidget *centralWidget = new QWidget(this);

    // Create layouts for the central widget
    QVBoxLayout *mainVerticalLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *mainHorizontalLayout = new QHBoxLayout();

    // Add the sidebar layout to the left side of the central widget
    sidebar_vlayout *sidebar = new sidebar_vlayout();
    mainHorizontalLayout->addLayout(sidebar);

    // Create a widget for the right side containing other layouts
    QWidget *rightSideWidget = new QWidget(centralWidget);
    QVBoxLayout *rightSideLayout = new QVBoxLayout(rightSideWidget);

    // Add the layouts to the right widget
    rightSideLayout->addLayout(createTimeAndButtonsLayout());
    rightSideLayout->addLayout(createTitleNoteLayout());
    rightSideLayout->addWidget(new CustomWidget());

    // Add the right widget to the right side of the central widget
    mainHorizontalLayout->addWidget(rightSideWidget);

    // Add the horizontal layout to the vertical layout
    mainVerticalLayout->addLayout(mainHorizontalLayout);

    // Set the overall layout for the central widget
    centralWidget->setLayout(mainVerticalLayout);

    // Set the central widget for the main window
    setCentralWidget(centralWidget);
}


QHBoxLayout* main_window::createTimeAndButtonsLayout()
{
    // Create a horizontal layout for time, buttons, and labels
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    // Create and set up the time label
    timeAgoLabel = new QLabel("Edited 2h ago");
    timeAgoLabel->setAlignment(Qt::AlignRight);
    timeAgoLabel->setObjectName("timeAgoLabel");

    layout->addWidget(timeAgoLabel);


    // Initialize and set up the dots button with a lambda expression
    saveNoteButton = new button_icon_vlayout(":/res/img/saveNote.png", "horizontalButton", QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT),
                                             Qt::AlignRight, [this]() {
                                                 qDebug() << "Dots button clicked!";
                                             });

    // Initialize and set up the share button with a lambda expression
    shareButton = new button_icon_vlayout(":/res/img/share.png", "horizontalButton", QSize(SIDEBAR_ICON_WIDTH, SIDEBAR_ICON_HEIGHT),
                                          Qt::AlignRight, [this]() {
                                              qDebug() << "Share button clicked!";
                                          });

    layout->addWidget(saveNoteButton->button);
    layout->addWidget(shareButton->button);

    return layout;
}

QHBoxLayout* main_window::createTitleNoteLayout()
{
    // Create a horizontal layout for the title note
    QHBoxLayout *layout = new QHBoxLayout();

    // Create and set up the title note text edit
    QTextEdit *titleNote = new QTextEdit("Untitled");
    titleNote->setAlignment(Qt::AlignLeft);
    titleNote->setProperty("class", "title");
    titleNote->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->addWidget(titleNote);

    return layout;
}

