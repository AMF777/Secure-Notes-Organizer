#ifndef TAG_WIDGET_H
#define TAG_WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class TagWidget : public QWidget {
    Q_OBJECT

public:
    explicit TagWidget(const QString& text, QHBoxLayout* layout, QWidget* parent = nullptr);

    void setText(QString& text);
    QString getText();

signals:
    void tagRemoved(TagWidget* tag);

private slots:
    void onRemoveButtonClicked();

private:
    QLabel* labelText;
    QPushButton* removeButton;
};

#endif // TAG_WIDGET_H
