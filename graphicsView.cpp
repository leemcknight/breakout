/*****************************************

  Simple "Breakout" type game with 
  difficulty levels, Scorekeeper, and 
  lives keeper.


  Written by Lee McKnight
  lee_mcknight@hotmail.com
******************************************/

// graphicsView.cpp : implementation of the CGraphicsView class
//

#include "stdafx.h"
#include "graphics.h"

#include "graphicsDoc.h"
#include "graphicsView.h"
#include "Math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView

IMPLEMENT_DYNCREATE(CGraphicsView, CView)

BEGIN_MESSAGE_MAP(CGraphicsView, CView)
	//{{AFX_MSG_MAP(CGraphicsView)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView construction/destruction

CGraphicsView::CGraphicsView()
{
	// TODO: add construction code here
	bInit = false;
	pGS = new gamestate_t;
	
}

CGraphicsView::~CGraphicsView()
{
	
}

BOOL CGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView drawing

void CGraphicsView::OnDraw(CDC* pDC)
{

	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	

	UpdateWindow();

	CRect rect;

	GetClientRect(&rect);
	pDC->FillRect(rect, &pGameBrush->BkgBrush);

	//
	//update paddle coords...
	//

	pShip->yShip_1 = rect.Height() - 60;
	pShip->yShip_2 = pShip->yShip_1 + 10;
	DrawBlocks();
	DrawScore();
	DrawLives();
	DrawLevel();
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView diagnostics

#ifdef _DEBUG
void CGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsDoc* CGraphicsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsDoc)));
	return (CGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView message handlers

void CGraphicsView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	
	bool	bGoodKey;

	CGraphicsDoc* pDoc = GetDocument();

	bGoodKey = true;

	switch (nChar)
	{
		case VK_LEFT:
			pGS->iAng = 30;
			MoveShip(-20);
			break;
		case VK_RIGHT:
			pGS->iAng = -30;
			MoveShip(20);
			break;
		default:
			bGoodKey = false;
	}

		
}


void CGraphicsView::UpdateWindow(void)
{

	CDC	*pDC = GetDC();
		
	if (!bInit)
		StartGame();

	//
	//draw ship
	//
	pDC->SelectObject(&pGameBrush->ShipBrush);
	pDC->SetBkMode(OPAQUE);
	pDC->Rectangle(pShip->xShip_1, pShip->yShip_1, pShip->xShip_2, pShip->yShip_2);
	
	//
	//draw the ball
	//
	pDC->SelectObject(&pGameBrush->BallBrush);
	pDC->SetBkMode(OPAQUE);
	pDC->Ellipse(pBall->x1, pBall->y1, pBall->x2, pBall->y2);

	pDC->DeleteDC();
		
}


void CGraphicsView::MoveShip(long deltaX)
{
	//remove the old ship	
	ClearArea(pShip->xShip_1, pShip->xShip_2, pShip->yShip_1, pShip->yShip_2);

	//
	//check boundaries
	//
	CRect rect;
	GetClientRect(&rect);
	if (pShip->xShip_1 >= rect.Width())
	{
		pShip->xShip_1 = 6;
		pShip->xShip_2 = 100;
	}

	if (pShip->xShip_1 <= 5)
	{
		pShip->xShip_1 = rect.Width() - 100;
		pShip->xShip_2 = rect.Width();
	}


	//
	//update coordinates
	//
	pShip->xShip_1 += deltaX;
	pShip->xShip_2 += deltaX;

	UpdateWindow();

}

