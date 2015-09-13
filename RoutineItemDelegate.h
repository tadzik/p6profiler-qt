#ifndef _ROUTINE_ITEM_DELEGATE_
#define _ROUTINE_ITEM_DELEGATE_

#include <QStyledItemDelegate>
#include <QTableView>

class RoutineItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
    QTableView *tableView;
public:
    RoutineItemDelegate(QTableView *tv);

    void paint(QPainter *, const QStyleOptionViewItem&,
               const QModelIndex &idx) const Q_DECL_OVERRIDE;
};

#endif
