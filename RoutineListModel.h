#ifndef _ROUTINE_LIST_MODEL_
#define _ROUTINE_LIST_MODEL_
#include <QAbstractTableModel>

struct RoutineListEntry {
    QString name;
    int line;
    QString file;
    int entries;
    int interpEntriesPercent;
    int speshEntriesPercent;
    int JITEntriesPercent;
    float inclusiveTime;
    int inclusiveTimePercent;
    float exclusiveTime;
    int exclusiveTimePercent;
    int OSR;
    // 12 columns
};

class RoutineListModel : public QAbstractTableModel {
    QVector<RoutineListEntry*> routineList;
public:
    RoutineListModel(QObject *, QVector<RoutineListEntry*> rl)
        : routineList(rl) { }

    int rowCount(const QModelIndex& parent) const;

    int columnCount(const QModelIndex&) const;

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif
