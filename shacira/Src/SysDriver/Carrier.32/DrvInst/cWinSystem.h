//---------------------------------------------------------------------------
#ifndef cWinSystemH
#define cWinSystemH
//---------------------------------------------------------------------------

#define UNDEFINED_SYSTEM    0
#define WIN_95    1
#define WIN_98    2
#define WIN_ME    3
#define WIN_NT    4
#define WIN_2K    5
#define WIN_XP    6

class cWinSystem
{
private:
   int _SystemType;
   OSVERSIONINFO _VersionInfo;
   char _SystemDirectory[512];
public:
   cWinSystem();
   virtual ~cWinSystem();
   int SystemType();
   OSVERSIONINFO * VersionInfo();
   const char * SystemDirectory();
};

#endif
