#include "PREC.h"
#include "PREC_vars.h"
#include "common.h"
#include "MyThreads.h"
#include "ConCommand.h" // Console commands
#include "Events.h" // Func for events

bool PREC::Load(	CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory )
{
	ConnectTier1Libraries( &interfaceFactory, 1 );
	ConnectTier2Libraries( &interfaceFactory, 1 );
	srv_engine		 = (IVEngineServer*)interfaceFactory(INTERFACEVERSION_VENGINESERVER, NULL);
	cli_engine		 = (IVEngineClient*)interfaceFactory(VENGINE_CLIENT_INTERFACE_VERSION, NULL);
	gameeventmanager = (IGameEventManager *)interfaceFactory(INTERFACEVERSION_GAMEEVENTSMANAGER,NULL);
	esound			 = ( IEngineSound* ) interfaceFactory( IENGINESOUND_CLIENT_INTERFACE_VERSION, NULL );
	playerinfomanager= (IPlayerInfoManager *)gameServerFactory(INTERFACEVERSION_PLAYERINFOMANAGER,NULL);
	g_pFullFileSystem= (IFileSystem *)interfaceFactory( FILESYSTEM_INTERFACE_VERSION, NULL );
	if(!(cli_engine && gameeventmanager && g_pFullFileSystem && esound)) return false;
	ConVar_Register( 0 );
#ifdef DEBUG
	gameeventmanager->AddListener(this,false);
#endif
	gameeventmanager->AddListener(this,"tournament_stateupdate",false);
	gameeventmanager->AddListener(this,"teamplay_game_over",false);
	gameeventmanager->AddListener(this,"tf_game_over",false);
	gameeventmanager->AddListener(this,"teamplay_round_restart_seconds",false);
	gameeventmanager->AddListener(this,"localplayer_respawn",false);
	gameeventmanager->AddListener(this,"player_death",false);
	gameeventmanager->AddListener(this,"player_activate",false);
	gameeventmanager->AddListener(this,"player_spawn",false);
	gameeventmanager->AddListener(this,"server_spawn",false);
	gameeventmanager->AddListener(this,"hltv_title",false);
	gameeventmanager->AddListener(this,"hltv_status",false);
	time(&global.StartDemoTime);//Init DemoTime
	srv_engine->ServerCommand("wait 5;prec_welcome\n");
	

	//Init Glob vars
	global.Recording=0;
	global.Streak=0;
	global.Enable=1;
	global.LastState=1;
	global.MakeStatus=0;
	global.StreakTick=0.0;
	global.DemoName = "";
	global.PrevDemoName = "";
	global.Mapname = "";
	return true;
}
void PREC::Unload( void )
{
	gameeventmanager->RemoveListener( this );
	ConVar_Unregister( );
	DisconnectTier2Libraries( );
	DisconnectTier1Libraries( );
}
void PREC::LevelShutdown( void ) // !!!!this can get called multiple times per map change
{
	global.Enable=1;
}
void PREC::FireGameEvent( KeyValues * event )
{
	if (!global.Enable) return;
	const char * name = event->GetName();
	UpdateTime;
	//OtherEvents(event);
	if (!strcmp(name,"tournament_stateupdate") && !event->GetInt("namechange"))  global.LastState=event->GetInt("readystate");
	else if (!strcmp(name,"teamplay_game_over") || !strcmp(name,"tf_game_over")) teamplay_game_over(event);
	else if (!strcmp(name,"teamplay_round_restart_seconds") && event->GetInt("seconds")==5) teamplay_round_restart_seconds(event);
	else if (!strcmp(name,"localplayer_respawn")) localplayer_respawn(event);
	else if (!strcmp(name,"player_death")) player_death(event);
	else if (!strcmp(name,"player_spawn")) player_spawn(event);
	else if (!strcmp(name,"player_activate")) player_activate(event);
	else if (!strcmp(name,"server_spawn")) server_spawn(event);
	else if (!strcmp(name,"hltv_status")) hltv_status(event);
	else if (!strcmp(name,"hltv_title")) hltv_title(event);
}