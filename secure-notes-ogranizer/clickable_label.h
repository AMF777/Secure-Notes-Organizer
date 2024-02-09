#ifndef CLICKABLE_LABEL_H
#define CLICKABLE_LABEL_H

#include <QWidget>
#include <QLabel>

class clickable_label : public QLabel
{
    Q_OBJECT
public:
    explicit clickable_label(QWidget *parent = nullptr);
    explicit clickable_label(const QString labelText);
    explicit clickable_label(const QString labelText, const QString labelClass);
    void mousePressEvent(QMouseEvent* event);
signals:
    void clicked();
};

#endif // CLICKABLE_LABEL_H
