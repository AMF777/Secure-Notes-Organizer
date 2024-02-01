#include "constants.h"
#include "QGraphicsBlurEffect"
#include "signout.h"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFrame>

signout::signout(QWidget *parent)
    : QWidget{parent}
{
    // create window set the desired properties and styles
    setWindowTitle(SIGNOUT_TITLE);
    setFixedSize(SIGNOUT_WIDTH, SIGNOUT_HEIGHT);
    setProperty("class","white-background");

    QLabel *label = new QLabel("Are you sure you want to sign out?");
    label->setStyleSheet("font-weight: bold; font-size: 16px;margin-bottom:20px;");
    // label->setProperty("class", "signout-button");
    // signoutButton->setCursor(Qt::PointingHandCursor);
    QVBoxLayout *labelLayout = new QVBoxLayout();
    labelLayout->addWidget(label, 0, Qt::AlignLeft);


    QPushButton *signoutButton = new QPushButton("Sign Out");
    signoutButton->setProperty("class", "signout-button");
    signoutButton->setCursor(Qt::PointingHandCursor);
    connect(signoutButton, &QPushButton::clicked, this, [=]() {
        onSignOutClicked();
    });

    QPushButton *cancelButton = new QPushButton("cancel");
    cancelButton->setProperty("class", "cancel-button");
    cancelButton->setCursor(Qt::PointingHandCursor);
    connect(cancelButton, &QPushButton::clicked, this, [=]() {
        onCancelClicked();
    });

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(signoutButton, 0, Qt::AlignLeft);
    buttonLayout->addWidget(cancelButton, 0, Qt::AlignRight);

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addLayout(labelLayout);
    centerLayout->addLayout(buttonLayout);


    // Set margins to zero to minimize spacing in the inner layout
    centerLayout->setAlignment(Qt::AlignCenter);
    centerLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    // Add the inner center layout to the main layout
    mainLayout->addLayout(centerLayout);

}

void signout::showEvent(QShowEvent *event){
    // Calculate the desired width and height based on the parent widget's size
    if (parentWidget()) {
        QSize parentSize = parentWidget()->size();
        int dialogWidth = parentSize.width() * 0.8;
        int dialogHeight = parentSize.height() * 0.7;
        setFixedSize(dialogWidth, dialogHeight);

        int x = parentWidget()->geometry().x() + (parentSize.width() - dialogWidth) / 2;
        int y = parentWidget()->geometry().y() + (parentSize.height() - dialogHeight) / 2;

        QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect();
        blurEffect->setBlurRadius(10); // Adjust the blur radius as needed
        parentWidget()->setGraphicsEffect(blurEffect);
        // parentWidget()->setDisabled(true);

        // Move the dialog to the center position
        move(x, y);
    }

    // Call the base class implementation of showEvent
    // QDialog::showEvent(event);
}

void signout::hideEvent(QHideEvent *event)
{
    qDebug()<<"hide event";
    if(parentWidget() ){
        parentWidget()->setGraphicsEffect(nullptr);
        parentWidget()->setDisabled(false);
    }
    // Call the base class implementation of hideEvent
    // QDialog::hideEvent(event);
}

void signout::onSignOutClicked()
{
    qDebug()<<"SignOutClicked";
    emit switchWidgets();
}

void signout::onCancelClicked()
{
    if(parentWidget()){
        qDebug() << "here";
        parentWidget()->setGraphicsEffect(nullptr);
    }
    qDebug() << "Canceled Button clicked";
    this->close();
}

QSize signout::sizeHint() const
{
    return QSize(SIGNIN_WIDTH,SIGNIN_HEIGHT);
}
