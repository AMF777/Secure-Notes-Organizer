#ifndef SIGNOUT_H
#define SIGNOUT_H

#include <QDialog>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class signout : public QDialog
{
    Q_OBJECT

public:
    explicit signout(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private slots:
    void onSignOutClicked();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
};

#endif // SIGNOUT_H
