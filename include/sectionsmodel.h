#ifndef SECTIONSMODEL_H
#define SECTIONSMODEL_H

#include <qstandarditemmodel.h>
#include <qabstractitemmodel.h>

#include "PEManager.h"

class SectionsModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QStringList columnLabels;

public:
    SectionsModel();

    ~SectionsModel();

    // 通过 QAbstractTableModel 继承
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

};

#endif // SECTIONSMODEL_H
