// graphicsView.h : interface of the CGraphicsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSVIEW_H__8B61C24C_3F0F_11D5_8D61_00B0D07E767D__INCLUDED_)
#define AFX_GRAPHICSVIEW_H__8B61C24C_3F0F_11D5_8D61_00B0D07E767D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "coord.h"


class CGraphicsView : public CView
{
protected: // create from serialization only
	CGraphicsView();
	DECLARE_DYNCREATE(CGraphicsView)

// Attributes
public:
	CGraphicsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicsView();
	void	StartGame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

#endif

private:
	void	UpdateWindow(void);
	void	MoveShip(long deltaX);
	void	MoveBall();
	void	DrawScore();
	void	DrawLives();
	void	DrawLevel();
	void	StartLevel();
	void	DrawBlocks();
	void	ClearArea(int x1, int x2, int y1, int y2);
	void	InitBrushType(void);
	bool	bInit;

	block_t		*aBlocks[C_XBLOCKS+1][C_YBLOCKS+1];
	ball_t		*pBall;
	ship_t		*pShip;
	gamestate_t	*pGS;
	gamebrush_t	*pGameBrush;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicsView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in graphicsView.cpp
inline CGraphicsDoc* CGraphicsView::GetDocument()
   { return (CGraphicsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSVIEW_H__8B61C24C_3F0F_11D5_8D61_00B0D07E767D__INCLUDED_)
