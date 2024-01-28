#ifndef BUTTON_ICON_VLAYOUT_H
#define BUTTON_ICON_VLAYOUT_H

#include "qboxlayout.h"
#include <QWidget>
#include <QPushButton>

class button_icon_vlayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit button_icon_vlayout(const QString &iconPath, const QString &className,QSize iconSize
                                , Qt::Alignment alignment, const std::function<void()> &onClick);

signals:

private:
    void setButtonSizePolicy();
    QPushButton* btn;
    QString path;
};

#endif // BUTTON_ICON_VLAYOUT_H
