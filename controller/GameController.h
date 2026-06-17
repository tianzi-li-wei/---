#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

// 引入你需要的头文件，不是包含自己！
#include "BoardModel.h"
#include <QString>

// 类声明
class GameController
{
public:
    // 函数声明
    void syncBoardFromEngine();
    void handleQmlClick(int x, int y);

private:
    BoardModel* m_boardModel = nullptr; // 你的成员变量，和你项目对应即可
};

#endif // GAMECONTROLLER_H