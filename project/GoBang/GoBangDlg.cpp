﻿
// GoBangDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GoBang.h"
#include "GoBangDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange * pDX);    // DDX/DDV 支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange * pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGoBangDlg 对话框



CGoBangDlg::CGoBangDlg(CWnd * pParent /*=nullptr*/)
    : CDialogEx(IDD_GOBANG_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGoBangDlg::DoDataExchange(CDataExchange * pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGoBangDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CGoBangDlg 消息处理程序

BOOL CGoBangDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu * pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    // TODO: 在此添加额外的初始化代码
    m_fontSize.CreatePointFont(150, _T("华文行楷"), NULL);
    GetDlgItem(IDC_BTN_START)->SetFont(&m_fontSize);
    GetDlgItem(IDC_BTN_EXIT_GAME)->SetFont(&m_fontSize);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGoBangDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGoBangDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
    drawCheckerBoard(GOBANG_BOARD_GRID_MAX, GOBANG_BOARD_GRID_MAX);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGoBangDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CGoBangDlg::drawCheckerBoard(UINT uiRow, UINT uiCol)
{
    CDC * pDC = GetDC();
    CFont fontSet;
    fontSet.CreateFont(120, 0, 0, 0, 700, FALSE, FALSE, 0, ANSI_CHARSET
                       , OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY
                       , DEFAULT_PITCH | FF_SWISS, _T("华文行楷"));
    pDC->SelectObject(&fontSet);

    CRect rect;
    GetClientRect(rect);
    pDC->FillSolidRect(rect, RGB(203, 159, 128));
    //pDC->SetTextColor(RGB(0, 0, 255));
    //pDC->TextOutW(15, 100, _T("五"));
    //pDC->TextOutW(15, 260, _T("子"));
    //pDC->TextOutW(15, 420, _T("棋"));
    //pDC->TextOutW(715, 100, _T("五"));
    //pDC->TextOutW(715, 260, _T("子"));
    //pDC->TextOutW(715, 420, _T("棋"));
    int x = (rect.Width() - MAX_GRID_COUNT * uiCol) / 2 + 20;  //居中
    int y = 40;
    int iWidth = (uiRow - 1) * MAX_GRID_COUNT + x;
    for (UINT i = 0; i < uiRow; i++)
    {
        pDC->MoveTo(x, i * MAX_GRID_COUNT + y);
        pDC->LineTo(iWidth, i * MAX_GRID_COUNT + y);
    }

    int iHeight = (uiCol - 1) * MAX_GRID_COUNT + y;
    for (UINT i = 0; i < uiCol; i++)
    {
        pDC->MoveTo(i * MAX_GRID_COUNT + x, y);
        pDC->LineTo(i * MAX_GRID_COUNT + x, iHeight);
    }
    int m = x + 7 * MAX_GRID_COUNT;
    int n = y + 7 * MAX_GRID_COUNT;
    pDC->Ellipse(m - RADIUS, n - RADIUS, m + RADIUS, n + RADIUS);
    m = x + 3 * MAX_GRID_COUNT;
    n = y + 3 * MAX_GRID_COUNT;
    pDC->Ellipse(m - RADIUS, n - RADIUS, m + RADIUS, n + RADIUS);
    m = x + 11 * MAX_GRID_COUNT;
    n = y + 3 * MAX_GRID_COUNT;
    pDC->Ellipse(m - RADIUS, n - RADIUS, m + RADIUS, n + RADIUS);
    m = x + 3 * MAX_GRID_COUNT;
    n = y + 11 * MAX_GRID_COUNT;
    pDC->Ellipse(m - RADIUS, n - RADIUS, m + RADIUS, n + RADIUS);
    m = x + 11 * MAX_GRID_COUNT;
    n = y + 11 * MAX_GRID_COUNT;
    pDC->Ellipse(m - RADIUS, n - RADIUS, m + RADIUS, n + RADIUS);
}
