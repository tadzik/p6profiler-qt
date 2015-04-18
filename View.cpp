#include "View.h"
#include <QVBoxLayout>

View::View(QWidget *parent) : QMainWindow(parent)
{
    tabWidget.addTab(&ov, "Overview");
    tabWidget.addTab(&rv, "Routines");
    setCentralWidget(&tabWidget);
}
void View::setRoutineModel(RoutineListModel *m)
{
    rv.setModel(m);
}

void View::setOverviewModel(QMap<QString, QVariant> *m)
{
    ov.setModel(m);
}
