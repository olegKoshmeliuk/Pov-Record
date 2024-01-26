void teamplay_game_over(KeyValues * event)
{
	if (!global.Recording || PREC_mode.GetInt()==3) return;
	StopRecord();
	if (PREC_screens.GetBool()) MakeThread(ScoreScreen);
	PlaySound("stop_rec");
	Notify("stop_rec");
	if (global.hltv_MaxClients && PREC_track_stv.GetBool())
	{
		con_nprint_s info;
		info.color[1]=1.0;
		info.time_to_live=10;
		info.fixed_width_font=true;
		info.index=2;
		cli_engine->Con_NXPrintf(&info,"    SourceTV stats:    ");
		info.index=3;
		cli_engine->Con_NXPrintf(&info,"Max Clients:%7d",global.hltv_MaxClients);
		info.index=4;
		cli_engine->Con_NXPrintf(&info,"Average Clients:%7.1f",global.hltv_AVGClients);
		info.index=5;
		cli_engine->Con_NXPrintf(&info,"Hits:%7d",global.hltv_Hits);
	}
}

void teamplay_round_restart_seconds(KeyValues * event)
{
	DWORD threadId;
	switch (PREC_mode.GetInt())
	{
		case 1 :
			if (strcmp(PREC_next_demoname.GetString(),"") && tournament) 
				CreateThread( NULL, 16000, OnReadyThread, NULL, 0, &threadId);
			break;
		case 2 :
			if (tournament) MakeThread(OnReadyThread);
			break;
	}
}
void localplayer_respawn(KeyValues * event)
{
	UpdatePinfo;
}
void player_death(KeyValues * event)
{
	if (!global.Recording) return;
	if (global.MakeStatus && event->GetInt("userid")==PlayerUserId) MakeThread(StatusScreen);
	if (event->GetInt("userid")==PlayerUserId) StreakProcessor(false);
	if (event->GetInt("attacker")==PlayerUserId && event->GetInt("userid")!=PlayerUserId)
	{
		StreakProcessor(true);
	}
}
void player_spawn(KeyValues * event)
{
	if (PREC_mode.GetInt()==3 && event->GetInt("userid")==PlayerUserId && !global.Recording)
	{
		RecordDemo();
	}
}
void player_activate(KeyValues * event)
{
	UpdatePinfo;
	//stop recording and  on player_activate
	if (PlayerUserId==event->GetInt("userid")) StopRecord();
	srv_engine->ServerCommand("prec_clear\n");
}
void server_spawn(KeyValues * event)
{
	ResetTVstatus;
	global.Mapname=event->GetString("mapname");
	int a=cli_engine->IsPlayingTimeDemo();
	int b=cli_engine->IsPlayingDemo();
	if (a || b)
	{
		ConColorMsg(ORANGE,"Playing demo.\n");
		global.Enable=0;
	}
}
void hltv_title(KeyValues * event)
{
	ConColorMsg(ORANGE,"Connected to SourceTV.\n");
	global.Enable=0;
}

void hltv_status(KeyValues * event)
{
	global.hltv_AVGClients=(long double)(global.hltv_AVGClients*((long double)global.hltv_StatusCount/((long double)global.hltv_StatusCount+1.0)))+((long double)event->GetInt("clients")/((long double)global.hltv_StatusCount+1.0));
	global.hltv_Hits+=(global.hltv_CurClients<event->GetInt("clients"))?event->GetInt("clients")-global.hltv_CurClients:0;
	global.hltv_CurClients=event->GetInt("clients");
	global.hltv_StatusCount++;
	global.hltv_MaxClients=global.hltv_MaxClients<global.hltv_CurClients?global.hltv_CurClients:global.hltv_MaxClients;
}
void OtherEvents(KeyValues * event)
{
	static char logmsg[200];
	sprintf(logmsg,"{%s}",event->GetName());
	for ( KeyValues *sub = event->GetFirstValue(); sub; sub = sub->GetNextValue() )
	{
		switch (sub->GetDataType())
		{
		case 1: sprintf(logmsg,"%s %s=\"%s\"",logmsg,sub->GetName(), sub->GetString()); break;
		case 2: sprintf(logmsg,"%s %s=%d",logmsg,sub->GetName(), sub->GetInt());break;
		case 3: sprintf(logmsg,"%s %s=%.3f",logmsg,sub->GetName(), sub->GetFloat());break;
		default: ConColorMsg(GREEN,"error at %d",__LINE__);


		}
	}

	sprintf(logmsg,"%s\n",logmsg);
	ConColorMsg(GREEN,"%s",logmsg);//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
}
