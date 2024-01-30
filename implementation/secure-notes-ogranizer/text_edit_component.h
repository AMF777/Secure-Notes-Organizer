#ifndef TEXT_EDIT_COMPONENT_H
#define TEXT_EDIT_COMPONENT_H

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QKeyEvent>

class TextEditComponent : public QWidget
{
    Q_OBJECT
public:
    explicit TextEditComponent(QWidget *parent = nullptr);

signals:
    void createNewComponent();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onFocusChanged(bool hasFocus);
    void updateHeight();

private:
    QTextEdit *textEdit;
    QLabel *selectColumnIcon;
    QHBoxLayout *layout;
};

#endif // TEXT_EDIT_COMPONENT_H
