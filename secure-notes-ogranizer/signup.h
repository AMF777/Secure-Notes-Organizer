#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QLabel>
#include "back-end/clientcontroller.h"

using namespace GlobalClient;

class signup : public QWidget
{
    Q_OBJECT
public:
    explicit signup(QWidget *parent = nullptr);
    QLabel* errMsg;
signals:
    void switchWidgets();
private slots:
    void signupButtonClicked(const QString username, const QString email, const QString password, const QString confirmPassword);
    void signinClicked();
};

#endif // SIGNUP_H
