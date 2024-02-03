#ifndef TAG_H
#define TAG_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class Tag : public QWidget {
    Q_OBJECT

public:
    explicit Tag(const QString& text, QHBoxLayout* layout, QWidget* parent = nullptr);

    void setText(const QString& text);
    QString getText() const;

signals:
    void tagRemoved(Tag* tag);

private slots:
    void onRemoveButtonClicked();

private:
    QLabel* labelText;
    QPushButton* removeButton;
};

#endif // TAG_H
