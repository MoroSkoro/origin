#include "qcomboboxmodel.h"
#include <QModelIndex>
#include <QDebug>


QComboBoxModel::QComboBoxModel(QObject *parent)
    : QAbstractListModel{parent}
{
    values = new QList<QPair<QString,QString>>();
}

int QComboBoxModel::rowCount(const QModelIndex &) const
{
    return values->count();
}

QVariant QComboBoxModel::data( const QModelIndex &index, int role ) const
{
    QVariant value;

    switch ( role ){
        case Qt::DisplayRole: //string
        {
            value = this->values->value(index.row()).first;
        }
        break;

        case Qt::UserRole: //data
        {
            value = this->values->value(index.row()).second;
        }
        break;

        default:
            break;
    }

    return value;
}
