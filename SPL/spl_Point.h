//---------------------------------------------------------------------------
// Unit:    spl_Point.cpp
// Classes: spl_Point,spl_Rect
// Purpose: Define Real Points In Different Sizes, By Changing
//          The double Defines By Your Own Type:
//          Real Types: Single, float, double, ...
// Company: AliSoft
// Address: www.AliSoft.com
// Author:  Ali Abbas
// E-Mail:  a.abbas@netcourrier.com
// Cr-Date: 19/12/2002
// la-Date: 19/12/2002
//---------------------------------------------------------------------------
#ifndef spl_PointH
#define spl_PointH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <windows.hpp>
#include <math.h>
#include <vector.h>
#include "spl_Types.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
//---------------------Usefull Defines---------------------------------------
//---------------------------------------------------------------------------
#define  spl_PDistance2(p1,p2)      (double((p2)->x-(p1)->x)*double((p2)->x-(p1)->x)+double((p2)->y-(p1)->y)*double((p2)->y-(p1)->y))
#define  spl_PDistance(p1,p2)       (sqrt(spl_PDistance2((p1),(p2))))

#define  spl_PVector(p1,p2,v)       (v)->x=(p2)->x-(p1)->x;    \
                                    (v)->y=(p2)->y-(p1)->y;
#define  spl_PVectorXY(x0,y0,v)     (v)->x=(x0), (v)->y=(y0)
#define  spl_PZeroVector(v)         (v)->x=0.0, (v)->y=0.0
#define  spl_PVectorEqual(v1,v2)    (((v1)->x==(v2)->x) && ((v1)->y == (v2)->y))
#define  spl_PAddVector(v1,v2,v)    (v)->x=(v1)->x+(v2)->x, (v)->y=(v1)->y+(v2)->y
#define  spl_PSubVector(v1,v2,v)    (v)->x=(v1)->x-(v2)->x, (v)->y=(v1)->y-(v2)->y
#define  spl_PCrossVector(v1,v2)    (double((v1)->x*(v2)->y)-double((v1)->y*(v2)->x))
#define  spl_PDotVector(v1,v2)      (double((v1)->x*(v2)->x)+double((v1)->y*(v2)->y))
#define  spl_PScaleVector(v,s)      (v)->x*=(s), (v)->y*=(s)
#define  spl_PNormalizeVector(v,n)  ((n)=sqrt(spl_PDotVector((v),(v))), \
								     (n)?((v)->x/=n, (v)->y/=n):0.0)
