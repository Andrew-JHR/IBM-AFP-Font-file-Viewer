// DisplayAFPDoc.cpp : implementation of the CDisplayAFPDoc class
//

#include "stdafx.h"
#include "DisplayAFP.h"

#include "DisplayAFPDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPDoc

IMPLEMENT_DYNCREATE(CDisplayAFPDoc, CDocument)

BEGIN_MESSAGE_MAP(CDisplayAFPDoc, CDocument)
	//{{AFX_MSG_MAP(CDisplayAFPDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPDoc construction/destruction

CDisplayAFPDoc::CDisplayAFPDoc():FontHeight(0),FontWidth(0),FontCount(0)
{
	// TODO: add one-time construction code here
	ResultBits = NULL; ;	// start addr. of the buffer to keep each font's image bits
}

CDisplayAFPDoc::~CDisplayAFPDoc()
{
	if (ResultBits != NULL)
	{
		delete [] ResultBits;	// return the allocated storage back to the system
		ResultBits = NULL;
	}
}

BOOL CDisplayAFPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPDoc serialization

void CDisplayAFPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPDoc diagnostics

#ifdef _DEBUG
void CDisplayAFPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDisplayAFPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPDoc commands

// Routine to tranlate code from EBCDIC to ASCII
void CDisplayAFPDoc::xcode(BYTE* bufptr, int len)
{
	for (int i=0 ; i < len ; i++)
	{
		*bufptr = b2a[(*bufptr)];
		bufptr++ ;
	}
	*bufptr = '\0';
}

/////////////////////////////////////////////////////////////////////////////

BOOL CDisplayAFPDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	AFPFileName =  lpszPathName ;

	unsigned short int RecLen;
	bool FNIonce = FALSE ;
	bool WidthFound = FALSE;
    BYTE ch[4];

	AFP * in = new AFP;
	BYTE * Result_ptr ;
    
	CFile cAFP(AFPFileName,CFile::modeRead);

	FontCount = 0 ; 

	for ( ; ; )
	{
		cAFP.Read(ch,3);
		if ( ch[0] != 'Z' )
		{
			AfxMessageBox(" Invalid file format ! ") ;
			return FALSE ;
		}

		RecLen = ch[1] * 0x100 + ch[2] ; // get this record's length

		cAFP.Read(in,RecLen-2); // read this record according to the length 

		if (strncmp(in->structure,(const char *)Begin_Font,sizeof(in->structure)) == 0)
		{
//			xcode(in->BFN_name,sizeof(in->BFN_name));
		} 

		if (strncmp(in->structure,(const char *)Font_Remarks,3) == 0)
		{
//			xcode(in->FRMRK,sizeof(in->FRMRK));
		} 
 
		if (strncmp(in->structure,(const char *)Font_Control,sizeof(in->structure)) == 0)
		{
//			unsigned short int pixel = in->FNC_xunit[0] * 0x100 + in->FNC_xunit[1] ;
//			pixel = in->FNC_yunit[0] * 0x100 + in->FNC_yunit[1] ;
		}
		
		if (strncmp(in->structure,(const char *)Font_Descriptor,sizeof(in->structure)) == 0)
		{
//		    unsigned short int maxvsize = in->FND_maxvsz[0] * 0x100 + in->FND_maxvsz[1]; 			 
//			unsigned short int norvsize = in->FND_norvsz[0] * 0x100 + in->FND_norvsz[1]; 			 
//			unsigned short int minvsize = in->FND_minvsz[0] * 0x100 + in->FND_minvsz[1]; 			 
//			unsigned short int maxhsize = in->FND_maxhsz[0] * 0x100 + in->FND_maxhsz[1]; 			 
//			unsigned short int norhsize = in->FND_norhsz[0] * 0x100 + in->FND_norhsz[1]; 			 
//			unsigned short int minhsize = in->FND_minhsz[0] * 0x100 + in->FND_minhsz[1]; 			 
		}

		if (strncmp(in->structure,(const char *)Font_Patterns_Map,sizeof(in->structure)) == 0)
		{
//			FNMentry * FNMP = FNM ;
//			
//			for (int i = 0 ; i < Total_Font_Number ; i++, FNMP++ )
//			{
//				for (int j = 0 ; j < 4 ; j++) 
//				{
//					FNT[i].offset[j] = FNMP->FNMoffset[j] ; 
//				}
//			}
		}

		// get each font's height
		if (strncmp(in->structure,(const char *)Font_Orientation,sizeof(in->structure)) == 0)
		{
			FontHeight = in->FNO_MaxBExt[0] * 0x100 + in->FNO_MaxBExt[1];
		}

		// Read the font index for all fonts
		if (strncmp(in->structure,(const char *)Font_Index,sizeof(in->structure)) == 0)
		{ 
			if ( FNIonce == TRUE )
				continue ;

			FNIentry * FNIP = in->FNI ;
			FontIndex * fx  = FontDirect ;

			for (unsigned int i =0 ; i < (RecLen-8)/sizeof(FNIentry) ; i++, FNIP++)
			{
				if (0 == (FNIP->FNI_size[0] * 0x100 + FNIP->FNI_size[1])) // empty 
					continue ;
				FontCount++; // increase font count
				BYTE tempname[10];
				strncpy((char *)tempname,FNIP->FNI_name,8);
				xcode(tempname,sizeof(tempname));
				tempname[8] = '\0'; // prevent the extra chars from showing
				fx->eFontName  = tempname;
				fx->eFontIndex = (FNIP->FNI_indx[0] * 0x100 + FNIP->FNI_indx[1]);

			//	CString szShow;
			//	szShow.Format("Font Index is %d and Font name is ",fx->eFontIndex);
			//	szShow = szShow + fx->eFontName;			
			//	AfxMessageBox(szShow);
                
				if (WidthFound == FALSE)
				{
					FontWidth = FNIP->FNI_size[0] * 0x100 + FNIP->FNI_size[1] ;
					WidthFound = TRUE;
				}

				fx++;
			}
			
			FNIonce = TRUE ;   // only need to process one Font_Index record, skip the rest

			ResultBits = new BYTE [FontWidth*FontHeight/8*Total_Font_Number];
			Result_ptr = ResultBits;
		}

		// Read in the bit patterns for all fonts
		if (strncmp(in->structure,(const char *)Font_Patterns,sizeof(in->structure)) == 0)
		{
			for (int i=0 ; i < RecLen-8 ; i++)
			{
				Result_ptr[i] = ~ (in->FNG[i]);  // invert the bit value into bitmap format
			} 
			Result_ptr += (RecLen-8) ;					
		}

	
		if (strncmp(in->structure,(const char *)End_Font,sizeof(in->structure)) == 0)
		{
			break;
		}
	} 

	cAFP.Close();

	delete [] in;  // delete input file buffer
	
	return TRUE;
}
