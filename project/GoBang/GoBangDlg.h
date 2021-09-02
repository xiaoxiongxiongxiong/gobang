
// GoBangDlg.h: 头文件
//

#pragma once
#include "../../src/GoBangImpl.h"

#define MAX_GRID_COUNT 40  //每格大小
#define RADIUS 6  //半径

// CGoBangDlg 对话框
class CGoBangDlg : public CDialogEx
{
// 构造
public:
    CGoBangDlg(CWnd * pParent = nullptr);    // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DLG_GOBANG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange * pDX);    // DDX/DDV 支持


// 实现
protected:
    HICON m_hIcon;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

protected:
    // 画棋盘
    void drawCheckerBoard(UINT uiRow, UINT uiCol);

private:
    CFont m_fontSize;
    CGoBangImpl * m_pGobang = nullptr;
    int m_iXpos = 0;   // 左上角横坐标
    int m_iYpos = 0;   // 左上角纵坐标

public:
    afx_msg void OnBnClickedBtnStart();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnBnClickedBtnExitGame();
};
