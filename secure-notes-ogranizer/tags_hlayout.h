#ifndef TAGS_HLAYOUT_H
#define TAGS_HLAYOUT_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QVector>
#include "qtextedit.h"
#include "tag_widget.h"
#include "back-end/clientcontroller.h"


class TagsLayout : public QHBoxLayout {
    Q_OBJECT

public:
    explicit TagsLayout(Note* note, QWidget* parent = nullptr);
    ~TagsLayout();

private slots:
    void addButtonPressed();
    void removeTag(TagWidget* tag);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QPushButton* addButton;
    QVector<TagWidget*> tags;
    QTextEdit* textInput;
    bool tagExists(const QString& tagText) const;
    void createTag(const QString& text);

    Note* note;
};

#endif // TAGS_HLAYOUT_H
