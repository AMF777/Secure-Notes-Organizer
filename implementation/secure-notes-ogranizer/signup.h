#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>

class signup : public QWidget
{
    Q_OBJECT
public:
    explicit signup(QWidget *parent = nullptr);
signals:
    void switchWidgets();
private slots:
    void signupButtonClicked(const QString username, const QString email, const QString password, const QString confirmPassword);
    void signinClicked();
};

#endif // SIGNUP_H
