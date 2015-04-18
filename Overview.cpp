#include "Overview.h"
#include <QDebug>

Overview::Overview(QWidget *parent) : QWidget(parent)
{
    vbox = new QVBoxLayout(this);

    timeSpent = new QLabel("<h2>Time Spent</h2>", this);
    timeSpentDesc = new QLabel(this);
    vbox->addWidget(timeSpent);
    vbox->addWidget(timeSpentDesc);

    timeSpentGrid = new QGridLayout(this);
    timeSpentGridLabel11 = new QLabel("<strong>Executing Code</strong>", this);
    timeSpentGridLabel12 = new QLabel("<strong>Garbage Collection</strong>", this);
    timeSpentGridLabel13 = new QLabel("<strong>Dynamic Optimization</strong>", this);
    timeSpentBar1 = new QProgressBar(this);
    timeSpentBar2 = new QProgressBar(this);
    timeSpentBar3 = new QProgressBar(this);
    timeSpentGridLabel21 = new QLabel(this);
    timeSpentGridLabel22 = new QLabel(this);
    timeSpentGridLabel23 = new QLabel(this);
    vbox->addLayout(timeSpentGrid);
    timeSpentGrid->addWidget(timeSpentGridLabel11, 1, 1);
    timeSpentGrid->addWidget(timeSpentGridLabel12, 2, 1);
    timeSpentGrid->addWidget(timeSpentGridLabel13, 3, 1);
    timeSpentGrid->addWidget(timeSpentBar1, 1, 2);
    timeSpentGrid->addWidget(timeSpentBar2, 2, 2);
    timeSpentGrid->addWidget(timeSpentBar3, 3, 2);
    timeSpentGrid->addWidget(timeSpentGridLabel21, 1, 3);
    timeSpentGrid->addWidget(timeSpentGridLabel22, 2, 3);
    timeSpentGrid->addWidget(timeSpentGridLabel23, 3, 3);

    callFrames = new QLabel("<h2>Call frames</h2>", this);
    callFramesDesc = new QLabel(this);
    vbox->addWidget(callFrames);
    vbox->addWidget(callFramesDesc);

    callFramesGrid = new QGridLayout(this);
    callFramesGridLabel11 = new QLabel("<strong>Interpreted Frames</strong>", this);
    callFramesGridLabel12 = new QLabel("<strong>Specialized Frames</strong>", this);
    callFramesGridLabel13 = new QLabel("<strong>JIT-compiled Frames</strong>", this);
    callFramesBar1 = new QProgressBar(this);
    callFramesBar2 = new QProgressBar(this);
    callFramesBar3 = new QProgressBar(this);
    callFramesGridLabel21 = new QLabel(this);
    callFramesGridLabel22 = new QLabel(this);
    callFramesGridLabel23 = new QLabel(this);
    vbox->addLayout(callFramesGrid);
    callFramesGrid->addWidget(callFramesGridLabel11, 1, 1);
    callFramesGrid->addWidget(callFramesGridLabel12, 2, 1);
    callFramesGrid->addWidget(callFramesGridLabel13, 3, 1);
    callFramesGrid->addWidget(callFramesBar1, 1, 2);
    callFramesGrid->addWidget(callFramesBar2, 2, 2);
    callFramesGrid->addWidget(callFramesBar3, 3, 2);
    callFramesGrid->addWidget(callFramesGridLabel21, 1, 3);
    callFramesGrid->addWidget(callFramesGridLabel22, 2, 3);
    callFramesGrid->addWidget(callFramesGridLabel23, 3, 3);

    garbageCollection = new QLabel("<h2>Garbage Collection</h2>", this);
    garbageCollectionDesc = new QLabel(this);
    vbox->addWidget(garbageCollection);
    vbox->addWidget(garbageCollectionDesc);

    dynamicOptimization = new QLabel("<h2>Dynamic Optimization</h2>", this);
    dynamicOptimizationDesc1 = new QLabel(this);
    dynamicOptimizationDesc2 = new QLabel(this);
    dynamicOptimizationDesc3 = new QLabel(this);
    vbox->addWidget(dynamicOptimization);
    vbox->addWidget(dynamicOptimizationDesc1);
    vbox->addWidget(dynamicOptimizationDesc2);
    vbox->addWidget(dynamicOptimizationDesc3);

    setLayout(vbox);
}

