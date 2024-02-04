#ifndef NOTE_WIDGET_H
#define NOTE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include<QObject>
#include<QEvent>

class note_widget : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit note_widget(QWidget *parent = nullptr);
    bool eventFilter(QObject *object, QEvent *event);
    QLabel *imageLabel;
    QLabel *title;
    QLabel *tags;
    QLabel *preview;
signals:
public slots:
    void widgetClicked();
};

#endif // NOTE_WIDGET_H
