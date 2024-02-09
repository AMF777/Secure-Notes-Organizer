#include "label_input_vlayout.h"

label_input_vlayout::
    label_input_vlayout(const QString labelText, const QString labelClass,
                        int inputWidth, const QString inputClass,
                        QLineEdit::EchoMode echoMode, Qt::Alignment alignment)
    : QVBoxLayout(nullptr)
{
    label = new QLabel(labelText);
    label->setProperty("class", labelClass);

    input = new QLineEdit();
    input->setFixedWidth(inputWidth);  // You can adjust this if needed
    input->setProperty("class", inputClass);
    input->setEchoMode(echoMode);

    addWidget(label,0,alignment);
    addWidget(input,0,alignment);
}

QString label_input_vlayout::getInputText()
{
    return input->text();
}
