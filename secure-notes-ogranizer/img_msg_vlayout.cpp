#include "img_msg_vlayout.h"


img_msg_vlayout::img_msg_vlayout(const QString url, int imgWidth, int imgHeight, const QString imgClass,
                                 const QString labelText, const QString labelClass, Qt::Alignment alignment)
    : QVBoxLayout(nullptr)
{
    imgLabel=new QLabel();
    QPixmap img(url);
    imgLabel->setPixmap(img.scaled(imgWidth, imgHeight, Qt::KeepAspectRatio) );
    imgLabel->setProperty("class", imgClass);

    msgLabel=new QLabel(labelText);
    msgLabel->setProperty("class", labelClass);

    addWidget(imgLabel,0,alignment);
    addWidget(msgLabel,0,alignment);
}
