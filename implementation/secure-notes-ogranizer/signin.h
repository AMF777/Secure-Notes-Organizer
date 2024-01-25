#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>

class signin : public QWidget
{
    Q_OBJECT
public:
    explicit signin(QWidget *parent = nullptr);

    // static const QString SIGNIN_TITLE;
    // static const int SIGNIN_WIDTH;
    // static const int SIGNIN_HEIGHT;
    // static const int SIEMENS_LOGO_WIDTH;
    // static const int SIEMENS_LOGO_HEIGHT;
signals:
    void switchWidgets();
private slots:
    void loginButtonClicked(const QString email, const QString password);
    void forgotPasswordClicked();
    void createAccountClicked();
private:
    QSize sizeHint() const;
};

#endif // SIGNIN_H
