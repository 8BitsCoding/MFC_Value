
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	srand((unsigned int)time(NULL));
	SetTimer(1, 500, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
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
		CRect r;
		CString str;
		POSITION pos = m_data_list.GetHeadPosition();

		dc.SelectStockObject(DC_BRUSH);
		dc.SetDCBrushColor(RGB(0, 0, 128));
		dc.SetBkColor(RGB(0, 0, 128));
		dc.SetTextColor(RGB(0, 255, 255));

		/*
		// 리스트를 이용하는 방법
		for(int i = 0;pos != NULL; i++) {
			str.Format(L"%d", *(int*)m_data_list.GetNext(pos));
			r.SetRect(10 + i*65, 10, 70+i*65, 40);
			dc.Rectangle(r);
			dc.DrawText(str, r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		*/

		/*
		// 배열을 이용하는 방법 - 1
		for (int i = 0; i < m_data_count; i++) {
			str.Format(L"%d", m_move_data[i]);
			r.SetRect(10 + i * 65, 10, 70 + i * 65, 40);
			dc.Rectangle(r);
			dc.DrawText(str, r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		*/

		/**/
		// 배열을 이용하는 방법 - 2
		for (int i = 0; i < m_data_count; i++) {
			str.Format(L"%d", m_index_data[(i+m_index)%10]);
			r.SetRect(10 + i * 65, 10, 70 + i * 65, 40);
			dc.Rectangle(r);
			dc.DrawText(str, r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		// CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		
		int temp = rand() % 100;
		int *p = new int;
		*p = temp;
		/*
		// 리스트를 이용하는 방법
		m_data_list.AddTail(p);

		if (m_data_list.GetCount() > 10) {
			delete (int*)m_data_list.GetHead();
			m_data_list.RemoveHead();
		}
		*/

		/*
		// 배열을 이용하는 방법 - 1
		if (m_data_count < 10) {
			m_move_data[m_data_count] = temp;
			m_data_count++;
		}
		else {
			//for (int i = 0; i < 9; i++) m_move_data[i] = m_move_data[i + 1];
			memcpy(m_move_data, m_move_data + 1, sizeof(int) * 9);
			m_move_data[9] = temp;
		}
		*/

		// 배열을 이용하는 방법 - 2
		if (m_data_count < 10) {
			m_move_data[m_data_count] = temp;
			m_index_data[m_data_count] = temp;
			m_data_count++;
		}
		else {
			// m_index : 0 -> 0 ... 9
			// m_index : 1 -> 1 ... 8 9 0
			// m_index : 2 -> 2 ... 8 9 0 1
			m_index_data[m_index] = temp;
			m_index = (m_index + 1) % 10;
		}

		Invalidate(FALSE);
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CMFCApplication1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);

	POSITION pos = m_data_list.GetHeadPosition();
	while (pos != NULL) {
		delete (int*)m_data_list.GetNext(pos);
	}
}
