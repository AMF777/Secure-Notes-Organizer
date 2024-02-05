#ifndef NOTE_EDITOR_H
#define NOTE_EDITOR_H

#include "button_icon_vlayout.h"
#include "custom_widget.h"
#include "qboxlayout.h"
#include "tags_hlayout.h"
#include "back-end/Note.h"
#include "back-end/NoteComponent.h"

#include <QWidget>
#include <vector>

class NoteEditor : public QVBoxLayout
{
public:
    NoteEditor(QWidget *mainWindowRef, QWidget *parent = nullptr);
    NoteEditor(QWidget *mainWindowRef, QStringList& lines, QString title, QWidget *parent = nullptr);
    NoteEditor(QWidget *mainWindowRef, Note *note, std::vector<NoteComponent> noteComponents, QWidget *parent = nullptr);
private:
    Note* note;
    QWidget *mainWindowRef;
    QLabel *timeAgoLabel;
    button_icon_vlayout *saveNoteButton;
    button_icon_vlayout *shareButton;

    TagsLayout *tagsLayout;
    CustomWidget *noteComponentsLayout;

    QString title;

    QHBoxLayout* createTimeAndButtonsLayout();
    QHBoxLayout* createTitleNoteLayout();
};

#endif // NOTE_EDITOR_H
