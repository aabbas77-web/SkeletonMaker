//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_ColorQuantizer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Byte spl_ColorsCount=0;
//---------------------------------------------------------------------------
DWORD spl_QuantizedColors[256];
//---------------------------------------------------------------------------
Byte  spl_QuantizedPalette[768];
//---------------------------------------------------------------------------
#define BOX   33
//---------------------------------------------------------------------------
struct box {
    int             r0;         // min value, exclusive 
    int             r1;         // max value, inclusive 
    int             g0;
    int             g1;
    int             b0;
    int             b1;
    int             vol;
};
//---------------------------------------------------------------------------
// Histogram is in elements 1..HISTSIZE along each axis,
//  element 0 is for base or marginal value.
//  NB: these must start out 0!	
// build 3-D color histogram of counts, r/g/b, c^2 
static void Hist3d(long *, long *, long *, long *, float *);
//---------------------------------------------------------------------------
// We now convert histogram into moments so that we can rapidly calculate
//   the sums of the above quantities over any desired box. 
static void Momt3d(long *, long *, long *, long *, float *);
//---------------------------------------------------------------------------
static long Vol(struct box *, long [BOX][BOX][BOX]);
//---------------------------------------------------------------------------
static long Bottom(struct box *, unsigned char , long [BOX][BOX][BOX]);
//---------------------------------------------------------------------------
static long Top(struct box * , unsigned char , int , long [BOX][BOX][BOX]);
//---------------------------------------------------------------------------
static float Var(struct box *);
//---------------------------------------------------------------------------
static float Maximize(struct box *,unsigned char,int,int,int *,long,long ,long ,long);
//---------------------------------------------------------------------------
static int   Cut(struct box *, struct box *);
//---------------------------------------------------------------------------
static void  Mark(struct box *, int, unsigned char *);
//---------------------------------------------------------------------------
#define MAXCOLOR	256
#define RED     	2
#define	GREEN		1
#define BLUE		0
//---------------------------------------------------------------------------
// Histogram is in elements 1..HISTSIZE along each axis,
//  element 0 is for base or marginal value.
//  NB: these must start out 0!
long    wt[BOX][BOX][BOX],
		mr[BOX][BOX][BOX],
		mg[BOX][BOX][BOX],
		mb[BOX][BOX][BOX];
float   m2[BOX][BOX][BOX];

int     ImageSize;           // image size 
int     PalSize;             // color look-up table size 