void CGraphicsView::StartGame(void)
{
	
	//
	//init game vars
	//
	pGS->lScore = 0;
	pGS->iLives = 3;
	pGS->bWait = true;
	pGS->iLevel = 1;
	pGS->lSpeed = 10;
	pGS->lBlocksLeft = 0;
	pGS->HitFlags = 0x0;

	//
	//get dims
	//
	int xDim, yDim;
	int iBlockHeight, iBlockWidth;
	CRect rect;

	GetClientRect(&rect);
	xDim = rect.Width();
	yDim = rect.Height();
	iBlockWidth = (int)xDim/(C_XBLOCKS + 1);
	iBlockHeight = (int)((yDim/5)/C_YBLOCKS);

	
	for(int i = 0; i <= C_XBLOCKS; i ++)
	{
		for (int j = 0; j <= C_YBLOCKS; j++)
		{
			aBlocks[i][j] = new block_t;
			aBlocks[i][j]->bExists = true;
			pGS->lBlocksLeft++;

			//
			//X Dims
			//
			aBlocks[i][j]->x1 = (int)(i*iBlockWidth);
			aBlocks[i][j]->x2 = aBlocks[i][j]->x1 + iBlockWidth;

			//
			//Y Dims
			//
			aBlocks[i][j]->y1 = (int)(j*iBlockHeight + 50);
			aBlocks[i][j]->y2 = aBlocks[i][j]->y1 + iBlockHeight;
		}
	}

	

	//init the ball
	pBall = new ball_t;
	pBall->iAng = 90;
	pBall->x1 = (int) xDim/2;
	pBall->x2 = pBall->x1 + 10;
	pBall->y1 = aBlocks[C_XBLOCKS][C_YBLOCKS]->y2;
	pBall->y2 = pBall->y1 + 10;
	pBall->color = RGB(255,0,0);

	//init the ship
	pShip = new ship_t;
	pShip->xShip_1 = xDim/2;
	pShip->xShip_2 = pShip->xShip_1 + 100;
	pShip->yShip_1 = yDim - 60;
	pShip->yShip_2 = pShip->yShip_1 + 10;
	pShip->color = RGB(0,0,255);

	bInit = true;

	InitBrushType();
	DrawLives();
	DrawScore();
	DrawLevel();
	DrawBlocks();

	SetTimer(1,30, NULL);

}


