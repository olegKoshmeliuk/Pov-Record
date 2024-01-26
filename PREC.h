#include "interface.h"

//C++ HEADERS
#include <stdio.h>
#include <time.h>
#include <io.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "wininet.h"

using namespace std;

//SOURCE GAME HEADERS
#include "define.h"
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
	string				DemoName;
	string				PrevDemoName;
	string				Mapname;
	string				Dir;
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