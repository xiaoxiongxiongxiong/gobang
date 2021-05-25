#pragma once
#include <stdbool.h>
#include <stdint.h>

#define GOBANG_BOARD_GRID_MAX 15  // 棋盘行/列数

// 棋子类型
typedef enum _GOBANG_PIECE_TYPE
{
    GOBANG_PIECE_NONE = 0,
    GOBANG_PIECE_WHITE,    // 白棋
    GOBANG_PIECE_BLACK,    // 黑棋
    GOBANG_PIECE_MAX
} GOBANG_PIECE_TYPE;

// 单格棋盘信息
typedef struct _gobang_board_info_t
{
    bool used;               // 是否已被使用
    int x;                   // 横坐标 列
    int y;                   // 纵坐标 行
    GOBANG_PIECE_TYPE type;  // 棋子类型
} gobang_board_info_t;

class CGoBangImpl
{
public:
    CGoBangImpl() = default;
    ~CGoBangImpl() = default;

    // 初始化
    bool init();

    // 销毁
    void uninit();

    // 获取棋盘信息
    bool getBoardInfo(gobang_board_info_t * board_info[GOBANG_BOARD_GRID_MAX]);

    // 落子
    bool pieceDown(int x, int y, GOBANG_PIECE_TYPE type);

    // 判断棋子是否能下
    bool checkPieceDown(int x, int y, GOBANG_PIECE_TYPE type);

    // 判断是否结束
    bool checkGameOver(int x, int y, GOBANG_PIECE_TYPE type);

protected:
    // 获取棋子上方同色棋子个数
    uint16_t getTopPiecesCount(int x, int y, GOBANG_PIECE_TYPE type);

    // 获取棋子左上方同色棋子个数
    uint16_t getTopLeftPiecesCount(int x, int y, GOBANG_PIECE_TYPE type);

    // 获取棋子右上方同色棋子个数
    uint16_t getTopRightPiecesCount(int x, int y, GOBANG_PIECE_TYPE type);

    // 获取棋子左方同色棋子个数
    uint16_t getLeftPiecesCount(int x, int y, GOBANG_PIECE_TYPE type);

    // 获取棋子右方同色棋子个数
    uint16_t getRightPiecesCount(int x, int y, GOBANG_PIECE_TYPE type);

    // 获取棋子下方同色棋子个数
    uint16_t getBottomPiecesCount(int x, int y, GOBANG_PIECE_TYPE type);

    // 获取棋子左下方同色棋子个数
    uint16_t getBottomLeftPiecesCount(int x, int y, GOBANG_PIECE_TYPE type);

    // 获取棋子右下方同色棋子个数
    uint16_t getBottomRightPiecesCount(int x, int y, GOBANG_PIECE_TYPE type);

private:
    // 棋盘信息
    gobang_board_info_t _board_info[GOBANG_BOARD_GRID_MAX][GOBANG_BOARD_GRID_MAX];
};
