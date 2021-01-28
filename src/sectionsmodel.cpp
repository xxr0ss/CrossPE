#include "sectionsmodel.h"

SectionsModel::SectionsModel()
{
}

SectionsModel::~SectionsModel()
{
}

int SectionsModel::rowCount(const QModelIndex& parent) const
{
    PEManager* manager = PEManager::getPEManager();
    return manager->getIMAGE_FILE_HEADER()->NumberOfSections;
}

int SectionsModel::columnCount(const QModelIndex& parent) const
{
	return 11;
}

QVariant SectionsModel::data(const QModelIndex& index, int role) const
{
    // TODO: write my own logic of display sections table
    int row = index.row();
    int col = index.column();
    //qDebug() << QString("row %1, col%2, role %3")
    //    .arg(row).arg(col).arg(role);


    switch (role) {
    case Qt::DisplayRole:
        //return QString::asprintf("(%d, %d)", row, col);
        break;
    case Qt::FontRole:
        
        break;
    case Qt::BackgroundRole:
        
        break;
    case Qt::TextAlignmentRole:
        
        break;
    case Qt::CheckStateRole:
        break;
    }

	return QVariant();
}

Qt::ItemFlags SectionsModel::flags(const QModelIndex& index) const
{
	return QAbstractTableModel::flags(index);
}
