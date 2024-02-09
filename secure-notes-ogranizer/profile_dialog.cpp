#include "profile_dialog.h"
#include "constants.h"
#include "button_icon_vlayout.h"
#include "round_img_label.h"

#include <QGraphicsBlurEffect>
#include <QFileDialog>

const QString LABEL_STYLE = "user-label";
const QString INPUT_STYLE = "user-input";

profile_dialog::profile_dialog(User *user, QWidget *parent)
    : QDialog{parent}
{
    this->user = user;

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setProperty("class","white-background round-corners profile-dialog-border");
    setModal(true);

    mainLayout = new QVBoxLayout(this);

    // label = new round_img_label(this);
    avatarLabel = new round_img_label(50, 2,":/res/img/kitten.jpeg",this);
    connect(avatarLabel, &clickable_label::clicked, this, [this]() {
        avatarClicked();
    });
    // uploadButton = new button_icon_vlayout(
    //     ":/res/img/camera.png", "sidebar-button camera-corners", QSize(15,15),
    //     Qt::AlignLeft, [this](){}
    // );

    // uploadButton->setAlignment(Qt::AlignCenter);

    notesCountLayout = new QVBoxLayout();
    notes = new QLabel("Notes");
    notes->setProperty("class","avatar-widget-label" );
    notesCount = new QLabel("999");
    notesCount->setProperty("class","avatar-widget-label" );
    notesCountLayout->addWidget(notes );
    notesCountLayout->addWidget(notesCount, 0, Qt::AlignCenter);
    notesCountLayout->setAlignment(Qt::AlignCenter);

    sharesCountLayout = new QVBoxLayout();
    shares = new QLabel("Shares");
    shares->setProperty("class","avatar-widget-label" );
    sharesCount = new QLabel("999");
    sharesCount->setProperty("class","avatar-widget-label" );
    sharesCountLayout->addWidget(shares);
    sharesCountLayout->addWidget(sharesCount, 0, Qt::AlignCenter);
    sharesCountLayout->setAlignment(Qt::AlignCenter);

    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::VLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("color: #CDCDCD;");

    notesSharesLayout = new QHBoxLayout();
    notesSharesLayout->addLayout(notesCountLayout);
    notesSharesLayout->addWidget(separator);
    notesSharesLayout->addLayout(sharesCountLayout);
    notesSharesLayout->setAlignment(Qt::AlignCenter);

    avatarLayout = new QVBoxLayout();
    avatarLayout->addWidget(avatarLabel,0,Qt::AlignCenter);
    // avatarLayout->addLayout(uploadButton);
    avatarLayout->addLayout(notesSharesLayout);

    // put into a widget so we can style corners
    QWidget *w= new QWidget();
    w->setProperty("class","avatar-widget");
    QHBoxLayout *avatarWidgetLayout= new QHBoxLayout();
    w->setLayout(avatarLayout);
    avatarWidgetLayout->addWidget(w);

    // mainLayout->addLayout(avatarLayout);
    mainLayout->addLayout(avatarWidgetLayout);
    usernameLayout = new label_input_vlayout(
        "Username:",
        LABEL_STYLE,
        PROFILE_INPUT_WIDTH,
        INPUT_STYLE,
        QLineEdit::Normal
        );
    usernameLayout->input->setText(QString::fromStdString(user->getuserName()));

    emailLayout = new label_input_vlayout(
        "Email Address:",
        LABEL_STYLE,
        PROFILE_INPUT_WIDTH,
        INPUT_STYLE
        );
    emailLayout->input->setText(QString::fromStdString(user->getemail()));
    emailLayout->input->setEnabled(false);

    passwordLayout = new label_input_vlayout(
        "Password:",
        LABEL_STYLE,
        PROFILE_INPUT_WIDTH,
        INPUT_STYLE,
        QLineEdit::Password
        );

    confirmPasswordLayout = new label_input_vlayout(
        "Confirm Password:",
        LABEL_STYLE,
        PROFILE_INPUT_WIDTH,
        INPUT_STYLE,
        QLineEdit::Password
        );
    const int n = 4;
    label_input_vlayout* inputRefs[n]={usernameLayout, emailLayout, passwordLayout, confirmPasswordLayout};
    for (int i=0;i<n;i++){
        // inputRefs[i]->setAlignment(Qt::AlignCenter);
        mainLayout->addLayout(inputRefs[i] );
    }

    saveButton = new QPushButton("Save");
    saveButton->setProperty("class","save-filepath-button");
    saveButton->setCursor(Qt::PointingHandCursor);
    connect(saveButton, &QPushButton::clicked, this, &profile_dialog::saveButtonClicked);

    cancelButton = new QPushButton("Cancel");
    cancelButton->setProperty("class","cancel-filepath-button white-background");
    cancelButton->setCursor(Qt::PointingHandCursor);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->setAlignment(Qt::AlignRight);

    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(Qt::AlignCenter);
}


void profile_dialog::showEvent(QShowEvent *event){
    // Calculate the desired width and height based on the parent widget's size
    auto parent=parentWidget()->parentWidget();
    if (parent ) {
        QSize parentSize = parent->size();
        int dialogWidth = width()+100;
        int dialogHeight = height()+50;
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

void profile_dialog::hideEvent(QHideEvent *event)
{
    qDebug()<<"hide event";
    auto parent=parentWidget()->parentWidget();
    if(parent ){
        parent->setGraphicsEffect(nullptr);
    }
    // Call the base class implementation of hideEvent
    QDialog::hideEvent(event);
}

void profile_dialog::avatarClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Choose a Photo"),
        QDir::homePath(),
        tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)")
        );

    if (!fileName.isEmpty()) {
        // You can handle the selected photo file here
        // For example, display the image in a QLabel or perform other operations.
        qDebug() << "Selected Photo: " << fileName;
        avatarLabel->replacePicture(fileName);
    }
    // qDebug()<<"avatar click";
}

void profile_dialog::saveButtonClicked()
{
    qDebug() << "saved";;
}
