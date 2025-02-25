#include "interface.h"

//C++ HEADERS
#include <stdio.h>
#include <time.h>
#include <io.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include "wininet.h"

//SOURCE GAME HEADERS
#include "filesystem.h"
#include "engine/iserverplugin.h"
#include "eiface.h"
#include "con_nprint.h"
#include "igameevents.h"
#include "convar.h"
#include "Color.h"
#include "vstdlib/random.h"
#include "engine/IEngineTrace.h"
#include "engine/IEngineSound.h"
#include "tier2/tier2.h"
#include "game/server/iplayerinfo.h"
#include "cdll_int.h"
#include "tier0/memdbgon.h"

//Define
#define VERSION "2.1.0"
#define CODENAME "prec"
#define NAME "Pov record plugin"
#define SEC_BEFORE_KILL  2.0
#define ADDON_INFO "Pov record plugin"
#define Sound_conf Config->FindKey("Sounds")
#define Text_conf Config->FindKey("Phrases")
//Color define for ConColorMsg
#define ORANGE Color(223,117,31,255)
#define GREEN Color(0,255,0,255)
#define DARK_GREEN Color(0,128,0,255)
#define DemoNameSwitch if (!global.DemoName.empty()) {global.PrevDemoName=global.DemoName;global.DemoName="";}
#define UpdateTime time ( &global.rawtime );\
				   global.timeinfo = localtime ( &global.rawtime )
#define ThreadFunc(func) DWORD g_##func##ID=0;\
						 DWORD WINAPI func## (void *param)
#define MakeThread(Thread)	CreateThread( NULL, 16000, ##Thread, (void*) &g_##Thread##ID, 0, &g_##Thread##ID)
#define CheckThread if (ThreadID!=*(DWORD *)param) {return 0;}
#define UpdatePinfo cli_engine->GetPlayerInfo(cli_engine->GetLocalPlayer(),&global.pinfo)
#define PlayerUserId global.pinfo.userID
#define DemoTick difftime(global.rawtime,global.StartDemoTime)*66.6
#define BUFFERSIZE 300
#define tournament cvar->FindVar("mp_tournament")->GetBool()
#define REDTEAM cvar->FindVar("mp_tournament_redteamname")->GetString() 
#define BLUTEAM cvar->FindVar("mp_tournament_blueteamname")->GetString()
#define HudMsg(_Red,_Green,_Blue,_time,_index,_fixed_width,_HudMsgText)  {\
				  con_nprint_s info;\
				  info.color[0]=_Red;\
				  info.color[1]=_Green;\
				  info.color[2]=_Blue;\
				  info.time_to_live=_time;\
				  info.fixed_width_font=_fixed_width;\
				  info.index=_index;\
				  cli_engine->Con_NXPrintf(&info,_HudMsgText);}
#define ResetTVstatus global.hltv_AVGClients=0;\
					  global.hltv_CurClients=0;\
					  global.hltv_Hits=0;\
					  global.hltv_StatusCount=0;\
					  global.hltv_MaxClients=0



//Global var's
struct PREC_globals
{
	int					Recording;
	int					Streak;
	int					Enable;
	int					LastState;
	int					MakeStatus;
	int					HasBookmarks;
	float				StreakTick;
	time_t				StartDemoTime;
	time_t				LastKillTime;
	time_t				rawtime;
	struct tm			*timeinfo;
	std::string				DemoName;
	std::string				PrevDemoName;
	std::string				Mapname;
	std::string				Dir;
	player_info_t		pinfo;
	long double			hltv_AVGClients;
	unsigned long		hltv_Hits;
	int					hltv_CurClients;
	int					hltv_MaxClients;
	unsigned long		hltv_StatusCount;

};
PREC_globals global;


// Interfaces from the engine
IVEngineServer		*srv_engine = NULL; 
IPlayerInfoManager	*playerinfomanager = NULL;
IVEngineClient		*cli_engine =NULL;
IGameEventManager	*gameeventmanager = NULL; 
IEngineSound		*esound =NULL;

class PREC: public IServerPluginCallbacks, public IGameEventListener
{
public:
	PREC()	{m_iClientCommandIndex = 0;};
	~PREC()	{};
	// IServerPluginCallbacks methods
	virtual bool			Load(	CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory );
	virtual void			Unload( void );
	virtual void			Pause( void ){};
	virtual void			UnPause( void ){};
	virtual const char 		*GetPluginDescription( void ){return ADDON_INFO;};      
	virtual void			LevelInit( char const *pMapName ){};
	virtual void			ServerActivate( edict_t *pEdictList, int edictCount, int clientMax ){};
	virtual void			GameFrame( bool simulating ){};
	virtual void			LevelShutdown( void );
	virtual void			ClientActive( edict_t *pEntity ){};
	virtual void			ClientDisconnect( edict_t *pEntity ){};
	virtual void			ClientPutInServer( edict_t *pEntity, char const *playername ){};
	virtual void			SetCommandClient( int index ){};
	virtual void			ClientSettingsChanged( edict_t *pEdict ){};
	virtual PLUGIN_RESULT	ClientConnect( bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen ){return PLUGIN_CONTINUE;}
	virtual PLUGIN_RESULT	ClientCommand( edict_t *pEntity, const CCommand &args ){return PLUGIN_CONTINUE;}
	virtual PLUGIN_RESULT	NetworkIDValidated( const char *pszUserName, const char *pszNetworkID ){return PLUGIN_CONTINUE;}
	virtual void			OnQueryCvarValueFinished( QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue ){};
	// added with version 3 of the interface.
	virtual void			OnEdictAllocated( edict_t *edict ){};
	virtual void			OnEdictFreed( const edict_t *edict  ){};
	// IGameEventListener Interface
	virtual void FireGameEvent( KeyValues * event );
	virtual int GetCommandIndex() { return m_iClientCommandIndex; }
private:
	int m_iClientCommandIndex;
};

PREC g_PREC;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(PREC, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_PREC );