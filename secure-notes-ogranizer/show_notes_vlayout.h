#ifndef SHOW_NOTES_VLAYOUT_H
#define SHOW_NOTES_VLAYOUT_H

#include <QWidget>
#include <QVBoxLayout>
#include  <vector>
#include <QLineEdit>
#include <QGridLayout>

#include "back-end/Note.h"
#include "back-end/User.h"
#include "note_widget.h"
class edit_notes_vlayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit edit_notes_vlayout(QWidget *parent = nullptr);
    explicit edit_notes_vlayout(User *user, QWidget *parent = nullptr);
    explicit edit_notes_vlayout(QWidget *mainWindowRef, User *user, QWidget *parent = nullptr);
    QWidget *mainWindowRef;
    User *user;
    QLabel *label1;
    QLineEdit *searchLineEdit;
    QGridLayout* b1;
    std::vector<note_widget*> noteWidgets;
    std::map<std::string, bool> tagsPool;
public slots:
    void filteredNotesByTag(QString tagName);
private slots:
    void preformSearch(const QString& text);
};

#endif // SHOW_NOTES_VLAYOUT_H