unsigned short  *Qadd;          // *must* be unsigned?
spl_Image 	*TrueColorPic;
//---------------------------------------------------------------------------
// build 3-D color histogram of counts, r/g/b, c^2 
static void Hist3d(long *vwt, long *vmr, long *vmg, long *vmb, float *m_2)
{
    int    ind,
		    r,
		    g,
		    b;
    int     inr,
		    ing,
		    inb,
		    table[256];

    for (int i = 0; i < 256; ++i)
		table[i] = i * i;

    int W=TrueColorPic->Width;
    int H=TrueColorPic->Height;
    Byte *pData;
    int i=0;
    for(int y=0;y<H;y++)
    {
        pData=TrueColorPic->ppLines[y];
        for(int x=0;x<W;x++)
        {
            b=*pData;
            pData++;
            g=*pData;
            pData++;
            r=*pData;
            pData++;

            inr = (r >> 3) + 1;
            ing = (g >> 3) + 1;
	        inb = (b >> 3) + 1;
	        Qadd[i] = ind = (inr << 10) + (inr << 6) + inr + (ing << 5) + ing + inb;
            i++;
	        // [inr][ing][inb]
	        ++vwt[ind];
	        vmr[ind] += r;
	        vmg[ind] += g;
	        vmb[ind] += b;
	        m_2[ind] += (float) (table[r] + table[g] + table[b]);
        }
    }
}
//---------------------------------------------------------------------------
// We now convert histogram into moments so that we can rapidly calculate
//   the sums of the above quantities over any desired box. 
static void Momt3d(long *vwt, long *vmr, long *vmg, long *vmb, float *m_2)
{
    unsigned short	 ind1,
					 ind2;
    unsigned char	 i,
					 r,
					 g,
					 b;
    long    line,
			line_r,
			line_g,
			line_b,
			area[BOX],
			area_r[BOX],
			area_g[BOX],
			area_b[BOX];
    float   line2,
		    area2[BOX];

    for (r = 1; r <= 32; ++r) {
		for (i = 0; i <= 32; ++i)
			area2[i] = float(area[i] = area_r[i] = area_g[i] = area_b[i] = 0L);
		for (g = 1; g <= 32; ++g) {
			line2 =  float( line = line_r = line_g = line_b = 0L);
			for (b = 1; b <= 32; ++b) {
				ind1 = (r << 10) + (r << 6) + r + (g << 5) + g + b;
				// [r][g][b] 
				line += vwt[ind1];
				line_r += vmr[ind1];
				line_g += vmg[ind1];
				line_b += vmb[ind1];
				line2 += m_2[ind1];
				area[b] += line;
				area_r[b] += line_r;
				area_g[b] += line_g;
				area_b[b] += line_b;
				area2[b] += line2;
				ind2 = ind1 - 1089; // [r-1][g][b] 
				vwt[ind1] = vwt[ind2] + area[b];
				vmr[ind1] = vmr[ind2] + area_r[b];
				vmg[ind1] = vmg[ind2] + area_g[b];
				vmb[ind1] = vmb[ind2] + area_b[b];
				m_2[ind1] = m_2[ind2] + area2[b];
			}
		}
    }
}
//---------------------------------------------------------------------------
static long Vol(struct box * cube, long mmt[BOX][BOX][BOX])
{
    return (mmt[cube->r1][cube->g1][cube->b1]
		    - mmt[cube->r1][cube->g1][cube->b0]
		    - mmt[cube->r1][cube->g0][cube->b1]
		    + mmt[cube->r1][cube->g0][cube->b0]
			- mmt[cube->r0][cube->g1][cube->b1]
		    + mmt[cube->r0][cube->g1][cube->b0]
		    + mmt[cube->r0][cube->g0][cube->b1]
			- mmt[cube->r0][cube->g0][cube->b0]);
}
//---------------------------------------------------------------------------
static long Bottom(struct box * cube, unsigned char dir, long mmt[BOX][BOX][BOX])
{
    switch (dir) {
		case RED:
			return (-mmt[cube->r0][cube->g1][cube->b1]
				+ mmt[cube->r0][cube->g1][cube->b0]
				+ mmt[cube->r0][cube->g0][cube->b1]
				- mmt[cube->r0][cube->g0][cube->b0]);
		case GREEN:
			return (-mmt[cube->r1][cube->g0][cube->b1]
				+ mmt[cube->r1][cube->g0][cube->b0]
				+ mmt[cube->r0][cube->g0][cube->b1]
				- mmt[cube->r0][cube->g0][cube->b0]);
		case BLUE:
			return (-mmt[cube->r1][cube->g1][cube->b0]
				+ mmt[cube->r1][cube->g0][cube->b0]
				+ mmt[cube->r0][cube->g1][cube->b0]
				- mmt[cube->r0][cube->g0][cube->b0]);
    }
    return 0;
}
//---------------------------------------------------------------------------
static long Top(struct box * cube, unsigned char dir, int pos, long mmt[BOX][BOX][BOX])
{
    switch (dir) {
		case RED:
			return (mmt[pos][cube->g1][cube->b1]
				- mmt[pos][cube->g1][cube->b0]
				- mmt[pos][cube->g0][cube->b1]
				+ mmt[pos][cube->g0][cube->b0]);
		case GREEN:
			return (mmt[cube->r1][pos][cube->b1]
				- mmt[cube->r1][pos][cube->b0]
				- mmt[cube->r0][pos][cube->b1]
				+ mmt[cube->r0][pos][cube->b0]);
		case BLUE:
			return (mmt[cube->r1][cube->g1][pos]
				- mmt[cube->r1][cube->g0][pos]
				- mmt[cube->r0][cube->g1][pos]
				+ mmt[cube->r0][cube->g0][pos]);
    }
    return 0;
}
//---------------------------------------------------------------------------
static float Var(struct box * cube)
{
    float   dr,
		    dg,
            db,
		    xx;

    dr = float (Vol(cube, mr));
    dg = float (Vol(cube, mg));
    db = float (Vol(cube, mb));
    xx = m2[cube->r1][cube->g1][cube->b1]
		- m2[cube->r1][cube->g1][cube->b0]
		- m2[cube->r1][cube->g0][cube->b1]
		+ m2[cube->r1][cube->g0][cube->b0]
		- m2[cube->r0][cube->g1][cube->b1]
		+ m2[cube->r0][cube->g1][cube->b0]
		+ m2[cube->r0][cube->g0][cube->b1]
		- m2[cube->r0][cube->g0][cube->b0];

    return (xx - (dr * dr + dg * dg + db * db) / (float) Vol(cube, wt));
}
//---------------------------------------------------------------------------
static float Maximize(struct box *cube,unsigned char   dir,int first,
	int last,int *cut,long whole_r,long whole_g,long whole_b,long whole_w)
    
