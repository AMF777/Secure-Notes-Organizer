#ifndef EDIT_NOTES_VLAYOUT_H
#define EDIT_NOTES_VLAYOUT_H

#include <QWidget>
#include <QVBoxLayout>

class edit_notes_vlayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit edit_notes_vlayout(QWidget *parent = nullptr);

signals:
};

#endif // EDIT_NOTES_VLAYOUT_H
