#include "main_window.h"
#include "note_widget.h"
#include "textedit_template.h"

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
void myDeleteV2(QLayout *layout){
    QLayoutItem * child;
    while(layout->count()!=0){
        child=layout->takeAt(0);
        if(child->layout()!=0) myDelteLayout(child->layout()  );
        else if (child->widget()!=0) delete child->widget();
        delete child;
    }
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

    for(TagWidget* tag: noteLayout->tagsLayout->tags)
        connect(tag, &TagWidget::tagClicked, editNotesLayout, &edit_notes_vlayout::filteredNotesByTag);

}

// each componnent should take in user rgument and uuse it
main_window::main_window(User* user, QWidget *parent)
    : QMainWindow(parent)
{
    setProperty("class","main-window-bg");
    setWindowFlags(windowFlags() |  Qt::CustomizeWindowHint);
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
    sidebarLayout = new sidebar_vlayout(this,[this](){swapToShowNotes();},
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

    // NoteEditor(QWidget *mainWindowRef, std::vector<NoteComponent> noteComponents, QString title, User *user, QWidget *parent = nullptr);
    editNotesLayout = new edit_notes_vlayout(this,user);
    noteLayout = new NoteEditor(this, {}, "Title", user);
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

void main_window::setUserTitle(std::string username)
{
    editNotesLayout->label1->setText("My notes("+QString::fromStdString(username)+")" );
}

void main_window::initEditorFromFile(QString filePath, QString title)
{
    std::vector<NoteComponent> noteComponents; // Vector to hold NoteComponents
    if (QFile::exists(filePath)) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Couldn't open file";
            return;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            // Assuming NoteComponent has a constructor that takes a QString
            NoteComponent component;
            component.setcomponentContent(textEdit::staticEncodeCaesarCipher(line ) );

            noteComponents.push_back(component);
        }
        file.close();
    }

    // Note *temp = new Note(user->getuserId(), title.toStdString());
    // temp->settitle(title.toStdString());
    // std::string response;
    // if (client.ClientCreateNote(temp, &response))
    //     qDebug() << response;

    myDelteLayout(noteLayout);
    // NoteEditor *newLayout = new NoteEditor(this, temp, noteComponents);
    // has to get user to update data properly
    NoteEditor *newLayout = new NoteEditor(this, noteComponents, title, user);

    noteLayout = newLayout;
    pageOne->setLayout(noteLayout);
    pageOne->update();
    stackedWidget->setCurrentIndex(1);
}


void main_window::initEditorFromNote(Note *note)
{

    std::vector<NoteComponent> noteComponents;
    std::string response = "";

    bool flag = client.ClientListComponents(note, &response, noteComponents);
    if(!flag){
        qDebug()<<response;
        return;
    }
    qDebug()<<response;


    myDelteLayout(noteLayout);
    NoteEditor *newLayout= new NoteEditor(this, note, user);

    noteLayout=newLayout;
    pageOne->setLayout(noteLayout);
    pageOne->update();
    stackedWidget->setCurrentIndex(1);
}

void main_window::refreshViewNotes(bool goBack)
{
    myDelteLayout(editNotesLayout);
    edit_notes_vlayout *newLayout= new edit_notes_vlayout(this, user);
    editNotesLayout=newLayout;
    pageTwo->setLayout(editNotesLayout);
    pageTwo->update();

    if(goBack) stackedWidget->setCurrentIndex(0);
}
