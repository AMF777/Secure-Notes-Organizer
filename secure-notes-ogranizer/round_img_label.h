#ifndef ROUND_IMAGE_LABEL_H
#define ROUND_IMAGE_LABEL_H
#include "clickable_label.h"

#include <QLabel>
#include <QPixmap>
#include <QBitmap>
class round_img_label : public clickable_label {
    Q_OBJECT

public:
    round_img_label(QWidget *parent = nullptr);
    round_img_label(int sideLen, int borderWidth, const QString imgPath, QWidget *parent = nullptr);
    void replacePicture(const QString imgPath);
    int sideLen, borderWidth;
protected:
           // void paintEvent(QPaintEvent *event) override;

private:
    // QPixmap createRoundedPixmap(const QPixmap& originalPixmap);

    QPixmap originalPixmap;
};

#endif // ROUND_IMAGE_LABEL_H
