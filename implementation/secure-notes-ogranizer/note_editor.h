#ifndef NOTE_EDITOR_H
#define NOTE_EDITOR_H

#include "button_icon_vlayout.h"
#include "custom_widget.h"
#include "qboxlayout.h"
#include "tags_hlayout.h"
#include <QWidget>

class NoteEditor : public QVBoxLayout
{
public:
    NoteEditor();

private:
    QLabel *timeAgoLabel;
    button_icon_vlayout *saveNoteButton;
    button_icon_vlayout *shareButton;

    TagsLayout *tagsLayout;
    CustomWidget *noteComponentsLayout;

    QHBoxLayout* createTimeAndButtonsLayout();
    QHBoxLayout* createTitleNoteLayout();
};

#endif // NOTE_EDITOR_H
