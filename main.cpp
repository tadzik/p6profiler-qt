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
        // perhaps we got .html in, let's try to rip JSON from that
        QByteArray pattern("var rawData = JSON.parse('");
        int lineStart = jsondata.indexOf(pattern);
        if (lineStart != -1) {
            int lineEnd = jsondata.indexOf("\n", lineStart);
            if (lineEnd != -1) {
                // get the actual positions of the JSON string
                lineStart += pattern.length();
                lineEnd   -= 3;
                // cut the excess HTML on both sides
                jsondata.truncate(lineEnd);
                jsondata = jsondata.mid(lineStart);
            }
        }
    }
    rawdata = QJsonDocument::fromJson(jsondata);
    if (!rawdata.isArray()) {
        // if that didn't work either, we're screwed
        qDebug() << "Malformed input file";
        return 1;
    }
    QJsonArray arr = rawdata.array();
    if (!arr[0].isObject()) {
        qDebug() << "Malformed input file";
        return 1;
    }

    ProfilingDataParser pdp(arr);
    RoutineListModel rlm(0, pdp.buildRoutineList());
    QMap<QString, QVariant> ovm(pdp.buildOverviewData());

    QApplication app(argc, argv);

    View view;
    view.setRoutineModel(&rlm);
    view.setOverviewModel(&ovm);
    view.show();
    return app.exec();
}
