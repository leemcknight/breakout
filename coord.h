//
//coord.h
//

#define	C_XBLOCKS	10
#define	C_YBLOCKS	5

//
//block_t
//
typedef struct
{
	long	x1;
	long	x2;

	long	y1;
	long	y2;

	bool	bExists;
} block_t;



//
//ball_t
//
typedef struct
{
	long		x1;
	long		x2;

	long		y1;
	long		y2;

	double		iAng;

	COLORREF	color;

} ball_t;


//
//ship_t
//

typedef struct
{
	long		xShip_1;
	long		xShip_2;

	long		yShip_1;
	long		yShip_2;

	COLORREF	color;

} ship_t;


//
//gamestate_t
//
typedef struct
{
	int				iLives;
	unsigned long	lScore;
	int				iAng;
	bool			bWait;
	short			iLevel;
	long			lSpeed;
	long			lBlocksLeft;
	BYTE			HitFlags;

} gamestate_t;

//
//gamebrush_t
//
typedef struct
{
	CBrush			ShipBrush;
	CBrush			BallBrush;
	CBrush			Block1Brush;
	CBrush			Block2Brush;
	CBrush			BkgBrush;

} gamebrush_t;