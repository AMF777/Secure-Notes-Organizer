#include "dropdown_label.h"
#include <QMouseEvent>

// Constructor for DropdownLabel with icon and size parameters
DropdownLabel::DropdownLabel(const QPixmap& icon, const QSize& size, QWidget *parent) : QLabel(parent)
{
    // Set context menu policy to custom for handling right-click events
    setContextMenuPolicy(Qt::CustomContextMenu);

    // Initialize the context menu
    contextMenu = new QMenu(this);

    // Set the icon, size, and connect context menu signal to slot
    this->icon = icon;
    this->setPixmap(icon);
    this->setFixedSize(size);

    // Connect right-click signal to showContextMenu slot
    connect(this, &DropdownLabel::customContextMenuRequested, this, &DropdownLabel::showContextMenu);
}

// Function to add an action to the context menu
void DropdownLabel::addActionToMenu(const QString& actionName)
{
    // Create a new action and add it to the context menu
    QAction* newAction = contextMenu->addAction(actionName);

    // Connect the action's triggered signal to a lambda emitting the optionSelected signal
    // with its action name as a parameter
    connect(newAction, &QAction::triggered, this, [this, actionName]() {
        emit optionSelected(actionName);
    });
}

// Slot to show the context menu at the current position
void DropdownLabel::showContextMenu()
{
    contextMenu->exec(mapToGlobal(QPoint(0, height())));
}

// Override mousePressEvent to emit a customContextMenuRequested signal on left-click
void DropdownLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit customContextMenuRequested(QPoint(0, height()));

    QLabel::mousePressEvent(event);
}
