#include "button_icon_vlayout.h"

button_icon_vlayout::button_icon_vlayout(const QString &iconPath, const QString &className,
                                         QSize iconSize, Qt::Alignment alignment, const std::function<void ()> &onClick)
{

    QPushButton *button = new QPushButton();
    button->setIcon(QIcon(iconPath));
    button->setIconSize(iconSize);

    connect(button, &QPushButton::clicked, onClick);

    setButtonSizePolicy();

    button->setProperty("class", className);

    addWidget(button, 0, alignment);
}

void button_icon_vlayout::setButtonSizePolicy()
{
    QSizePolicy buttonSizePolicy = this->btn->sizePolicy();
    buttonSizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    buttonSizePolicy.setVerticalPolicy(QSizePolicy::Minimum);
    this->btn->setSizePolicy(buttonSizePolicy);
}
