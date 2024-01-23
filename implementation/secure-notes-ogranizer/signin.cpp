#include "constants.h"

#include "signin.h"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>

const QString signin::SIGNIN_TITLE = "Sign in";
const int signin::SIGNIN_WIDTH = 520;
const int signin::SIGNIN_HEIGHT = 620;
const int signin::SIEMENS_LOGO_WIDTH = 180;
const int signin::SIEMENS_LOGO_HEIGHT = 55;

signin::signin(QWidget *parent)
    : QWidget{parent}
{
    // use resize function instead to have a dynamic window/widget
    // cannot apply width or height through qss styles
    setWindowTitle(SIGNIN_TITLE);
    setFixedSize(SIGNIN_WIDTH, SIGNIN_HEIGHT);
    setProperty("class", "white-background");

    QLabel *imageLabel = new QLabel(this);

    // now use res to load any file including images
    // this is how to upload image in qt
    QPixmap image(":/res/img/siemens-logo.png");
    // specify aspect ratio?
    imageLabel->setPixmap(image.scaled(SIEMENS_LOGO_WIDTH, SIEMENS_LOGO_HEIGHT, Qt::KeepAspectRatio) );

    // Set the label alignment to center
    imageLabel->setAlignment(Qt::AlignCenter);

    // Set the QLabel alignment within the parent widget
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    layout->setAlignment(Qt::AlignCenter);

    // QLabel* label=new QLabel(this);
    // label->setText("this is first label ever");
    // label->move(50,50);

    // QLabel *label1 = new QLabel(this);
    // label1->setText("This is the first label ever");
    // label1->move(50, 50);

    // QLabel *label2 = new QLabel(this);
    // label2->setText("Blue Background Label");
    // label2->move(255, 50);

    // how to style using css:
    // first define all css classes you would link in styles.qss
    // this is how to assign a css class to qt component
    // label2->setProperty("class", "blue-label");
    // you can assign mul classes as follows
    // label2->setProperty("class", "blue-label big-font");
}

void signin::buttonClicked()
{
    QMessageBox::information(this,"message","hello world");
}
// this gives a hint and might not give widget desired width and height
QSize signin::sizeHint() const
{
    return QSize(SIGNIN_WIDTH,SIGNIN_HEIGHT);
}
