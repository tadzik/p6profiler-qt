#include "RoutineView.h"
#include <QHBoxLayout>

RoutineView::RoutineView(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(&tableView);
    tableView.verticalHeader()->hide();
    tableView.resizeColumnsToContents();
    tableView.show();
    setLayout(hbox);
}

void RoutineView::setModel(RoutineListModel *rlm)
{
    tableView.setModel(rlm);
}
