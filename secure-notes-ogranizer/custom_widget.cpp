// custom_widget.cpp
#include "custom_widget.h"
#include "component.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
    note=nullptr;
    // Set the outermost widget's margins to zero
    setContentsMargins(0, 0, 0, 0);

    // Create the layout for text edits and initialize the first component
    verticalLayoutTextEdits = new QVBoxLayout();

    // Wrap the verticalLayoutTextEdits in a QScrollArea
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(new QWidget()); // Set an empty widget as the scroll area's widget
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);  // Set the vertical scroll bar policy

    // Set the inner layout for the scroll area's widget
    scrollArea->widget()->setLayout(verticalLayoutTextEdits);

    createComponent(0);

    // Create the main layout that includes all the sub-layouts
    QVBoxLayout *mainLayout = createMainLayout();
    mainLayout->addWidget(scrollArea);

    // Set the overall layout for the CustomWidget
    setLayout(mainLayout);
}

CustomWidget::CustomWidget(QStringList &lines, QWidget *parent)
{
    // Set the outermost widget's margins to zero
    setContentsMargins(0, 0, 0, 0);

    // Create the layout for text edits and initialize the first component
    verticalLayoutTextEdits = new QVBoxLayout();

    // Wrap the verticalLayoutTextEdits in a QScrollArea
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(new QWidget()); // Set an empty widget as the scroll area's widget
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);  // Set the vertical scroll bar policy

    // Set the inner layout for the scroll area's widget
    // qDebug()<<"im inside my custom widget constructor";
    scrollArea->widget()->setLayout(verticalLayoutTextEdits);
    int cid=-1;
    for (auto& line:lines){
        initComponentWithLine(cid,line);
        // qDebug()<<cid;n
        cid++;
    }
    //  INCASE WHERE THERE IS NOCMPOONENTS ,  ADD AN EMPTY COMPONENT
    QString line="";
    initComponentWithLine(cid, line);

    // Create the main layout that includes all the sub-layouts
    QVBoxLayout *mainLayout = createMainLayout();
    mainLayout->addWidget(scrollArea);

    // Set the overall layout for the CustomWidget
    setLayout(mainLayout);
}

CustomWidget::CustomWidget(Note *note, std::vector<NoteComponent> noteComponents, QWidget *parent) : QWidget(parent)
{
    this->note=note;
    this->noteComponents=noteComponents;

    setContentsMargins(0, 0, 0, 0);
    // Create the layout for text edits and initialize the first component
    verticalLayoutTextEdits = new QVBoxLayout();

    // Wrap the verticalLayoutTextEdits in a QScrollArea
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(new QWidget()); // Set an empty widget as the scroll area's widget
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);  // Set the vertical scroll bar policy

    // Set the inner layout for the scroll area's widget
    // qDebug()<<"im inside my custom widget constructor";
    scrollArea->widget()->setLayout(verticalLayoutTextEdits);
    int cid=-1;
    for (auto& compoonent:noteComponents){
        QString line=QString::fromStdString(compoonent.getcomponentContent() );
        initComponentWithLine(cid, line );
        // qDebug()<<cid;
        cid++;
    }
    //  INCASE WHERE THERE IS NOCMPOONENTS ,  ADD AN EMPTY COMPONENT
    QString line="";
    initComponentWithLine(cid, line);
    // Create the main layout that includes all the sub-layouts
    QVBoxLayout *mainLayout = createMainLayout();
    mainLayout->addWidget(scrollArea);

    // Set the overall layout for the CustomWidget
    setLayout(mainLayout);
}

QVBoxLayout* CustomWidget::createMainLayout()
{
    // Create a vertical layout for the main layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add the sub-layouts for time and buttons, title note, and text edits
    layout->addLayout(verticalLayoutTextEdits);

    return layout;
}

void CustomWidget::createComponent(int index)
{
    // Create a new TextEditComponent
    TextEditComponent *newComponent = new TextEditComponent(index, this);

    // Connect signals for creating a new component and backspacing when empty
    connect(newComponent, &TextEditComponent::createNewComponent, this, &CustomWidget::createComponent);
    connect(newComponent, &TextEditComponent::backspaceEmpty, this, &CustomWidget::deleteComponent);
    connect(newComponent, &TextEditComponent::backspaceNotEmpty, this, &CustomWidget::deleteComponentAppendText);
    connect(newComponent, &TextEditComponent::middleEnterKeyPressed, this, &CustomWidget::createComponentWithText);
    connect(newComponent, &TextEditComponent::tabKeyPressed, this, &CustomWidget::focusNextComponent);

    // Special Case For index 0: Insert the new component at the beginning
    if (componentVector.isEmpty()) {
        componentVector.push_back(newComponent);
        verticalLayoutTextEdits->insertWidget(index, newComponent);
        return;
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

void CustomWidget::focusNextComponent(int index)
{
    // Check if the index is within the valid range
    if (index < componentVector.size() - 1)
        // Change focus to the next component's textEdit
        componentVector[index + 1]->text->focusAndMoveCursor(0);
}

void CustomWidget::initComponentWithLine(int index, QString &line)
{
    // Create new component
    createComponent(index);

    // Set the text of the newly created component
    componentVector[index+1]->text->setText(line);

    // To focus on new component and Move Cursor to last postion
    componentVector[index+1]->text->focusAndMoveCursor();
}