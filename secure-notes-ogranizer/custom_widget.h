#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include  <vector>

#include "component.h"
#include "back-end/Note.h"
#include "back-end/NoteComponent.h"
#include "back-end/User.h"
#include "back-end/clientcontroller.h"
#include <string>

using namespace GlobalClient;

class CustomWidget : public QWidget {
    Q_OBJECT
public:
    CustomWidget(QWidget *parent = nullptr);
    CustomWidget(Note *note, std::vector<NoteComponent> noteComponents, QWidget *parent = nullptr);
    CustomWidget(Note *note, User *user, QWidget *parent = nullptr);
    CustomWidget(std::vector<NoteComponent> noteComponents, User *user, QWidget *parent = nullptr);
    Note* saveNote(std::string title);


    User *user;
    Note *note;
    std::vector<NoteComponent> noteComponents;
private slots:
    TextEditComponent* createComponent(int index);
    void deleteComponent(int index);
    void createComponentWithText(int index, const QString &text);
    void deleteComponentAppendText(int index, const QString &text);
    void focusAdjacentComponent(int currentIndex, bool forward);
    void initComponentWithLine(int index, NoteComponent &component);

private:
    QVector<TextEditComponent*> componentVector;
    QVBoxLayout *verticalLayoutTextEdits;

    QVBoxLayout *createMainLayout();
    void initializeWidget();
};

#endif // CUSTOMWIDGET_H
