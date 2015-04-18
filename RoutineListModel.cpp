#include "RoutineListModel.h"

int RoutineListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    } else {
        return routineList.count();
    }
}

int RoutineListModel::columnCount(const QModelIndex&) const
{
    return 4;
}

QVariant RoutineListModel::data(const QModelIndex &idx, int role) const
{
    RoutineListEntry *rle = routineList[idx.row()];
    if (role != Qt::DisplayRole && role != Qt::UserRole) {
        return QVariant();
    }
    if (role == Qt::UserRole && idx.column() == 2) {
        return rle->inclusiveTimePercent;
    }
    if (role == Qt::UserRole && idx.column() == 3) {
        return rle->exclusiveTimePercent;
    }
    switch (idx.column()) {
    case 0:
        return rle->name + " (" + rle->file + ":" + QString::number(rle->line) + ")";
        break;
    case 1:
        return rle->entries;
        break;
    case 2:
        return QString::number(rle->inclusiveTimePercent)
            + "% (" + QString::number(rle->inclusiveTime) + "ms)";
        break;
    case 3:
        return QString::number(rle->exclusiveTimePercent)
            + "% (" + QString::number(rle->exclusiveTime) + "ms)";
        break;
    default:
        return QVariant();
    }
}

QVariant RoutineListModel::headerData(int section, Qt::Orientation orientation, int role)
    const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }
    return QString("Routine,Entries,Inclusive time,Exclusive time").split(",")[section];
}
