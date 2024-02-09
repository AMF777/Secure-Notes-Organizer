// custom_widget.cpp
#include "custom_widget.h"
#include "component.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QTimer>

#include "back-end/clientcontroller.h"
#include "main_window.h"
#include "qdialog.h"


CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
    this->note=nullptr;
    initializeWidget();
    createComponent(0);
}

CustomWidget::CustomWidget(Note *note, std::vector<NoteComponent> noteComponents, QWidget *parent) : QWidget(parent)
{
    this->note=note;
    this->noteComponents=noteComponents;
    initializeWidget();
    int cid=-1;
    for (auto& component:noteComponents){
        initComponentWithLine(cid, component);
        cid++;
    }
    //  INCASE WHERE THERE IS NOCMPOONENTS ,  ADD AN EMPTY COMPONENT
    if(cid == -1)
        createComponent(0);

}

CustomWidget::CustomWidget(Note *note, User *user, QWidget *parent)
{
    this->note=note;
    this->user=user;
    initializeWidget();

    std::vector<NoteComponent> noteComponents;
    std::string response = "";
    bool flag = client.ClientListComponents(note, &response, noteComponents);
    if(!flag){
        qDebug()<<response;
    }
    int cid=-1;
    for (auto& component:noteComponents){
        initComponentWithLine(cid, component);
        cid++;
    }
    //  INCASE WHERE THERE IS NOCMPOONENTS ,  ADD AN EMPTY COMPONENT
    if(cid == -1)
        createComponent(0);
}

CustomWidget::CustomWidget(std::vector<NoteComponent> noteComponents, User *user, QWidget *parent) : QWidget{parent}
{
    this->note=nullptr;
    this->user=user;
    initializeWidget();

    int cid=-1;
    for (auto& component:noteComponents){
        initComponentWithLine(cid, component);
        cid++;
    }
    //  INCASE WHERE THERE IS NOCMPOONENTS ,  ADD AN EMPTY COMPONENT
    if(cid == -1)
        createComponent(0);
}

void CustomWidget::initializeWidget(){

    setProperty("class","main-windown-bg");
    setContentsMargins(0, 0, 0, 0);
    // Create the layout for text edits and initialize the first component
    verticalLayoutTextEdits = new QVBoxLayout();
    verticalLayoutTextEdits->setAlignment(Qt::AlignTop);
    // Wrap the verticalLayoutTextEdits in a QScrollArea
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(new QWidget()); // Set an empty widget as the scroll area's widget
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);  // Set the vertical scroll bar policy
    scrollArea->widget()->setProperty("class","main-window-bg");
    scrollArea->widget()->setLayout(verticalLayoutTextEdits);

    // Create the main layout that includes all the sub-layouts
    QVBoxLayout *mainLayout = createMainLayout();
    mainLayout->addWidget(scrollArea);

    // Set the overall layout for the CustomWidget
    setLayout(mainLayout);
}

Note* CustomWidget::saveNote(std::string title)
{
    // user must be set to init note
    bool flag;
    if(!user) return nullptr;
    std::string response = "";
    if(!note){
        note = new Note(user->getuserId(), title);
        // create note in db if it doesnt exist
        GlobalClient::client.ClientCreateNote(note,&response);
    }
    else{
        note->settitle(title);
        flag=GlobalClient::client.ClientUpdateNoteTitle(note,&response);
        qDebug()<<response;
    }
    // save componentss to db
    // get components of current note

    std::vector<NoteComponent> noteComponents;
    flag = client.ClientListComponents(note, &response, noteComponents);
    if(!flag){
        // qDebug()<<response;
        return nullptr;
    }
    // delete alll the components firrst
    for(auto& cmp:noteComponents){
        client.ClientDeleteComponent(&cmp,user,&response);
        // qDebug()<<response;
    }
    // clear all components
    noteComponents.clear();
    // add (create) new components
    for(TextEditComponent* cmp:this->componentVector){
        NoteComponent dbCmp=TextEditComponent::toNoteComponent(note,*cmp);
        dbCmp.setcomponentContent(cmp->text->encodeCaesarCipher());
        // qDebug()<<dbCmp.getcomponentContent();
            client.ClientCreateComponent(&dbCmp,user,&response);
        // qDebug()<<response;
    }
    return this->note;

}

QVBoxLayout* CustomWidget::createMainLayout()
{
    // Create a vertical layout for the main layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add the sub-layouts for time and buttons, title note, and text edits
    layout->addLayout(verticalLayoutTextEdits);

    return layout;
}

