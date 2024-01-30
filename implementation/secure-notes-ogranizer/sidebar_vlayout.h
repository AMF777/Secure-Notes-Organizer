#ifndef SIDEBAR_LAYOUT_H
#define SIDEBAR_LAYOUT_H

#include <QVBoxLayout>
#include <QPushButton>

using namespace std;

class sidebar_vlayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit sidebar_vlayout(QWidget *parent = nullptr);
    QPushButton *createButton(const QString &iconPath, const QString &className,
                             Qt::Alignment alignment = Qt::AlignLeft, const function<void()> &onClick = nullptr);

private:
    static const QSize iconSize;

private slots:
    void setButtonSizePolicy(QPushButton *button);
    void profileButtonClicked();
    void addNewNoteButtonClicked();
    void editNoteButtonClicked();
    void logoutButtonClicked();
};

#endif // SIDEBAR_LAYOUT_H
