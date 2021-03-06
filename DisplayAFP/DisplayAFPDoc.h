// DisplayAFPDoc.h : interface of the CDisplayAFPDoc class
//
/////////////////////////////////////////////////////////////////////////////
#define Total_Font_Number  190

const   BYTE b2a[256] = {	                //EBCDIC to ASCII 
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,	//00 - 07
		0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,	//08 - 0f
		0x10,0x11,0x12,0x13,0x14,0x0A,0x16,0x17,	//10 - 17
		0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,	//18 - 1f
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//20 - 27
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//28 - 2f
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//30 - 37
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//38 - 3f
		0x20,0x5B,0x5C,0x5D,0x5E,0x60,0x7B,0x7D,	//40 - 47
		0x7E,0x20,0x20,0x2E,0x3C,0x28,0x2B,0x7C,	//48 - 48
		0x26,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//50 - 57
		0x20,0x20,0x21,0x24,0x2A,0x29,0x3B,0x20,	//58 - 5f
		0x2D,0x2F,0x20,0x20,0x20,0x20,0x20,0x20,	//60 - 67
		0x20,0x20,0x20,0x2C,0x25,0x5F,0x3E,0x3F,	//68 - 6f
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//70 - 77
		0x20,0x20,0x3A,0x23,0x40,0x27,0x3D,0x22,	//78 - 7f
		0x20,0x61,0x62,0x63,0x64,0x65,0x66,0x67,	//80 - 87
		0x68,0x69,0x20,0x20,0x20,0x20,0x20,0x20,	//88 - 8f
		0x20,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,	//90 - 97
		0x71,0x72,0x20,0x20,0x20,0x20,0x20,0x20,	//98 - 9f
		0x20,0x20,0x73,0x74,0x75,0x76,0x77,0x78,	//a0 - a7
		0x79,0x7A,0x20,0x20,0x20,0x20,0x20,0x20,	//a8 - af
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//b0 - b7
		0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,	//b8 - bf
		0x20,0x41,0x42,0x43,0x44,0x45,0x46,0x47,	//c0 - c7
		0x48,0x49,0x20,0x20,0x20,0x20,0x20,0x20,	//c8 - cf
		0x20,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,	//d0 - d7  
		0x51,0x52,0x20,0x20,0x20,0x20,0x20,0x20,	//d8 - df
		0x20,0x20,0x53,0x54,0x55,0x56,0x57,0x58,	//e0 - e7
		0x59,0x5A,0x20,0x20,0x20,0x20,0x20,0x20,	//e8 - ef
		0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,	//f0 - f7
		0x38,0x39,0x20,0x20,0x20,0x20,0x20,0x20 };	//f8 - ff

const BYTE Begin_Font[3]        = {0xd3,0xa8,0x89};
const BYTE Font_Remarks[3]      = {0xd3,0xee,0xee};
const BYTE Font_Descriptor[3]   = {0xd3,0xa6,0x89}; 
const BYTE Font_Control[3]      = {0xd3,0xa7,0x89}; 
const BYTE Font_Patterns_Map[3] = {0xd3,0xa2,0x89}; 
const BYTE Font_Orientation[3]  = {0xd3,0xae,0x89};
const BYTE Font_Position[3]     = {0xd3,0xac,0x89};
const BYTE Font_Index[3]        = {0xd3,0x8c,0x89}; 
const BYTE Font_Patterns[3]     = {0xd3,0xee,0x89};
const BYTE End_Font[3]          = {0xd3,0xa9,0x89};

struct  FNMentry
{
	BYTE boxwidth[2];
	BYTE boxheight[2];
	BYTE FNMoffset[4];
};

struct  FNIentry    //Font  Index
{
	char FNI_name[8];
	BYTE FNI_size[2];
	BYTE FNI_skip[6];
	BYTE FNI_indx[2];
	BYTE FNI_rest[10];
};

// AFP font file's  map	
typedef struct AFPtag
	{
		char structure[3];
		BYTE rec_seq[3];
		union
		{
			struct
			{
				BYTE BFN_name[10];
			};
			struct
			{
				BYTE FRMRK[80];
			};
			struct
			{
				char FNC_header[6];
				BYTE FNC_xunit[2];
				BYTE FNC_yunit[2];
			};
			struct      //Font Descriptor
			{
				char FND_facetype[32];
				BYTE FND_weight[1];
				BYTE FND_width[1];
				BYTE FND_maxvsz[2];
				BYTE FND_norvsz[2];
				BYTE FND_minvsz[2];
				BYTE FND_maxhsz[2];
				BYTE FND_norhsz[2];
				BYTE FND_minhsz[2];
			};
			FNMentry FNM[Total_Font_Number]; 
			struct    //Font Orientation
			{
				BYTE FNO_sp[4];
				BYTE FNO_MaxBOset[2];
				BYTE FNO_MaxCharInc[2];
				BYTE FNO_SpCharInc[2];
				BYTE FNO_MaxBExt[2];
			};
			FNIentry FNI[Total_Font_Number];
			BYTE FNG[12298];             // Font patterns record
		};
	} AFP ;
//AFP font file map

typedef struct FontIndextag
{
	CString eFontName;
	int		eFontIndex;
} FontIndex ;

/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPLAYAFPDOC_H__C0B85B3E_1275_11D7_88F9_00055D51214C__INCLUDED_)
#define AFX_DISPLAYAFPDOC_H__C0B85B3E_1275_11D7_88F9_00055D51214C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDisplayAFPDoc : public CDocument
{
	void xcode(BYTE* ,int) ;

protected: // create from serialization only
	CDisplayAFPDoc();
	DECLARE_DYNCREATE(CDisplayAFPDoc)

// Attributes
public:
	CString AFPFileName ; // the AFP font file's filename
	int FontHeight;		// image height
	int FontWidth;		// image width
	FontIndex FontDirect[Total_Font_Number] ; // buffer to keep each font's name & index
	BYTE * ResultBits ;	// start addr. of the buffer to keep each font's image bits
	short int FontCount ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayAFPDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDisplayAFPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayAFPDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYAFPDOC_H__C0B85B3E_1275_11D7_88F9_00055D51214C__INCLUDED_)
