#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QStackedWidget>

#include "show_notes_vlayout.h"
#include "constants.h"
#include "note_editor.h"
#include "sidebar_vlayout.h"
#include "back-end/User.h"
#include "back-end/Note.h"


class main_window : public QMainWindow
{
    Q_OBJECT
public:

    explicit main_window(QWidget *parent = nullptr);
    explicit main_window(User* user, QWidget *parent = nullptr);

    void helloWorld();
    void initEditorFromNote(Note* note);

    User* user;
    NoteEditor* noteLayout;
    edit_notes_vlayout* editNotesLayout;
    sidebar_vlayout* sidebarLayout;
    QStackedWidget* stackedWidget;
    QWidget* pageOne;
    QWidget* pageTwo;
    void setC1(const ClientController &newC1);

private slots:
    void swapToEditNote();
    void swapToShowNotes();
    void initEditorFromFile(QString filePath, QString title);
private:
    QVBoxLayout *mainVerticalLayout;
    QHBoxLayout *mainHorizontalLayout;
};

#endif // MAIN_WINDOW_H
