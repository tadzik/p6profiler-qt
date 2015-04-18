#include "ProfilingDataParser.h"
#include "RoutineListModel.h"
#include "View.h"
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

    ProfilingDataParser pdp(thingy);
    RoutineListModel rlm(0, pdp.buildRoutineList());
    QMap<QString, QVariant> ovm(pdp.buildOverviewData());

    QApplication app(argc, argv);

    View view;
    view.setRoutineModel(&rlm);
    view.setOverviewModel(&ovm);
    view.show();
    return app.exec();
}
