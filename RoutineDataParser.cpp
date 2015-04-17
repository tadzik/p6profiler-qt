#include "RoutineDataParser.h"

// I kept is as close as possible to the JS version, some thing could've been
// done better, but this at least looks mostly the same as the original, so
// it's easier to track changes to both
void RoutineDataParser::walkCallGraphNode(QJsonObject& node)
{
    int id = node["id"].toInt();
    if (!routines.contains(id)) {
        routines[id] = new RoutineData(id);
    }
    routines[id]->name = node["name"].toString();
    routines[id]->file = node["file"].toString();
    routines[id]->line = node["line"].toInt();

    routines[id]->entries      += node["entries"].toInt();
    routines[id]->speshEntries += node["spesh_entries"].toInt();
    routines[id]->JITEntries   += node["jit_entries"].toInt();
    routines[id]->exclusive    += node["exclusive_time"].toInt();
    totalExclusive             += node["exclusive_time"].toInt();
    routines[id]->OSR          += node["osr"].toInt();
    if (routines[id]->recDepth == 0) {
        routines[id]->inclusive += node["exclusive_time"].toInt();
    }
    QJsonArray callees(node["callees"].toArray());
    if (callees.count() > 0) {
        routines[id]->recDepth++;
        QJsonArray::const_iterator it;
        for (it = callees.begin(); it != callees.end(); it++) {
            QJsonObject obj = (*it).toObject();
            walkCallGraphNode(obj);
        }
        routines[id]->recDepth--;
    }
}

QVector<RoutineListEntry*> RoutineDataParser::buildRoutineList()
{
    QVector<RoutineListEntry*> routineList;
    QMap<int, RoutineData*>::iterator it;
    for (it = routines.begin(); it != routines.end(); it++) {
        RoutineData *rd = *it;
        RoutineListEntry *rle = new RoutineListEntry();
        rle->name    = rd->name;
        rle->file    = rd->file;
        rle->line    = rd->line;
        rle->entries = rd->entries;
        rle->speshEntriesPercent  = (100 * rd->speshEntries / rd->entries);
        rle->JITEntriesPercent    = (100 * rd->JITEntries   / rd->entries);
        rle->interpEntriesPercent = 100 - rle->speshEntriesPercent
                                        - rle->JITEntriesPercent;
        rle->inclusiveTime = (double)rd->inclusive / 1000;
        rle->inclusiveTimePercent = 100 * rd->inclusive / totalInclusive;
        rle->exclusiveTime = (double)rd->exclusive / 1000;
        rle->exclusiveTimePercent = 100 * rd->exclusive / totalExclusive;
        rle->OSR = rd->OSR;
        routineList.push_back(rle);
    }
    return routineList;
}
