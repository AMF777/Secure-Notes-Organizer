#include "signin.h"
#include "signup.h"
#include "main_window.h"
#include "switcher_widget.h"

switcher_widget::switcher_widget(QWidget *parent)
    : QWidget{parent}
{
    setProperty("class", "white-background");

    curIdx=1;
    widgets.append(new signin() );
    widgets.append(new signup() );

    // the signal must be of same class of sender
    connect(static_cast<signin*>(widgets[0]), &signin::switchWidgets, this, &switcher_widget::switchWidgets);
    connect(static_cast<signup*>(widgets[1]), &signup::switchWidgets, this, &switcher_widget::switchWidgets);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(widgets[curIdx] );
    switchWidgets();
}

void switcher_widget::switchWidgets()
{
    int nextIdx=(curIdx+1)%2;

    mainLayout->removeWidget(widgets[curIdx] );
    mainLayout->addWidget(widgets[nextIdx]);
    widgets[curIdx]->hide();
    widgets[nextIdx]->show();
    setWindowTitle(widgets[nextIdx]->windowTitle() );
    curIdx=nextIdx;
}
