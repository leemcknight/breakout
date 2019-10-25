// graphicsDoc.cpp : implementation of the CGraphicsDoc class
//

#include "stdafx.h"
#include "graphics.h"

#include "graphicsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc

IMPLEMENT_DYNCREATE(CGraphicsDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicsDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphicsDoc)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc construction/destruction

CGraphicsDoc::CGraphicsDoc()
{
	// TODO: add one-time construction code here

	
}

CGraphicsDoc::~CGraphicsDoc()
{
}

BOOL CGraphicsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc serialization

void CGraphicsDoc::Serialize(CArchive& ar)
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
// CGraphicsDoc diagnostics

#ifdef _DEBUG
void CGraphicsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc commands


void CGraphicsDoc::OnFileNew() 
{
	// TODO: Add your command handler code here
	
}
