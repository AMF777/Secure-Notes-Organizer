#ifndef NOTE_EDITOR_H
#define NOTE_EDITOR_H

#include "button_icon_vlayout.h"
#include "custom_widget.h"
#include "qboxlayout.h"
#include "tags_hlayout.h"
#include "back-end/Note.h"
#include "back-end/NoteComponent.h"
#include "back-end/User.h"
#include "show_notes_vlayout.h"

#include <QWidget>
#include <vector>
#include <QTextEdit>

class NoteEditor : public QVBoxLayout
{
public:
    NoteEditor(QWidget *mainWindowRef, QWidget *parent = nullptr);
    NoteEditor(QWidget *mainWindowRef, Note *note, std::vector<NoteComponent> noteComponents, QWidget *parent = nullptr);
    NoteEditor(QWidget *mainWindowRef, Note *note, User *user, QWidget *parent = nullptr);
    NoteEditor(QWidget *mainWindowRef, std::vector<NoteComponent> noteComponents, QString title, User *user, QWidget *parent = nullptr);

    TagsLayout *tagsLayout;

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Note* note;
    User* user;
    QTextEdit *titleNote;
    QWidget *mainWindowRef;
    QLabel *timeAgoLabel;
    QTextEdit *textInput;
    button_icon_vlayout *saveNoteButton;
    button_icon_vlayout *deleteNoteButton;
    button_icon_vlayout *shareButton;
    button_icon_vlayout *addButton;

    CustomWidget *noteComponentsLayout;

    QString title;
    void initialize(QWidget *mainWindowRef, Note *note, CustomWidget *customWidget) ;
    QHBoxLayout* createTimeAndButtonsLayout();
    QHBoxLayout* createTitleNoteLayout();
    QHBoxLayout * createTagLayout();

    void createTagFromInput();

    QLabel *savedMessageLabel;
    QTimer *savedMessageTimer;
    QDialog *savedMessageDialog;
    void hideSavedMessage();
};

#endif // NOTE_EDITOR_H
