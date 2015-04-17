#include "ProfilingDataParser.h"
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
        qDebug() << "Usage:" << argv[0] << "<filename.json>";
        return 1;
    }
    QFile profile(argv[1]);
    if (!profile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open" << argv[1];
        return 1;
    }
    QByteArray jsondata = profile.readAll();
    profile.close();

    QJsonDocument rawdata(QJsonDocument::fromJson(jsondata));
    if (!rawdata.isArray()) {
        qDebug() << "Malformed input file";
        return 1;
    }
    QJsonArray arr = rawdata.array();
    if (!arr[0].isObject()) {
        qDebug() << "Malformed input file";
        return 1;
    }
    QJsonObject thingy = arr[0].toObject();
    qDebug() << "Total time:" << thingy["total_time"].toInt();
    qDebug() << "Spesh time:" << thingy["spesh_time"].toInt();

    QJsonObject callGraph = thingy["call_graph"].toObject();
    ProfilingDataParser pdp(callGraph);
    pdp.buildRoutineList();

    RoutineListModel rlm(0, pdp.buildRoutineList());

    QApplication app(argc, argv);

    RoutineView view;
    view.setModel(&rlm);
    view.show();
    return app.exec();
}
