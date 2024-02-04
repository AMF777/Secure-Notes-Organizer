#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include "component.h"

class CustomWidget : public QWidget {
    Q_OBJECT
public:
    CustomWidget(QWidget *parent = nullptr);
    CustomWidget(QStringList& lines, QWidget *parent = nullptr);
private slots:
    void createComponent(int index);
    void deleteComponent(int index);
    void createComponentWithText(int index, const QString &text);
    void deleteComponentAppendText(int index, const QString &text);
    void focusNextComponent(int index);
    void initComponentWithLine(int index, QString& line);

private:
    QVector<TextEditComponent*> componentVector;
    QVBoxLayout *verticalLayoutTextEdits;

    QVBoxLayout *createMainLayout();
};

#endif // CUSTOMWIDGET_H