void Overview::setModel(QMap<QString, QVariant> *m)
{
    model = m;

    QString tsd = QString("The profiled code ran for <strong>%1ms</strong>."
                          " Of this, <strong>%2ms</strong> were spent on garbage"
                          " collection and dynamic optimization (that's <strong>%3%</strong>)")
                          .arg((*m)["TotalTime"].toString())
                          .arg((*m)["OverheadTime"].toString())
                          .arg((*m)["OverheadTimePercent"].toString());
    timeSpentDesc->setText(tsd);

    timeSpentBar1->setValue((*m)["ExecutingTimePercent"].toInt());
    timeSpentBar2->setValue((*m)["GCTimePercent"].toInt());
    timeSpentBar3->setValue((*m)["SpeshTimePercent"].toInt());

    QString tsgl21 = QString("%1% (%2ms)")
        .arg(QString::number((*m)["ExecutingTimePercent"].toDouble(), 'f', 2))
        .arg(QString::number((*m)["ExecutingTime"].toDouble(), 'f', 2));
    QString tsgl22 = QString("%1% (%2ms)")
        .arg(QString::number((*m)["GCTimePercent"].toDouble(), 'f', 2))
        .arg(QString::number((*m)["GCTime"].toDouble(), 'f', 2));
    QString tsgl23 = QString("%1% (%2ms)")
        .arg(QString::number((*m)["SpeshTimePercent"].toDouble(), 'f', 2))
        .arg(QString::number((*m)["SpeshTime"].toDouble(), 'f', 2));
    timeSpentGridLabel21->setText(tsgl21);
    timeSpentGridLabel22->setText(tsgl22);
    timeSpentGridLabel23->setText(tsgl23);

    QString cfd = QString("In total, <strong>%1 call frames</strong> were entered and exited "
                          "by the profiled code. Inlining eliminated the need to create "
                          "<strong>%2 call frames</strong> (that's <strong>%3%</strong>).")
        .arg((*m)["EntriesWithoutInline"].toString())
        .arg((*m)["EntriesInline"].toString())
        .arg((*m)["InlinePercent"].toString());
    callFramesDesc->setText(cfd);

    callFramesBar1->setValue((*m)["InterpFramesPercent"].toInt());
    callFramesBar2->setValue((*m)["SpeshFramesPercent"].toInt());
    callFramesBar3->setValue((*m)["JITFramesPercent"].toInt());

    QString cfgl21 = QString("%1% (%2)").arg(QString::number((*m)["InterpFramesPercent"].toDouble(), 'f', 2))
                                        .arg((*m)["InterpFrames"].toInt());
    QString cfgl22 = QString("%1% (%2)").arg(QString::number((*m)["SpeshFramesPercent"].toDouble(), 'f', 2))
                                        .arg((*m)["SpeshFrames"].toInt());
    QString cfgl23 = QString("%1% (%2)").arg(QString::number((*m)["JITFramesPercent"].toDouble(), 'f', 2))
                                        .arg((*m)["JITFrames"].toInt());
    callFramesGridLabel21->setText(cfgl21);
    callFramesGridLabel22->setText(cfgl22);
    callFramesGridLabel23->setText(cfgl23);

    QString gcd = QString("The profiled code did <strong>%1 garbage collections</strong>. "
                          "There were <strong>%2 full collections</strong> involving "
                          "the entire heap.")
                          .arg((*m)["GCRuns"].toString())
                          .arg((*m)["FullGCRuns"].toString());
    garbageCollectionDesc->setText(gcd);

    QString dod1 = QString("Of %1 specialized or JIT-compiled frames, there were "
                           "<strong>%2 deoptimizations</strong> "
                           "(that's <strong> %3%</strong> of all optimized frames).")
                           .arg((*m)["OptimizedFrames"].toString())
                           .arg((*m)["DeoptOnes"].toString())
                           .arg(QString::number((*m)["DeoptOnePercent"].toDouble(), 'f', 2));
    dynamicOptimizationDesc1->setText(dod1);

    int doa = (*m)["DeoptAlls"].toInt();
    if (doa == 0) {
        QString dod2 = QString("There was <strong>no global deoptimization</strong> "
                               "triggered by the profiled code.");
        dynamicOptimizationDesc2->setText(dod2);
    } else if (doa == 1) {
        QString dod2 = QString("There was <strong>one global deoptimization</strong> "
                               "triggered by the profiled code.");
        dynamicOptimizationDesc2->setText(dod2);
    } else {
        QString dod2 = QString("There were <strong>%1 global deoptimizations</strong> "
                               "triggered by the profiled code.").arg(doa);
        dynamicOptimizationDesc2->setText(dod2);
    }

    int osrs = (*m)["OSRs"].toInt();
    if (osrs == 0) {
        QString dod3 = QString("There was <strong>no On Stack Replacement</strong> performed "
                               "while executing the profiled code (normal if the code lacks "
                               "long-running loops with many iterations).");
        dynamicOptimizationDesc3->setText(dod3);
    } else if (osrs == 1) {
        QString dod3 = QString("There was <strong>one On Stack Replacement</strong> performed "
                               "while executing the profiled code.");
        dynamicOptimizationDesc3->setText(dod3);
    } else {
        QString dod3 = QString("There were <strong>%1 On Stack Replacements</strong> "
                               "performed while executing the profiled code.").arg(osrs);
        dynamicOptimizationDesc3->setText(dod3);
    }
}
