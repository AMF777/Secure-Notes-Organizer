// DropdownLabel.h
#ifndef DROPDOWN_LABEL_H
#define DROPDOWN_LABEL_H

#include <QLabel>
#include <QMenu>

// DropdownLabel class, derived from QLabel
class DropdownLabel : public QLabel
{
    Q_OBJECT

public:
    // Constructor with icon and size parameters
    DropdownLabel(const QPixmap& icon, const QSize& size, QWidget *parent);

    // Function to add an action to the context menu
    void addActionToMenu(const QString& actionName);

signals:
    // Signal emitted when an option is selected from the context menu
    void optionSelected(QString selectedOption);

protected:
    // Override mousePressEvent to handle left-click events
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    // Slot to show the context menu
    void showContextMenu();

private:
    // Context menu for the label
    QMenu *contextMenu;

    // Icon for the label
    QPixmap icon;
};

#endif // DROPDOWN_LABEL_H
