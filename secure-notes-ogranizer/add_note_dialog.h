#ifndef ADD_NOTE_DIALOG_H
#define ADD_NOTE_DIALOG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDialog>

#include "label_input_vlayout.h"
#include "button_icon_vlayout.h"
#include "back-end/clientcontroller.h"

using namespace GlobalClient;

class add_note_dialog : public QDialog
{
    Q_OBJECT
public:
    std::function<void(QString, QString)> initEditorFromFile;
    explicit add_note_dialog(QWidget *parent = nullptr);
    explicit add_note_dialog(const std::function<void(QString, QString)> initEditorFromFile, QWidget *parent = nullptr);
    QVBoxLayout *mainLayout;
    QVBoxLayout *contentLayout;

    QWidget *overlayWidget;
    label_input_vlayout *filePathLayout;
    label_input_vlayout *fileName;
    button_icon_vlayout *openFileButton;
    QHBoxLayout *inputButtonLayout;

    QPushButton *saveButton;
    QPushButton *cancelButton;
    QHBoxLayout *buttonLayout;
    void openFileDialog();
    void saveButtonClicked();
protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
signals:
};

#endif // ADD_NOTE_DIALOG_H
