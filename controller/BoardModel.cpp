#include "BoardModel.h"

BoardModel::BoardModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_cells.resize(90);

    for (int y = 0; y < 10; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            int idx = indexFromXY(x, y);

            m_cells[idx].row = y;
            m_cells[idx].col = x;
            m_cells[idx].side = 0;
            m_cells[idx].type = 0;
            m_cells[idx].text = "";
            m_cells[idx].selected = false;
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

QVariant BoardModel::data(
    const QModelIndex &index,
    int role) const
{
    if (!index.isValid())
    {
        return {};
    }

    int rowIndex = index.row();

    if (rowIndex < 0 || rowIndex >= m_cells.size())
    {
        return {};
    }

    const CellData &cell = m_cells[rowIndex];

    switch (role)
    {
    case RowRole:
        return cell.row;

    case ColRole:
        return cell.col;

    case IndexRole:
        return cell.row * 9 + cell.col;

    case SideRole:
        return cell.side;

    case TypeRole:
        return cell.type;

    case TextRole:
        return cell.text;

    case SelectedRole:
        return cell.selected;

    default:
        return {};
    }
}

QHash<int, QByteArray> BoardModel::roleNames() const
{
    return {
        { RowRole, "row" },
        { ColRole, "col" },
        { IndexRole, "index" },
        { SideRole, "side" },
        { TypeRole, "type" },
        { TextRole, "text" },
        { SelectedRole, "selected" }
    };
}

void BoardModel::setCell(
    int x,
    int y,
    int side,
    int type)
{
    if (x < 0 || x >= 9 || y < 0 || y >= 10)
    {
        return;
    }

    int idx = indexFromXY(x, y);

    m_cells[idx].side = side;
    m_cells[idx].type = type;
    m_cells[idx].text = pieceText(side, type);

    QModelIndex modelIndex = createIndex(idx, 0);

    emit dataChanged(
        modelIndex,
        modelIndex,
        {
            SideRole,
            TypeRole,
            TextRole
        });
}

void BoardModel::setSelected(
    int x,
    int y)
{
    clearSelected();

    if (x < 0 || x >= 9 || y < 0 || y >= 10)
    {
        return;
    }

    int idx = indexFromXY(x, y);

    m_cells[idx].selected = true;

    QModelIndex modelIndex = createIndex(idx, 0);

    emit dataChanged(
        modelIndex,
        modelIndex,
        { SelectedRole });
}

void BoardModel::clearSelected()
{
    for (int i = 0; i < m_cells.size(); ++i)
    {
        if (m_cells[i].selected)
        {
            m_cells[i].selected = false;

            QModelIndex modelIndex = createIndex(i, 0);

            emit dataChanged(
                modelIndex,
                modelIndex,
                { SelectedRole });
        }
    }
}

void BoardModel::refreshAll()
{
    if (m_cells.isEmpty())
    {
        return;
    }

    QModelIndex topLeft = createIndex(0, 0);
    QModelIndex bottomRight = createIndex(m_cells.size() - 1, 0);

    emit dataChanged(
        topLeft,
        bottomRight,
        {
            RowRole,
            ColRole,
            IndexRole,
            SideRole,
            TypeRole,
            TextRole,
            SelectedRole
        });
}

int BoardModel::indexFromXY(
    int x,
    int y) const
{
    return y * 9 + x;
}

// 新增：根据棋盘坐标获取格子数据
CellData BoardModel::getCellAt(
    int x,
    int y) const
{
    if (x < 0 || x >= 9 || y < 0 || y >= 10)
    {
        return CellData{};
    }

    int idx = indexFromXY(x, y);

    if (idx < 0 || idx >= m_cells.size())
    {
        return CellData{};
    }

    return m_cells[idx];
}

QString BoardModel::pieceText(
    int side,
    int type) const
{
    if (side == 0 || type == 0)
    {
        return "";
    }

    // side: 1 红方
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
            return "车";
        case 6:
            return "炮";
        case 7:
            return "兵";
        default:
            return "";
        }
    }

    // side: 2 黑方
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
            return "车";
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