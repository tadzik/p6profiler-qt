#ifndef _OVERVIEW_
#define _OVERVIEW_
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMap>
#include <QString>
#include <QVariant>

class Overview : public QWidget {
    Q_OBJECT;
    QMap<QString, QVariant> *model;
    QVBoxLayout *vbox;
    QLabel *timeSpent;
    QLabel *timeSpentDesc;
    QLabel *callFrames;
    QLabel *callFramesDesc;
    QLabel *garbageCollection;
    QLabel *garbageCollectionDesc;
    QLabel *dynamicOptimization;
    QLabel *dynamicOptimizationDesc1;
    QLabel *dynamicOptimizationDesc2;
    QLabel *dynamicOptimizationDesc3;

public:
    Overview(QWidget *parent = 0);
    void setModel(QMap<QString, QVariant> *);
};

#endif
