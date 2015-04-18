#ifndef _PROFILING_DATA_PARSER_
#define _PROFILING_DATA_PARSER_
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
    int inlinedEntries;
    int exclusive;
    int inclusive;
    int deoptOnes;
    int deoptAlls;
    int OSR;
    int recDepth;
    QString name;
    QString file;
    int line;

    RoutineData(int eye_dee)
    {
        id = eye_dee;
        entries = speshEntries = JITEntries = inlinedEntries
                = exclusive = inclusive
                = deoptOnes = deoptAlls
                = OSR = recDepth = line = 0;
    }
};

struct GCData {
    int gcNursery;
    int gcNurseryTime;
    int gcFull;
    int gcFullTime;

    GCData()
    {
        gcNursery = gcNurseryTime = gcFull = gcFullTime = 0;
    }
};

class ProfilingDataParser {
    QMap<int, RoutineData*> routines;
    int totalExclusive;
    int totalInclusive;
    GCData gcData;
    int totalTime;
    int speshTime;
    int totalEntries;
    int speshEntries;
    int inlinedEntries;
    int JITEntries;
    int totalOSR;
    int totalDeoptOnes;
    int totalDeoptAlls;

public:
    ProfilingDataParser(QJsonObject &root)
    {
        totalExclusive = totalInclusive = totalTime = speshTime
            = totalEntries = speshEntries = inlinedEntries = JITEntries
            = totalOSR = totalDeoptOnes = totalDeoptAlls = 0;
        totalTime = root["total_time"].toInt();
        speshTime = root["spesh_time"].toInt();
        QJsonObject callGraph = root["call_graph"].toObject();
        totalInclusive = callGraph["inclusive_time"].toInt();
        walkCallGraphNode(callGraph);
        QJsonArray gcData = root["gcs"].toArray();
        walkGCNodes(gcData);
    }

    void walkCallGraphNode(QJsonObject&);
    void walkGCNodes(QJsonArray&);

    QVector<RoutineListEntry*> buildRoutineList();
    QMap<QString, QVariant> buildOverviewData();
};

#endif