#define  spl_PLenVector(v)          (sqrt(spl_PDotVector((v),(v))))
#define  spl_PAvgVector(v1,v2,v)    (v)->x=((v1)->x+(v2)->x)*0.5, (v)->y=((v1)->y+(v2)->y)*0.5
//---------------------------------------------------------------------------
class spl_Point
{
public:
    double x;    
    double y;
    spl_Point *pPrev;// Previous Point In Snake Definition
    spl_Point *pNext;// Next Point In Snake Definition
    spl_Point():x(0.0),y(0.0),pPrev(NULL),pNext(NULL){}
    spl_Point(double ax,double ay):x(ax),y(ay),pPrev(NULL),pNext(NULL){}
    spl_Point(POINT& pt):x(pt.x),y(pt.y),pPrev(NULL),pNext(NULL){}
    operator POINT() const
    {
        POINT pt;
        pt.x=x;
        pt.y=y;
        return pt;
    }
    spl_Point &operator =(const spl_Point &P)
    {
        x=P.x;
        y=P.y;
        pPrev=NULL;
        pNext=NULL;
        return *this;
    }
    bool operator ==(const spl_Point &P)
    {
        return ((x==P.x)&&(y==P.y));
    }
    bool operator !=(const spl_Point &P)
    {
        return ((x!=P.x)||(y!=P.y));
    }
    spl_Point operator +(const spl_Point &P)
    {
    	spl_Point p;
    	p.x = x + P.x;
        p.y = y + P.y;
        return p;
    }
    spl_Point operator +=(const spl_Point &P)
    {
    	x += P.x;
        y += P.y;
        return *this;
    }
    spl_Point operator -(const spl_Point &P)
    {
    	spl_Point p;
    	p.x = x - P.x;
        p.y = y - P.y;
        return p;
    }
    spl_Point operator -=(const spl_Point &P)
    {
    	x -= P.x;
        y -= P.y;
        return *this;
    }
    spl_Point operator ^(const double &d)
    {
    	spl_Point p;
    	p.x = x * d;
        p.y = y * d;
        return p;
    }
    spl_Point operator ^=(const double &d)
    {
    	x *= d;
        y *= d;
        return *this;
    }
    double operator *(const spl_Point &P)
    {
        return ((x * P.x) + (y * P.y));
    }
    bool operator <(const spl_Point &P)
    {
        return ((x+spl_MaxImageWidth*y)<(P.x+spl_MaxImageWidth*P.y));// ZigZag Algorithm
    }
    bool operator >(const spl_Point &P)
    {
        return ((x+spl_MaxImageWidth*y)>(P.x+spl_MaxImageWidth*P.y));// ZigZag Algorithm
    }
};
//---------------------------------------------------------------------------
spl_Point splPoint(double x,double y)
{
    spl_Point p(x,y);
//    spl_Point p;
//    p.x=x;
//    p.y=y;
    return p;
}
//---------------------------------------------------------------------------
const spl_Point spl_K1[8]= {
                            splPoint(+1,00),// 0
                            splPoint(+spl_sqrt1_2,+spl_sqrt1_2),// 1
                            splPoint(00,+1),// 2
                            splPoint(-spl_sqrt1_2,+spl_sqrt1_2),// 3
                            splPoint(-1,00),// 4
                            splPoint(-spl_sqrt1_2,-spl_sqrt1_2),// 5
                            splPoint(00,-1),// 6
                            splPoint(+spl_sqrt1_2,-spl_sqrt1_2),// 7
                        };
//---------------------------------------------------------------------------
// Directions
//---------------------------------------------------------------------------
#define     spl_Horizontal      ((spl_UByte)0)
#define     spl_Diagonal        ((spl_UByte)1)
#define     spl_Vertical        ((spl_UByte)2)
//---------------------------------------------------------------------------
extern spl_UByte spl_Global_Dir;
extern spl_UByte spl_Global_StartDir;
extern spl_Point spl_Global_StartPoint;
extern spl_Point spl_Global_k;
extern spl_Point spl_Global_n;
//---------------------------------------------------------------------------
class spl_Rect
{
public:
    double left;
    double top;
    double right;
    double bottom;
    spl_Rect():left(0),top(0),right(0),bottom(0){}
    spl_Rect(const spl_Point& TL,const spl_Point& BR):
        left(TL.x),top(TL.y),right(BR.x),bottom(BR.y){}
    spl_Rect(const double &l,const double &t,const double &r,const double &b):
        left(l),top(t),right(r),bottom(b){}
    spl_Rect(RECT& r):left(r.left),top(r.top),right(r.right),bottom(r.bottom){}
    spl_Rect(spl_Rect& r):left(r.left),top(r.top),right(r.right),bottom(r.bottom){}
    double Width() const {return (right-left);}
    double Height() const {return (bottom-top);}
    bool operator ==(const spl_Rect& rc) const
    {
        return left==rc.left && top==rc.top &&
                right==rc.right && bottom==rc.bottom;
    }
    bool operator !=(const spl_Rect& rc)  const
    {
        return !(rc==*this);
    }
    operator RECT() const
    {
        RECT r;
        r.left=left;
        r.top=top;
        r.right=right;
        r.bottom=bottom;
        return r;
    }
    bool PointInIt(spl_Point &p)
    {
		return ((p.x >= left)&&(p.x <= right)&&(p.y >= top)&&(p.y <= bottom));
    }
};
//---------------------------------------------------------------------------
spl_Rect splRect(double left,double top,double right,double bottom)
{
 	spl_Rect r(left,top,right,bottom);
    return r;
}
//---------------------------------------------------------------------------
// Pixel/Disiem
void spl_GetDeviceResulotion_PPDisiem(HDC hdc,double &XRes,double &YRes);
void spl_GetBitmapResulotion_PPDisiem(HBITMAP hbmp,double &XRes,double &YRes);
//---------------------------------------------------------------------------
BYTE spl_GetDirection(TPoint *P1,TPoint *P2);
spl_UByte spl_GetDirection(spl_Point *P1,spl_Point *P2);
double spl_Distance(spl_Point *p,spl_Point *p0,spl_Point *k);
int spl_Compare(const spl_Point *p1,const spl_Point *p2,const spl_Point *k);
bool spl_Intersect(spl_Point *p0,spl_Point *kp,spl_Point *v0,spl_Point *kv,spl_Point *p);
bool spl_IntersectSegment(spl_Point *p1,spl_Point *p2,spl_Point *v1,spl_Point *v2,spl_Point *p);
bool spl_IsSegmentIntersect(spl_Point *p1,spl_Point *p2,spl_Point *v1,spl_Point *v2);
void spl_Rotate(spl_Point *p,double Rot,spl_Point *P);
void spl_GetSkeletonPoint(double Step,double E,spl_Point *p1,spl_Point *p2,spl_Point *p3,spl_Point *p);
void spl_Projection(spl_Point *P1,spl_Point *P2,spl_Point *P,spl_Point *V);
bool spl_ProjectionSegment(spl_Point *P1,spl_Point *P2,spl_Point *P,spl_Point *V);
void spl_ExtrudeBySkeleton(double ExtrudeDistance,spl_UInt PointsCount,spl_Point *pContour,spl_Point *pExtrude);

