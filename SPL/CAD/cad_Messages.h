//---------------------------------------------------------------------------
#ifndef cad_MessagesH
#define cad_MessagesH
//---------------------------------------------------------------------------
#define spl_CMD_LINE            	VC_CUSTOM+1
#define spl_CMD_POLYLINE        	VC_CUSTOM+2
#define spl_CMD_POLYSATIN       	VC_CUSTOM+3
#define spl_CMD_POLYSHAPE			VC_CUSTOM+4
#define spl_CMD_TEXT       			VC_CUSTOM+5
#define spl_CMD_EXTRUDE_POLYSHAPE  	VC_CUSTOM+6
#define spl_CMD_PLUG_IN			 	VC_CUSTOM+7
//---------------------------------------------------------------------------
typedef enum{ctNone,ctPolySatin} TCommandType;
//---------------------------------------------------------------------------
int CALLBACK DwgProc (int iDwg,UINT Msg,int Prm1,int Prm2,double Prm3,double Prm4,void* Prm5);
//---------------------------------------------------------------------------
void spl_Initialize_Commands();
//---------------------------------------------------------------------------
extern int g_nEdgeCounts;
extern AnsiString g_strText;
extern TCommandType CommandType;
//---------------------------------------------------------------------------
#endif
