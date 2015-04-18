#include "RoutineItemDelegate.h"
#include <QStyleOptionProgressBar>
#include <QApplication>

RoutineItemDelegate::RoutineItemDelegate(QTableView *tv) : QItemDelegate(tv)
{
    tableView = tv;
}

void RoutineItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                const QModelIndex &idx) const Q_DECL_OVERRIDE
{
    if (idx.column() < 2) {
        QItemDelegate::paint(painter, option, idx);
        return;
    }

    QStyleOptionProgressBar progressBarOption;
    progressBarOption.state = QStyle::State_Enabled;
    progressBarOption.direction = QApplication::layoutDirection();
    progressBarOption.rect = option.rect;
    progressBarOption.fontMetrics = QApplication::fontMetrics();
    progressBarOption.minimum = 0;
    progressBarOption.maximum = 100;
    progressBarOption.textAlignment = Qt::AlignCenter;
    progressBarOption.textVisible = true;
    QVariant progress = tableView->model()->data(idx, Qt::UserRole);
    QVariant text     = tableView->model()->data(idx, Qt::DisplayRole);
    progressBarOption.text = text.toString();
    progressBarOption.progress = progress.toInt();

    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
}
