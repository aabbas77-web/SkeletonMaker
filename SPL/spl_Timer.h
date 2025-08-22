//---------------------------------------------------------------------------
#ifndef spl_TimerH
#define spl_TimerH
//---------------------------------------------------------------------------
#include <mmsystem.h>
//---------------------------------------------------------------------------
// UINT msInterval: Timer interval in millisecond.
// DWORD dwUser: User defined value.
UINT	spl_CreateTimer(LPTIMECALLBACK pTimeCallBack,UINT msInterval, DWORD dwUser);
void	spl_DestroyTimer();
//---------------------------------------------------------------------------
// Return the capabilites of the computer for hight resolution counter.
void spl_GetTimeDevCaps(UINT &wPeriodMin,UINT &wPeriodMax);
//---------------------------------------------------------------------------
extern bool spl_TimerEnabled;
//---------------------------------------------------------------------------
#endif
