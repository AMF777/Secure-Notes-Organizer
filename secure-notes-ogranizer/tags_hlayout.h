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
    explicit TagsLayout(Note* note, QWidget* parent = nullptr);
    ~TagsLayout();
    void createTag(const QString &text, bool loadedFromDatabase, int id);
    void loadTags();

private slots:
    void removeTag(TagWidget* tag);

private:
    QVector<TagWidget*> tags;
    bool tagExists(const QString& tagText) const;
    int tagId;

    static int nextTagId;

    Note* note;
};

#endif // TAGS_HLAYOUT_H
