#include "tag_widget.h"
#include <QDebug>

TagWidget::TagWidget(const QString& text, QHBoxLayout* layout, QWidget* parent) : QWidget(parent) {
    // Create label for displaying tag text
    labelText = new QLabel(text, this);
    labelText->setAlignment(Qt::AlignCenter);
    labelText->setProperty("class", "tagLabel");

    // Create remove button for removing the tag
    removeButton = new QPushButton(this);
    removeButton->setFixedSize(20, 20);
    removeButton->setProperty("class", "tagButtons");

    // Set the icon for the remove button from a resource file
    QIcon icon(":/res/img/cancel.png");
    removeButton->setIcon(icon);

    // Set maximum width for the widget based on the tag text length
    setMaximumWidth(70 + text.length() * 6);  // Adjust the multiplier as needed

    // Set up connections to handle remove button click event
    connect(removeButton, &QPushButton::clicked, this, &TagWidget::onRemoveButtonClicked);

    // Add label and remove button to the provided layout
    layout->addWidget(labelText);
    layout->addWidget(removeButton);
}

void TagWidget::setText(const QString& text) {
    // Set the text of the label to the provided text
    labelText->setText(text);
}

QString TagWidget::getText() const {
    // Retrieve the current text of the label
    return labelText->text();
}

void TagWidget::onRemoveButtonClicked() {
    // Emit the tagRemoved signal, indicating that the remove button was clicked for this tag
    emit tagRemoved(this);
}
