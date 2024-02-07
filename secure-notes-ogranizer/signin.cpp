#include "constants.h"
#include "label_input_vlayout.h"
#include "img_msg_vlayout.h"
#include "clickable_label.h"
#include "signin.h"
#include "back-end/clientcontroller.h"
#include "main_window.h"


#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFrame>

signin::signin(QWidget *parent)
    : QWidget{parent}
{
    // create window set the desired properties and styles
    setWindowTitle(SIGNIN_TITLE);
    setFixedSize(SIGNIN_WIDTH, SIGNIN_HEIGHT);
    // setProperty("class", "white-background");
    errMsg=new QLabel("Your Email and Password do not match. Pleasse try again.");
    img_msg_vlayout *logoLayout=new img_msg_vlayout(
        ":/res/img/siemens-logo.png",
        SIEMENS_LOGO_WIDTH,
        SIEMENS_LOGO_HEIGHT,
        "margin-bottom-8px",
        "Welcome! Login to your account",
        "user-label margin-bottom-16px",
        Qt::AlignCenter
    );

    label_input_vlayout *emailLayout=new label_input_vlayout("Email Address:","user-label",INPUT_WIDTH,"user-input");
    emailLayout->input->setText("mo3@gmail.com");
    label_input_vlayout *passwordLayout=new label_input_vlayout("Password:","user-label",INPUT_WIDTH,
                                                                  "user-input",QLineEdit::Password);
    passwordLayout->input->setText("2001");
    QPushButton *loginButton = new QPushButton("Login");
    // loginButton->setFixedWidth(LOGIN_BUTTON_WIDTH);
    // loginButton->setFixedHeight(LOGIN_BUTTON_HEIGHT);mmmm
    loginButton->setProperty("class", "login-button margin-bottom-8px");
    loginButton->setCursor(Qt::PointingHandCursor);
    connect(loginButton, &QPushButton::clicked, this, [=]() {
        loginButtonClicked(emailLayout->getInputText(), passwordLayout->getInputText() );  // Replace with your actual arguments
    });
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loginButton, 0, Qt::AlignLeft);

    QFrame *separatorLabel = new QFrame();
    separatorLabel->setFrameShape(QFrame::HLine);
    separatorLabel->setProperty("class", "separator-line");

    clickable_label *forgotPasswordLabel = new clickable_label("Forgot Password?", "clickable-label");
    connect(forgotPasswordLabel, &clickable_label::clicked, this, [=]() {
        forgotPasswordClicked();
    });

    clickable_label *createAccountLabel  = new clickable_label("Don't have an account? Create an account!", "clickable-label");
    connect(createAccountLabel, &clickable_label::clicked, this, [=]() {
        createAccountClicked();
    });
    QVBoxLayout *clickableLabelsLayout = new QVBoxLayout();
    clickableLabelsLayout->addWidget(separatorLabel);
    clickableLabelsLayout->addWidget(forgotPasswordLabel,0,Qt::AlignLeft);
    clickableLabelsLayout->addWidget(createAccountLabel,0,Qt::AlignLeft);

    QVBoxLayout *centerLayout = new QVBoxLayout();

    centerLayout->addLayout(logoLayout);
    centerLayout->addLayout(emailLayout);
    centerLayout->addLayout(passwordLayout);
    centerLayout->addLayout(buttonLayout);
    centerLayout->addWidget(errMsg);
    errMsg->hide();
    errMsg->setWordWrap(true);
    errMsg->setAlignment(Qt::AlignLeft);
    errMsg->setStyleSheet("color:red;");
    centerLayout->addLayout(clickableLabelsLayout);

    // Set margins to zero to minimize spacing in the inner layout
    centerLayout->setAlignment(Qt::AlignCenter);
    centerLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    // Add the inner center layout to the main layout
    mainLayout->addLayout(centerLayout);

}

void signin::loginButtonClicked(const QString email, const QString password)
{
    errMsg->hide();
    std::string response = "";

    User* user = new User();
    user->setemail(email.toStdString() );
    QString hashedPassword = user->hashPassword(password);
    user->sethashedPassword(hashedPassword.toStdString());

    bool flag = client.ClientLogIn(user, &response);

    qDebug()<<response;
    if(flag){
        qDebug()<<"sign in success";
        parentWidget()->close();

        close();
        // create a new main_windooconsttructor that take in  email of  user
        main_window *mw = new main_window(user);
        mw->show();
        return;
    }
    qDebug()<<"sign in failed";
    errMsg->show();
}

void signin::forgotPasswordClicked()
{
    qDebug()<<"forgotPasswordClicked";
    QMessageBox::information(this,"Restore password","what should i do?");
}

void signin::createAccountClicked()
{
    qDebug()<<"createAccountClicked";
    emit switchWidgets();
}
// this gives a hint and might not give widget desired width and height
QSize signin::sizeHint() const
{
    return QSize(SIGNIN_WIDTH,SIGNIN_HEIGHT);
}
