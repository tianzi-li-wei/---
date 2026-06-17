#pragma once

#include <QAbstractListModel>
#include <QVector>
#include <QString>

struct CellData
{
    int row = 0;          // y
    int col = 0;          // x
    int side = 0;         // 0 空，1 红，2 黑
    int type = 0;         // 0 空，1-7 棋子类型
    QString text;         // QML 显示文字
    bool selected = false;
};

class BoardModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum BoardRoles
    {
        RowRole = Qt::UserRole + 1,
        ColRole,
        IndexRole,
        SideRole,
        TypeRole,
        TextRole,
        SelectedRole
    };

    explicit BoardModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(
        const QModelIndex &index,
        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setCell(
        int x,
        int y,
        int side,
        int type);

    void setSelected(
        int x,
        int y);

    void clearSelected();

    void refreshAll();

    int indexFromXY(
        int x,
        int y) const;

    // 新增：根据棋盘坐标获取格子数据
    CellData getCellAt(
        int x,
        int y) const;

private:
    QString pieceText(
        int side,
        int type) const;

private:
    QVector<CellData> m_cells;
};