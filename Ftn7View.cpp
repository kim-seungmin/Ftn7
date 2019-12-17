
// Ftn7View.cpp: CFtn7View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Ftn7.h"
#endif

#include "Ftn7Doc.h"
#include "Ftn7View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

SData data;
// CFtn7View

IMPLEMENT_DYNCREATE(CFtn7View, CView)

BEGIN_MESSAGE_MAP(CFtn7View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CFtn7View::On32771)
	ON_MESSAGE(WM_MIN, &CFtn7View::OnMaxFound)
END_MESSAGE_MAP()

// CFtn7View 생성/소멸

CFtn7View::CFtn7View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CFtn7View::~CFtn7View()
{
}

BOOL CFtn7View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CFtn7View 그리기

void CFtn7View::OnDraw(CDC* /*pDC*/)
{
	CFtn7Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CFtn7View 인쇄

BOOL CFtn7View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CFtn7View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CFtn7View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CFtn7View 진단

#ifdef _DEBUG
void CFtn7View::AssertValid() const
{
	CView::AssertValid();
}

void CFtn7View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFtn7Doc* CFtn7View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFtn7Doc)));
	return (CFtn7Doc*)m_pDocument;
}
#endif //_DEBUG


// CFtn7View 메시지 처리기

CWinThread* Thread;
UINT ThreadProcedure(LPVOID pParm);

UINT ThreadProcedure(LPVOID pParam) {
	SData* pData = (SData*)pParam;
	if (pData->array[0] < pData->max)
		pData->max = pData->array[0];
	::PostMessage(pData->NotifyWindow, WM_MIN, 0, 0);
	return 0;
}

void CFtn7View::On32771()
{
	data.array[0] = 1;
	data.array[1] = 2;
	data.max = data.array[0];
	data.NotifyWindow = m_hWnd;
	Thread = AfxBeginThread(ThreadProcedure, &data);

}


LRESULT CFtn7View::OnMaxFound(WPARAM wParam, LPARAM lParam)
{
	CClientDC dc(this);
	CString msg;
	msg.Format(L"%d", data.max);
	dc.TextOut(10,100,msg);
	TerminateThread(Thread, 0);
	return 0;
}
