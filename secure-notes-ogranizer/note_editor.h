#ifndef NOTE_EDITOR_H
#define NOTE_EDITOR_H

#include "button_icon_vlayout.h"
#include "custom_widget.h"
#include "qboxlayout.h"
#include "tags_hlayout.h"
#include "back-end/Note.h"
#include "back-end/NoteComponent.h"
#include "back-end/User.h"

#include <QWidget>
#include <vector>

class NoteEditor : public QVBoxLayout
{
public:
    NoteEditor(QWidget *mainWindowRef, QWidget *parent = nullptr);
    NoteEditor(QWidget *mainWindowRef, QStringList& lines, QString title, QWidget *parent = nullptr);
    NoteEditor(QWidget *mainWindowRef, Note *note, std::vector<NoteComponent> noteComponents, QWidget *parent = nullptr);
    NoteEditor(QWidget *mainWindowRef, Note *note, User *user, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Note* note;
    User* user;
    QWidget *mainWindowRef;
    QLabel *timeAgoLabel;
    QTextEdit *textInput;
    button_icon_vlayout *saveNoteButton;
    button_icon_vlayout *shareButton;
    button_icon_vlayout *addButton;

    TagsLayout *tagsLayout;
    CustomWidget *noteComponentsLayout;

    QString title;

    QHBoxLayout* createTimeAndButtonsLayout();
    QHBoxLayout* createTitleNoteLayout();
    QHBoxLayout * createTagLayout();

    void createTagFromInput();
};

#endif // NOTE_EDITOR_H
