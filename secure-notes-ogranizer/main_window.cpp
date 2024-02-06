#include "main_window.h"

#include "back-end/NoteComponent.h"
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QFileDialog>
void myDelteLayout(QLayout *layout){
    QLayoutItem * item;
    QLayout * sublayout;
    QWidget * widget;
    while ((item = layout->takeAt(0))) {
        if ((sublayout = item->layout()) != 0) {myDelteLayout(sublayout);}
        else if ((widget = item->widget()) != 0) {widget->hide(); delete widget;}
        else {delete item;}
    }

    delete layout;
}
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
    // sidebarLayout = new sidebar_vlayout([this](){swapToShowNotes();},
    //                                     [this](){swapToEditNote();});
    sidebarLayout = new sidebar_vlayout([this](){swapToShowNotes();},
                                        [this](){swapToEditNote();},
                                        [this](QString filePath, QString  title){
                                            initEditorFromFile(filePath, title);
                                        });
    mainHorizontalLayout->addLayout(sidebarLayout);

    // Create a stacked widget for the right side containing other layouts
    stackedWidget = new QStackedWidget();
    editNotesLayout = new edit_notes_vlayout();
    noteLayout = new NoteEditor(this);

    // Create a stacked widget for the right side containing other layouts
    pageOne = new QWidget();
    pageTwo = new QWidget();
    pageOne->setLayout(noteLayout);
    pageTwo->setLayout(editNotesLayout);
    editNotesLayout->setContentsMargins(50, 0, 0, 0);

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

// each componnent should take in user rgument and uuse it
main_window::main_window(User* user, QWidget *parent)
    : QMainWindow(parent)
{
    this->user = user;
    setMinimumSize(MAIN_WINDOW_MIN_WIDTH, MAIN_WINDOW_MIN_HEIGHT);

    // Create the central widget that contains all layouts and widgets
    QWidget *centralWidget = new QWidget(this);

    // Create layouts for the central widget
    mainVerticalLayout = new QVBoxLayout(centralWidget);
    mainHorizontalLayout = new QHBoxLayout();

    // Add the sidebar layout to the left side of the central widget
    // sidebarLayout = new sidebar_vlayout([this](){swapToShowNotes();},
    //                                     [this](){swapToEditNote();});
    sidebarLayout = new sidebar_vlayout([this](){swapToShowNotes();},
                                        [this](){swapToEditNote();},
                                        [this](QString filePath, QString title){
                                            initEditorFromFile(filePath, title);
                                        });
    sidebarLayout->setUser(user);
    mainHorizontalLayout->addLayout(sidebarLayout);

    // Create a stacked widget for the right side containing other layouts
    stackedWidget = new QStackedWidget();

    // Create a stacked widget for the right side containing other layouts
    pageOne = new QWidget();
    pageTwo = new QWidget();

    editNotesLayout = new edit_notes_vlayout(this,user);
    noteLayout = new NoteEditor(this);
    pageOne->setLayout(noteLayout);
    pageTwo->setLayout(editNotesLayout);
    // editNotesLayout->setContentsMargins(50, 0, 0, 0);

    // Add layouts to the stacked widget
    stackedWidget->addWidget(pageTwo);
    stackedWidget->addWidget(pageOne);

    // Add the stacked widget to the horizontal layout
    mainHorizontalLayout->addWidget(stackedWidget);

    // Add the horizontal layout to the vertical layout
    mainVerticalLayout->addLayout(mainHorizontalLayout);

    // Set the overall layout for the central widget
    centralWidget->setLayout(mainVerticalLayout);

    // show useername make sure it;ss working
    setCentralWidget(centralWidget);
}

void main_window::helloWorld()
{
    qDebug()<<"hello world";
}

void main_window::swapToEditNote()
{
    // swap to widget 1
    stackedWidget->setCurrentIndex(1);  // Index of editNotesLayout
}

void main_window::swapToShowNotes()
{
    stackedWidget->setCurrentIndex(0);  // Index of noteLayout
}

void main_window::initEditorFromFile(QString filePath, QString title)
{
    ClientController c1("127.0.0.1", "12345");
    QStringList lines;
    if(QFile::exists(filePath) ){
        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text) ){
            qDebug()<<"couldn't open file";
            return;
        }
        QTextStream in(&file);
        QString fileContents = in.readAll();
        lines = fileContents.split("\n", Qt::SkipEmptyParts);
        file.close();
    }
    Note* temp = new Note(user->getuserId(), title.toStdString());
    std::string response;
    if(c1.ClientCreateNote(temp, &response))
        qDebug() << response;

    myDelteLayout(noteLayout);
    NoteEditor *newLayout= new NoteEditor(this, lines, title);

    noteLayout=newLayout;
    pageOne->setLayout(noteLayout);
    pageOne->update();
    stackedWidget->setCurrentIndex(1);
}

void main_window::initEditorFromNote(Note *note)
{

    std::vector<NoteComponent> noteComponents;
    std::string response = "";

    ClientController c1("127.0.0.1", "12345");
    bool flag = c1.ClientListComponents(note, &response, noteComponents);
    if(!flag){
        qDebug()<<response;
        return;
    }
    qDebug()<<response;


    myDelteLayout(noteLayout);
    NoteEditor *newLayout= new NoteEditor(this, note, noteComponents);

    noteLayout=newLayout;
    pageOne->setLayout(noteLayout);
    pageOne->update();
    stackedWidget->setCurrentIndex(1);
}
