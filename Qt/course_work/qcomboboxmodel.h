#ifndef QCOMBOBOXMODEL_H
#define QCOMBOBOXMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>

class QComboBoxModel : public QAbstractListModel
{
public:
    explicit QComboBoxModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QList<QPair<QString,QString>> *values;
};

#endif // QCOMBOBOXMODEL_H
