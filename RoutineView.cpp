#include "RoutineView.h"
#include <QVBoxLayout>

RoutineView::RoutineView(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout();
    searchField.setPlaceholderText("Search...");
    connect(&searchField, SIGNAL(textChanged(const QString&)),
            this, SLOT(setFilterText(const QString&)));
    vbox->addWidget(&searchField);
    vbox->addWidget(&tableView);
    tableView.verticalHeader()->hide();
    tableView.resizeColumnsToContents();
    tableView.setSortingEnabled(true);
    tableView.show();
    setLayout(vbox);
}

void RoutineView::setModel(RoutineListModel *rlm)
{
    sfpmodel.setSourceModel(rlm);
    sfpmodel.setFilterKeyColumn(0);
    tableView.setModel(&sfpmodel);
}

void RoutineView::setFilterText(const QString& query)
{
    sfpmodel.setFilterRegExp(QRegExp(query, Qt::CaseInsensitive));
}
