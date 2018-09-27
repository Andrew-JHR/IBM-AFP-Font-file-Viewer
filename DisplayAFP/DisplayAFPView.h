// DisplayAFPView.h : interface of the CDisplayAFPView class
//
/////////////////////////////////////////////////////////////////////////////

#define BoxWidth  100	//the box for each character to display
#define BoxHeight 100	//the box for each character to display

#if !defined(AFX_DISPLAYAFPVIEW_H__C0B85B40_1275_11D7_88F9_00055D51214C__INCLUDED_)
#define AFX_DISPLAYAFPVIEW_H__C0B85B40_1275_11D7_88F9_00055D51214C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDisplayAFPView : public CScrollView
{
protected: // create from serialization only
	CDisplayAFPView();
	DECLARE_DYNCREATE(CDisplayAFPView)

// Attributes
public:
	CDisplayAFPDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayAFPView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDisplayAFPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayAFPView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DisplayAFPView.cpp
inline CDisplayAFPDoc* CDisplayAFPView::GetDocument()
   { return (CDisplayAFPDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYAFPVIEW_H__C0B85B40_1275_11D7_88F9_00055D51214C__INCLUDED_)
