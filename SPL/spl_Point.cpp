//---------------------------------------------------------------------------
#include <math.h>
#include <assert.h>
#include <malloc.h>
#include <Math.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_Point.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
spl_UByte spl_Global_Dir=spl_Diagonal;
spl_UByte spl_Global_StartDir=spl_Vertical; 
spl_Point spl_Global_StartPoint=splPoint(0,0);
spl_Point spl_Global_k=splPoint(spl_K1[spl_Global_Dir].x,spl_K1[spl_Global_Dir].y);
spl_Point spl_Global_n=splPoint(spl_Global_k.x,-spl_Global_k.y);
//---------------------------------------------------------------------------
// Pixel/Disiem
void spl_GetDeviceResulotion_PPDisiem(HDC hdc,double &XRes,double &YRes)
{
    double XResPixelPerInch=GetDeviceCaps(hdc,LOGPIXELSX);
    double YResPixelPerInch=GetDeviceCaps(hdc,LOGPIXELSY);
    XRes=XResPixelPerInch/spl_DisiemPerInch;
    YRes=YResPixelPerInch/spl_DisiemPerInch;
}
//---------------------------------------------------------------------------
// Pixel/Disiem
void spl_GetBitmapResulotion_PPDisiem(HBITMAP hbmp,double &XRes,double &YRes)
{
    DIBSECTION DIBSection;
    GetObject(hbmp,sizeof(DIBSection),&DIBSection);
    XRes=DIBSection.dsBmih.biXPelsPerMeter/10000.0;
    YRes=DIBSection.dsBmih.biYPelsPerMeter/10000.0;
    if((XRes<=0.0)||(YRes<=0.0))
    {
        HDC hdc=CreateDC("DISPLAY",NULL,NULL,NULL);
        spl_GetDeviceResulotion_PPDisiem(hdc,XRes,YRes);
        DeleteDC(hdc);
    }
}
//---------------------------------------------------------------------------
double spl_Distance(spl_Point *p,spl_Point *p0,spl_Point *k)
{
    return spl_ABS((p->x-p0->x)*k->y-(p->y-p0->y)*k->x); 
}
//---------------------------------------------------------------------------
double spl_Angle(spl_Point *p0,spl_Point *p1,spl_Point *p2)
{
	double Angle = 0.0;
    double X,Y;
    spl_Point V1,V2;
//    spl_PVector(p1,p0,&V1);
	V1.x = p0->x - p1->x;
	V1.y = p0->y - p1->y;
	V2.x = p2->x - p1->x;
	V2.y = p2->y - p1->y;
//    spl_PVector(p1,p2,&V2);
    Y = spl_PCrossVector(&V1,&V2);
    X = spl_PDotVector(&V1,&V2);
    if(X != 0.0)
		Angle = RadToDeg(ArcTan2(Y,X));
    else
    {
		Angle = 90.0*(X > 0.0?+1:-1);
    }
    return Angle;
}
//---------------------------------------------------------------------------
BYTE spl_GetDirection(TPoint *P1,TPoint *P2)
{
    int dx=(P2->x-P1->x);
    int dy=(P2->y-P1->y);
    int Dir=0;
    if(dx==0)
    {
        if(dy==0)
        {
            Dir=8;
        }
        else
        if(dy>0)
        {
            Dir=2;
        }
        else
        {
            Dir=6;
        }
    }
    else
    if(dx>0)
    {
        if(dy==0)
        {
            Dir=0;
        }
        else
        if(dy>0)
        {
            Dir=1;
        }
        else
        {
            Dir=7;
        }
    }
    else
    {
        if(dy==0)
        {
            Dir=4;
        }
        else
        if(dy>0)
        {
            Dir=3;
        }
        else
        {
            Dir=5;
        }
    }
    return Dir;
}
//---------------------------------------------------------------------------
spl_UByte spl_GetDirection(spl_Point *P1,spl_Point *P2)
{
    double dx=(P2->x-P1->x);
    double dy=(P2->y-P1->y);
    spl_UByte Dir=0;
    if(dx==0)
    {
        if(dy==0)
        {
            Dir=8;
            assert(Dir != 8);
        }
        else
        if(dy>0)
        {
            Dir=2;
        }
        else
        {
            Dir=6;
        }
    }
    else
    if(dx>0)
    {
        if(dy==0)
        {
            Dir=0;
        }
        else
        if(dy>0)
        {
            Dir=1;
        }
        else
        {
            Dir=7;
        }
    }
    else
    {
        if(dy==0)
        {
            Dir=4;
        }
        else
        if(dy>0)
        {
            Dir=3;
        }
        else
        {
            Dir=5;
        }
    }
    return Dir;
}
//---------------------------------------------------------------------------
int spl_Compare(const spl_Point *p1,const spl_Point *p2,const spl_Point *k)
{
    spl_Point v;
    int Result;
    spl_PVector(p1,p2,&v);
    Result=spl_PDotVector(&v,k);
    if(Result>0.0) // p1<p2
        return -1;
    else
    if(Result==0.0)// p1==p2
        return 0;
    else // p1>p2
        return +1;
}
//---------------------------------------------------------------------------
bool spl_Intersect(spl_Point *p0,spl_Point *kp,spl_Point *v0,spl_Point *kv,spl_Point *p)
{
    double Delta;
    Delta=kp->y*kv->x-kp->x*kv->y;
    if(Delta==0.0)
        return false;
    double tp;
    tp=(-(v0->x-p0->x)*kv->y+(v0->y-p0->y)*kv->x)/Delta;

    p->x=p0->x+tp*kp->x;
    p->y=p0->y+tp*kp->y;
    return true;
}
//---------------------------------------------------------------------------
bool spl_IntersectSegment(spl_Point *p1,spl_Point *p2,spl_Point *v1,spl_Point *v2,spl_Point *p)
{
    spl_Point Kp,Kv;
    double Lp,Lv;
    spl_PVector(p1,p2,&Kp);
    spl_PNormalizeVector(&Kp,Lp);
    spl_PVector(v1,v2,&Kv);
    spl_PNormalizeVector(&Kv,Lv);

    double Delta;
    Delta=Kp.y*Kv.x-Kp.x*Kv.y;
    if(Delta==0.0)
        return false;
    double tp;
    tp=(-(v1->x-p1->x)*Kv.y+(v1->y-p1->y)*Kv.x)/Delta;

    p->x=p1->x+tp*Kp.x;
    p->y=p1->y+tp*Kp.y;

    if((tp>=0)&&(tp<=Lp))
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------
bool spl_IsSegmentIntersect(spl_Point *p1,spl_Point *p2,spl_Point *v1,spl_Point *v2)
{
    spl_Point Kp,Kv;
    double Lp,Lv;
    spl_PVector(p1,p2,&Kp);
    spl_PNormalizeVector(&Kp,Lp);
    if(Lp<=0.0) return false;
    spl_PVector(v1,v2,&Kv);
    spl_PNormalizeVector(&Kv,Lv);
    if(Lv<=0.0) return false;

    double Delta;
    Delta=Kp.y*Kv.x-Kp.x*Kv.y;
    if(Delta==0.0)  return false;
    double tp,tv;
    tp=(-(v1->x-p1->x)*Kv.y+(v1->y-p1->y)*Kv.x)/Delta;
    tv=(-(v1->x-p1->x)*Kp.y+(v1->y-p1->y)*Kp.x)/Delta;
    return ((tp>=0)&&(tp<=Lp)&&(tv>=0)&&(tv<=Lv));
}
//---------------------------------------------------------------------------
void spl_Rotate(spl_Point *p,double Rot,spl_Point *P)
{
    P->x=p->x*cos(Rot)-p->y*sin(Rot);
    P->y=p->x*sin(Rot)+p->y*cos(Rot);
}
//---------------------------------------------------------------------------
void spl_Projection(spl_Point *P1,spl_Point *P2,spl_Point *P,spl_Point *V)
{
 spl_Point K;
 double L,t;
 spl_PVector(P1,P2,&K);
 spl_PNormalizeVector(&K,L);
 t=(P->x-P1->x)*K.x+(P->y-P1->y)*K.y;
 V->x=P1->x+t*K.x;
 V->y=P1->y+t*K.y;
}
//---------------------------------------------------------------------------
bool spl_ProjectionSegment(spl_Point *P1,spl_Point *P2,spl_Point *P,spl_Point *V)
{
 spl_Point K;
 double L,t;
 spl_PVector(P1,P2,&K);
 spl_PNormalizeVector(&K,L);
 t=(P->x-P1->x)*K.x+(P->y-P1->y)*K.y;
 V->x=P1->x+t*K.x;
 V->y=P1->y+t*K.y;
 if((t>=0)&&(t<=L))
  return true;
 else
  return false;
}
//---------------------------------------------------------------------------
void spl_GetSkeletonPoint(double Step,double E,spl_Point *p1,spl_Point *p2,spl_Point *p3,spl_Point *p)
{
    spl_Point K,V1,V2;
    double Angle,L,X,Y;
    double L1,L2;

    spl_PVector(p2,p1,&V1);
    spl_PVector(p2,p3,&V2);
    X=spl_PDotVector(&V1,&V2);
    Y=spl_PCrossVector(&V1,&V2);
    if(X==0.0f)
    {
        if(Y>=0.0f)
            Angle=spl_PI/2.0f;
        else
            Angle=-spl_PI/2.0f;
    }
    else
        Angle=ArcTan2(Y,X);

    L1=spl_PLenVector(&V1);
    L2=spl_PLenVector(&V2);
    if((L1<=0.0)||(L2<=0.0))
    {
        p->x=p2->x;
        p->y=p2->y;
        return;
    }

    if(L1<=L2)
    {
        spl_Rotate(&V1,Angle/2.0f,&K);
    }
    else
    {
        spl_Rotate(&V2,-Angle/2.0f,&K);
    }
    spl_PNormalizeVector(&K,L);

    if((spl_ABS(Angle-0.0)<=E)||(spl_ABS(Angle-spl_PI)<=E))
    {
        p->x=p2->x+Step*K.x;
        p->y=p2->y+Step*K.y;
    }
    else
    {
        p->x=p2->x+Step*K.x/sin(Angle/2.0f);
        p->y=p2->y+Step*K.y/sin(Angle/2.0f);
    }
}
//---------------------------------------------------------------------------
void spl_ExtrudeBySkeleton(double ExtrudeDistance,spl_UInt PointsCount,spl_Point *pContour,spl_Point *pExtrude)
{
    if(!pContour)   return;
    if(!pExtrude)   return;
    if(PointsCount<=0)  return;
    for(spl_UInt i=1;i<=PointsCount;i++)
    {
        spl_GetSkeletonPoint(ExtrudeDistance,0.0,&pContour[(PointsCount+i-1) % PointsCount],&pContour[(i+0) % PointsCount],&pContour[(i+1) % PointsCount],&pExtrude[(i+0) % PointsCount]);
    }
}
//---------------------------------------------------------------------------
/*
void spl_GetSkeletonPoint(double Step,spl_Point *p1,spl_Point *p2,spl_Point *p3,spl_Point *p)
{
    spl_Point K,V1,V2;
    double Angle,L,X,Y;

    spl_PVector(p2,p1,&V1);
    spl_PVector(p2,p3,&V2);
    X=spl_PDotVector(&V1,&V2);
    Y=spl_PCrossVector(&V1,&V2);
    if(X==0.0f)
    {
        if(Y>=0.0f)
            Angle=spl_PI/2.0f;
        else
            Angle=-spl_PI/2.0f;
    }
    else
        Angle=ArcTan2(Y,X);
    spl_Rotate(&V1,Angle/2.0f,&K);
    spl_PNormalizeVector(&K,L);
    if((Angle==0.0f)||(Angle==spl_PI))
    {
        p->x=p2->x+Step*K.x;
        p->y=p2->y+Step*K.y;
    }
    else
    {
        p->x=p2->x+Step*K.x/sin(Angle/2.0f);
        p->y=p2->y+Step*K.y/sin(Angle/2.0f);
    }
}
*/
//---------------------------------------------------------------------------
//****************
//   2d Library   
//****************
/*
//---------------------------------------------------------------------------
// returns squared length of input vector 	
double V2SquaredLength(spl_Point *a)
//spl_Point *a;
{	return((a->x * a->x)+(a->y * a->y));
	};
	
// returns length of input vector 
double V2Length(spl_Point *a)
//spl_Point *a;
{
	return(sqrt(V2SquaredLength(a)));
	};
	
// negates the input vector and returns it 
spl_Point *V2Negate(spl_Point *v)
//spl_Point *v;
{
	v->x = -v->x;  v->y = -v->y;
	return(v);
	};

// normalizes the input vector and returns it 
spl_Point *V2Normalize(spl_Point *v)
//spl_Point *v;
{
double len = V2Length(v);
	if (len != 0.0) { v->x /= len;  v->y /= len; };
	return(v);
	};


// scales the input vector to the new length and returns it 
spl_Point *V2Scale(spl_Point *v,double newlen)
//spl_Point *v;
//double newlen;
{
double len = V2Length(v);
	if (len != 0.0) { v->x *= newlen/len;   v->y *= newlen/len; };
	return(v);
	};

// return vector sum c = a+b 
spl_Point *V2Add(spl_Point *a,spl_Point * b,spl_Point * c)
//spl_Point *a, *b, *c;
{
	c->x = a->x+b->x;  c->y = a->y+b->y;
	return(c);
	};
	
// return vector difference c = a-b 
spl_Point *V2Sub(spl_Point *a,spl_Point * b,spl_Point * c)
//spl_Point *a, *b, *c;
{
	c->x = a->x-b->x;  c->y = a->y-b->y;
	return(c);
	};

// return the dot product of vectors a and b 
double V2Dot(spl_Point *a,spl_Point * b)
//spl_Point *a, *b;
{
	return((a->x*b->x)+(a->y*b->y));
	};

// linearly interpolate between vectors by an amount alpha 
// and return the resulting vector. 
// When alpha=0, result=lo.  When alpha=1, result=hi. 
spl_Point *V2Lerp(spl_Point *lo,spl_Point * hi,double alpha,spl_Point * result)
//spl_Point *lo, *hi, *result;
//double alpha;
{
	result->x = LERP(alpha, lo->x, hi->x);
	result->y = LERP(alpha, lo->y, hi->y);
	return(result);
	};


// make a linear combination of two vectors and return the result. 
// result = (a * ascl) + (b * bscl) 
spl_Point *V2Combine (spl_Point *a,spl_Point * b,spl_Point * result,double ascl,double bscl)
//spl_Point *a, *b, *result;
//double ascl, bscl;
{
	result->x = (ascl * a->x) + (bscl * b->x);
	result->y = (ascl * a->y) + (bscl * b->y);
	return(result);
	};

// multiply two vectors together component-wise 
spl_Point *V2Mul (spl_Point *a,spl_Point * b,spl_Point * result)
//spl_Point *a, *b, *result;
{
	result->x = a->x * b->x;
	result->y = a->y * b->y;
	return(result);
	};

// return the distance between two points 
double V2DistanceBetween2Points(spl_Point *a,spl_Point * b)
//spl_Point *a, *b;
{
double dx = a->x - b->x;
double dy = a->y - b->y;
	return(sqrt((dx*dx)+(dy*dy)));
	};

// return the vector perpendicular to the input vector a 
spl_Point *V2MakePerpendicular(spl_Point *a,spl_Point * ap)
//spl_Point *a, *ap;
{
	ap->x = -a->y;
	ap->y = a->x;
	return(ap);
	};

// create, initialize, and return a new vector 
spl_Point *V2New(double x,double y)
//double x, y;
{
spl_Point *v = NEWTYPE(spl_Point);
	v->x = x;  v->y = y; 
	return(v);
	};
	

// create, initialize, and return a duplicate vector 
spl_Point *V2Duplicate(spl_Point *a)
//spl_Point *a;
{
spl_Point *v = NEWTYPE(spl_Point);
	v->x = a->x;  v->y = a->y; 
	return(v);
	};
	
// multiply a point by a matrix and return the transformed point 
spl_Point *V2MulPointByMatrix(spl_Point *p,Matrix3 * m)
//spl_Point *p;
//Matrix3 *m;
{
double w;
spl_Point ptmp;
	ptmp.x = (p->x * m->element[0][0]) + 
             (p->y * m->element[1][0]) + m->element[2][0];
	ptmp.y = (p->x * m->element[0][1]) + 
             (p->y * m->element[1][1]) + m->element[2][1];
	w    = (p->x * m->element[0][2]) + 
             (p->y * m->element[1][2]) + m->element[2][2];
	if (w != 0.0) { ptmp.x /= w;  ptmp.y /= w; }
	*p = ptmp;
	return(p);
	};

// multiply together matrices c = ab 
// note that c must not point to either of the input matrices 
Matrix3 *V2MatMul(Matrix3 *a,Matrix3 * b,Matrix3 * c)
//Matrix3 *a, *b, *c;
{
int i, j, k;
	for (i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			c->element[i][j] = 0;
		for (k=0; k<3; k++) c->element[i][j] += 
				a->element[i][k] * b->element[k][j];
			};
		};
	return(c);
	};
*/
//---------------------------------------------------------------------------

