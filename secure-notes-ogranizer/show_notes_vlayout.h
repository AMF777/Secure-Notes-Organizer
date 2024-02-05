#ifndef SHOW_NOTES_VLAYOUT_H
#define SHOW_NOTES_VLAYOUT_H

#include <QWidget>
#include <QVBoxLayout>
#include  <vector>

#include "back-end/Note.h"
#include "back-end/User.h"
class edit_notes_vlayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit edit_notes_vlayout(QWidget *parent = nullptr);
    explicit edit_notes_vlayout(User *user, QWidget *parent = nullptr);
signals:
};

#endif // SHOW_NOTES_VLAYOUT_H