/*===============================
MoveBall()

  This function moves the ball
  frame by frame, all the while
  checking for border hits, 
  paddle hits, and block hits.
================================*/
void CGraphicsView::MoveBall(void)
{
	
	BYTE	tempHF;		//temp HitFlags
	//
	//trig functs
	//
	double dblNewX, dblNewY;
	double pi = 3.14159;
	double dblRad = (pBall->iAng/57.29577);

	dblNewX = (cos(dblRad))*pGS->lSpeed;
	dblNewX = (long) dblNewX;
	dblNewX += pBall->x1;

	dblNewY = (sin(dblRad))*pGS->lSpeed;
	dblNewY = (long) dblNewY;
	dblNewY += pBall->y1;

	//
	//erase the old ball
	//
	
	ClearArea(pBall->x1, pBall->x2, pBall->y1, pBall->y2);

	pBall->x1 = (long)dblNewX;
	pBall->x2 = (long)dblNewX + 10;

	pBall->y1 = (long)dblNewY;
	pBall->y2 = (long)dblNewY + 10;
	

	//
	//change direction for any reason?
	//
	
	if((pBall->x1 >= pShip->xShip_1) &&
		(pBall->x2 <= pShip->xShip_2) &&
		(pBall->y2 >= pShip->yShip_1) &&
		(pBall->y1 <= pShip->yShip_2))
	{
		if (pBall->iAng <= 180)
			pBall->iAng = (360-(pBall->iAng) + pGS->iAng);
	}
	
	//
	//check for block hits, if we're close enough...
	//

	if (pBall->y1 <= aBlocks[0][C_YBLOCKS]->y2)
	{
		pGS->HitFlags = 0x0;

		for (int i = 0; i <= C_XBLOCKS; i++)
		{
			for (int j = 0; j <= C_YBLOCKS; j++)
			{
				
				if ((pBall->x1 >= aBlocks[i][j]->x1) &&
					(pBall->x1 <= aBlocks[i][j]->x2) &&
					(pBall->y1 <= aBlocks[i][j]->y2) &&
					(pBall->y1 >= aBlocks[i][j]->y1) &&
					(aBlocks[i][j]->bExists) &&
					(pBall->iAng >= 180))
				{
					//
					//hit the underside of a block! 
					//
					pGS->HitFlags |= 0x10;		//set current block bit

					tempHF = pGS->HitFlags;
					tempHF &= 0x01;

					if(!tempHF)
					{
						pGS->HitFlags |= 0x01;		//set current block bit
						pBall->iAng = 360 - pBall->iAng;
					}
				}
				else if ((pBall->y1 >= aBlocks[i][j]->y1) &&
						(pBall->y2 <= aBlocks[i][j]->y2) &&
						(pBall->x1 <= aBlocks[i][j]->x2) &&
						(pBall->x2 >= aBlocks[i][j]->x2) &&
						(aBlocks[i][j]->bExists))
				{
					//
					//hit the right side of a block!
					//
					pGS->HitFlags |= 0x10;		//set current block bit
					
					tempHF = pGS->HitFlags;
					tempHF &= 0x01;

					if(!tempHF)
					{
						if(pBall->iAng >= 270)	
							pBall->iAng = 180 + (360 - pBall->iAng);		//up
						else
							pBall->iAng = 180 - pBall->iAng;				//down				
						pGS->HitFlags |= 0x01;	//set pass bit;
					}

				}
				else if ((pBall->y1 >= aBlocks[i][j]->y1) &&
						(pBall->y2 <= aBlocks[i][j]->y2) &&
						(pBall->x2 >= aBlocks[i][j]->x1) &&
						(pBall->x1 <= aBlocks[i][j]->x2) &&
						(aBlocks[i][j]->bExists))
				{
					//
					//hit the left side of a block!
					//
					pGS->HitFlags |= 0x10;
					tempHF = pGS->HitFlags;
					tempHF &= 0x01;
					if (!tempHF)
					{
						if(pBall->iAng >= 180)
							pBall->iAng = 360 - (pBall->iAng - 180);		//up
						else
							pBall->iAng = 180 - pBall->iAng;				//down	
						pGS->HitFlags |= 0x01;	//set pass bit
					}
					
				}

				else if ((pBall->x1 >= aBlocks[i][j]->x1) &&
					(pBall->x2 <= aBlocks[i][j]->x2) &&
					(pBall->y2 >= aBlocks[i][j]->y1) &&
					(pBall->y1 <= aBlocks[i][j]->y1) &&
					(aBlocks[i][j]->bExists))
				{
					//
					//hit the top of a block!
					//
					pGS->HitFlags |= 0x10;
					tempHF = pGS->HitFlags;
					tempHF &= 0x01;

					if(!tempHF)
					{
						pBall->iAng = 360 - pBall->iAng;				
						pGS->HitFlags |= 0x01;
					}
					
				}


				//
				//why, oh why, is this needed?
				//
				tempHF = pGS->HitFlags;
				tempHF &= 0x10;
				//

				if (tempHF)
				{
					//current block hit.
					ClearArea(aBlocks[i][j]->x1, 
								aBlocks[i][j]->x2,
								aBlocks[i][j]->y1,
								aBlocks[i][j]->y2);
					aBlocks[i][j]->bExists = false;
					pGS->lScore += 100;
					DrawScore();
					pGS->lBlocksLeft--;
					if(pGS->lBlocksLeft == 0)
					{
						pGS->iLevel++;
						pGS->lSpeed++;
						StartLevel();
					}	

				}

				pGS->HitFlags &= 0x01;
			}
		}
	}

	//
	//hitting the side?
	//
	CRect rect;
	GetClientRect(&rect);
	
	//
	//left side
	//
	if (pBall->x1 <= 5)
	{
		if(pBall->iAng >= 180)
			pBall->iAng = 360 - (pBall->iAng - 180);		//up
		else
			pBall->iAng = 180 - pBall->iAng;				//down
	}

	//
	//right side
	//
	if (pBall->x2 >= rect.Width())
	{
		
		if(pBall->iAng >= 270)	
			pBall->iAng = 180 + (360 - pBall->iAng);		//up
		else
			pBall->iAng = 180 - pBall->iAng;				//down
	}
	
	//
	//top
	//
	if (pBall->y1 <= 5)
	{
		pBall->iAng = 360 - pBall->iAng;
	}


	//
	//lost ball?
	//
	if (pBall->y2 >= (pShip->yShip_2 + 10))
	{
		KillTimer(1);
		SetTimer(2,500,NULL);
		pGS->iLives--;
		pBall->iAng = 90;
		pBall->x1 = (int) rect.Height()/2;
		pBall->x2 = pBall->x1 + 10;
		pBall->y1 = aBlocks[C_XBLOCKS][C_YBLOCKS]->y2;
		pBall->y2 = pBall->y1 + 10;
		ClearArea(pBall->x1, pBall->x2, pBall->y1, pBall->y2);
		ClearArea(pShip->xShip_1, pShip->xShip_2, pShip->yShip_1, pShip->yShip_2);
		pShip->xShip_1 = rect.Width()/2;
		pShip->xShip_2 = pShip->xShip_1 + 100;
		DrawLives();
		if(pGS->iLives < 0)
		{
			pGS->iLives = 3;
			pGS->lScore = 0;
			pGS->lSpeed = 10;
			StartLevel();
		}
	}
	//
	//update delta RAD
	//
	if (pGS->iAng > 0)
		pGS->iAng--;
	else if (pGS->iAng < 0)
		pGS->iAng++;

	
	UpdateWindow();

}

