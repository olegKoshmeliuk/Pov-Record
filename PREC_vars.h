void PREC_dir_Callback( IConVar *var, const char *pOldValue, float flOldValue );
void PREC_mode_Callback( IConVar *var, const char *pOldValue, float flOldValue );
//---------------------------------------------------------------------------------
// Purpose: console CVARS
//---------------------------------------------------------------------------------
static ConVar PREC_version("prec_version", VERSION, FCVAR_DONTRECORD, "Plugin verison\n");
static ConVar PREC_next_demoname("prec_next_demoname", "", FCVAR_DONTRECORD, "Set name of next demo\n");
static ConVar PREC_notify("prec_notify", "1", FCVAR_ARCHIVE|FCVAR_DONTRECORD, "Notify when started/stoped recording and setting bookmarks\n0 - show message in console\n1 - displays message in team chat\n2 - displays message in hud\n");
static ConVar PREC_mode("prec_mode", "2", FCVAR_ARCHIVE|FCVAR_DONTRECORD, "0-turn off addon.\n   1-record only curstomnamed demos.\n   2-record all demos (on servers with mp_tournament 1).\n   3-record all demos\n"/*,PREC_mode_Callback*/);
static ConVar PREC_minStreak("prec_min_streak", "4", FCVAR_ARCHIVE|FCVAR_DONTRECORD, "Minimum kill streak to log\n",true,2.0,false,100.0);
static ConVar PREC_KillsDelay("prec_kill_delay", "15.0", FCVAR_ARCHIVE|FCVAR_DONTRECORD, "Max delay between kill's in KillStreaks\n",true,5.0,false,100.0);
static ConVar PREC_dir("prec_dir", "", FCVAR_ARCHIVE|FCVAR_DONTRECORD, "Directory to save demos\n",PREC_dir_Callback);
static ConVar PREC_sound("prec_sound", "1", FCVAR_ARCHIVE|FCVAR_DONTRECORD, "Play sound when start/stop recording (1 - on ,0 - off)\n");
static ConVar PREC_screens("prec_screens", "0", FCVAR_ARCHIVE|FCVAR_DONTRECORD, "Make screenshoots of score and status\n");
static ConVar PREC_log("prec_log", "1", FCVAR_ARCHIVE|FCVAR_DONTRECORD, "0-Don't log.\n   1-log into killstreaks.txt\n   2-log separately for each demo.\n   3-log separately for each map.\n");
static ConVar PREC_delete_useless_demo("prec_delete_useless_demo", "0", FCVAR_ARCHIVE|FCVAR_DONTRECORD, "Delete demo files without bookmarks and killstreaks\n",true,0.0,true,1.0);
static ConVar PREC_track_stv("prec_stv_status","1",FCVAR_ARCHIVE|FCVAR_DONTRECORD,"Show SourceTV statistic after the match\n",true,0.0,true,1.0);
static ConVar PREC_tag("prec_tag","",FCVAR_ARCHIVE|FCVAR_DONTRECORD,"tag for demo\n");
static ConVar PREC_check_update("prec_check_update","1",FCVAR_ARCHIVE|FCVAR_DONTRECORD,"Check for updates on startup\n");
#ifdef DEBUG
static ConVar PREC_log_events("prec_log_events", "0",FCVAR_DONTRECORD, "");
#endif 
//---------------------------------------------------------------------------------
// Purpose: CVARS CallBacks
//---------------------------------------------------------------------------------
void PREC_dir_Callback( IConVar *var, const char *pOldValue, float flOldValue )
{
	char dir[BUFFERSIZE];
	if ( strchr(PREC_dir.GetString(),'.'))
	{
		ConColorMsg(GREEN,"Error: Invalid dir name (%s)\n",dir);
		PREC_dir.SetValue("");
	}
	sprintf(dir,"tf\\%s",PREC_dir.GetString());	
	if (access(dir,0)==-1) 
		if (CreateDirectory(dir,NULL))
		{
			ConColorMsg(GREEN,"Created new directory (%s)\n",dir);
		}
		else 
		{
			ConColorMsg(GREEN,"Error: Invalid dir name (%s)\n",dir);
			PREC_dir.SetValue("");
		}
		if (PREC_dir.GetString()[0]) global.Dir=PREC_dir.GetString()+string("/");
		else global.Dir="";
}

void PREC_mode_Callback( IConVar *var, const char *pOldValue, float flOldValue )
{
	switch (PREC_mode.GetInt())
	{
		case 0:ConColorMsg(DARK_GREEN,"Plugin disabled!\n"); break;
		case 1:ConColorMsg(DARK_GREEN,"Recording only curstomnamed demos\n"); break;
		case 2:ConColorMsg(DARK_GREEN,"Record demos from tournament servers\n"); break;
		case 3:ConColorMsg(DARK_GREEN,"Record demos from all servers\n"); break;
		default:ConColorMsg(GREEN,"ERROR:Wrong prec_mode value!\n");
	}
}