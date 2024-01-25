#include "clickable_label.h"

clickable_label::clickable_label(QWidget *parent)
    : QLabel{parent}
{
    setCursor(Qt::PointingHandCursor);
}

clickable_label::clickable_label(const QString labelText)
    : QLabel{labelText}
{
    setCursor(Qt::PointingHandCursor);
}

clickable_label::clickable_label(const QString labelText, const QString labelClass)
    : QLabel{labelText}
{
    setCursor(Qt::PointingHandCursor);
    setProperty("class", labelClass);
}

void clickable_label::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}
