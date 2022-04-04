#include "GoBangImpl.h"
#include "os_log.h"
#include <string.h>

bool CGoBangImpl::init(const int x, const int y, const int grid_size)
{
    if (_is_init)
    {
        log_msg_warn("already inited.");
        return false;
    }

    if (x < 0 || y < 0 || grid_size <= 0)
    {
        log_msg_warn("Input param is invalid");
        return false;
    }

    for (int i = 0; i < GOBANG_BOARD_GRID_MAX; i++)
    {
        for (int j = 0; j < GOBANG_BOARD_GRID_MAX; j++)
        {
            _board_info[i][j].used = false;
            _board_info[i][j].type = GOBANG_PIECE_NONE;
        }
    }

    _begin_x_pos = x;
    _begin_y_pos = y;
    _end_x_pos = x + GOBANG_BOARD_GRID_MAX * grid_size;
    _end_y_pos = y + GOBANG_BOARD_GRID_MAX * grid_size;
    _grid_size = grid_size;
    _grid_radius = grid_size / 2;
    _piece_count = 0;

    return true;
}

void CGoBangImpl::uninit()
{
    if (_is_init)
    {
        _begin_x_pos = 0;
        _begin_y_pos = 0;
        _grid_size = 0;
        _piece_count = 0;
        _is_init = false;
    }
}

bool CGoBangImpl::pieceDown(const int x, const int y, const GOBANG_PIECE_TYPE type)
{
    if (!checkPieceValid(x, y, type))
        return false;

    const int x_diff = x - _begin_x_pos;
    const int x_gain = x_diff % _grid_size >= _grid_radius ? 1 : 0;

    const int y_diff = y - _begin_y_pos;
    const int y_gain = y_diff % _grid_size >= _grid_radius ? 1 : 0;

    const int col = x_diff / _grid_size + x_gain;  // 列
    const int row = y_diff / _grid_size + y_gain;  // 行

    if (!_board_info[row][col].used)
    {
        _board_info[row][col].used = true;
        _board_info[row][col].type = type;
        ++_piece_count;
        return true;
    }

    return false;
}

bool CGoBangImpl::getPiecesInfo(gobang_board_info_t info[GOBANG_BOARD_GRID_MAX][GOBANG_BOARD_GRID_MAX])
{
    for (int i = 0; i < GOBANG_BOARD_GRID_MAX; i++)
    {
        for (int j = 0; j < GOBANG_BOARD_GRID_MAX; j++)
        {
            info[i][j].used = _board_info[i][j].used;
            info[i][j].type = _board_info[i][j].type;
        }
    }

    return true;
}

bool CGoBangImpl::checkGameOver(const int x, const int y, GOBANG_PIECE_TYPE type)
{
    if (!checkPieceValid(x, y, type))
        return false;

    const int x_diff = x - _begin_x_pos;
    const int x_gain = x_diff % _grid_size >= _grid_radius ? 1 : 0;

    const int y_diff = y - _begin_y_pos;
    const int y_gain = y_diff % _grid_size >= _grid_radius ? 1 : 0;

    const int col = x_diff / _grid_size + x_gain;  // 列
    const int row = y_diff / _grid_size + y_gain;  // 行

    if (getTopPiecesCount(row, col, type) + getBottomPiecesCount(row, col, type) >= 6)
        return true;

    if (getTopLeftPiecesCount(row, col, type) + getBottomRightPiecesCount(row, col, type) >= 6)
        return true;

    if (getTopRightPiecesCount(row, col, type) + getBottomLeftPiecesCount(row, col, type) >= 6)
        return true;

    if (getLeftPiecesCount(row, col, type) + getRightPiecesCount(row, col, type) >= 6)
        return true;

    return false;
}

bool CGoBangImpl::checkGameStalemate()
{
    return 225 == _piece_count;
}

bool CGoBangImpl::checkPieceValid(int x, int y, GOBANG_PIECE_TYPE type)
{
    if (x < _begin_x_pos - _grid_size || x + _grid_radius > _end_x_pos)
    {
        log_msg_warn("Input param x: %d is invalid.", x);
        return false;
    }

    if (y < _begin_y_pos - _grid_radius || y + _grid_radius > _end_y_pos)
    {
        log_msg_warn("Input param y: %d is invalid.", y);
        return false;
    }

    if (GOBANG_PIECE_WHITE != type && GOBANG_PIECE_BLACK != type)
    {
        log_msg_warn("Input piece type: %d is invalid.", type);
        return false;
    }

    return true;
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
