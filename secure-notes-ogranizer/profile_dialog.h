#ifndef PROFILE_DIALOG_H
#define PROFILE_DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include "button_icon_vlayout.h"
#include "label_input_vlayout.h"
#include "round_img_label.h"
#include "back-end/clientcontroller.h"

using namespace GlobalClient;

class profile_dialog : public QDialog
{
    Q_OBJECT
public:
    explicit profile_dialog(User* user, QWidget *parent = nullptr);

    QVBoxLayout *mainLayout;

    QVBoxLayout *avatarLayout;
    round_img_label *avatarLabel;
    button_icon_vlayout* uploadButton;
    QHBoxLayout *notesSharesLayout;
    QVBoxLayout *notesCountLayout;
    QLabel *notes;
    QLabel *notesCount;
    QVBoxLayout *sharesCountLayout;
    QLabel *shares;
    QLabel *sharesCount;

    QVBoxLayout *contentLayout;
    label_input_vlayout *usernameLayout;
    label_input_vlayout *emailLayout;
    label_input_vlayout *passwordLayout;
    label_input_vlayout *confirmPasswordLayout;

    QHBoxLayout *buttonLayout;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QLabel *errMsg;
protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

public slots:
    void avatarClicked();
    void saveButtonClicked();

private:
    User* user;
};

#endif // PROFILE_DIALOG_H
