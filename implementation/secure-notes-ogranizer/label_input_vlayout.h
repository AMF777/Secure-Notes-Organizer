#ifndef LABEL_INPUT_VLAYOUT_H
#define LABEL_INPUT_VLAYOUT_H

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

class label_input_vlayout : public QVBoxLayout
{
    Q_OBJECT

public:
    explicit label_input_vlayout(const QString labelText, const QString labelClass,
                                 int inputWidth, const QString inputClass,
                                 QLineEdit::EchoMode echoMode = QLineEdit::Normal,
                                 Qt::Alignment alignment = Qt::Alignment());
    QString getInputText();
private:
    QLabel *label;
    QLineEdit *input;

};

#endif // LABEL_INPUT_VLAYOUT_H
