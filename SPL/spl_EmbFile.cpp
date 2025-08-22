//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_EmbFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void spl_CenterStithcs(spl_Rect &Frame,spl_GlobalStitchPath &GlobalStitchPath)
{
    if(GlobalStitchPath.empty())    return;
    spl_Point Center;
    Center.x=Frame.left+Frame.Width()/2.0;
    Center.y=Frame.top+Frame.Height()/2.0;
    spl_UInt count=GlobalStitchPath.size();
    for(spl_UInt i=0;i<count;i++)
    {
        GlobalStitchPath[i].x-=Center.x;
        GlobalStitchPath[i].y-=Center.y;
    }
}
//---------------------------------------------------------------------------
void spl_ScaleStithcs(double Scale,spl_GlobalStitchPath &GlobalStitchPath)
{
    if(GlobalStitchPath.empty())    return;

    for(spl_UInt i=0;i<GlobalStitchPath.size();i++)
    {
        GlobalStitchPath[i].x*=Scale;
        GlobalStitchPath[i].y*=Scale;
    }
}
//---------------------------------------------------------------------------
void spl_ReverseStithcs(double Height,spl_GlobalStitchPath &GlobalStitchPath)
{
    if(GlobalStitchPath.empty())    return;

    for(spl_UInt i=0;i<GlobalStitchPath.size();i++)
    {
        GlobalStitchPath[i].y = Height - 1 - GlobalStitchPath[i].y;
    }
}
//---------------------------------------------------------------------------
void spl_ReConstructStitchs(double Epsilon,spl_GlobalStitchPath &iGlobalStitchPath,spl_GlobalStitchPath &oGlobalStitchPath)
{
	oGlobalStitchPath.clear();
    if(iGlobalStitchPath.empty())    return;
    spl_Contour iContour,oContour;
    spl_Point p;
    spl_UByte StitchType;
    spl_GlobalStitch GlobalStitch;

    StitchType = iGlobalStitchPath[0].type;
    for(spl_UInt i=0;i<iGlobalStitchPath.size();i++)
    {
    	if(iGlobalStitchPath[i].type != StitchType)
        {
        	spl_FindBestContour(Epsilon,iContour,oContour);
            for(UINT j=0;j<oContour.Points.size();j++)
            {
            	GlobalStitch.x = oContour.Points[j].x;
                GlobalStitch.y = oContour.Points[j].y;
                GlobalStitch.type = StitchType;
                oGlobalStitchPath.push_back(GlobalStitch);
            }

         	StitchType = iGlobalStitchPath[i].type;
            iContour.Points.clear();
        }

    	p.x = iGlobalStitchPath[i].x;
    	p.y = iGlobalStitchPath[i].y;
    	iContour.Points.push_back(p);
    }

    spl_FindBestContour(Epsilon,iContour,oContour);
    for(UINT j=0;j<oContour.Points.size();j++)
    {
    	GlobalStitch.x = oContour.Points[j].x;
        GlobalStitch.y = oContour.Points[j].y;
        GlobalStitch.type = StitchType;
        oGlobalStitchPath.push_back(GlobalStitch);
    }
}
//---------------------------------------------------------------------------
void spl_AdjustStitchs0(bool ApplyPattern,spl_Point &op,spl_GlobalStitchPath &GlobalStitchPath,spl_StitchPath &StitchPath)
{
//    StitchPath.erase(StitchPath.begin(),StitchPath.end());
    if(spl_RunStitchStep<=0.0)   return;
    if(GlobalStitchPath.empty())    return;

    spl_Point p,oop,P,OP;
    spl_Point K;
    spl_Stitch Stitch;
    spl_UByte StitchType;
    double L;
    double Length;
    spl_Point p0,kp;
    spl_Point v0,kv;
    double Pattern;
    spl_Contour Contour;
    kv=spl_K1[spl_Global_StartDir];
    v0=spl_Global_StartPoint;
    kp=spl_Global_n;

    OP=op;
    for(UINT i=0;i<GlobalStitchPath.size();i++)
    {
        P.x=GlobalStitchPath[i].x;
        P.y=GlobalStitchPath[i].y;
        StitchType=GlobalStitchPath[i].type;

        if(StitchType==spl_stColorChanged)// Color Stitch
        {
        }
        else
        if(StitchType==spl_stJump)// Jump Stitch
        {
            L=spl_PDistance(&OP,&P);
            if(L>spl_JumpStitchStep)
            {
                K.x=(P.x-OP.x)/L;
                K.y=(P.y-OP.y)/L;
                for(double t=spl_JumpStitchStep;t<L;t+=spl_JumpStitchStep)
                {
                    p.x=OP.x+t*K.x;
                    p.y=OP.y+t*K.y;

                    Stitch.x=p.x-op.x;
                    Stitch.y=p.y-op.y;
                    Stitch.type=StitchType;
                    StitchPath.push_back(Stitch);
                    op.x+=Stitch.x;
                    op.y+=Stitch.y;
                }
            }
        }
        else// Normal Stitch
        {
            L=spl_PDistance(&OP,&P);
//            if(L>spl_RunStitchStep)
            if(L>=spl_MaxStitchLength)
            {
                K.x=(P.x-OP.x)/L;
                K.y=(P.y-OP.y)/L;

                if(ApplyPattern)
                {
                    oop=op;
                    spl_Intersect(&OP,&kp,&v0,&kv,&p0);
                    Contour.Points.clear();
                    double L1,L2;
				    int n1,n2;
                    spl_Point pt,pt1;
                    L1=spl_PDistance(&p0,&OP);
                    L2=spl_PDistance(&p0,&P);
                    if(L1 <= L2)
                    {
                		n1 = int(L1 / spl_RunStitchStep);
                		n2 = int(L2 / spl_RunStitchStep);
						if(n1 + 1 < n2)// More than one segment
                        {
                        	for(int j = n1 + 1; j <= n2; j++)
                            {
								pt = p0 + kv ^ (j * spl_RunStitchStep);
								Contour.Points.push_back(pt);
                            }
                            if(Contour.Points.size() == 1)
                            {
								if(L >= spl_MaxStitchLength)
                                {
                                	p = Contour.Points[0];
		                            Stitch.x=p.x-op.x;
		                            Stitch.y=p.y-op.y;
	    	                        Stitch.type=StitchType;
            		                StitchPath.push_back(Stitch);
                    		        op.x+=Stitch.x;
		                            op.y+=Stitch.y;
		                            oop=p;
                                }
                            }
                            else
                            if(Contour.Points.size() == 2)
                            {
                             	if(spl_PDistance(&OP,&Contour.Points[1]) < spl_MaxStitchLength)
                                {
                                	p = Contour.Points[1];
		                            Stitch.x=p.x-op.x;
		                            Stitch.y=p.y-op.y;
	    	                        Stitch.type=StitchType;
            		                StitchPath.push_back(Stitch);
                    		        op.x+=Stitch.x;
		                            op.y+=Stitch.y;
		                            oop=p;
                                }
                                else
                             	if(spl_PDistance(&P,&Contour.Points[0]) < spl_MaxStitchLength)
                                {
                                	p = Contour.Points[0];
		                            Stitch.x=p.x-op.x;
		                            Stitch.y=p.y-op.y;
	    	                        Stitch.type=StitchType;
            		                StitchPath.push_back(Stitch);
                    		        op.x+=Stitch.x;
		                            op.y+=Stitch.y;
		                            oop=p;
                                }
                                else
                                {
                                	p = Contour.Points[0];
		                            Stitch.x=p.x-op.x;
		                            Stitch.y=p.y-op.y;
	    	                        Stitch.type=StitchType;
            		                StitchPath.push_back(Stitch);
                    		        op.x+=Stitch.x;
		                            op.y+=Stitch.y;
		                            oop=p;

                                	p = Contour.Points[1];
		                            Stitch.x=p.x-op.x;
		                            Stitch.y=p.y-op.y;
	    	                        Stitch.type=StitchType;
            		                StitchPath.push_back(Stitch);
                    		        op.x+=Stitch.x;
		                            op.y+=Stitch.y;
		                            oop=p;
                                }
                            }
                            else
                            if(Contour.Points.size() > 2)
                            {
                             	if(spl_PDistance(&OP,&Contour.Points[1]) >= spl_MaxStitchLength)
                                {
                                	p = Contour.Points[0];
		                            Stitch.x=p.x-op.x;
		                            Stitch.y=p.y-op.y;
	    	                        Stitch.type=StitchType;
            		                StitchPath.push_back(Stitch);
                    		        op.x+=Stitch.x;
		                            op.y+=Stitch.y;
		                            oop=p;
                                }
                               	for(UINT j=1;j<Contour.Points.size()-1;j++)
                                {
                                	p = Contour.Points[j];
		                            Stitch.x=p.x-op.x;
		                            Stitch.y=p.y-op.y;
	    	                        Stitch.type=StitchType;
            		                StitchPath.push_back(Stitch);
                    		        op.x+=Stitch.x;
		                            op.y+=Stitch.y;
		                            oop=p;
                                }
                                int count = Contour.Points.size();
                             	if(spl_PDistance(&P,&Contour.Points[count - 2]) >= spl_MaxStitchLength)
                                {
                                	p = Contour.Points[count - 1];
		                            Stitch.x=p.x-op.x;
		                            Stitch.y=p.y-op.y;
	    	                        Stitch.type=StitchType;
            		                StitchPath.push_back(Stitch);
                    		        op.x+=Stitch.x;
		                            op.y+=Stitch.y;
		                            oop=p;
                                }
                            }
                        }
                    }
                    else
                    {

                    }
/*
                    if(p0 * kp < 0)
                    {
                     	p0 += kp ^ spl_RunStitchStep;
                    } 
                    for(double t=0.0;t<L;t+=0.1)
                    {
                        p.x=OP.x+t*K.x;
                        p.y=OP.y+t*K.y;

                        Length=spl_PDistance(&oop,&p);
                        Pattern=spl_PDistance(&p0,&p);
                        n = int(Pattern / spl_RunStitchStep);
                        if  (
//                            ((spl_ABS(p.x-p0.x)==0)&&(int(spl_ABS(p.y-p0.y))% spl_RunStitchStep ==0)) ||
//                            ((int(spl_ABS(p.x-p0.x))% spl_RunStitchStep ==0)&&(spl_ABS(p.y-p0.y)==0)) ||
//                            (Pattern==0) ||
//                            (Pattern % spl_RunStitchStep ==0) ||
//                            (spl_ABS(Pattern - n * spl_RunStitchStep) <= 0.001) ||
//                            ((spl_Global_Dir!=spl_Global_StartDir)&&(Length>=spl_RunStitchStep)) ||
//                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir==spl_Diagonal)&&(Length>=spl_RunStitchStep)) ||
//                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir!=spl_Diagonal)&&(spl_Global_StartDir==spl_Horizontal)&&((int(spl_ABS(p.x-p0.x))% spl_RunStitchStep ==0))&&(spl_ABS(p.x-p0.x)<=spl_StitchMargin)) ||
//                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir!=spl_Diagonal)&&(spl_Global_StartDir==spl_Vertical)&&((int(spl_ABS(p.y-p0.y))% spl_RunStitchStep ==0))&&(spl_ABS(p.y-p0.y)<=spl_StitchMargin)) ||
//                            (Length>=spl_MaxStitchLength)
                            (Length>=spl_RunStitchStep)
                            )
                        {
                            Stitch.x=p.x-op.x;
                            Stitch.y=p.y-op.y;
                            Stitch.type=StitchType;
                            StitchPath.push_back(Stitch);
                            op.x+=Stitch.x;
                            op.y+=Stitch.y;
                            oop=p;

                            OP = p;
                        	L=spl_PDistance(&op,&P);
		                    for(double m=0.0;m<L;m+=spl_RunStitchStep)
        		            {
                		        p.x=OP.x+m*K.x;
                        		p.y=OP.y+m*K.y;

	                            Stitch.x=p.x-op.x;
	                            Stitch.y=p.y-op.y;
	                            Stitch.type=StitchType;
                                StitchPath.push_back(Stitch);
    	                        op.x+=Stitch.x;
	                            op.y+=Stitch.y;
                            }
                            break;
                        }
                    }
*/                    
                }
                else
                {
                    for(double t=0.0;t<L;t+=spl_RunStitchStep)
                    {
                        p.x=OP.x+t*K.x;
                        p.y=OP.y+t*K.y;

                        Stitch.x=p.x-op.x;
                        Stitch.y=p.y-op.y;
                        Stitch.type=StitchType;
                        StitchPath.push_back(Stitch);
                        op.x+=Stitch.x;
                        op.y+=Stitch.y;
                    }
                }
            }
        }

        // Last Point
        Stitch.x=P.x-op.x;
        Stitch.y=P.y-op.y;
        Stitch.type=StitchType;
        StitchPath.push_back(Stitch);
        op.x+=Stitch.x;
        op.y+=Stitch.y;

        OP=P;
    }
}
//---------------------------------------------------------------------------
void spl_AdjustStitchs(bool ApplyPattern,spl_Point &op,spl_GlobalStitchPath &GlobalStitchPath,spl_StitchPath &StitchPath)
{
//    StitchPath.erase(StitchPath.begin(),StitchPath.end());
    if(spl_RunStitchStep<=0.0)   return;
    if(GlobalStitchPath.empty())    return;

    double Epsilon = 3;
    spl_GlobalStitchPath oGlobalStitchPath;
    spl_ReConstructStitchs(Epsilon,GlobalStitchPath,oGlobalStitchPath);
    GlobalStitchPath = oGlobalStitchPath;

    spl_Point p,oop,P,OP;
    spl_Point K;
    spl_Stitch Stitch;
    spl_UByte StitchType;
    double L;
    int Length;
    spl_Point p0,kp;
    spl_Point v0,kv;
    int Pattern;
    int Step;
	spl_Contour Contour;
    bool bIsPrevColorChanged;
    kv=spl_K1[spl_Global_StartDir];
    v0=spl_Global_StartPoint;
    kp=spl_Global_n;

    bIsPrevColorChanged = false;
    OP=op;
    for(UINT i=0;i<GlobalStitchPath.size();i++)
    {
        P.x=GlobalStitchPath[i].x;
        P.y=GlobalStitchPath[i].y;
        StitchType=GlobalStitchPath[i].type;

        if(StitchType==spl_stColorChanged)// Color Stitch
        {
		    bIsPrevColorChanged = true;
        }
        else
        if(StitchType==spl_stJump)// Jump Stitch
        {
            L=spl_PDistance(&OP,&P);
            if(L>spl_JumpStitchStep)
            {
                K.x=(P.x-OP.x)/L;
                K.y=(P.y-OP.y)/L;
                for(double t=spl_JumpStitchStep;t<L;t+=spl_JumpStitchStep)
                {
                    p.x=OP.x+t*K.x;
                    p.y=OP.y+t*K.y;

                    Stitch.x=p.x-op.x;
                    Stitch.y=p.y-op.y;
            		if(spl_ReplaceJump)
                    {
                    	if(bIsPrevColorChanged)
	                    	Stitch.type=StitchType;
                        else
	                    	Stitch.type=spl_stNormal;
                    }
                    else
                    	Stitch.type=StitchType;
                    StitchPath.push_back(Stitch);
                    op.x+=Stitch.x;
                    op.y+=Stitch.y;
                }
            }
        }
        else// Normal Stitch
        {
		    bIsPrevColorChanged = false;
            L=spl_PDistance(&OP,&P);
            if(L>spl_RunStitchStep)
            {
                K.x=(P.x-OP.x)/L;
                K.y=(P.y-OP.y)/L;

                if(ApplyPattern)
                {
                    oop=op;
                    spl_Intersect(&OP,&kp,&v0,&kv,&p0);
                    Contour.Points.clear();
                    for(double t=0.0;t<L;t+=0.5)
                    {
                        p.x=OP.x+t*K.x;
                        p.y=OP.y+t*K.y;

                        Length=spl_Round(spl_PDistance(&oop,&p));
                        Pattern=spl_Round(spl_PDistance(&p0,&p));
                        if  (
//                            (Length>=spl_StitchMargin) ||
//                            (Length>=spl_Global_EmbParameters.StitchMargin) ||
                            ((spl_ABS(p.x-p0.x)==0)&&(int(spl_ABS(p.y-p0.y))% spl_RunStitchStep ==0)) ||
                            ((int(spl_ABS(p.x-p0.x))% spl_RunStitchStep ==0)&&(spl_ABS(p.y-p0.y)==0)) ||
                            (Pattern==0) ||
                            (Pattern % spl_RunStitchStep ==0) ||
                            ((spl_Global_Dir!=spl_Global_StartDir)&&(Length>=spl_RunStitchStep)) ||
                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir==spl_Diagonal)&&(Length>=spl_RunStitchStep)) ||
                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir!=spl_Diagonal)&&(spl_Global_StartDir==spl_Horizontal)&&((int(spl_ABS(p.x-p0.x))% spl_RunStitchStep ==0))&&(spl_ABS(p.x-p0.x)<=spl_StitchMargin)) ||
                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir!=spl_Diagonal)&&(spl_Global_StartDir==spl_Vertical)&&((int(spl_ABS(p.y-p0.y))% spl_RunStitchStep ==0))&&(spl_ABS(p.y-p0.y)<=spl_StitchMargin)) ||
                            (Length>=spl_Global_EmbParameters.StitchMargin)
                            )
                        {
                        	Contour.Points.push_back(p);
                            oop=p;
                        }
                    }

                    switch(spl_AdjustMethode)
                    {
                     	case spl_amMethode0:
                        {
	    	                int count = Contour.Points.size();
		    	            for(int j=0;j<count;j++)
	            		    {
								p = Contour.Points[j];
			                    Stitch.x=p.x-op.x;
		    	                Stitch.y=p.y-op.y;
		        	            Stitch.type=StitchType;
		            	        StitchPath.push_back(Stitch);
		                	    op.x+=Stitch.x;
		                        op.y+=Stitch.y;
		    	            }
                         	break;
                        }
                     	case spl_amMethode1:
                        {
		                    int count = Contour.Points.size();
		                    spl_Point prevP;
		                    if(count > 0)
		                    {
								prevP = Contour.Points[0];

		                        Stitch.x=prevP.x-op.x;
		                        Stitch.y=prevP.y-op.y;
		                        Stitch.type=StitchType;
		                        StitchPath.push_back(Stitch);
		                        op.x+=Stitch.x;
		                        op.y+=Stitch.y;
		                    }

                            for(int j=0;j<count;j++)
                            {
                            	p = Contour.Points[j];
                                L = spl_PDistance(&op,&p);
                                if(L >= spl_StitchMargin)
                                {
                                	Stitch.x=prevP.x-op.x;
                                    Stitch.y=prevP.y-op.y;
                                    Stitch.type=StitchType;
                                    StitchPath.push_back(Stitch);
                                    op.x+=Stitch.x;
                                    op.y+=Stitch.y;
                                }
                                prevP = p;
                            }

		                    if(count > 1)
		                    {
								prevP = Contour.Points[count-1];

		                        Stitch.x=prevP.x-op.x;
		                        Stitch.y=prevP.y-op.y;
		                        Stitch.type=StitchType;
		                        StitchPath.push_back(Stitch);
		                        op.x+=Stitch.x;
		                        op.y+=Stitch.y;
		                    }
                         	break;
                        }
                     	case spl_amMethode2:
                        {
		                    int count = Contour.Points.size();
		                    spl_Point prevP;
		                    if(count > 0)
		                    {
								prevP = Contour.Points[0];

		                        Stitch.x=prevP.x-op.x;
		                        Stitch.y=prevP.y-op.y;
		                        Stitch.type=StitchType;
		                        StitchPath.push_back(Stitch);
		                        op.x+=Stitch.x;
		                        op.y+=Stitch.y;
		                    }

                            for(int j=0;j<count;j++)
                            {
                            	p = Contour.Points[j];
                                L = spl_PDistance(&prevP,&p);
                                if(L >= spl_RunStitchStep)
                                {
                                	Stitch.x=prevP.x-op.x;
                                    Stitch.y=prevP.y-op.y;
                                    Stitch.type=StitchType;
                                    StitchPath.push_back(Stitch);
                                    op.x+=Stitch.x;
                                    op.y+=Stitch.y;

                                    prevP = p;
                                }
                            }

		                    if(count > 1)
		                    {
								prevP = Contour.Points[count-1];

		                        Stitch.x=prevP.x-op.x;
		                        Stitch.y=prevP.y-op.y;
		                        Stitch.type=StitchType;
		                        StitchPath.push_back(Stitch);
		                        op.x+=Stitch.x;
		                        op.y+=Stitch.y;
		                    }
                         	break;
                        }
                    }
                }
                else
                {
                    for(double t=0.0;t<L;t+=spl_RunStitchStep)
                    {
                        p.x=OP.x+t*K.x;
                        p.y=OP.y+t*K.y;

                        Stitch.x=p.x-op.x;
                        Stitch.y=p.y-op.y;
                        Stitch.type=StitchType;
                        StitchPath.push_back(Stitch);
                        op.x+=Stitch.x;
                        op.y+=Stitch.y;
                    }
                }
            }
        }

        // Last Point
        Stitch.x=P.x-op.x;
        Stitch.y=P.y-op.y;
        if(StitchType==spl_stJump)
        {
        	if(spl_ReplaceJump)
            	Stitch.type=spl_stNormal;
            else
        		Stitch.type=StitchType;
        }
        else
        {
	        Stitch.type=StitchType;
        }
        StitchPath.push_back(Stitch);
        op.x+=Stitch.x;
        op.y+=Stitch.y;

        OP=P;
    }
}
//---------------------------------------------------------------------------
/*
void spl_AdjustStitchs(bool ApplyPattern,spl_Point &op,spl_GlobalStitchPath &GlobalStitchPath,spl_StitchPath &StitchPath)
{
//    StitchPath.erase(StitchPath.begin(),StitchPath.end());
    if(spl_RunStitchStep<=0.0)   return;
    if(GlobalStitchPath.empty())    return;

    spl_Point p,oop,P,OP;
    spl_Point K;
    spl_Stitch Stitch;
    spl_UByte StitchType;
    double L;
    int Length;
    spl_Point p0,kp;
    spl_Point v0,kv;
    int Pattern;
    int Step;
    kv=spl_K1[spl_Global_StartDir];
    v0=spl_Global_StartPoint;
    kp=spl_Global_n;

    OP=op;
    for(UINT i=0;i<GlobalStitchPath.size();i++)
    {
        P.x=GlobalStitchPath[i].x;
        P.y=GlobalStitchPath[i].y;
        StitchType=GlobalStitchPath[i].type;

        if(StitchType==spl_stColorChanged)// Color Stitch
        {
        }
        else
        if(StitchType==spl_stJump)// Jump Stitch
        {
            L=spl_PDistance(&OP,&P);
            if(L>spl_JumpStitchStep)
            {
                K.x=(P.x-OP.x)/L;
                K.y=(P.y-OP.y)/L;
                for(double t=spl_JumpStitchStep;t<L;t+=spl_JumpStitchStep)
                {
                    p.x=OP.x+t*K.x;
                    p.y=OP.y+t*K.y;

                    Stitch.x=p.x-op.x;
                    Stitch.y=p.y-op.y;
                    Stitch.type=StitchType;
                    StitchPath.push_back(Stitch);
                    op.x+=Stitch.x;
                    op.y+=Stitch.y;
                }
            }
        }
        else// Normal Stitch
        {
            L=spl_PDistance(&OP,&P);
            if(L>spl_RunStitchStep)
            {
                K.x=(P.x-OP.x)/L;
                K.y=(P.y-OP.y)/L;

                if(ApplyPattern)
                {
                    oop=op;
                    spl_Intersect(&OP,&kp,&v0,&kv,&p0);
                    for(double t=0.0;t<L;t+=1.0)
                    {
                        p.x=OP.x+t*K.x;
                        p.y=OP.y+t*K.y;

                        Length=spl_Round(spl_PDistance(&oop,&p));
                        Pattern=spl_Round(spl_PDistance(&p0,&p));
                        if  (
                            ((spl_ABS(p.x-p0.x)==0)&&(int(spl_ABS(p.y-p0.y))% spl_RunStitchStep ==0)) ||
                            ((int(spl_ABS(p.x-p0.x))% spl_RunStitchStep ==0)&&(spl_ABS(p.y-p0.y)==0)) ||
                            (Pattern==0) ||
                            (Pattern % spl_RunStitchStep ==0) ||
                            ((spl_Global_Dir!=spl_Global_StartDir)&&(Length>=spl_RunStitchStep)) ||
                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir==spl_Diagonal)&&(Length>=spl_RunStitchStep)) ||
                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir!=spl_Diagonal)&&(spl_Global_StartDir==spl_Horizontal)&&((int(spl_ABS(p.x-p0.x))% spl_RunStitchStep ==0))&&(spl_ABS(p.x-p0.x)<=spl_StitchMargin)) ||
                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir!=spl_Diagonal)&&(spl_Global_StartDir==spl_Vertical)&&((int(spl_ABS(p.y-p0.y))% spl_RunStitchStep ==0))&&(spl_ABS(p.y-p0.y)<=spl_StitchMargin)) ||
                            (Length>=spl_MaxStitchLength)
                            )
                        {
                            Stitch.x=p.x-op.x;
                            Stitch.y=p.y-op.y;
                            Stitch.type=StitchType;
                            StitchPath.push_back(Stitch);
                            op.x+=Stitch.x;
                            op.y+=Stitch.y;
                            oop=p;
                        }
                    }
                }
                else
                {
                    for(double t=0.0;t<L;t+=spl_RunStitchStep)
                    {
                        p.x=OP.x+t*K.x;
                        p.y=OP.y+t*K.y;

                        Stitch.x=p.x-op.x;
                        Stitch.y=p.y-op.y;
                        Stitch.type=StitchType;
                        StitchPath.push_back(Stitch);
                        op.x+=Stitch.x;
                        op.y+=Stitch.y;
                    }
                }
            }
        }

        // Last Point
        Stitch.x=P.x-op.x;
        Stitch.y=P.y-op.y;
        Stitch.type=StitchType;
        StitchPath.push_back(Stitch);
        op.x+=Stitch.x;
        op.y+=Stitch.y;

        OP=P;
    }
}
*/
//---------------------------------------------------------------------------
/*
void spl_AdjustStitchs(bool ApplyPattern,spl_Point &op,spl_GlobalStitchPath &GlobalStitchPath,spl_StitchPath &StitchPath)
{
//    StitchPath.erase(StitchPath.begin(),StitchPath.end());
    if(spl_RunStitchStep<=0.0)   return;
    if(GlobalStitchPath.empty())    return;

    spl_Point p,P,OP;
    spl_Point K;
    spl_Stitch Stitch;
    spl_UByte StitchType;
    double L;
    int Length;
    spl_Point p0,kp;
    spl_Point v0,kv;
    int Pattern;
    kv=spl_K1[spl_Global_StartDir];
    v0=spl_Global_StartPoint;
    kp=spl_Global_n;

    OP=op;
    for(UINT i=0;i<GlobalStitchPath.size();i++)
    {
        P.x=GlobalStitchPath[i].x;
        P.y=GlobalStitchPath[i].y;
        StitchType=GlobalStitchPath[i].type;

        if(StitchType==spl_stColorChanged)// Color Stitch
        {
        }
        else
        if(StitchType==spl_stJump)// Jump Stitch
        {
            L=spl_PDistance(&OP,&P);
            if(L>spl_JumpStitchStep)
            {
                K.x=(P.x-OP.x)/L;
                K.y=(P.y-OP.y)/L;
                for(double t=spl_JumpStitchStep;t<L;t+=spl_JumpStitchStep)
                {
                    p.x=OP.x+t*K.x;
                    p.y=OP.y+t*K.y;

                    Stitch.x=p.x-op.x;
                    Stitch.y=p.y-op.y;
                    Stitch.type=StitchType;
                    StitchPath.push_back(Stitch);
                    op.x+=Stitch.x;
                    op.y+=Stitch.y;
                }
            }
        }
        else// Normal Stitch
        {
            L=spl_PDistance(&OP,&P);
            if(L>spl_RunStitchStep)
            {
                K.x=(P.x-OP.x)/L;
                K.y=(P.y-OP.y)/L;

                if(ApplyPattern)    spl_Intersect(&OP,&kp,&v0,&kv,&p0);
                for(double t=0.0;t<L;t+=1.0)
                {
                    p.x=OP.x+t*K.x;
                    p.y=OP.y+t*K.y;

                    Length=spl_Round(spl_PDistance(&op,&p));
                    if(ApplyPattern)
                    {
                        Pattern=spl_Round(spl_PDistance(&p0,&p));
                        if(
                            ((spl_ABS(p.x-p0.x)==0)&&(int(spl_ABS(p.y-p0.y))% spl_RunStitchStep ==0)) ||
                            ((int(spl_ABS(p.x-p0.x))% spl_RunStitchStep ==0)&&(spl_ABS(p.y-p0.y)==0)) ||
                            (Pattern==0) ||
                            (Pattern % spl_RunStitchStep ==0) ||
                            ((spl_Global_Dir!=spl_Global_StartDir)&&(Length>=spl_RunStitchStep)) ||
                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir==spl_Diagonal)&&(Length>=spl_RunStitchStep)) ||
                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir!=spl_Diagonal)&&(spl_Global_StartDir==spl_Horizontal)&&((int(spl_ABS(p.x-p0.x))% spl_RunStitchStep ==0))&&(spl_ABS(p.x-p0.x)<=spl_StitchMargin)) ||
                            ((spl_Global_Dir==spl_Global_StartDir)&&(spl_Global_Dir!=spl_Diagonal)&&(spl_Global_StartDir==spl_Vertical)&&((int(spl_ABS(p.y-p0.y))% spl_RunStitchStep ==0))&&(spl_ABS(p.y-p0.y)<=spl_StitchMargin)) ||
                            (Length>=spl_MaxStitchLength)
                          )
                        {
                            Stitch.x=p.x-op.x;
                            Stitch.y=p.y-op.y;
                            Stitch.type=StitchType;
                            StitchPath.push_back(Stitch);
                            op.x+=Stitch.x;
                            op.y+=Stitch.y;
                        }
                    }
                    else
                    {
                        if(Length>=spl_RunStitchStep)
                        {
                            Stitch.x=p.x-op.x;
                            Stitch.y=p.y-op.y;
                            Stitch.type=StitchType;
                            StitchPath.push_back(Stitch);
                            op.x+=Stitch.x;
                            op.y+=Stitch.y;
                        }
                    }
                }
            }
        }

        // Last Point
        Stitch.x=P.x-op.x;
        Stitch.y=P.y-op.y;
        Stitch.type=StitchType;
        StitchPath.push_back(Stitch);
        op.x+=Stitch.x;
        op.y+=Stitch.y;

        OP=P;
    }
}
*/
//---------------------------------------------------------------------------
void spl_MakeTatami(spl_GlobalStitchPath &iGlobalStitchPath,spl_GlobalStitchPath &oGlobalStitchPath)
{
    oGlobalStitchPath.erase(oGlobalStitchPath.begin(),oGlobalStitchPath.end());
    if(iGlobalStitchPath.empty())  return;
    spl_GlobalStitchPath Temp;
    UINT count3;
    UINT count=iGlobalStitchPath.size();

    for(UINT i=0;i<=count;i++)
    {
        if((i<count-1)&&(iGlobalStitchPath[i % count].type==spl_stNormal))
        {
            Temp.push_back(iGlobalStitchPath[i % count]);
        }
        else
        {
            if(!Temp.empty())
            {
                count3=Temp.size()/3;
                if(count3>0)
                {
                    for(UINT j=0;j<count3;j++)
                    {
                        oGlobalStitchPath.push_back(Temp[3*j+0]);
                        oGlobalStitchPath.push_back(Temp[3*j+2]);
                        oGlobalStitchPath.push_back(Temp[3*j+1]);
                    }
                    Temp.erase(Temp.begin(),&Temp[3*count3]);
                }

                for(UINT j=0;j<Temp.size();j++)
                {
                    oGlobalStitchPath.push_back(Temp[j]);
                }
                Temp.erase(Temp.begin(),Temp.end());
            }

            oGlobalStitchPath.push_back(iGlobalStitchPath[i % count]);
        }
    }
}
//---------------------------------------------------------------------------

