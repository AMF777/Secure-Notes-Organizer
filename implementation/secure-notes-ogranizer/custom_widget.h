#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QVector>
#include "button_icon_vlayout.h"
#include "text_edit_component.h"

class CustomWidget : public QVBoxLayout  {
    Q_OBJECT
public:
    CustomWidget(QWidget *parent = nullptr);
private:
    QLabel *timeAgoLabel;
    button_icon_vlayout *shareButton;
    button_icon_vlayout *dotsButton;
    QVBoxLayout *verticalLayoutTextEdits;
    QVector<TextEditComponent*> componentVector;

    void createComponent(QWidget *parent);
};

#endif // CUSTOMWIDGET_H
