#include "constants.h"
#include "label_input_vlayout.h"
#include "img_msg_vlayout.h"
#include "clickable_label.h"

#include "signup.h"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFrame>
signup::signup(QWidget *parent)
    : QWidget{parent}
{

    setWindowTitle(SIGNUP_TITLE);
    setFixedSize(SIGNIN_WIDTH, SIGNIN_HEIGHT);
    // setProperty("class", "white-background");

    img_msg_vlayout *logoLayout=new img_msg_vlayout(
        ":/res/img/siemens-logo.png",
        SIEMENS_LOGO_WIDTH,
        SIEMENS_LOGO_HEIGHT,
        "margin-bottom-8px",
        "Sign up for secNotes!",
        "user-label margin-bottom-16px",
        Qt::AlignCenter
    );

    label_input_vlayout *usernameLayout=new label_input_vlayout(
        "Username:",
        "user-label",
        INPUT_WIDTH,
        "user-input"
    );
    label_input_vlayout *emailLayout=new label_input_vlayout(
        "Email Address:",
        "user-label",
        INPUT_WIDTH,
        "user-input"
    );
    label_input_vlayout *passwordLayout=new label_input_vlayout(
        "Password:",
        "user-label",
        INPUT_WIDTH,
        "user-input",
        QLineEdit::Password
    );
    label_input_vlayout *confirmPasswordLayout=new label_input_vlayout(
        "Confirm Password:",
        "user-label",
        INPUT_WIDTH,
        "user-input",
        QLineEdit::Password
    );

    QPushButton *signupButton = new QPushButton("Sign up");
    // signupButton->setFixedWidth(LOGIN_BUTTON_WIDTH);
    // signupButton->setFixedHeight(LOGIN_BUTTON_HEIGHT);
    signupButton->setProperty("class", "login-button margin-bottom-8px");
    signupButton->setCursor(Qt::PointingHandCursor);

    connect(signupButton, &QPushButton::clicked, this, [=]() {
        signupButtonClicked(usernameLayout->getInputText(),emailLayout->getInputText(),
            passwordLayout->getInputText(), confirmPasswordLayout->getInputText() );  // Replace with your actual arguments
    });
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(signupButton, 0, Qt::AlignLeft);

    QFrame *separatorLabel = new QFrame();
    separatorLabel->setFrameShape(QFrame::HLine);
    separatorLabel->setProperty("class", "separator-line");

    clickable_label *haveAccount = new clickable_label("Already have an account? Login here!", "clickable-label");
    connect(haveAccount, &clickable_label::clicked, this, [=]() {
        signinClicked();
    });

    QVBoxLayout *clickableLabelsLayout = new QVBoxLayout();
    clickableLabelsLayout->addWidget(separatorLabel);
    clickableLabelsLayout->addWidget(haveAccount,0,Qt::AlignLeft);

    QVBoxLayout *centerLayout = new QVBoxLayout();

    centerLayout->addLayout(logoLayout);
    centerLayout->addLayout(usernameLayout);
    centerLayout->addLayout(emailLayout);
    centerLayout->addLayout(passwordLayout);
    centerLayout->addLayout(confirmPasswordLayout);
    centerLayout->addLayout(buttonLayout);
    centerLayout->addLayout(clickableLabelsLayout);

    // Set margins to zero to minimize spacing in the inner layout
    centerLayout->setAlignment(Qt::AlignCenter);
    centerLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    // Add the inner center layout to the main layout
    mainLayout->addLayout(centerLayout);
}

void signup::signupButtonClicked(const QString username, const QString email, const QString password, const QString confirmPassword)
{
    qDebug() << "Username: " << username;
    qDebug() << "Email: " << email;
    qDebug() << "Password: " << password;
    qDebug() << "Confirm Password: " << confirmPassword;
}

void signup::signinClicked()
{
    qDebug()<<"signinClicked";
    emit switchWidgets();
}
