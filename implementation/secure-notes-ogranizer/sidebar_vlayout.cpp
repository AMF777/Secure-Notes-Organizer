// sidebar_layout.cpp
#include "sidebar_vlayout.h"

const QSize SidebarLayout::iconSize = QSize(20, 20);

SidebarLayout::SidebarLayout(QWidget *parent) : QVBoxLayout(parent)
{
}

QPushButton *SidebarLayout::createButton(const QString &iconPath, const QString &className,
                                         Qt::Alignment alignment, const std::function<void()> &onClick)
{

    QPushButton *button = new QPushButton();
    button->setIcon(QIcon(iconPath));
    button->setIconSize(iconSize);

    connect(button, &QPushButton::clicked, onClick);

    setButtonSizePolicy(button);

    button->setProperty("class", className);

    addWidget(button, 0, alignment);

    return button;
}

void SidebarLayout::setButtonSizePolicy(QPushButton *button)
{
    QSizePolicy buttonSizePolicy = button->sizePolicy();
    buttonSizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    buttonSizePolicy.setVerticalPolicy(QSizePolicy::Minimum);
    button->setSizePolicy(buttonSizePolicy);
}