TextEditComponent* CustomWidget::createComponent(int index)
{
    // Create a new TextEditComponent
    TextEditComponent *newComponent = new TextEditComponent(index, this);

    // Connect signals for creating a new component and backspacing when empty
    connect(newComponent, &TextEditComponent::createNewComponent, this, &CustomWidget::createComponent);
    connect(newComponent, &TextEditComponent::backspaceEmpty, this, &CustomWidget::deleteComponent);
    connect(newComponent, &TextEditComponent::backspaceNotEmpty, this, &CustomWidget::deleteComponentAppendText);
    connect(newComponent, &TextEditComponent::middleEnterKeyPressed, this, &CustomWidget::createComponentWithText);
    connect(newComponent, &TextEditComponent::tabKeyPressed, this, &CustomWidget::focusAdjacentComponent);

    // Special Case For index 0: Insert the new component at the beginning
    if (componentVector.isEmpty()) {
        componentVector.push_back(newComponent);
        verticalLayoutTextEdits->insertWidget(index, newComponent);
        return newComponent;
    }

    // Use const_iterator to iterate through the vector
    auto it = componentVector.cbegin();
    std::advance(it, index + 1);

    // Add the new component to the vector using const_iterator
    componentVector.insert(it, newComponent);

    // Update indices for components after the inserted one
    for (int i = index + 1; i < componentVector.size(); i++)
        componentVector[i]->index++;

    // Add the new component to the layout
    verticalLayoutTextEdits->insertWidget(index + 1, newComponent);

    // To focus on new component and Move Cursor to first postion
    newComponent->text->focusAndMoveCursor(0);


    return newComponent;
}

void CustomWidget::createComponentWithText(int index, const QString &text)
{
    // Create new component
    createComponent(index);

    // Set the text of the newly created component
    componentVector[index + 1]->text->setText(text);

    // To focus on new component and Move Cursor to last postion
    componentVector[index + 1]->text->focusAndMoveCursor();
}

void CustomWidget::deleteComponentAppendText(int index, const QString &text)
{
    // To focus on previous component and Move Cursor to last postion
    componentVector[index - 1]->text->focusAndMoveCursor();

    // Append Text to the previous component
    componentVector[index - 1]->text->appendText(text);

    // Delete Component With text
    deleteComponent(index);
}

void CustomWidget::deleteComponent(int index)
{
    // Update indices for components after the deleted one
    for (int i = index + 1; i < componentVector.size(); ++i)
        componentVector[i]->index = i - 1;

    // Use const_iterator to iterate through the vector
    auto it = componentVector.cbegin();
    std::advance(it, index);

    // Remove the component from the vector using const_iterator
    componentVector.erase(it);

    // Remove the component from the layout
    QLayoutItem *item = verticalLayoutTextEdits->takeAt(index);
    if (item) {
        // Delete the widget and layout item
        delete item->widget();
        delete item;
    }

    // To focus on previous component and Move Cursor to last postion
    componentVector[index - 1]->text->focusAndMoveCursor();
}

void CustomWidget::focusAdjacentComponent(int currentIndex, bool forward)
{
    // Check if the index is within the valid range
    if (currentIndex >= 0 && currentIndex < componentVector.size()) {
        int nextIndex = forward ? currentIndex + 1 : currentIndex - 1;

        // Check if the next index is within the valid range
        if (nextIndex >= 0 && nextIndex < componentVector.size()) {
            // Change focus to the next component's textEdit
            componentVector[nextIndex]->text->setFocus();
            componentVector[nextIndex]->text->selectAll(); // Optionally select all text
        }
    }
}


void CustomWidget::initComponentWithLine(int index, NoteComponent &component)
{
    TextEditComponent *newComponent = new TextEditComponent();
    std::string line = newComponent->text->decodeCaesarCipher(component.getcomponentContent());
    // Create new component
    newComponent = createComponent(index);

    newComponent->text->setAttributes(
        component.getfontSize(),
        QString::fromStdString(component.getfontColor()),
        QString::fromStdString(component.getbackgroundColor()),
        QString::fromStdString(component.getfontFamily()),
        QString::fromStdString(component.getfontStyle()),
        component.getisBold(),
        component.getisItalic(),
        component.getisUnderlined()
    );


    // Set the text of the newly created component
    componentVector[index+1]->text->setText(QString::fromStdString(line));

    // To focus on new component and Move Cursor to last postion
    componentVector[index+1]->text->focusAndMoveCursor();
}

