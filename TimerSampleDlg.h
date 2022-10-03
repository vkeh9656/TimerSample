﻿
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

// CTimerSampleDlg 대화 상자
class CTimerSampleDlg : public CDialogEx
{
private:
	CircleData m_circleList[MAX_COUNT];
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
};
