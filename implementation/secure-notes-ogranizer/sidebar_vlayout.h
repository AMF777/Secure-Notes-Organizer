#ifndef SIDEBAR_LAYOUT_H
#define SIDEBAR_LAYOUT_H

#include <QVBoxLayout>
#include <QPushButton>
#include "button_icon_vlayout.h"

using namespace std;

class sidebar_vlayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit sidebar_vlayout(QWidget *parent = nullptr);

    explicit sidebar_vlayout(const std::function<void()> swapToEdit,
                             const std::function<void()> swapToShow, QWidget *parent = nullptr);

    void createButton(const QString &iconPath, const QString &className, const QSize iconSize,
                      Qt::Alignment alignment, const std::function<void()> &onClick);

private:
    static const QSize iconSize;

private slots:
    void profileButtonClicked();
    void addNewNoteButtonClicked();
    // void editNoteButtonClicked();
    void logoutButtonClicked();
    // void viewNotesClicked();

private:
    QVector <button_icon_vlayout*> buttons;
};

#endif // SIDEBAR_LAYOUT_H