/*=================================
ClearArea()

erases given rectangular area 
off screen
====================================*/
void CGraphicsView::ClearArea(int x1, int x2, int y1, int y2)
{
	CDC *pDC = GetDC();

	for (int xPoint = x1; xPoint <= x2; xPoint++)
	{
		for (int yPoint = y1; yPoint <= y2; yPoint++)
		{
			pDC->SetPixel(xPoint, yPoint, RGB(0,0,0));
		}
	}

	pDC->DeleteDC();
}


/*==================================
OnTimer()

Timer Event fired for animation
frames

reused in case of game over/new game
====================================*/
void CGraphicsView::OnTimer(UINT nIDEvent) 
{
	
	if (nIDEvent == 1)
		MoveBall();

	if (nIDEvent == 2)
	{
		if (!pGS->bWait)
		{
			KillTimer(2);
			SetTimer(1,30,NULL);
			pGS->bWait = true;
		}
		else {

			pGS->bWait = false;
		}
	}
}

/*============================
DrawLives()

  refreshes the lives on the
  screen
===========================*/
void CGraphicsView::DrawLives()
{
	CDC *pDC = GetDC();
	CString szLives;
	CRect rect;
	CFont	font;

	GetClientRect(&rect);
	szLives.Format(_T("Lives: %i  "), pGS->iLives);
	font.CreatePointFont(150, szLives);
	pDC->SetTextColor(RGB(255,0,0));
	pDC->SetBkColor(RGB(0,0,255));
	pDC->SelectObject(&font);
	pDC->TextOut(400,rect.Height()-25,szLives);

	pDC->DeleteDC();
}

/*============================
DrawScore()
	refreshes the score on the 
	screen
=============================*/
void CGraphicsView::DrawScore()
{
	CDC *pDC = GetDC();
	CRect rect;
	CString szScore;
	CFont	font;

	GetClientRect(&rect);
	rect.Height();
	szScore.Format(_T("Score: %i    "), pGS->lScore);
	font.CreatePointFont(150, szScore);
	pDC->SetTextColor(RGB(255,0,0));
	pDC->SetBkColor(RGB(0,0,255));
	pDC->SelectObject(&font);
	pDC->TextOut(200,rect.Height() - 25, szScore);

	pDC->DeleteDC();

}

/*==============================
DrawLevel()
	refreshes the level on the
	screen
===============================*/
void CGraphicsView::DrawLevel()
{
	CDC *pDC = GetDC();
	CRect rect;
	CString szLevel;
	CFont	font;
	

	GetClientRect(&rect);
	rect.Height();
	szLevel.Format(_T("Level: %i   "), pGS->iLevel);
	font.CreatePointFont(150, szLevel);
	
	pDC->SetBkColor(RGB(0,0,255));
	//pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,0,0));
	pDC->SelectObject(&font);
	pDC->TextOut(10,rect.Height() - 25, szLevel);

	pDC->DeleteDC();
}


