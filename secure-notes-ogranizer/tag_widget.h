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

    int getTagId() const;
    void setTagId(int newTagId);
    QLabel* labelText;
signals:
    void tagRemoved(TagWidget* tag);
    void tagClicked(QString tagName);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onRemoveButtonClicked();

private:
    QPushButton* removeButton;
    int tagId;
};

#endif // TAG_WIDGET_H
