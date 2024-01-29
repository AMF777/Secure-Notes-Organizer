#ifndef BUTTON_ICON_VLAYOUT_H
#define BUTTON_ICON_VLAYOUT_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>

class button_icon_vlayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit button_icon_vlayout(const QString &iconPath, const QString &className, const QSize iconSize,
                                 Qt::Alignment alignment, const std::function<void()> &onClick);
    QPushButton* button;
    QIcon* icon;
signals:

private:
    void setButtonSizePolicy();
};

#endif // BUTTON_ICON_VLAYOUT_H
