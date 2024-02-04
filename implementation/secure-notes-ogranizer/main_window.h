#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QStackedWidget>
#include "edit_notes_vlayout.h"
#include "constants.h"
#include "note_editor.h"
#include "sidebar_vlayout.h"

class main_window : public QMainWindow
{
    Q_OBJECT
public:
    explicit main_window(QWidget *parent = nullptr);
    NoteEditor* noteLayout;
    edit_notes_vlayout* editNotesLayout;
    sidebar_vlayout* sidebarLayout;
    QStackedWidget* stackedWidget;

private slots:
    void swapToEditNote();
    void swapToShowNotes();

private:
    QVBoxLayout *mainVerticalLayout;
    QHBoxLayout *mainHorizontalLayout;
};

#endif // MAIN_WINDOW_H
