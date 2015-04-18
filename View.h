#ifndef _VIEW_
#define _VIEW_
#include <QMainWindow>
#include "Overview.h"
#include "RoutineView.h"

class View : public QMainWindow {
    Q_OBJECT;
    QTabWidget tabWidget;
    Overview ov;
    RoutineView rv;
public:
    View(QWidget *parent = 0);
    void setRoutineModel(RoutineListModel*);
    void setOverviewModel(QMap<QString, QVariant> *m);
};

#endif
