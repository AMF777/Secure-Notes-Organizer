#ifndef SIGNOUT_H
#define SIGNOUT_H

#include <QWidget>

class signout : public QWidget {
    Q_OBJECT  // Macro required for signals and slots

public:
    explicit signout(QWidget *parent = nullptr);
signals:
    void switchWidgets();
protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
private slots:
    void onSignOutClicked();
    void onCancelClicked();
private:
    QSize sizeHint() const;
};

#endif // SIGNOUT_H
