
// TimerSampleDlg.h: 헤더 파일
//

#pragma once

#define MAX_COUNT	100 // 원을 50개까지만 호출하기
struct CircleData
{
	int x, y;	// 중심점
	int r;		// 반지름
	COLORREF color;
};

class SJ_MemDC
{
private:
	CDC m_mem_dc; // 가상으로 메모리에 쓸 DC
	CBitmap m_mem_bmp;
	int m_width, m_height;

public:
	SJ_MemDC()
	{
		m_width = m_height = 0;
	}

	~SJ_MemDC()
	{
		if (m_mem_dc.m_hDC != NULL) 
		{
			m_mem_bmp.DeleteObject();
			m_mem_dc.DeleteDC();
		}
	}

	void Create(CWnd *ap_wnd, int a_width, int a_height)
	{
		CClientDC dc(ap_wnd);

		m_width = a_width;
		m_height = a_height;
		m_mem_dc.CreateCompatibleDC(&dc);
		m_mem_bmp.CreateCompatibleBitmap(&dc, m_width, m_height);
		m_mem_dc.SelectObject(&m_mem_bmp);
	}

	void Resize(CWnd *ap_wnd, int a_width, int a_height)
	{	
		if (a_width != m_width || a_height != m_height)
		{
			if (m_width && m_height)
			{
				m_mem_bmp.DeleteObject();

				m_width = a_width;
				m_height = a_height;

				CClientDC dc(ap_wnd);
				m_mem_bmp.CreateCompatibleBitmap(&dc, m_width, m_height);
				m_mem_dc.SelectObject(&m_mem_bmp);
			}
		}
	}

	inline CDC* GetDC()
	{
		return &m_mem_dc;
	}

	inline int GetWidth()
	{
		return m_width;
	}

	inline int GetHeight()
	{
		return m_height;
	}

	void Draw(CDC* ap_dc, int a_x, int a_y)
	{
		ap_dc->BitBlt(0, 0, m_width, m_height, &m_mem_dc, 0, 0, SRCCOPY);
	}
};

// CTimerSampleDlg 대화 상자
class CTimerSampleDlg : public CDialogEx
{
private:
	CircleData m_circleList[MAX_COUNT];
	
	CImage m_mem_view;
	//SJ_MemDC m_mem_dc;
	//CDC m_mem_dc; // 가상으로 메모리에 쓸 DC
	//CBitmap m_mem_bmp;
	//int m_width =0, m_height =0;

// 생성입니다.
public:
	CTimerSampleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMERSAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
