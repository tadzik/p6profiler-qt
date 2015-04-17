#ifndef _ROUTINE_DATA_PARSER_
#define _ROUTINE_DATA_PARSER_
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QMap>
#include "RoutineListModel.h"

struct RoutineData {
    int id;
    int entries;
    int speshEntries;
    int JITEntries;
    int exclusive;
    int inclusive;
    int OSR;
    int recDepth;
    QString name;
    QString file;
    int line;

    RoutineData(int eye_dee)
    {
        id = eye_dee;
        entries = speshEntries = JITEntries = exclusive = inclusive
                = OSR = recDepth = line = 0;
    }
};

class RoutineDataParser {
    QMap<int, RoutineData*> routines;
    int totalExclusive;
    int totalInclusive;

public:
    RoutineDataParser(QJsonObject &root)
    {
        totalExclusive = 0;
        totalInclusive = root["inclusive_time"].toInt();
        walkCallGraphNode(root);
    }

    void walkCallGraphNode(QJsonObject&);

    QVector<RoutineListEntry*> buildRoutineList();
};

#endif
