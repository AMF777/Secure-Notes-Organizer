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
                                        [this](QString filePath){
                                            initEditorFromFile(filePath);
                                        });
    mainHorizontalLayout->addLayout(sidebarLayout);

    // Create a stacked widget for the right side containing other layouts
    stackedWidget = new QStackedWidget();
    editNotesLayout = new edit_notes_vlayout();
    noteLayout = new NoteEditor();

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
                                        [this](QString filePath){
                                            initEditorFromFile(filePath);
                                        });
    sidebarLayout->setUser(user);
    mainHorizontalLayout->addLayout(sidebarLayout);

    // Create a stacked widget for the right side containing other layouts
    stackedWidget = new QStackedWidget();
    // editNotesLayout = new edit_notes_vlayout();
    editNotesLayout = new edit_notes_vlayout(user);
    noteLayout = new NoteEditor();

    // Create a stacked widget for the right side containing other layouts
    pageOne = new QWidget(centralWidget);
    pageTwo = new QWidget(centralWidget);
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

    // show useername make sure it;ss working
    setCentralWidget(centralWidget);
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

void main_window::initEditorFromFile(QString filePath)
{
    if(!QFile::exists(filePath) ){
        qDebug()<<"file dne";
        return;
    }

    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text) ){
        qDebug()<<"couldn't open file";
        return;
    }
    QTextStream in(&file);
    QString fileContents = in.readAll();
    QStringList lines = fileContents.split("\n", Qt::SkipEmptyParts);
    // Print the contents using qDebug
    // qDebug()<<"init called correctly";
    // qDebug() << "Number of lines:" << lines.size();
    // for (const QString &line : lines) {
    //     qDebug() << line;
    // }
    file.close();

    myDelteLayout(noteLayout);
    NoteEditor *newLayout= new NoteEditor(lines);

    noteLayout=newLayout;
    pageOne->setLayout(noteLayout);
    pageOne->update();
    stackedWidget->setCurrentIndex(1);
}

void main_window::initEditorFromNote(Note *note)
{
    // bool ClientCreateComponent(NoteComponent *noteComponent, User* user, std::string* response); //client set in user object (user id) and set in component object (note id, component content, Font(size, color, bold, italic, underlined, style, family, backgroundColor)) and get (component id)
    // bool ClientUpdateComponent(NoteComponent *noteComponent, User* user, std::string* response); //client set in user object (user id) and set in component object (note id, component content, Font(size, color, bold, italic, underlined, style, family, backgroundColor)) and get (component id)
    // bool ClientDeleteComponent(NoteComponent *noteComponenNotet, User* user, std::string* response); //client set in user object (user id) and set in component object (note id, component id)
    // bool ClientListComponents(Note *note, std::string* response, std::vector<NoteComponent>& ComponentsList); //client set(user id, note id) and get vector(ComponentsList))
    std::vector<NoteComponent> noteComponents;
    std::string response = "";
    ClientController c1("127.0.0.1", "12345");
    bool flag = c1.ClientListComponents(note, &response, noteComponents);
    if(!flag){
        qDebug()<<response;
        return;
    }

}
