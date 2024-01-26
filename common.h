//---------------------------------------------------------------------------------
// Purpose: Some Common Functions
//---------------------------------------------------------------------------------
char *format_time(const char *frm)//ok
{
	static char buff[300];
	strftime(buff,100,frm,global.timeinfo);
	return buff;
}
char *ParsString(const char *str)//ok
{
	static char buff[100];
	char key[] = " /\\:*?\"<>|";
	char * pch;
	strcpy(buff,str);
	pch = strpbrk (buff,key);
	while (pch != NULL)
	{
		*pch='_';
	    pch = strpbrk (buff,key);
	}
	return buff;
}
void LogToFile( char *Msg)
{
	if (!global.HasBookmarks)
	{
		global.HasBookmarks=1;
		LogToFile("\n");
	}
	string file="tf/"+global.Dir;
	switch (PREC_log.GetInt())
	{
		case 1:
			file+="KillStreaks.txt";
			if (FILE *fo = fopen(file.c_str(),"a")) 
			{
				fprintf( fo,Msg);
				fclose(fo); 
			}
			break;
		case 2:
			file+=global.DemoName+".txt";
			if (FILE *fo = fopen(file.c_str(),"a")) 
			{
				fprintf( fo,Msg);
				fclose(fo); 
			}
			break;
		case 3:
			file+=global.Mapname+".txt";
			if (FILE *fo = fopen(file.c_str(),"a")) 
			{
				fprintf( fo,Msg);
				fclose(fo); 
			}
			break;
	}
	ConColorMsg(ORANGE,Msg);
}
const char *Settings(char *key)
{
	KeyValues *Config =new KeyValues("Pov-Record Config");
	if (!Config->LoadFromFile(g_pFullFileSystem,"addons/PREC.cfg"))
	{
		ConColorMsg(GREEN,"Error: can't load PREC.cfg file\n");
		Config->deleteThis();
		return "";
	}
	if(!Config->FindKey("Settings"))
	{
		ConColorMsg(GREEN,"Error: can't find Settings in PREC.cfg\n");
		Config->deleteThis();
		return "";
	}
	if (!Config->FindKey("Settings")->GetDataType(key))
	{
		ConColorMsg(GREEN,"Error: can't find \"%s\" in PREC.cfg\n",key);
		Config->deleteThis();
		return "";
	}
	return Config->FindKey("Settings")->GetString(key);
	Config->deleteThis();
}

void Notify( char *key)//good
{
	KeyValues *Config =new KeyValues("Pov-Record Config");
	if (!Config->LoadFromFile(g_pFullFileSystem,"addons/PREC.cfg"))
	{
		ConColorMsg(GREEN,"Error can't load PREC.cfg file\n");
		Config->deleteThis();
		return;
	}
	if (!Text_conf)
	{
		ConColorMsg(GREEN,"Error can't find Phrases in PREC.cfg\n");
		Config->deleteThis();
		return;
	}
	if (strlen(Text_conf->GetString(key)))
	{
		string Msg;
		switch (PREC_notify.GetInt())
		{
			case 1:
				Msg="say_team [P-REC] ";
				Msg+=Text_conf->GetString(key);
				Msg+="\n";
				if (PREC_mode.GetInt()!=3) srv_engine->ServerCommand(Msg.c_str());
				break;
			case 2:
				Msg="[P-REC] ";
				Msg+=Text_conf->GetString(key);
				HudMsg(0.0,1.0,0.0,5,0,false,Msg.c_str());
				break;
		}
		ConColorMsg(ORANGE,"[P-REC] %s\n",Text_conf->GetString(key));
	}
	Config->deleteThis();
}

