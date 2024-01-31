#ifndef ADD_NOTE_DIALOG_H
#define ADD_NOTE_DIALOG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDialog>

#include "label_input_vlayout.h"
#include "button_icon_vlayout.h"

class add_note_dialog : public QDialog
{
    Q_OBJECT
public:
    explicit add_note_dialog(QWidget *parent = nullptr);

    QVBoxLayout *mainLayout;
    QVBoxLayout *contentLayout;

    QWidget *overlayWidget;
    label_input_vlayout *filePathLayout;
    button_icon_vlayout *openFileButton;
    QHBoxLayout *inputButtonLayout;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QHBoxLayout *buttonLayout;
    void openFileDialog();
protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
signals:
};

#endif // ADD_NOTE_DIALOG_H
