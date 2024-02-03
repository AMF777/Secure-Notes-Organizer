#ifndef TAGS_HLAYOUT_H
#define TAGS_HLAYOUT_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QVector>
#include "qtextedit.h"
#include "tag.h"

class TagsLayout : public QHBoxLayout {
    Q_OBJECT

public:
    explicit TagsLayout(QWidget* parent = nullptr);
    ~TagsLayout();

private slots:
    void addButtonPressed();
    void removeTag(Tag* tag);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QPushButton* addButton;
    QVector<Tag*> tags;
    QTextEdit* textInput;
    bool tagExists(const QString& tagText) const;

    void createTag(const QString& text);

};

#endif // TAGS_HLAYOUT_H
