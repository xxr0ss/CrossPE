#ifndef SECTIONSMODEL_H
#define SECTIONSMODEL_H

#include <QAbstractTableModel>

#include "PEManager.h"

class SectionsModel : public QAbstractTableModel
{
public:
    SectionsModel();

    ~SectionsModel();

    // 通过 QAbstractTableModel 继承
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

};

#endif // SECTIONSMODEL_H
