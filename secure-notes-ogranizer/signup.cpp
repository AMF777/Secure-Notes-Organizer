#include "constants.h"
#include "label_input_vlayout.h"
#include "img_msg_vlayout.h"
#include "clickable_label.h"
#include "back-end/clientcontroller.h"
#include "main_window.h"

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
    errMsg=new QLabel("Your Email and Password do not match. Pleasse try again.");
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
    centerLayout->addWidget(errMsg);
    errMsg->hide();
    errMsg->setWordWrap(true);
    errMsg->setAlignment(Qt::AlignLeft);
    errMsg->setStyleSheet("color:red;");
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
    if(password != confirmPassword){
        errMsg->setText("The Passwords do not match. Please try again");
        errMsg->show();
        return;
    }
    errMsg->hide();
    ClientController c1("127.0.0.1", "12345");
    User user;
    user.setuserName(username.toStdString() );
    user.setemail(email.toStdString() );
    user.sethashedPassword(password.toStdString() );
    std::string response = "";
    bool flag = c1.ClientSignUp(&user, &response);

    qDebug()<<response;
    if(flag){
        qDebug()<<"sign up success";
        parentWidget()->close();
        // create a new main_windooconsttructor that take in  email of  user
        main_window *mw = new main_window();
        mw->show();
        return;
    }
    errMsg->setText("Email already exiss. Please try again");
    errMsg->show();
    qDebug()<<"sign up failed";
    return;


}

void signup::signinClicked()
{
    qDebug()<<"signinClicked";
    emit switchWidgets();
}