void PlaySound( char *key)//good
{
	if (!PREC_sound.GetBool()) return;
	KeyValues *Config =new KeyValues("Pov-Record Config");
	if (!Config->LoadFromFile(g_pFullFileSystem,"addons/PREC.cfg"))
	{
		ConColorMsg(GREEN,"Error can't load PREC.cfg file\n");
		Config->deleteThis();
		return;
	}
	if (!Sound_conf)
	{
		ConColorMsg(GREEN,"Error can't find Sounds in PREC.cfg\n");
		Config->deleteThis();
		return;
	}
	if (strlen(Sound_conf->GetString(key)))
	{
		if (!esound->IsSoundPrecached(Sound_conf->GetString(key)))	esound->PrecacheSound(Sound_conf->GetString(key));
		esound->EmitAmbientSound(Sound_conf->GetString(key),1.0);
	}
	Config->deleteThis();
}
void StopRecord()
{
	if (cli_engine->IsRecordingDemo()) srv_engine->ServerCommand("stop\n");
	DemoNameSwitch;
	if (!global.HasBookmarks && PREC_delete_useless_demo.GetBool() && global.Recording) {srv_engine->ServerCommand("prec_delete_demo\n");}
	global.Recording=0;
	global.Streak=0;
	global.StreakTick=0;
}
void RecordDemo()
{
	string RecCom;
	string file;
	UpdateTime;
	size_t pos=string::npos;
	time ( &global.StartDemoTime );
	DemoNameSwitch;
	try
	{
		string c_map(ParsString(global.Mapname.c_str()));
		string c_red(ParsString(REDTEAM));
		string c_blu(ParsString(BLUTEAM));
		string c_tag(ParsString(PREC_tag.GetString()));
 		RecCom=ParsString(format_time(Settings("DemoTime_format")));
		file=ParsString(Settings("DemoName_format"));
		pos=file.find("%date%");
		if(pos!= string::npos) file.replace(pos,6,RecCom);
		pos=file.find("%map%");
		if(pos!= string::npos) file.replace(pos,5,c_map);
		pos=file.find("%red%");
		if(pos!= string::npos) file.replace(pos,5,c_red);
		pos=file.find("%blu%");
		if(pos!= string::npos) file.replace(pos,5,c_blu);
		pos=file.find("%tag%");
		if(pos!= string::npos) file.replace(pos,5,c_tag);
		if	(file.empty())  return;
		global.DemoName=file;
	}
	catch ( ... ) 
	{
		ConColorMsg(GREEN,"Unknown error while generating file name\n");
		return;
	}
	// %1% -date %2% map %3%- RED %4$ - BLU %5% - tag
	if (PREC_next_demoname.GetString()[0]) global.DemoName=PREC_next_demoname.GetString();
	PREC_next_demoname.SetValue("");
	file=global.Dir+global.DemoName;
	RecCom="stop;record \""+file+"\"\n";
	srv_engine->ServerCommand(RecCom.c_str());
	//set global VARS
	global.Recording=1;
	ResetTVstatus;
	if (tournament)	global.MakeStatus=PREC_screens.GetBool();
	global.HasBookmarks=0;
	global.StreakTick=0;

	PlaySound("start_rec");
	Notify("start_rec");
}



void StreakProcessor(bool Kill) // true - kill false -dead
{
	if (Kill && difftime(global.rawtime,global.LastKillTime)<PREC_KillsDelay.GetFloat()) 
	{
		global.Streak++;
		time ( &global.LastKillTime );
		return;
	}
	if (global.Streak>=PREC_minStreak.GetInt())
	{
		char buff [BUFFERSIZE];
		strftime (buff,BUFFERSIZE,"[%Y/%m/%d/ %H:%M]",global.timeinfo);
		sprintf(buff, "%s Kill Streak:%d (\"%s\" at %.0f)\n",buff,global.Streak,global.DemoName.c_str(),global.StreakTick); 
		PlaySound("on_killstreak");
		LogToFile(buff);
	}
	global.Streak=Kill?1:0;
	time ( &global.LastKillTime );
	global.StreakTick=DemoTick;
}

