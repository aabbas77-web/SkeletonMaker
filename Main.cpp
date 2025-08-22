//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*
void __fastcall TFormMain::Skeletonize(spl_Image *pImage,spl_Contour &Contour)
{
  	int Lx, Ly, Lindex;
  	Byte LB, LA, LN, LAN6, LAN4;
  	TPoint LNOff;
  	bool LChanging;
    int AWidth,AHeight;
    AWidth = pImage->Width;
    AHeight = pImage->Height;
  	vector<int> LRemove;
  	Byte **ppLImage;

	Contour.Points.clear();
    for(int y=0;y<pImage->Height;y++)
    {
		for(int x=0;x<pImage->Width;x++)
        {
         	if(pImage->ppLines[y][x] == 0)
            {
            	Contour.Points.push_back(splPoint(x,y));
            }
        }
    }

  	// create a 2D image from the points - LImage array
  	// the LImage array will be larger than the actual image
  	// and offset by 1 in x and y to prevent access violations
  	// when accessing neighbouring points to those at the edge of the image
    ppLImage = new Byte *[AWidth+3];
    for(int y=0;y<AWidth+3;y++)
    {
    	ppLImage[y] = new Byte[AHeight+3];
        ZeroMemory(ppLImage[y],AHeight+3);
    }
  	for(UINT i=0;i<Contour.Points.size();i++)
    	ppLImage[int(Contour.Points[i].x+1)][int(Contour.Points[i].y+1)] = 1;

  	LRemove.resize(Contour.Points.size());

  	LChanging = true;
  	while(LChanging) // stop if pixels are no longer being removed
    {
    	LChanging = false;
        // loop through all points in the binary object
        for(int Lindex = 0;Lindex<Contour.Points.size();Lindex++)
		{
          	LRemove[Lindex] = false;

          	Lx = Contour.Points[Lindex].x + 1;
          	Ly = Contour.Points[Lindex].y + 1;

            // calculate B
            // B is the sum of non-zero neighbours
            LB = 0;
            for(LN = 2;LN<= 9;LN++)
            {
                  LNOff = Neighbour(LN);
                  LB += ppLImage[Lx+LNOff.x][Ly+LNOff.y];
            }

            if((LB < 2) || (LB > 6) ) continue; // failed B removal test

            // calculate A
            // A is the number of 0 -> 1 patterns around the neighbourhood
            LA = 0;
            for(LN = 2;LN<= 9;LN++)
            {
                  LNOff = Neighbour(LN);
                  if(ppLImage[Lx+LNOff.x][Ly+LNOff.y] == 0)
                  {
                      LNOff = Neighbour(LN+1);
                      if(ppLImage[Lx+LNOff.x][Ly+LNOff.y] == 1)
                          LA++;
                  }
                  if(LA > 1) break; // fails if LA <> 1 so no need to continue
            }

            if(LA != 1) continue; // failed A removal test

            // calculate the A value for neighbour 6
            LAN6 = 0;
            for(LN = 2;LN<= 9;LN++)
            {
                  LNOff = Neighbour(LN);
                  if(ppLImage[Lx+LNOff.x][Ly+LNOff.y+1] == 0)
                  {
                      LNOff = Neighbour(LN+1);
                      if(ppLImage[Lx+LNOff.x][Ly+LNOff.y+1] == 1)
                          LAN6++;
                  }
            }

            if((ppLImage[Lx][Ly+1] * ppLImage[Lx+1][Ly] * ppLImage[Lx-1][Ly] != 0) && (LAN6 == 1)) continue; // failed test

            // calculate the A value for neighbour 4
            LAN4 = 0;
            for(LN = 2;LN<= 9;LN++)
            {
                  LNOff = Neighbour(LN);
                  if(ppLImage[Lx+LNOff.x+1][Ly+LNOff.y] == 0)
                  {
                      LNOff = Neighbour(LN+1);
                      if(ppLImage[Lx+LNOff.x+1][Ly+LNOff.y] == 1)
                          LAN4++;
                  }
            }

            // final removal test
            if((ppLImage[Lx][Ly-1] * ppLImage[Lx+1][Ly] * ppLImage[Lx][Ly+1] == 0) || (LAN4 != 1))
            {
                  // erosion cannot be done sequencially - so flag all points that
                  // must be removed to remove them all at once after each pass
                  LRemove[Lindex] = true;
                  LChanging = true; // still removing pixels so continue for another pass
            }
        } // loop through points

		// remove the points that are flagged in the LRemove array
        if(LChanging)
        {
          	Lindex = 0;
          	while(Lindex < Contour.Points.size())
            {
            	if(LRemove[Lindex])
                {
                    // set value of image for this point to zero
    				ppLImage[int(Contour.Points[Lindex].x+1)][int(Contour.Points[Lindex].y+1)] = 0;
                    // remove point from points list by moving the last element to the
                    // points position and then reducing the length of the array by 1
                    Contour.Points.erase(&Contour.Points[Lindex]);
                    // must do the same for this element in the LRemove array
                    LRemove.erase(&LRemove[Lindex]);
                }
                else
                {
                    Lindex++;
                }
          	};
        }
  	} // passes loop

    if(ppLImage)
    {
        for(int y=0;y<AWidth+3;y++)
        {
            delete[] ppLImage[y];
            ppLImage[y] = NULL;
        }
        delete[] ppLImage;
        ppLImage = NULL;
    }
}
//---------------------------------------------------------------------------
// return the offset of a neighbouring point
TPoint __fastcall TFormMain::Neighbour(Byte ANeighbour)
{
    //    ___________
    //   | 9 | 2 | 3 |
    //   |___|___|___|
    //   | 8 | 1 | 4 |
    //   |___|___|___|
    //   | 7 | 6 | 5 |
    //   |___|___|___|
    //
	TPoint Result;
  	ANeighbour = (ANeighbour - 2) % 8 + 2; // neighbourhood wrap-round
  	switch(ANeighbour)
  	{
    	case 2 :
        {
        	Result.x =  0;
            Result.y = -1;
            break;
        };
    	case 3 :
        {
        	Result.x =  1;
            Result.y = -1;
            break;
        }
    	case 4 :
        {
         	Result.x =  1;
            Result.y =  0;
            break;
        }
    	case 5 :
        {
         	Result.x =  1;
            Result.y =  1;
            break;
        }
    	case 6 :
        {
         	Result.x =  0;
            Result.y =  1;
            break;
        }
    	case 7 :
        {
         	Result.x = -1;
            Result.y =  1;
            break;
        }
    	case 8 :
        {
        	Result.x = -1;
            Result.y =  0;
            break;
        }
    	case 9 :
        {
         	Result.x = -1;
            Result.y = -1;
            break;
        }
  	}
    return Result;
}
*/
//---------------------------------------------------------------------------
void __fastcall TFormMain::Skeletonize(spl_Image *pImage,spl_Contour &Contour)
{
	Contour.Points.clear();

  	int Lx, Ly, Lindex;
  	Byte LB, LA, LN, LAN6, LAN4;
  	spl_Point LNOff;
  	bool LChanging;
    int AWidth,AHeight;
    AWidth = pImage->Width;
    AHeight = pImage->Height;
  	vector<int> LRemove;
  	Byte **ppLImage;

    for(int y=0;y<pImage->Height;y++)
    {
		for(int x=0;x<pImage->Width;x++)
        {
         	if(pImage->ppLines[y][x] == 0)
            {
            	Contour.Points.push_back(splPoint(x,y));
            }
        }
    }

  	// create a 2D image from the points - LImage array
  	// the LImage array will be larger than the actual image
  	// and offset by 1 in x and y to prevent access violations
  	// when accessing neighbouring points to those at the edge of the image
    ppLImage = new Byte *[AHeight+3];
    for(int y=0;y<AHeight+3;y++)
    {
    	ppLImage[y] = new Byte[AWidth+3];
        ZeroMemory(ppLImage[y],AWidth+3);
    }
  	for(UINT i=0;i<Contour.Points.size();i++)
    	ppLImage[int(Contour.Points[i].y+1)][int(Contour.Points[i].x+1)] = 1;

  	LRemove.resize(Contour.Points.size());

  	LChanging = true;
  	while(LChanging) // stop if pixels are no longer being removed
    {
    	LChanging = false;
        // loop through all points in the binary object
        for(int Lindex = 0;Lindex<Contour.Points.size();Lindex++)
		{
          	LRemove[Lindex] = False;

          	Lx = Contour.Points[Lindex].x + 1;
          	Ly = Contour.Points[Lindex].y + 1;

            // calculate B
            // B is the sum of non-zero neighbours
            LB = 0;
            for(LN = 2;LN<= 9;LN++)
            {
                  LNOff = Neighbour(LN);
                  LB += ppLImage[int(Ly+LNOff.y)][int(Lx+LNOff.x)];
            }

            if((LB < 2) || (LB > 6) ) continue; // failed B removal test

            // calculate A
            // A is the number of 0 -> 1 patterns around the neighbourhood
            LA = 0;
            for(LN = 2;LN<= 9;LN++)
            {
                  LNOff = Neighbour(LN);
                  if(ppLImage[int(Ly+LNOff.y)][int(Lx+LNOff.x)] == 0)
                  {
                      LNOff = Neighbour(LN+1);
                      if(ppLImage[int(Ly+LNOff.y)][int(Lx+LNOff.x)] == 1)
                          LA++;
                  }
                  if(LA > 1) break; // fails if LA <> 1 so no need to continue
            }

            if(LA != 1) continue; // failed A removal test

            // calculate the A value for neighbour 6
            LAN6 = 0;
            for(LN = 2;LN<= 9;LN++)
            {
                  LNOff = Neighbour(LN);
                  if(ppLImage[int(Ly+LNOff.y+1)][int(Lx+LNOff.x)] == 0)
                  {
                      LNOff = Neighbour(LN+1);
                      if(ppLImage[int(Ly+LNOff.y+1)][int(Lx+LNOff.x)] == 1)
                          LAN6++;
                  }
            }

            if((ppLImage[Ly+1][Lx] * ppLImage[Ly][Lx+1] * ppLImage[Ly][Lx-1] != 0) && (LAN6 == 1)) continue; // failed test

            // calculate the A value for neighbour 4
            LAN4 = 0;
            for(LN = 2;LN<= 9;LN++)
            {
                  LNOff = Neighbour(LN);
                  if(ppLImage[int(Ly+LNOff.y)][int(Lx+LNOff.x+1)] == 0)
                  {
                      LNOff = Neighbour(LN+1);
                      if(ppLImage[int(Ly+LNOff.y)][int(Lx+LNOff.x+1)] == 1)
                          LAN4++;
                  }
            }

            // final removal test
            if((ppLImage[Ly-1][Lx] * ppLImage[Ly][Lx+1] * ppLImage[Ly+1][Lx] == 0) || (LAN4 != 1))
            {
                  // erosion cannot be done sequencially - so flag all points that
                  // must be removed to remove them all at once after each pass
                  LRemove[Lindex] = true;
                  LChanging = true; // still removing pixels so continue for another pass
            }
        } // loop through points

		// remove the points that are flagged in the LRemove array
        if(LChanging)
        {
          	Lindex = 0;
          	while(Lindex < Contour.Points.size())
            {
            	if(LRemove[Lindex])
                {
                    // set value of image for this point to zero
    				ppLImage[int(Contour.Points[Lindex].y+1)][int(Contour.Points[Lindex].x+1)] = 0;
                    // remove point from points list by moving the last element to the
                    // points position and then reducing the length of the array by 1
                    Contour.Points.erase(&Contour.Points[Lindex]);
                    // must do the same for this element in the LRemove array
                    LRemove.erase(&LRemove[Lindex]);
                }
                else
                {
                    Lindex++;
                }
          	};
        }
  	} // passes loop

    if(ppLImage)
    {
        for(int y=0;y<AHeight+3;y++)
        {
            delete[] ppLImage[y];
            ppLImage[y] = NULL;
        }
        delete[] ppLImage;
        ppLImage = NULL;
    }
}
//---------------------------------------------------------------------------
// return the offset of a neighbouring point
spl_Point __fastcall TFormMain::Neighbour(Byte ANeighbour)
{
    //    ___________
    //   | 9 | 2 | 3 |
    //   |___|___|___|
    //   | 8 | 1 | 4 |
    //   |___|___|___|
    //   | 7 | 6 | 5 |
    //   |___|___|___|
    //
	spl_Point Result;
  	ANeighbour = (ANeighbour - 2) % 8 + 2; // neighbourhood wrap-round
  	switch(ANeighbour)
  	{
    	case 2 :
        {
        	Result.x =  0;
            Result.y = -1;
            break;
        }; 													
    	case 3 :
        {
        	Result.x =  1;
            Result.y = -1;
            break;
        }
    	case 4 :
        {
         	Result.x =  1;
            Result.y =  0;
            break;
        }
    	case 5 :
        {
         	Result.x =  1;
            Result.y =  1;
            break;
        }
    	case 6 :
        {
         	Result.x =  0;
            Result.y =  1;
            break;
        }
    	case 7 :
        {
         	Result.x = -1;
            Result.y =  1;
            break;
        }
    	case 8 :
        {
        	Result.x = -1;
            Result.y =  0;
            break;
        }
    	case 9 :
        {
         	Result.x = -1;
            Result.y = -1;
            break;
        }
  	}
    return Result;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClearImage()
{
	Image->Canvas->Brush->Style = bsSolid;
    Image->Canvas->Brush->Color = clWhite;
    Image->Canvas->FillRect(Image->BoundsRect);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Open1Click(TObject *Sender)
{
	if(OpenPictureDialog->Execute())
    {
    	m_pImage->LoadFromFile(OpenPictureDialog->FileName);
		m_pImage->SetPixelFormat(pf8bit);        
    	Image->Picture->Assign(m_pImage->pBitmap);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Saveas1Click(TObject *Sender)
{
	if(SavePictureDialog->Execute())
    {
    	Image->Picture->SaveToFile(SavePictureDialog->FileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Exit1Click(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Skeletonize1Click(TObject *Sender)
{
	spl_Point P;
	spl_Contour Contour;
	Skeletonize(m_pImage,Contour);

    ClearImage();
    for(UINT i=0;i<Contour.Points.size();i++)
    {
     	P = Contour.Points[i];
        Image->Canvas->Pixels[int(P.x)][int(P.y)] = clBlack;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	m_pImage = new spl_Image();	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
	if(m_pImage)
    {
     	delete m_pImage;
        m_pImage = NULL;
    }
}
//---------------------------------------------------------------------------

