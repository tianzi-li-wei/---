#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QString>

struct CellData
{
    int col = 0;
    int row = 0;
    int side = 0;      // 0 空，1 红方，2 黑方
    int type = 0;      // 0 空，1 将/帅，2 士/仕，3 象/相，4 马，5 车，6 炮，7 兵/卒
    bool selected = false;
};

class BoardModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum BoardRoles
    {
        ColRole = Qt::UserRole + 1,
        RowRole,
        SideRole,
        TypeRole,
        TextRole,
        SelectedRole
    };

    explicit BoardModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    CellData getCellAt(int col, int row) const;

    void setCell(int col, int row, int side, int type);
    void clearBoard();

    void setSelected(int col, int row);
    void clearSelected();

private:
    int indexOf(int col, int row) const;
    QString textForPiece(int side, int type) const;

private:
    QVector<CellData> m_cells;
};

#endif // BOARDMODEL_H