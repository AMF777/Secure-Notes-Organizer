#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSplitter>
#include <QLabel>
#include "button_icon_vlayout.h"
#include "tags_hlayout.h"

class main_window : public QMainWindow
{
    Q_OBJECT
public:
    explicit main_window(QWidget *parent = nullptr);

private:
    QLabel *timeAgoLabel;
    button_icon_vlayout *saveNoteButton;
    button_icon_vlayout *shareButton;

    QHBoxLayout* createTimeAndButtonsLayout();
    QHBoxLayout* createTitleNoteLayout();
};

#endif // MAIN_WINDOW_H
