#ifndef TAGS_HLAYOUT_H
#define TAGS_HLAYOUT_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QVector>
#include "qtextedit.h"
#include "tag_widget.h"
#include "back-end/clientcontroller.h"

using namespace GlobalClient;

class TagsLayout : public QHBoxLayout {
    Q_OBJECT

public:
    explicit TagsLayout(QWidget* parent = nullptr);
    explicit TagsLayout(Note* note, QWidget* parent = nullptr);
    ~TagsLayout();
    void createTag(const QString &text, bool loadedFromDatabase, int id, bool insideView = false);
    void loadTags();
    QVector<TagWidget*> tags;

private slots:
    void removeTag(TagWidget* tag);

private:
    bool tagExists(const QString& tagText) const;
    int tagId;

    Note* note;
};

#endif // TAGS_HLAYOUT_H
