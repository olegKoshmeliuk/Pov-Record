//Define
#define VERSION "2.0.7"
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
					