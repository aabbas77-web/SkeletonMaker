//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_Timer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
static MMRESULT  m_TimerID = 0;
//---------------------------------------------------------------------------
bool spl_TimerEnabled=false;
//---------------------------------------------------------------------------
UINT spl_CreateTimer(
	LPTIMECALLBACK pTimeCallBack,
    UINT msInterval, // event interval
	DWORD dwUser)    // user defined data
{
	spl_DestroyTimer();

    m_TimerID = timeSetEvent(
        msInterval,                    // delay
        1,                     		   // resolution (global variable)
        pTimeCallBack,                 // callback function
        dwUser,                  	   // user data
        TIME_PERIODIC);                // PERIODIC timer event
    if(! m_TimerID)
		return 0;
	else
        return 0xFFFF;
}
//---------------------------------------------------------------------------
void spl_DestroyTimer()
{
	// is timer event pending?
	// cancel the event
    if(m_TimerID)
	{
        timeKillEvent(m_TimerID);
        m_TimerID = 0;
    }
}
//---------------------------------------------------------------------------
void spl_GetTimeDevCaps(UINT &wPeriodMin,UINT &wPeriodMax)
{
	TIMECAPS timeCaps;
	MMRESULT mmRes = timeGetDevCaps(&timeCaps, sizeof(timeCaps));

	if (mmRes == TIMERR_NOERROR)
	{
		wPeriodMax = timeCaps.wPeriodMax;
		wPeriodMin = timeCaps.wPeriodMin;
	}
}
//---------------------------------------------------------------------------

