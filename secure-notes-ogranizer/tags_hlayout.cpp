#include "tags_hlayout.h"
#include <QDebug>
#include <QTextEdit>
#include <QKeyEvent>

using namespace GlobalClient;

int TagsLayout::nextTagId = 0;

TagsLayout::TagsLayout(Note* note, QWidget* parent) : QHBoxLayout(parent) {
    this->note = note;

    // Initialize the tags vector to an empty QVector
    tags = QVector<TagWidget*>();
}

TagsLayout::~TagsLayout() {
}

void TagsLayout::createTag(const QString &text, bool loadedFromDatabase, int id) {
    // Call the function to create a tag with the entered text
    if(tagExists(text))
        return;

    Tag tag;

    if(!loadedFromDatabase){
        std::string response = "";


        tag.setnoteId(note->getnoteId());
        tag.settagName(text.toStdString());

        if(id == -1)
            tag.settagId(++nextTagId);

        User* user = new  User();
        user->setuserId(note->getuserId());
        if(client.ClientAddTag(&tag, user, &response))
            qDebug() << response;

        delete user;
    }

    // Create a new Tag widget with the provided text and set TagsLayout as its parent
    TagWidget* newTag = new TagWidget(text, this);

    if(!loadedFromDatabase)
        newTag->setTagId(tag.gettagId());
    else
        newTag->setTagId(id);

    // Connect the tag's remove signal to the TagsLayout removeTag slot
    connect(newTag, &TagWidget::tagRemoved, this, &TagsLayout::removeTag);

    // Add the new tag to the Tags Vector
    tags.push_back(newTag);

    // Add the new tag at the end of the layout
    addWidget(newTag);
}

void TagsLayout::removeTag(TagWidget* tag) {
    std::string response = "";

    QString string = tag->getText();
    Tag tempTag(string.toStdString(), note->getnoteId());
    tempTag.settagId(tag->getTagId());
    User* user = new  User();
    user->setuserId(note->getuserId());
    if(client.ClientDeleteTag(&tempTag, user, &response))
        qDebug() << response;

    // Remove tag from the layout and vector

    // Retrieve the button and tagText widgets associated with the tag
    QWidget* button = takeAt(indexOf(tag) - 2)->widget();
    QWidget* tagText = takeAt(indexOf(tag) - 1)->widget();

    // Schedule the deletion of the button and tagText widgets
    button->deleteLater();
    tagText->deleteLater();

    // Explicitly delete the button and tagText objects
    delete button;
    delete tagText;

    // Remove the tag from the vector

    // Find the tag in the vector and move it to the end
    auto it = std::remove(tags.begin(), tags.end(), tag);

    // Erase the elements that were moved to the end
    tags.erase(it, tags.end());
}

bool TagsLayout::tagExists(const QString& tagText) const {
    // Iterate through all widgets in the layout
    for (int i = 0; i < tags.size(); ++i)
        // If it is a QTextEdit, compare its text with the provided tagText
        if (tags[i]->getText() == tagText)
            // Tag with the specified text already exists
            return true;

    // Tag with the specified text does not exist
    return false;
}

void TagsLayout::loadTags()
{
    qDebug() << note->getnoteId();
    qDebug() << note->getuserId();

    std::string response = "";
    std::vector<Tag> TagsList;

    if(client.ClientListNoteTags(note, &response, TagsList))
        qDebug() << response;

    for(auto& tag:TagsList)
        createTag(QString::fromStdString(tag.gettagName()), true, tag.gettagId());
}




