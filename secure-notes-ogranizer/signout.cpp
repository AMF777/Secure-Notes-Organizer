#include "signout.h"
#include "constants.h"
#include "switcher_widget.h"
#include <QGraphicsBlurEffect>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

signout::signout(QWidget *parent)
    : QDialog{parent}
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setProperty("class", "white-background round-corners profile-dialog-border");
    setModal(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setProperty("class", "white-background");

    QLabel *label = new QLabel("Are you sure you want to sign out?");
    label->setStyleSheet("font-weight: bold; font-size: 16px; margin-bottom: 20px; color: black;");
    mainLayout->addWidget(label, 0, Qt::AlignCenter);

    QPushButton *signoutButton = new QPushButton("Sign Out");
    signoutButton->setProperty("class", "signout-button");
    signoutButton->setCursor(Qt::PointingHandCursor);
    connect(signoutButton, &QPushButton::clicked, this, &signout::onSignOutClicked);

    QPushButton *cancelButton = new QPushButton("Cancel");
    cancelButton->setProperty("class", "cancel-button");
    cancelButton->setCursor(Qt::PointingHandCursor);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(signoutButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(Qt::AlignCenter);
}

void signout::showEvent(QShowEvent *event){
    // auto parent=parentWidget()->parentWidget();
    auto parent=parentWidget();
    if (parent) {
        QSize parentSize = parent->size();
        int dialogWidth = parentSize.width() * 0.4;
        int dialogHeight = parentSize.height() * 0.3;
        setFixedSize(dialogWidth, dialogHeight);

        int x = parent->geometry().x() + (parentSize.width() - dialogWidth) / 2;
        int y = parent->geometry().y() + (parentSize.height() - dialogHeight) / 2;

        QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect();
        blurEffect->setBlurRadius(10);
        parent->setGraphicsEffect(blurEffect);
        move(x, y);
    }

    QDialog::showEvent(event);
}

void signout::hideEvent(QHideEvent *event)
{
    // auto parent=parentWidget()->parentWidget();
    auto parent=parentWidget();
    if(parent){
        parent->setGraphicsEffect(nullptr);
    }

    QDialog::hideEvent(event);
}


void signout::onSignOutClicked()
{
    accept();
    parentWidget()->close();
    switcher_widget* s = new switcher_widget();
    s->show();
}
