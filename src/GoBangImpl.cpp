#include "GoBangImpl.h"
#include <string.h>

bool CGoBangImpl::init()
{
    for (int i = 0; i < GOBANG_BOARD_GRID_MAX; i++)
    {
        for (int j = 0; j < GOBANG_BOARD_GRID_MAX; j++)
        {
            _board_info[i][j].x = i;
            _board_info[i][j].y = j;
            _board_info[i][j].used = false;
            _board_info[i][j].type = GOBANG_PIECE_NONE;
        }
    }

    return true;
}

void CGoBangImpl::uninit()
{

}

bool CGoBangImpl::getBoardInfo(gobang_board_info_t * board_info[GOBANG_BOARD_GRID_MAX])
{
    memcpy(board_info, &_board_info, sizeof(_board_info[0]) * GOBANG_BOARD_GRID_MAX);
    return true;
}

bool CGoBangImpl::pieceDown(const int x, const int y, GOBANG_PIECE_TYPE type)
{
    if (checkPieceDown(x, y, type))
    {
        _board_info[x][y].type = type;
        _board_info[x][y].used = true;
        return true;
    }

    return false;
}

bool CGoBangImpl::checkPieceDown(const int x, const int y, GOBANG_PIECE_TYPE type)
{
    if (x < 0 || x >= GOBANG_BOARD_GRID_MAX ||
        y < 0 || y >= GOBANG_BOARD_GRID_MAX ||
        (GOBANG_PIECE_WHITE != type && GOBANG_PIECE_BLACK != type))
    {
        return false;
    }

    return !_board_info[y][x].used;
}

bool CGoBangImpl::checkGameOver(const int x, const int y, GOBANG_PIECE_TYPE type)
{
    if (getTopPiecesCount(x, y, type) + getBottomPiecesCount(x, y, type) >= 6)
        return true;

    if (getTopLeftPiecesCount(x, y, type) + getBottomRightPiecesCount(x, y, type) >= 6)
        return true;

    if (getTopRightPiecesCount(x, y, type) + getBottomLeftPiecesCount(x, y, type) >= 6)
        return true;

    if (getLeftPiecesCount(x, y, type) + getRightPiecesCount(x, y, type) >= 6)
        return true;

    return false;
}

uint16_t CGoBangImpl::getTopPiecesCount(int x, int y, GOBANG_PIECE_TYPE type)
{
    uint16_t count = 0;
    while (y >= 0)
    {
        if (!_board_info[x][y].used)
            break;
        if (_board_info[x][y].type != type)
            break;
        count++;
        y--;
    }

    return count;
}

uint16_t CGoBangImpl::getTopLeftPiecesCount(int x, int y, GOBANG_PIECE_TYPE type)
{
    uint16_t count = 0;
    while (y >= 0 && x >= 0)
    {
        if (!_board_info[x][y].used)
            break;
        if (_board_info[x][y].type != type)
            break;
        count++;
        x--;
        y--;
    }

    return count;
}

uint16_t CGoBangImpl::getTopRightPiecesCount(int x, int y, GOBANG_PIECE_TYPE type)
{
    uint16_t count = 0;
    while (y >= 0 && x <= 14)
    {
        if (!_board_info[x][y].used)
            break;
        if (_board_info[x][y].type != type)
            break;
        count++;
        y--;
        x++;
    }

    return count;
}

uint16_t CGoBangImpl::getLeftPiecesCount(int x, int y, GOBANG_PIECE_TYPE type)
{
    uint16_t count = 0;
    while (x >= 0)
    {
        if (!_board_info[x][y].used)
            break;
        if (_board_info[x][y].type != type)
            break;
        count++;
        x--;
    }

    return count;
}

uint16_t CGoBangImpl::getRightPiecesCount(int x, int y, GOBANG_PIECE_TYPE type)
{
    uint16_t count = 0;
    while (x <= 14)
    {
        if (!_board_info[x][y].used)
            break;
        if (_board_info[x][y].type != type)
            break;
        count++;
        x++;
    }

    return count;
}

uint16_t CGoBangImpl::getBottomPiecesCount(int x, int y, GOBANG_PIECE_TYPE type)
{
    uint16_t count = 0;
    while (y <= 14)
    {
        if (!_board_info[x][y].used)
            break;
        if (_board_info[x][y].type != type)
            break;
        count++;
        y++;
    }

    return count;
}

uint16_t CGoBangImpl::getBottomLeftPiecesCount(int x, int y, GOBANG_PIECE_TYPE type)
{
    uint16_t uiCount = 0;
    while (y <= 14 && x >= 0)
    {
        if (!_board_info[x][y].used)
            break;
        if (_board_info[x][y].type != type)
            break;
        uiCount++;
        x--;
        y++;
    }

    return uiCount;
}

uint16_t CGoBangImpl::getBottomRightPiecesCount(int x, int y, GOBANG_PIECE_TYPE type)
{
    uint16_t count = 0;
    while (y <= 14 && x <= 14)
    {
        if (!_board_info[x][y].used)
            break;
        if (_board_info[x][y].type != type)
            break;
        count++;
        x++;
        y++;
    }

    return count;
}
