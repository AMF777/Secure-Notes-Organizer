#include "button_icon_vlayout.h"

button_icon_vlayout::button_icon_vlayout(const QString &iconPath, const QString &className, const QSize iconSize,
                                         Qt::Alignment alignment, const std::function<void()> &onClick)
{

    button = new QPushButton();
    icon = new QIcon(iconPath);

    button->setIcon(*icon);
    button->setIconSize(iconSize);

    connect(button, &QPushButton::clicked, onClick);

    button->setProperty("class", className);

    addWidget(button, 0, alignment);
}
