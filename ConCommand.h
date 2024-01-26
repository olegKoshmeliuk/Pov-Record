//---------------------------------------------------------------------------------
// Purpose: All console func
//---------------------------------------------------------------------------------

CON_COMMAND_F( prec_about, "About plugin" ,FCVAR_DONTRECORD)
{
	if (!global.Enable) return;
	PlaySound("on_about");
	Msg("Pov-RECord: addon for TF2.\n");
	Msg("Version: %s\n",VERSION);
	Msg("Addon Site: http://orangad.com.ua/\n");
	Msg("Author: ");ConColorMsg(ORANGE,"Orange\n");
}
CON_COMMAND_F( prec_mark, "Set bookmark to current moment." ,FCVAR_DONTRECORD)
{
	if (!cli_engine->IsRecordingDemo()) return;
	if(!global.Recording) return;
	char buff [BUFFERSIZE];
	char MarkName[BUFFERSIZE];
	strcpy(MarkName,"Player bookmark");
	if (args.ArgC()>1) strcpy(MarkName,args.Arg(1));
	UpdateTime;
	strftime (buff,BUFFERSIZE,"[%Y/%m/%d/ %H:%M]",global.timeinfo);
	sprintf(buff, "%s %s (\"%s\" at %.0f)\n",buff,MarkName,global.DemoName.c_str(),DemoTick); 
	LogToFile(buff);
	Notify("on_mark");
	PlaySound("on_mark");
}
CON_COMMAND_F( prec_delete_demo, "Delete previous recorded demo." ,FCVAR_DONTRECORD)
{
	if (!global.Enable) return;
	if (global.PrevDemoName.empty())
	{
		Warning("Can't find last demo name!\n");
		return;
	}
	string file;
	file="tf/"+global.Dir+global.PrevDemoName+".dem";
	if (DeleteFile(file.c_str())) ConColorMsg(ORANGE,"Deleted file :%s\n",file.c_str());

	file="tf/"+global.Dir+global.PrevDemoName+".txt";
	if (DeleteFile(file.c_str())) ConColorMsg(ORANGE,"Deleted file :%s\n",file.c_str());

	file="tf/"+global.Dir+global.PrevDemoName+"_status.jpg";
	if (DeleteFile(file.c_str())) ConColorMsg(ORANGE,"Deleted file :%s\n",file.c_str());

	file="tf/"+global.Dir+global.PrevDemoName+"_score.jpg";
	if (DeleteFile(file.c_str())) ConColorMsg(ORANGE,"Deleted file :%s\n",file.c_str());

	global.PrevDemoName="";

}
CON_COMMAND_F( prec_record, "Record a demo." ,FCVAR_DONTRECORD)
{
	if (!global.Enable) return;
	if (!cli_engine->IsInGame()) return;
	StopRecord();
	RecordDemo();
}
CON_COMMAND_F( prec_info, "List of commands.",FCVAR_DONTRECORD)
{
	srv_engine->ServerCommand("find prec_\n");
}
CON_COMMAND_F(prec_welcome,"",FCVAR_HIDDEN|FCVAR_DONTRECORD)
{
	ConColorMsg(ORANGE,"Pov-Record %s loaded\n",VERSION);
#ifdef DEBUG
	ConColorMsg(GREEN,"Debug Version!111\n");
#endif 
	switch (PREC_mode.GetInt())
	{
		case 0:ConColorMsg(DARK_GREEN,"Plugin disabled!\n"); break;
		case 1:ConColorMsg(DARK_GREEN,"Recording only curstomnamed demos\n"); break;
		case 2:ConColorMsg(DARK_GREEN,"Record demos from tournament servers\n"); break;
		case 3:ConColorMsg(DARK_GREEN,"Record demos from all servers\n"); break;
		default:ConColorMsg(DARK_GREEN,"ERROR:Wrong prec_mode value!\n");
	}
	if (PREC_check_update.GetBool())MakeThread(UpdateFunc);
}
CON_COMMAND_F(prec_clear,"Clean up demos directory (delete *_2.dem).",FCVAR_DONTRECORD|FCVAR_HIDDEN)
{
	string file;
	file="tf/"+global.Dir+global.PrevDemoName+"_2.dem";
	if (DeleteFile(file.c_str())) ConColorMsg(ORANGE,"Deleted file :%s\n",file.c_str());
}
CON_COMMAND_F(prec_show_stv_status,"Show current sourcetv status.",FCVAR_DONTRECORD)
{
	if (!global.Enable || !cli_engine->IsInGame()) return;
	if (global.hltv_MaxClients)
	{
		con_nprint_s info;
		info.color[1]=1.0;
		info.time_to_live=10;
		info.fixed_width_font=true;
		info.index=2;
		cli_engine->Con_NXPrintf(&info,"    SourceTV stats:    ");
		info.index=3;
		cli_engine->Con_NXPrintf(&info,"Current clients:%7d",global.hltv_CurClients);
		info.index=4;
		cli_engine->Con_NXPrintf(&info,"Max clients:%7d",global.hltv_MaxClients);
		info.index=5;
		cli_engine->Con_NXPrintf(&info,"Hits:%7d",global.hltv_Hits);
	}
}
#ifdef DEBUG


CON_COMMAND(prec_debug,"")
{
	Msg("Test");
	Msg(ParsString("dsad     \n"));

	Msg(ParsString("dsa!     \n"));
	Msg(ParsString("dsad     \n"));
}
#endif