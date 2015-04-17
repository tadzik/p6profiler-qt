#ifndef _ROUTINE_VIEW_
#define _ROUTINE_VIEW_
#include "RoutineListModel.h"
#include <QTableView>
#include <QHeaderView>
#include <QWidget>

class RoutineView : public QWidget {
    Q_OBJECT;
    QTableView tableView;

public:
    RoutineView(QWidget *parent = 0);
    void setModel(RoutineListModel *);
};

#endif
