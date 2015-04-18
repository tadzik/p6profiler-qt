#include "Overview.h"
#include <QDebug>

Overview::Overview(QWidget *parent) : QWidget(parent)
{
    vbox = new QVBoxLayout(this);

    timeSpent = new QLabel("<h2>Time Spent</h2>", this);
    timeSpentDesc = new QLabel(this);
    vbox->addWidget(timeSpent);
    vbox->addWidget(timeSpentDesc);

    callFrames = new QLabel("<h2>Call frames</h2>", this);
    callFramesDesc = new QLabel(this);
    vbox->addWidget(callFrames);
    vbox->addWidget(callFramesDesc);

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

    QString cfd = QString("In total, <strong>%1 call frames</strong> were entered and exited "
                          "by the profiled code. Inlining eliminated the need to create "
                          "<strong>%2 call frames</strong> (that's <strong>%3%</strong>).")
        .arg((*m)["EntriesWithoutInline"].toString())
        .arg((*m)["EntriesInline"].toString())
        .arg((*m)["InlinePercent"].toString());
    callFramesDesc->setText(cfd);

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
                           .arg((*m)["DeoptOnePercent"].toString());
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
