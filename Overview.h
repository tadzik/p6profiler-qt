#ifndef _OVERVIEW_
#define _OVERVIEW_
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMap>
#include <QString>
#include <QVariant>
#include <QProgressBar>

class Overview : public QWidget {
    Q_OBJECT;
    QMap<QString, QVariant> *model;
    QVBoxLayout *vbox;

    QLabel *timeSpent;
    QLabel *timeSpentDesc;
    QGridLayout *timeSpentGrid;
    QLabel *timeSpentGridLabel11;
    QLabel *timeSpentGridLabel12;
    QLabel *timeSpentGridLabel13;
    QLabel *timeSpentGridLabel21;
    QLabel *timeSpentGridLabel22;
    QLabel *timeSpentGridLabel23;
    QProgressBar *timeSpentBar1;
    QProgressBar *timeSpentBar2;
    QProgressBar *timeSpentBar3;

    QLabel *callFrames;
    QLabel *callFramesDesc;
    QGridLayout *callFramesGrid;
    QLabel *callFramesGridLabel11;
    QLabel *callFramesGridLabel12;
    QLabel *callFramesGridLabel13;
    QLabel *callFramesGridLabel21;
    QLabel *callFramesGridLabel22;
    QLabel *callFramesGridLabel23;
    QProgressBar *callFramesBar1;
    QProgressBar *callFramesBar2;
    QProgressBar *callFramesBar3;

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
