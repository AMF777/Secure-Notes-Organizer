#ifndef NOTE_WIDGET_H
#define NOTE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include<QObject>
#include<QEvent>

#include "back-end/Note.h"

class note_widget : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit note_widget(QWidget *parent = nullptr);
    explicit note_widget(Note* note, QWidget *parent = nullptr);
    explicit note_widget(QWidget *mainWindowRef, Note* note, QWidget *parent = nullptr);
    bool eventFilter(QObject *object, QEvent *event);
    QWidget *mainWindowRef;
    QWidget *centralWidget;
    QLabel *imageLabel;
    QLabel *title;
    QLabel *tags;
    QLabel *preview;
    Note* note;
    std::vector<std::string> tagsVector;
signals:
public slots:
    void widgetClicked();
};

#endif // NOTE_WIDGET_H