/*==============================
StartLevel()
	called for a new level.  
	resets ball position, creates
	new blocks, and resets paddle
	and updates ball speed.
===============================*/
void CGraphicsView::StartLevel()
{
	//
	//refresh the blocks
	//
	for(int i = 0; i <= C_XBLOCKS; i ++)
	{
		for (int j = 0; j <= C_YBLOCKS; j++)
		{
			aBlocks[i][j]->bExists = true;
			pGS->lBlocksLeft++;
		}
	}

	
	DrawBlocks();

	//
	//reposition ball and paddle
	//
	CRect rect;

	GetClientRect(&rect);
	pBall->iAng = 90;
	pBall->x1 = (int) rect.Height()/2;
	pBall->x2 = pBall->x1 + 10;
	pBall->y1 = aBlocks[C_XBLOCKS][C_YBLOCKS]->y2;
	pBall->y2 = pBall->y1 + 10;
	ClearArea(pBall->x1, pBall->x2, pBall->y1, pBall->y2);
	ClearArea(pShip->xShip_1, pShip->xShip_2, pShip->yShip_1, pShip->yShip_2);
	pShip->xShip_1 = rect.Width()/2;
	pShip->xShip_2 = pShip->xShip_1 + 100;


	//
	//update the console
	//
	DrawLevel();
	DrawScore();
	DrawLives();
}

void CGraphicsView::InitBrushType()
{
	pGameBrush = new gamebrush_t;
	
	pGameBrush->BallBrush.CreateSolidBrush(pBall->color);
	pGameBrush->ShipBrush.CreateSolidBrush(pShip->color);		

	pGameBrush->Block1Brush.CreateSolidBrush(RGB(0,0,255));
	pGameBrush->Block2Brush.CreateSolidBrush(RGB(255,0,0));

	pGameBrush->BkgBrush.CreateSolidBrush(RGB(0,0,0));

}

void CGraphicsView::DrawBlocks(void)
{
	//
	//draw blocks
	//

	CDC *pDC = GetDC();
	
		//
	//get dims
	//
	int xDim, yDim;
	int iBlockHeight, iBlockWidth;
	int i,j;
	CRect rect;

	GetClientRect(&rect);
	xDim = rect.Width();
	yDim = rect.Height();
	iBlockWidth = (int)xDim/(C_XBLOCKS + 1);
	iBlockHeight = (int)((yDim/5)/C_YBLOCKS);

	bool bRed = true;

	for(i = 0; i <= C_XBLOCKS; i ++)
	{
		for (j = 0; j <= C_YBLOCKS; j++)
		{
			//
			//X Dims
			//
			aBlocks[i][j]->x1 = (int)(i*iBlockWidth);
			aBlocks[i][j]->x2 = aBlocks[i][j]->x1 + iBlockWidth;

			//
			//Y Dims
			//
			aBlocks[i][j]->y1 = (int)(j*iBlockHeight + 50);
			aBlocks[i][j]->y2 = aBlocks[i][j]->y1 + iBlockHeight;
		}
	}


	for(i = 0; i <= C_XBLOCKS; i ++)
	{
		for(j = 0; j <= C_YBLOCKS; j ++)
		{
			if (aBlocks[i][j]->bExists)
			{
				if (bRed)
					pDC->SelectObject(&pGameBrush->Block1Brush);
				else 
					pDC->SelectObject(&pGameBrush->Block2Brush);
				pDC->SetBkMode(OPAQUE);
				pDC->Rectangle(aBlocks[i][j]->x1, aBlocks[i][j]->y1, aBlocks[i][j]->x2, aBlocks[i][j]->y2);
			}

			bRed = !bRed;
		}
	}

	pDC->DeleteDC();
}

