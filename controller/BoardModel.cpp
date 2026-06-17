#include "BoardModel.h"

BoardModel::BoardModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_cells.resize(90);

    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            int i = indexOf(col, row);
            m_cells[i].col = col;
            m_cells[i].row = row;
            m_cells[i].side = 0;
            m_cells[i].type = 0;
            m_cells[i].selected = false;
        }
    }
}

int BoardModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return m_cells.size();
}

QVariant BoardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    int i = index.row();

    if (i < 0 || i >= m_cells.size())
    {
        return QVariant();
    }

    const CellData &cell = m_cells[i];

    switch (role)
    {
    case ColRole:
        return cell.col;

    case RowRole:
        return cell.row;

    case SideRole:
        return cell.side;

    case TypeRole:
        return cell.type;

    case TextRole:
        return textForPiece(cell.side, cell.type);

    case SelectedRole:
        return cell.selected;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> BoardModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ColRole] = "col";
    roles[RowRole] = "row";
    roles[SideRole] = "side";
    roles[TypeRole] = "type";
    roles[TextRole] = "text";
    roles[SelectedRole] = "selected";

    return roles;
}

CellData BoardModel::getCellAt(int col, int row) const
{
    if (col < 0 || col >= 9 || row < 0 || row >= 10)
    {
        return CellData();
    }

    return m_cells[indexOf(col, row)];
}

void BoardModel::setCell(int col, int row, int side, int type)
{
    if (col < 0 || col >= 9 || row < 0 || row >= 10)
    {
        return;
    }

    int i = indexOf(col, row);

    m_cells[i].side = side;
    m_cells[i].type = type;

    QModelIndex modelIndex = createIndex(i, 0);
    emit dataChanged(modelIndex, modelIndex);
}

void BoardModel::clearBoard()
{
    for (int i = 0; i < m_cells.size(); ++i)
    {
        m_cells[i].side = 0;
        m_cells[i].type = 0;
        m_cells[i].selected = false;
    }

    if (!m_cells.isEmpty())
    {
        emit dataChanged(createIndex(0, 0),
                         createIndex(m_cells.size() - 1, 0));
    }
}

void BoardModel::setSelected(int col, int row)
{
    clearSelected();

    if (col < 0 || col >= 9 || row < 0 || row >= 10)
    {
        return;
    }

    int i = indexOf(col, row);
    m_cells[i].selected = true;

    QModelIndex modelIndex = createIndex(i, 0);
    emit dataChanged(modelIndex, modelIndex);
}

void BoardModel::clearSelected()
{
    for (int i = 0; i < m_cells.size(); ++i)
    {
        if (m_cells[i].selected)
        {
            m_cells[i].selected = false;

            QModelIndex modelIndex = createIndex(i, 0);
            emit dataChanged(modelIndex, modelIndex);
        }
    }
}

int BoardModel::indexOf(int col, int row) const
{
    return row * 9 + col;
}

QString BoardModel::textForPiece(int side, int type) const
{
    if (side == 0 || type == 0)
    {
        return "";
    }

    if (side == 1)
    {
        switch (type)
        {
        case 1:
            return "帅";
        case 2:
            return "仕";
        case 3:
            return "相";
        case 4:
            return "马";
        case 5:
            return "車";
        case 6:
            return "炮";
        case 7:
            return "兵";
        default:
            return "";
        }
    }

    if (side == 2)
    {
        switch (type)
        {
        case 1:
            return "将";
        case 2:
            return "士";
        case 3:
            return "象";
        case 4:
            return "马";
        case 5:
            return "車";
        case 6:
            return "炮";
        case 7:
            return "卒";
        default:
            return "";
        }
    }

    return "";
}