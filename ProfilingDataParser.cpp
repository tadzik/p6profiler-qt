#include "ProfilingDataParser.h"

// I kept is as close as possible to the JS version, some thing could've been
// done better, but this at least looks mostly the same as the original, so
// it's easier to track changes to both
void ProfilingDataParser::walkCallGraphNode(QJsonObject& node)
{
    int id = node["id"].toInt();
    if (!routines.contains(id)) {
        routines[id] = new RoutineData(id);
    }
    routines[id]->name = node["name"].toString();
    routines[id]->file = node["file"].toString();
    routines[id]->line = node["line"].toInt();

    routines[id]->entries        += node["entries"].toInt();
    totalEntries                 += node["entries"].toInt();
    routines[id]->speshEntries   += node["spesh_entries"].toInt();
    speshEntries                 += node["spesh_entries"].toInt();
    routines[id]->inlinedEntries += node["inlined_entries"].toInt();
    inlinedEntries               += node["inlined_entries"].toInt();
    routines[id]->JITEntries     += node["jit_entries"].toInt();
    JITEntries                   += node["jit_entries"].toInt();
    routines[id]->exclusive      += node["exclusive_time"].toInt();
    totalExclusive               += node["exclusive_time"].toInt();
    routines[id]->OSR            += node["osr"].toInt();
    totalOSR                     += node["osr"].toInt();
    routines[id]->deoptOnes      += node["deopt_one"].toInt();
    totalDeoptOnes               += node["deopt_one"].toInt();
    routines[id]->deoptAlls      += node["deopt_all"].toInt();
    totalDeoptAlls               += node["deopt_all"].toInt();
    if (routines[id]->recDepth == 0) {
        routines[id]->inclusive += node["inclusive_time"].toInt();
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

void ProfilingDataParser::walkGCNodes(QJsonArray& arr)
{
    QJsonArray::const_iterator it;
    for (it = arr.begin(); it != arr.end(); it++) {
        QJsonObject obj = (*it).toObject();
        if (obj["full"].toInt() != 0) {
            gcData.gcFull++;
            gcData.gcFullTime += obj["time"].toInt();
        } else {
            gcData.gcNursery++;
            gcData.gcNurseryTime += obj["time"].toInt();
        }
    }
}

QVector<RoutineListEntry*> ProfilingDataParser::buildRoutineList()
{
    QVector<RoutineListEntry*> routineList;
    QMap<int, RoutineData*>::iterator it;
    for (it = routines.begin(); it != routines.end(); it++) {
        RoutineData *rd = *it;
        RoutineListEntry *rle = new RoutineListEntry();
        rle->name    = rd->name;
        if (rd->name == "") rle->name = "<anon>";
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

QMap<QString, QVariant> ProfilingDataParser::buildOverviewData()
{
    QMap<QString, QVariant> ret;
    // Time spent
    float gcTime        = gcData.gcNurseryTime + gcData.gcFullTime;
    float overheadTime  = speshTime + gcTime;
    float executingTime = totalTime - overheadTime;
    ret["TotalTime"]            = (float)totalTime / 1000;
    ret["OverheadTime"]         = overheadTime / 1000;
    ret["OverheadTimePercent"]  = 100 * overheadTime / totalTime;
    ret["ExecutingTime"]        = executingTime / 1000;
    ret["ExecutingTimePercent"] = 100 * executingTime / totalTime;
    ret["GCTime"]               = gcTime / 1000;
    ret["GCTimePercent"]        = 100 * gcTime / totalTime;
    ret["SpeshTime"]            = (float)speshTime / 1000;
    ret["SpeshTimePercent"]     = 100 * (float)speshTime / totalTime;
    // Routines
    int interpEntries           = totalEntries - (JITEntries + speshEntries);
    ret["EntriesWithoutInline"] = totalEntries - inlinedEntries;
    ret["EntriesInline"]        = inlinedEntries;
    ret["InlinePercent"]        = 100 * (float)inlinedEntries / totalEntries;
    ret["InterpFrames"]         = interpEntries;
    ret["InterpFramesPercent"]  = 100 * (float)interpEntries / totalEntries;
    ret["SpeshFrames"]          = speshEntries;
    ret["SpeshFramesPercent"]   = 100 * (float)speshEntries / totalEntries;
    ret["JITFrames"]            = JITEntries;
    ret["JITFramesPercent"]     = 100 * (float)JITEntries / totalEntries;

    // Garbage collection
    ret["GCRuns"]         = gcData.gcNursery + gcData.gcFull;
    ret["FullGCRuns"]     = gcData.gcFull;
    ret["NurseryAverage"] = ((float)gcData.gcNurseryTime / 1000) / gcData.gcNursery;
    ret["FullAverage"]    = ((float)gcData.gcFullTime / 1000) / gcData.gcFull;

    // Dynamic optimization
    int optimizedFrames    = speshEntries + JITEntries;
    ret["OptimizedFrames"] = optimizedFrames;
    ret["DeoptOnes"]       = totalDeoptOnes;
    if (!optimizedFrames) optimizedFrames = 1;
    ret["DeoptOnePercent"] = 100 * (float)totalDeoptOnes / optimizedFrames;
    ret["DeoptAlls"]       = totalDeoptAlls;
    ret["OSRs"]            = totalOSR;

    return ret;
}
