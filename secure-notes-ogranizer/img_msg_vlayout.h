#ifndef IMG_MSG_VLAYOUT_H
#define IMG_MSG_VLAYOUT_H

#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>

class img_msg_vlayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit img_msg_vlayout(const QString url, int imgWidth, int imgHeight, const QString imgClass,
                    const QString labelText, const QString labelClass,
                    Qt::Alignment alignment = Qt::Alignment());
    QLabel *msgLabel;
    QLabel *imgLabel;
};

#endif // IMG_MSG_VLAYOUT_H
