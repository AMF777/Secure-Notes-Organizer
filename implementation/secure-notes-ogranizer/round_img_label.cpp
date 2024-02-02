#include "round_img_label.h"
#include <QPainter>
#include <QPainterPath>

round_img_label::round_img_label(QWidget *parent)
    : clickable_label(parent){
    // setScaledContents(true);
    // setPixmap(createRoundedPixmap(originalPixmap));
    const int radius=25;
    setMaximumSize(50, 50);
    setMinimumSize(50, 50);
    QPixmap target = QPixmap(size());
    target.fill(Qt::transparent);

    QPixmap originalPixmap(":/res/img/kitten.jpeg");
    QPixmap scaledPixmap = originalPixmap.scaled(50, 50, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPainter painter(&target);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    int borderWidth = 1;
    int outerRectX = borderWidth / 2;
    int outerRectY = borderWidth / 2;
    int outerRectWidth = width() - borderWidth;
    int outerRectHeight = height() - borderWidth;

    painter.setPen(QPen(Qt::white, borderWidth));
    painter.drawRoundedRect(outerRectX, outerRectY, outerRectWidth, outerRectHeight, radius, radius);

    QPainterPath path;
    path.addRoundedRect(outerRectX, outerRectY, outerRectWidth, outerRectHeight, radius, radius);

    painter.setClipPath(path);
    painter.drawPixmap(outerRectX, outerRectY, scaledPixmap);
    setPixmap(target);
}

round_img_label::round_img_label(int sideLen, int borderWidth, const QString imgPath, QWidget *parent)
    : clickable_label(parent)
{
    this->sideLen=sideLen;
    this->borderWidth=borderWidth;
    const int radius=sideLen / 2;
    setMaximumSize(sideLen, sideLen);
    setMinimumSize(sideLen, sideLen);
    QPixmap target = QPixmap(size());
    target.fill(Qt::transparent);

    QPixmap originalPixmap(imgPath);
    QPixmap scaledPixmap = originalPixmap.scaled(sideLen, sideLen, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPainter painter(&target);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    int outerRectX = borderWidth / 2;
    int outerRectY = borderWidth / 2;
    int outerRectWidth = width() - borderWidth;
    int outerRectHeight = height() - borderWidth;

    painter.setPen(QPen(Qt::white, borderWidth));
    painter.drawRoundedRect(outerRectX, outerRectY, outerRectWidth, outerRectHeight, radius, radius);

    QPainterPath path;
    path.addRoundedRect(outerRectX, outerRectY, outerRectWidth, outerRectHeight, radius, radius);

    painter.setClipPath(path);
    painter.drawPixmap(outerRectX, outerRectY, scaledPixmap);
    setPixmap(target);
}

void round_img_label::replacePicture(const QString imgPath)
{
    const int radius=sideLen / 2;
    setMaximumSize(sideLen, sideLen);
    setMinimumSize(sideLen, sideLen);
    QPixmap target = QPixmap(size());
    target.fill(Qt::transparent);

    QPixmap originalPixmap(imgPath);
    QPixmap scaledPixmap = originalPixmap.scaled(sideLen, sideLen, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPainter painter(&target);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    int outerRectX = borderWidth / 2;
    int outerRectY = borderWidth / 2;
    int outerRectWidth = width() - borderWidth;
    int outerRectHeight = height() - borderWidth;

    painter.setPen(QPen(Qt::white, borderWidth));
    painter.drawRoundedRect(outerRectX, outerRectY, outerRectWidth, outerRectHeight, radius, radius);

    QPainterPath path;
    path.addRoundedRect(outerRectX, outerRectY, outerRectWidth, outerRectHeight, radius, radius);

    painter.setClipPath(path);
    painter.drawPixmap(outerRectX, outerRectY, scaledPixmap);
    setPixmap(target);
}
// void round_img_label::paintEvent(QPaintEvent *event) {
//     Q_UNUSED(event);

//     QPixmap originalPixmap(":/res/img/avatar.png");

//     // Resize the original pixmap to the desired size
//     QPixmap scaledPixmap = originalPixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

//     // Create a brush with the scaled pixmap
//     QBrush brush(scaledPixmap);

//     // Set up the painter
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);

//     // Draw the rounded rectangle with the scaled pixmap
//     painter.setBrush(brush);
//     painter.drawRoundedRect(0, 0, width(), height(), 30, 30);

//     // Call the base class implementation to handle the rest
//     QLabel::paintEvent(event);
// }

// QPixmap round_img_label::createRoundedPixmap(const QPixmap &originalPixmap)
// {
//     QBitmap mask(originalPixmap.size());
//     mask.fill(Qt::color0);

//     QPainter painter(&mask);
//     painter.setRenderHint(QPainter::Antialiasing, true);
//     painter.setBrush(Qt::color1);
//     painter.drawRoundedRect(mask.rect(), 50, 50);
//     painter.end();

//     QPixmap roundedPixmap = originalPixmap;
//     roundedPixmap.setMask(mask);

//     return roundedPixmap;
// }
