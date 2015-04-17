#include "RoutineDataParser.h"
#include "RoutineListModel.h"
#include "RoutineView.h"
#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        qDebug() << "wrong usage";
        return 1;
    }
    QFile profile(argv[1]);
    if (!profile.open(QIODevice::ReadOnly)) {
        qDebug() << "fuck";
        return 1;
    }
    QByteArray jsondata = profile.readAll();
    profile.close();

    QJsonDocument rawdata(QJsonDocument::fromJson(jsondata));
    if (!rawdata.isArray()) {
        qDebug() << "wrong format";
        return 1;
    }
    QJsonArray arr = rawdata.array();
    if (!arr[0].isObject()) {
        qDebug() << "wrong format";
        return 1;
    }
    QJsonObject thingy = arr[0].toObject();
    qDebug() << "Total time:" << thingy["total_time"].toInt();
    qDebug() << "Spesh time:" << thingy["spesh_time"].toInt();

    QJsonObject callGraph = thingy["call_graph"].toObject();
    RoutineDataParser rc(callGraph);
    rc.buildRoutineList();

    RoutineListModel rlm(0, rc.buildRoutineList());

    QApplication app(argc, argv);

    RoutineView view;
    view.setModel(&rlm);
    view.show();
    return app.exec();
}
