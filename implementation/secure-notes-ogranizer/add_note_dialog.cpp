#include "add_note_dialog.h"
#include "constants.h"

#include <QGraphicsBlurEffect>
#include <QFileDialog>

add_note_dialog::add_note_dialog(QWidget *parent)
    : QDialog{parent}
{


    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setProperty("class","white-background round-corners profile-dialog-border");
    setModal(true);
    // parentWidget()->setGraphicsEffect(blurEffect);
    // Create overlay widget
    // overlayWidget = new QWidget(this);
    // overlayWidget->setStyleSheet("background-color: rgba(0, 0, 0, 50%);");
    // overlayWidget->setVisible(false);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setProperty("class","white-background");
    filePathLayout = new label_input_vlayout(
        "File Path:",
        "user-label",
        FILEPATH_INPUT_WIDTH,
        "user-input",
        QLineEdit::Normal
    );
    QAction *openFileAction = filePathLayout->input->addAction(QIcon(":/res/img/file.png"), QLineEdit::TrailingPosition);
    connect(openFileAction, &QAction::triggered, this, &add_note_dialog::openFileDialog);

    saveButton = new QPushButton("Save");
    saveButton->setProperty("class","save-filepath-button");
    saveButton->setCursor(Qt::PointingHandCursor);
    connect(saveButton, &QPushButton::clicked, this, &QDialog::reject);

    cancelButton = new QPushButton("Cancel");
    cancelButton->setProperty("class","cancel-filepath-button white-background");
    cancelButton->setCursor(Qt::PointingHandCursor);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->setAlignment(Qt::AlignRight);

    mainLayout->addLayout(filePathLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(Qt::AlignCenter);

}

void add_note_dialog::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open Text File"),
        QDir::homePath(),
        tr("Text Files (*.txt);;All Files (*)")
        );
    if (!filePath.isEmpty()) {
        // Process the selected file path, e.g., update UI with the file path
        filePathLayout->input->setText(filePath);
    }
}
void add_note_dialog::showEvent(QShowEvent *event){
    // Calculate the desired width and height based on the parent widget's size
    auto parent=parentWidget()->parentWidget();
    if (parent ) {
        QSize parentSize = parent->size();
        int dialogWidth = parentSize.width() * 0.8;
        int dialogHeight = parentSize.height() * 0.7;
        setFixedSize(dialogWidth, dialogHeight);

        int x = parent->geometry().x() + (parentSize.width() - dialogWidth) / 2;
        int y = parent->geometry().y() + (parentSize.height() - dialogHeight) / 2;

        QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect();
        blurEffect->setBlurRadius(10); // Adjust the blur radius as needed
        parent->setGraphicsEffect(blurEffect);
        // Move the dialog to the center position
        move(x, y);
    }

    // Call the base class implementation of showEvent
    QDialog::showEvent(event);
}

void add_note_dialog::hideEvent(QHideEvent *event)
{
    qDebug()<<"hide event";
    auto parent=parentWidget()->parentWidget();
    if(parent ){
        parent->setGraphicsEffect(nullptr);
    }
    // Call the base class implementation of hideEvent
    QDialog::hideEvent(event);
}
