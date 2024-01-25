#ifndef SWITCHER_WIDGET_H
#define SWITCHER_WIDGET_H
#include "signin.h"
#include "signup.h"

#include <QWidget>
#include <QVBoxLayout>

class switcher_widget : public QWidget
{
    Q_OBJECT
public:
    explicit switcher_widget(QWidget *parent = nullptr);
private slots:
    void switchWidgets();
private:
    QVBoxLayout *mainLayout;
    QList<QWidget*> widgets;
    int curIdx;
};

#endif // SWITCHER_WIDGET_H