// Calculate the angle between p1p0 and p1p2 in degrees
double spl_Angle(spl_Point *p0,spl_Point *p1,spl_Point *p2);
//---------------------------------------------------------------------------
class spl_BoundingBox
{
public:
    spl_Point k;// Direction
    spl_Point n;// Perpendecular Direction
    spl_Point left;
    spl_Point right;
    spl_Point top;
    spl_Point bottom;

    spl_Point NW;// North West
    spl_Point NE;// North East
    spl_Point SW;// South West
    spl_Point SE;// South East

    spl_BoundingBox(){}
    spl_BoundingBox(const spl_Point &ak,const spl_Point &p):k(ak),left(p),right(p),top(p),bottom(p)
    {
        n.x=-k.y;
        n.y=k.x;
    }
    void Init(const spl_Point &ak,const spl_Point &p)
    {
        k=ak;
        n.x=-k.y;
        n.y=k.x;
        left=right=top=bottom=p;
    }
    void Add(spl_Point &p)
    {
        if(spl_Compare(&p,&left,&k)<0)      left=p;
        if(spl_Compare(&p,&top,&n)<0)       top=p;
        if(spl_Compare(&p,&right,&k)>=0)    right=p;
        if(spl_Compare(&p,&bottom,&n)>=0)   bottom=p;
    }
    void Update()
    {
        // NW: (left+t*n) ^ (top+t*k)
        spl_Intersect(&left,&n,&top,&k,&NW);
        // NE: (right+t*n) ^ (top+t*k)
        spl_Intersect(&right,&n,&top,&k,&NE);
        // SW: (left+t*n) ^ (bottom+t*k)
        spl_Intersect(&left,&n,&bottom,&k,&SW);
        // SE: (right+t*n) ^ (bottom+t*k)
        spl_Intersect(&right,&n,&bottom,&k,&SE);
    }
};
//---------------------------------------------------------------------------
struct spl_Scale
{
    double Ax,Bx;
    double Ay,By;
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
typedef struct Matrix3Struct {	/* 3-by-3 matrix */
	double element[3][3];
	} Matrix3;
//---------------------------------------------------------------------------
//********************
// one-argument macros
//********************
/*
// absolute value of a 
#define ABS(a)		(((a)<0) ? -(a) : (a))

// round a to nearest integer towards 0
#define FLOOR(a)		((a)>0 ? (int)(a) : -(int)(-a))

// round a to nearest integer away from 0
#define CEILING(a) \
((a)==(int)(a) ? (a) : (a)>0 ? 1+(int)(a) : -(1+(int)(-a)))

// round a to nearest int
#define ROUND(a)	((a)>0 ? (int)(a+0.5) : -(int)(0.5-a))

// take sign of a, either -1, 0, or 1 
#define ZSGN(a)		(((a)<0) ? -1 : (a)>0 ? 1 : 0)	

// take binary sign of a, either -1, or 1 if >= 0 
#define SGN(a)		(((a)<0) ? -1 : 0)

// shout if something that should be true isn't 
#define ASSERT(x) \
if (!(x)) fprintf(stderr," Assert failed: x\n");

// square a 
#define SQR(a)		((a)*(a))	


///********************
// two-argument macros 
///********************

// find minimum of a and b
#define MIN(a,b)	(((a)<(b))?(a):(b))	

// find maximum of a and b 
#define MAX(a,b)	(((a)>(b))?(a):(b))	

// swap a and b (see Gem by Wyvill) 
#define SWAP(a,b)	{ a^=b; b^=a; a^=b; }

// linear interpolation from l (when a=0) to h (when a=1)
// (equal to (a*h)+((1-a)*l) 
#define LERP(a,l,h)	((l)+(((h)-(l))*(a)))

// clamp the input to the specified range
#define CLAMP(v,l,h)	((v)<(l) ? (l) : (v) > (h) ? (h) : v)
//---------------------------------------------------------------------------

//**************************
// memory allocation macros 
//**************************

// create a new instance of a structure (see Gem by Hultquist) 
#define NEWSTRUCT(x)	(struct x *)(malloc((unsigned)sizeof(struct x)))

// create a new instance of a type
#define NEWTYPE(x)	(x *)(malloc((unsigned)sizeof(x)))


//******************
// useful constants 
//******************

#define PI		3.141592	// the venerable pi 
#define PITIMES2	6.283185	// 2 * pi 
#define PIOVER2		1.570796	// pi / 2 
#define E		2.718282	// the venerable e 
#define SQRT2		1.414214	// sqrt(2) 
#define SQRT3		1.732051	// sqrt(3) 
#define GOLDEN		1.618034	// the golden ratio 
#define DTOR		0.017453	// convert degrees to radians 
#define RTOD		57.29578	// convert radians to degrees 


//**********
// booleans 
//**********
#define TRUE		1
#define FALSE		0
#define ON		1
#define OFF 		0
//typedef int boolean;			// boolean data type 
//typedef boolean flag;			// flag data type 
typedef bool flag;			// flag data type 
//---------------------------------------------------------------------------
double V2SquaredLength(spl_Point *a);
double V2Length(spl_Point *a);
spl_Point *V2Negate(spl_Point *v);
spl_Point *V2Normalize(spl_Point *v);
spl_Point *V2Scale(spl_Point *v,double newlen);
spl_Point *V2Add(spl_Point *a,spl_Point * b,spl_Point * c);
spl_Point *V2Sub(spl_Point *a,spl_Point * b,spl_Point * c);
double V2Dot(spl_Point *a,spl_Point * b);
spl_Point *V2Lerp(spl_Point *lo,spl_Point * hi,double alpha,spl_Point * result);
spl_Point *V2Combine (spl_Point *a,spl_Point * b,spl_Point * result,double ascl,double bscl);
spl_Point *V2Mul (spl_Point *a,spl_Point * b,spl_Point * result);
double V2DistanceBetween2Points(spl_Point *a,spl_Point * b);
spl_Point *V2MakePerpendicular(spl_Point *a,spl_Point * ap);
spl_Point *V2New(double x,double y);
spl_Point *V2Duplicate(spl_Point *a);
spl_Point *V2MulPointByMatrix(spl_Point *p,Matrix3 * m);
Matrix3 *V2MatMul(Matrix3 *a,Matrix3 * b,Matrix3 * c);
*/
//---------------------------------------------------------------------------
#endif
