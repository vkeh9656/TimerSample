
// TimerSampleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "TimerSample.h"
#include "TimerSampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTimerSampleDlg 대화 상자



CTimerSampleDlg::CTimerSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMERSAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTimerSampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTimerSampleDlg 메시지 처리기

BOOL CTimerSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CRect r;
	GetClientRect(r);
	m_mem_dc.Create(this, r.Width(), r.Height());

	CClientDC dc(this);
	srand((unsigned int)time(NULL)); // 랜덤 시드 세팅(srand)은 프로그램 시작때 한번만 하면 됨.
	
	for (int i = 0; i < MAX_COUNT; i++)
	{
		m_circleList[i].x = rand() % m_mem_dc.GetWidth(); // w 값을 넘어가지 않도록  0 ~ w-1 (너비)
		m_circleList[i].y = rand() % m_mem_dc.GetHeight(); // h 값을 넘어가지 않도록  0 ~ h-1 (높이)
		m_circleList[i].r = rand() % 40 + 10; // 최소크기 10인 반지름 50 이내의 원 (10~49)
		m_circleList[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	SetTimer(1, 50, NULL); // NULL -> WM_TIMER

	// CircleData m_circleList[MAX_COUNT];

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTimerSampleDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		m_mem_dc.Draw(&dc, 0, 0);
		//dc.BitBlt(0, 0, m_mem_dc.GetWidth(), m_mem_dc.GetHeight(), m_mem_dc.GetDC(), 0, 0, SRCCOPY);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTimerSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimerSampleDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) 
	{
		CDC* p_dc = m_mem_dc.GetDC();
		CRect r;
		GetClientRect(r);

		CircleData* p = m_circleList;
		CBrush fill_brush, * p_old_brush = p_dc->GetCurrentBrush();
		p_dc->FillSolidRect(0, 0, m_mem_dc.GetWidth(), m_mem_dc.GetHeight(), RGB(220, 220, 220));
		for (int i = 0; i < MAX_COUNT; i++)
		{
			p->r--;
			if (p->r == 0)
			{
				p->x = rand() % m_mem_dc.GetWidth();
				p->y = rand() % m_mem_dc.GetHeight();
				p->r = rand() % 40 + 10;
				p->color = RGB(rand() % 256, rand() % 256, rand() % 256);
			}
			fill_brush.CreateSolidBrush(p->color);
			p_dc->SelectObject(&fill_brush);
			p_dc->Ellipse(p->x - p->r, p->y - p->r, p->x + p->r, p->y + p->r);
			fill_brush.DeleteObject();
			
			p++;
		}
		p_dc->SelectObject(p_old_brush);

		Invalidate(FALSE); // WM_PAINT message 발생
	}
	else
	{
		CDialogEx::OnTimer(nIDEvent);
	}

}


void CTimerSampleDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);
}


void CTimerSampleDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_mem_dc.Resize(this, cx, cy);
}
