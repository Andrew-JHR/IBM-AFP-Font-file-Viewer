// DisplayAFPView.cpp : implementation of the CDisplayAFPView class
//

#include "stdafx.h"
#include "DisplayAFP.h"

#include "DisplayAFPDoc.h"
#include "DisplayAFPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPView

IMPLEMENT_DYNCREATE(CDisplayAFPView, CScrollView)

BEGIN_MESSAGE_MAP(CDisplayAFPView, CScrollView)
	//{{AFX_MSG_MAP(CDisplayAFPView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPView construction/destruction

CDisplayAFPView::CDisplayAFPView()
{
	// TODO: add construction code here

}

CDisplayAFPView::~CDisplayAFPView()
{
}

BOOL CDisplayAFPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPView drawing

void CDisplayAFPView::OnDraw(CDC* pDC)
{
	CDisplayAFPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm); // get current font's sizes
	
	int multi,orgX,orgY,coeff=1;
	CString s;
	switch (pDC->GetDeviceCaps(TECHNOLOGY))
	{
		case DT_RASDISPLAY :
			multi = 1;
			orgX = orgY = 0;
			break;
		case DT_RASPRINTER :
			if (pDC->GetDeviceCaps(LOGPIXELSX) < 500)
				multi = 2;
			else
				multi = 3;

			if (pDoc->FontWidth <= 16)	//enlarge the font image within the same box size
				coeff = 2;

			orgX = 200;
			CString szInfo;
			szInfo.Format("File Name  %s",pDoc->AFPFileName);
			pDC->TextOut(orgX,0,szInfo);
			szInfo.Format("Font Width:%d,Height:%d,Total Fonts:%d",
				          pDoc->FontWidth,
						  pDoc->FontHeight,
						  pDoc->FontCount);
			pDC->TextOut(orgX, (tm.tmHeight+tm.tmExternalLeading) , szInfo);
		    orgY = (tm.tmHeight+tm.tmExternalLeading)*2 ;
	}
		
	
	for (int i=0 ; i < Total_Font_Number/10 + 1 ; i++) //depict all horizontal lines
	{
		pDC->MoveTo(orgX , orgY+multi*BoxHeight*i);	// horizontal line start point 
		pDC->LineTo(orgX+multi*BoxWidth*10, orgY+multi*BoxHeight*i); // horizontal line end point
	}

	for (int i = 0 ; i < 11 ; i++)	//depict all vertical lines
	{
		pDC->MoveTo(orgX+multi*BoxWidth*i, orgY);	// vertical line start point
		pDC->LineTo(orgX+multi*BoxWidth*i, orgY+multi*BoxHeight*Total_Font_Number/10); //vertical line end point
	}

	
	FontIndex * pIndx = pDoc->FontDirect ;	// each font's name & index
	BYTE * pBits = pDoc->ResultBits;	// the bitmap array for all fonts


	CBitmap  bitmap;	// create a bitmap for a font's size
	bitmap.CreateBitmap(pDoc->FontWidth,pDoc->FontHeight,1,1,NULL);
	BITMAP bm;	// bitmap structure
	bitmap.GetObject(sizeof(BITMAP),&bm); //a bitmap for each font 
	CDC dcMem;	//create a memory dc
	dcMem.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp =dcMem.SelectObject(&bitmap);


	BYTE * temp = new BYTE [bm.bmHeight * bm.bmWidthBytes] ;

	CFont font, *pOldfont;
	if ( multi > 1)
	{
		if (multi ==3)
			font.CreatePointFont (320, ("Arial"));
		else
			font.CreatePointFont (220, ("Arial"));
		pOldfont = pDC->SelectObject(&font);
	}


	for (int y=0, z=0 ; y < Total_Font_Number/10 ; y++)
	{
		for (int x=0 ; x < 10  && z < pDoc->FontCount ; x++, z++)
		{
			pDC->TextOut(orgX+multi*BoxWidth*x+15*multi,
					     orgY+multi*BoxHeight*y+(multi*BoxHeight-17*multi),
					     pIndx[z].eFontName);

			BYTE * temp1 = temp ;
			BYTE * pBits1 = pBits + (pIndx[z].eFontIndex) * bm.bmHeight * bm.bmWidth/8 ;

			for (int i = 0 ; i < pDoc->FontHeight ; i++ , temp1 += bm.bmWidthBytes)
			{
				BYTE * temp2 =temp1;
				for (int j = 0 ; j < pDoc->FontWidth/8 ; j++ , pBits1++, temp2++)
					*temp2 = *pBits1;	
			} 
			bitmap.SetBitmapBits(bm.bmHeight * bm.bmWidthBytes, temp);

			//move from memory dc to screen dc						
			pDC->StretchBlt(orgX+multi*BoxWidth*x+(multi*BoxWidth-coeff*multi*bm.bmWidth)/2,
						orgY+multi*BoxHeight*y+(multi*BoxHeight-15-coeff*multi*bm.bmHeight)/2,
						coeff*multi*bm.bmWidth,coeff*multi*bm.bmHeight,
						&dcMem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY) ;
			}
	}

	delete [] temp;

	dcMem.SelectObject(pOldBmp); 
	if ( multi > 1)
		pDC->SelectObject(pOldfont);

}		// end of CDisplayAFPView::OnDraw



void CDisplayAFPView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = BoxWidth*10;
	sizeTotal.cy = BoxHeight*Total_Font_Number/10;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPView printing

BOOL CDisplayAFPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);

}

void CDisplayAFPView::OnBeginPrinting(CDC* /*pDC*/ , CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDisplayAFPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPView diagnostics

#ifdef _DEBUG
void CDisplayAFPView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDisplayAFPView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDisplayAFPDoc* CDisplayAFPView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDisplayAFPDoc)));
	return (CDisplayAFPDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPView message handlers