{
    long   half_r,
           half_g,
           half_b,
           half_w;
    long   base_r,
           base_g,
           base_b,
		   base_w;
    int    i;
    float  temp,
		   max;

    base_r = Bottom(cube, dir, mr);
    base_g = Bottom(cube, dir, mg);
    base_b = Bottom(cube, dir, mb);
    base_w = Bottom(cube, dir, wt);
    max = 0.0;
    *cut = -1;
    for (i = first; i < last; ++i) {
		half_r = base_r + Top(cube, dir, i, mr);
        half_g = base_g + Top(cube, dir, i, mg);
        half_b = base_b + Top(cube, dir, i, mb);
        half_w = base_w + Top(cube, dir, i, wt);
        // now half_x is sum over lower half of box, if split at i 
        if (half_w == 0) {      // subbox could be empty of pixels! 
            continue;           // never split into an empty box 
        } else
            temp = ((float) half_r * half_r + (float) half_g * half_g +
					(float) half_b * half_b) / half_w;

		half_r = whole_r - half_r;
        half_g = whole_g - half_g;
		half_b = whole_b - half_b;
        half_w = whole_w - half_w;
        if (half_w == 0) {      // subbox could be empty of pixels! 
			continue;           // never split into an empty box 
        } else
            temp += ((float) half_r * half_r + (float) half_g * half_g +
					 (float) half_b * half_b) / half_w;

        if (temp > max) {
            max = temp;
			*cut = i;
		}
    }
    return (max);
}
//---------------------------------------------------------------------------
static int Cut(struct box * set1, struct box * set2)
{
    unsigned char   dir;
    
	int     cutr,
            cutg,
            cutb;
    float   maxr,
		    maxg,
            maxb;
    long    whole_r,
		    whole_g,
		    whole_b,
            whole_w;

    whole_r = Vol(set1, mr);
    whole_g = Vol(set1, mg);
    whole_b = Vol(set1, mb);
    whole_w = Vol(set1, wt);

    maxr = Maximize(set1, RED, set1->r0 + 1, set1->r1, &cutr,
		    whole_r, whole_g, whole_b, whole_w);
    maxg = Maximize(set1, GREEN, set1->g0 + 1, set1->g1, &cutg,
		    whole_r, whole_g, whole_b, whole_w);
    maxb = Maximize(set1, BLUE, set1->b0 + 1, set1->b1, &cutb,
            whole_r, whole_g, whole_b, whole_w);

    if ((maxr >= maxg) && (maxr >= maxb)) {
		dir = RED;
        if (cutr < 0)
            return 0;           // can't split the box 
		} else if ((maxg >= maxr) && (maxg >= maxb))
			dir = GREEN;
		  else
			dir = BLUE;

    set2->r1 = set1->r1;
    set2->g1 = set1->g1;
    set2->b1 = set1->b1;

    switch (dir) {
		case RED:
			set2->r0 = set1->r1 = cutr;
			set2->g0 = set1->g0;
			set2->b0 = set1->b0;
			break;
		case GREEN:
	        set2->g0 = set1->g1 = cutg;
			set2->r0 = set1->r0;
			set2->b0 = set1->b0;
			break;
		case BLUE:
			set2->b0 = set1->b1 = cutb;
			set2->r0 = set1->r0;
			set2->g0 = set1->g0;
			break;
    }
    set1->vol = (set1->r1 - set1->r0) * (set1->g1 - set1->g0) * (set1->b1 - set1->b0);
    set2->vol = (set2->r1 - set2->r0) * (set2->g1 - set2->g0) * (set2->b1 - set2->b0);
    return 1;
}
//---------------------------------------------------------------------------
static void	Mark(struct box * cube, int label, unsigned char *tag)
{
    int	r,
		g,
		b;
    
	for (r = cube->r0 + 1; r <= cube->r1; ++r)
		for (g = cube->g0 + 1; g <= cube->g1; ++g)
			for (b = cube->b0 + 1; b <= cube->b1; ++b){
//				r,g,b
				tag[(r << 10) + (r << 6) + r + (g << 5) + g + b] = label;
			//=label;
			}


}
//---------------------------------------------------------------------------
#define WEIG // >>1 // >>2
//---------------------------------------------------------------------------
void spl_QuantizeImageColors(spl_Image *pImage,spl_UInt ColorsCount,bool CreatePalette,bool bFullPalette)
{
    struct box      cube[MAXCOLOR];
    unsigned char  *tag = 0;
    float   vv[MAXCOLOR],
		    temp = 0.;
    long    i = 0,
		    weight = 0;
    int     next = 0;
    int     j = 0,
			k = 0,
			l = 0;

    // input R,G,B components into TrueColorPic;
    //   set ImageSize to width*height
    pImage->SetPixelFormat(pf24bit);
    
    TrueColorPic = pImage;

    ImageSize = pImage->Width*pImage->Height;
    if(ColorsCount>=255)
        ColorsCount=254;
    PalSize = ColorsCount;
    spl_ColorsCount=0;

    for (j=0;j<BOX;j++)
		for (k=0;k<BOX;k++)
			for (l=0;l<BOX;l++) {
				wt[j][k][l] = 0;
				mr[j][k][l] = 0;
				mg[j][k][l] = 0;
				mb[j][k][l] = 0;
				m2[j][k][l] = 0.;
			}

    Qadd = (unsigned short *)malloc(ImageSize * sizeof(short));

    Hist3d((long *)&wt, (long *)&mr, (long *)&mg, (long *)&mb, (float *)&m2);
    Momt3d((long *)&wt, (long *)&mr, (long *)&mg, (long *)&mb, (float *)&m2);

    cube[0].r0 = cube[0].g0 = cube[0].b0 = 0;
    cube[0].r1 = cube[0].g1 = cube[0].b1 = 32;
    next = 0;
    for (i = 1; i < PalSize; ++i) {
		if (Cut(&cube[next], &cube[i])) {
			vv[next] = (cube[next].vol > 1) ? Var(&cube[next]) : 0.0f;
			vv[i] = (cube[i].vol > 1) ? Var(&cube[i]) : 0.0f;
		} else {
			vv[next] = 0.0;
			i--;
		}
		next = 0;
		temp = vv[0];
		for (k = 1; k <= i; ++k)
			if (vv[k] > temp) {
				temp = vv[k];
				next = k;
			}
			if (temp <= 0.0) {
			PalSize = i + 1;
			break;
			}
	}
    spl_ColorsCount=PalSize;

    tag = (unsigned char *) malloc(BOX * BOX * BOX);

    if(CreatePalette)
    {
        // Create Palette
        LogPal SysPal;
        FillMemory(SysPal.lpal.palPalEntry,256,PC_RESERVED);
        int nFull = 253;
        SysPal.lpal.palVersion = 0x300;
        if(bFullPalette)
	        SysPal.lpal.palNumEntries = nFull;
        else
	        SysPal.lpal.palNumEntries = spl_ColorsCount;

        int K;
        for (k = 0; k < spl_ColorsCount; ++k) {
    		Mark(&cube[k], k, tag);

    		weight = Vol(&cube[k], wt);
            K=3*k;
    		if (weight)
            {
    			spl_QuantizedPalette[K+2] = (Byte)(Vol(&cube[k], mr) / weight) WEIG;
    			spl_QuantizedPalette[K+1] = (Byte)(Vol(&cube[k], mg) / weight) WEIG;
    			spl_QuantizedPalette[K+0] = (Byte)(Vol(&cube[k], mb) / weight) WEIG;
    		}
            else
            {
    			spl_QuantizedPalette[K+2] =
    			spl_QuantizedPalette[K+1] =
    			spl_QuantizedPalette[K+0] = 0;
    		}

            spl_QuantizedColors[k]=RGB(spl_QuantizedPalette[K+2],
                                       spl_QuantizedPalette[K+1],
                                       spl_QuantizedPalette[K+0]);

            SysPal.lpal.palPalEntry[k].peRed=spl_QuantizedPalette[K+2];
            SysPal.lpal.palPalEntry[k].peGreen=spl_QuantizedPalette[K+1];
            SysPal.lpal.palPalEntry[k].peBlue=spl_QuantizedPalette[K+0];
            SysPal.lpal.palPalEntry[k].peFlags=PC_RESERVED;
        }

        if(bFullPalette)
        {
	        for(int k=spl_ColorsCount;k<nFull;k++)
	        {
	            SysPal.lpal.palPalEntry[k].peRed=k;
	            SysPal.lpal.palPalEntry[k].peGreen=k;
	            SysPal.lpal.palPalEntry[k].peBlue=k;
	            SysPal.lpal.palPalEntry[k].peFlags=PC_RESERVED;
            }
        }

        pImage->SetPixelFormat(pf8bit);
        pImage->pBitmap->Palette=::CreatePalette(&SysPal.lpal);
        pImage->UpdateLines();

        i=0;
        for(spl_UInt y=0;y<pImage->Height;y++)
        {
            for(spl_UInt x=0;x<pImage->Width;x++)
            {
                pImage->ppLines[y][x]=tag[Qadd[i]];
                i++;
            }
        }
    }
    else
    {
        int K;
        for (k = 0; k < PalSize; ++k) {
    		Mark(&cube[k], k, tag);

    		weight = Vol(&cube[k], wt);
            K=3*k;
    		if (weight)
            {
    			spl_QuantizedPalette[K+2] = (Byte)(Vol(&cube[k], mr) / weight) WEIG;
    			spl_QuantizedPalette[K+1] = (Byte)(Vol(&cube[k], mg) / weight) WEIG;
    			spl_QuantizedPalette[K+0] = (Byte)(Vol(&cube[k], mb) / weight) WEIG;
    		}
            else
            {
    			spl_QuantizedPalette[K+2] =
    			spl_QuantizedPalette[K+1] =
    			spl_QuantizedPalette[K+0] = 0;
    		}

            spl_QuantizedColors[k]=RGB(spl_QuantizedPalette[K+2],
                                       spl_QuantizedPalette[K+1],
                                       spl_QuantizedPalette[K+0]);
        }

        i=0;
        for(spl_UInt y=0;y<pImage->Height;y++)
        {
            for(spl_UInt x=0;x<pImage->LineSize;x+=3)
            {
                K=3*tag[Qadd[i]];
                pImage->ppLines[y][x+2]=spl_QuantizedPalette[K+2];
                pImage->ppLines[y][x+1]=spl_QuantizedPalette[K+1];
                pImage->ppLines[y][x  ]=spl_QuantizedPalette[K];
                i++;
            }
        }
    }

    free(tag);
    free(Qadd);
}
//---------------------------------------------------------------------------
// Output:     spl_QuantizedPalette[numcolors*3];
//	       Picture256[picsize];
//---------------------------------------------------------------------------

