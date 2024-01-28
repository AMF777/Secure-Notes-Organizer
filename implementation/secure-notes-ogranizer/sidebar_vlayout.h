#ifndef SIDEBAR_LAYOUT_H
#define SIDEBAR_LAYOUT_H

#include <QVBoxLayout>
#include <QPushButton>

using namespace std;

class SidebarLayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit SidebarLayout(QWidget *parent = nullptr);
    QPushButton *createButton(const QString &iconPath, const QString &className,
                             Qt::Alignment alignment = Qt::AlignLeft, const function<void()> &onClick = nullptr);

private:

    static const QSize iconSize;
    void setButtonSizePolicy(QPushButton *button);
};

#endif // SIDEBAR_LAYOUT_H
