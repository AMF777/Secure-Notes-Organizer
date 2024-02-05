// button_icon_vlayout.cpp

#include "button_icon_vlayout.h"

// Constructor for the button with an icon in a vertical layout
button_icon_vlayout::button_icon_vlayout(const QString &iconPath, const QString &className, const QSize iconSize,
                                         Qt::Alignment alignment, const std::function<void()> &onClick)
{
    // Create a QPushButton and QIcon
    button = new QPushButton();
    icon = new QIcon(iconPath);

    // Set the icon and its size for the button
    button->setIcon(*icon);
    button->setIconSize(iconSize);

    // Connect the clicked signal of the button to the provided onClick function
    connect(button, &QPushButton::clicked, onClick);

    // Set a custom property for styling purposes
    button->setProperty("class", className);

    // Add the button to the layout with the specified alignment
    addWidget(button, 0, alignment);
}

// Function to set the onClick handler for the button
void button_icon_vlayout::setClickHandler(const std::function<void()> &onClick)
{
    // Disconnect the existing connection
    disconnect(button, &QPushButton::clicked, nullptr, nullptr);

    // Connect the clicked signal to the new onClick function
    connect(button, &QPushButton::clicked, onClick);
}

// Function to set the size policy of the button
void button_icon_vlayout::setButtonSizePolicy()
{
    // Get the current size policy of the button
    QSizePolicy buttonSizePolicy = button->sizePolicy();

    // Set the horizontal size policy to Fixed and vertical size policy to Minimum
    buttonSizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    buttonSizePolicy.setVerticalPolicy(QSizePolicy::Minimum);

    // Apply the updated size policy to the button
    button->setSizePolicy(buttonSizePolicy);
}
