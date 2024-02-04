#include "main_window.h"

#include <QHBoxLayout>
#include <QStackedWidget>

main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(MAIN_WINDOW_MIN_WIDTH, MAIN_WINDOW_MIN_HEIGHT);

    // Create the central widget that contains all layouts and widgets
    QWidget *centralWidget = new QWidget(this);

    // Create layouts for the central widget
    mainVerticalLayout = new QVBoxLayout(centralWidget);
    mainHorizontalLayout = new QHBoxLayout();

    // Add the sidebar layout to the left side of the central widget
    sidebarLayout = new sidebar_vlayout([this](){swapToShowNotes();},
                                        [this](){swapToEditNote();});

    mainHorizontalLayout->addLayout(sidebarLayout);

    // Create a stacked widget for the right side containing other layouts
    stackedWidget = new QStackedWidget();
    editNotesLayout = new edit_notes_vlayout();
    noteLayout = new NoteEditor();

    // Create a stacked widget for the right side containing other layouts
    QWidget* pageOne = new QWidget();
    QWidget* pageTwo = new QWidget();
    pageOne->setLayout(noteLayout);
    pageTwo->setLayout(editNotesLayout);

    // Add layouts to the stacked widget
    stackedWidget->addWidget(pageTwo);
    stackedWidget->addWidget(pageOne);

    // Add the stacked widget to the horizontal layout
    mainHorizontalLayout->addWidget(stackedWidget);

    // Add the horizontal layout to the vertical layout
    mainVerticalLayout->addLayout(mainHorizontalLayout);

    // Set the overall layout for the central widget
    centralWidget->setLayout(mainVerticalLayout);

    // Set the central widget for the main window
    setCentralWidget(centralWidget);
}

void main_window::swapToEditNote()
{
    stackedWidget->setCurrentIndex(1);  // Index of editNotesLayout
}

void main_window::swapToShowNotes()
{
    stackedWidget->setCurrentIndex(0);  // Index of noteLayout
}
