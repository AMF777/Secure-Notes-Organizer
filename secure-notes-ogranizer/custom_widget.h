#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include  <vector>

#include "component.h"
#include "back-end/Note.h"
#include "back-end/NoteComponent.h"
class CustomWidget : public QWidget {
    Q_OBJECT
public:
    CustomWidget(QWidget *parent = nullptr);
    CustomWidget(QStringList& lines, QWidget *parent = nullptr);
    CustomWidget(Note *note, std::vector<NoteComponent> noteComponents, QWidget *parent = nullptr);
    Note *note;
    std::vector<NoteComponent> noteComponents;
private slots:
    TextEditComponent* createComponent(int index);
    void deleteComponent(int index);
    void createComponentWithText(int index, const QString &text);
    void deleteComponentAppendText(int index, const QString &text);
    void focusNextComponent(int index);
    void initComponentWithLine(int index, NoteComponent &component);

private:
    QVector<TextEditComponent*> componentVector;
    QVBoxLayout *verticalLayoutTextEdits;

    QVBoxLayout *createMainLayout();
};

#endif // CUSTOMWIDGET_H
