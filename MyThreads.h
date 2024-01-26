ThreadFunc(StatusScreen)
{
	DWORD ThreadID;
	ThreadID=*(DWORD *)param;
	if (difftime(global.rawtime,global.StartDemoTime)<10.0) return 0;
	global.MakeStatus=0;
	con_nprint_s info;
	info.color[1]=1.0;
	info.time_to_live=3;
	info.index=0;
	info.fixed_width_font=false;
	cli_engine->Con_NXPrintf(&info,"Making Status screenshot");
	Sleep(7000);
	CheckThread;
	srv_engine->ServerCommand("gameui_activate;showconsole;clear;status\n");
	Sleep(300);
	UpdateTime;
	char comm[400];
	sprintf(comm, "jpeg \"../%s%s_status\" 100\n", global.Dir.c_str(), global.DemoName.c_str());
	CheckThread;
	srv_engine->ServerCommand(comm);
	Sleep(300);
	CheckThread;
	srv_engine->ServerCommand("gameui_hide\n");
	return 0;

}
ThreadFunc(ScoreScreen)
{
	DWORD ThreadID;
	ThreadID=*(DWORD *)param;
	if (!global.HasBookmarks && PREC_delete_useless_demo.GetBool()) return 0;
	srv_engine->ServerCommand("gameui_hide;+score\n");
	Sleep(50);
	char comm[400];
	sprintf(comm, "jpeg \"../%s%s_score\" 100\n", global.Dir.c_str(), global.PrevDemoName.c_str());
	srv_engine->ServerCommand(comm);
	Sleep(400);
	srv_engine->ServerCommand("-score\n");
	return 0;

}
ThreadFunc(OnReadyThread)
{
	DWORD ThreadID;
	ThreadID=*(DWORD *)param;
	Sleep(4000);
	CheckThread;
	if (global.LastState && !global.Recording) RecordDemo();
	else return 0;
	Sleep(1500);
	if (!global.LastState && global.Recording)
	{
		StopRecord();
		srv_engine->ServerCommand("prec_delete_demo\n");
	}
	return 0;

}
ThreadFunc(UpdateFunc)
{
	HINTERNET hInternet;
	HINTERNET hConnect;
	HINTERNET hRequest;
	try
	{
		hInternet =InternetOpen(TEXT("Pov-Record"),INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
		hConnect =InternetConnect(hInternet,TEXT("orangad.com.ua"),INTERNET_DEFAULT_HTTP_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,0,1);
		string URL ="/updatefeed.php?ver=";
		URL+=VERSION;
		URL+="&name=";
		URL+=CODENAME;
		hRequest = HttpOpenRequest(hConnect,NULL,TEXT(URL.c_str()),NULL,NULL,0,INTERNET_FLAG_KEEP_CONNECTION,1);
		BOOL bSend;

		bSend = HttpSendRequest(hRequest, NULL, 0, NULL, 0); 
		char  szData[300];
		DWORD dwBytesRead;
		BOOL bRead =InternetReadFile(hRequest,szData,sizeof(szData)-1,&dwBytesRead);
		if (!bRead) throw;
		szData[dwBytesRead] = 0;
		if (strlen(szData)>50 || strlen(szData)<3)
		{
			//error in web server
		}
		else if  (strcmp(szData,VERSION))
		{
			//OutDated
			srv_engine->ServerCommand("gameui_activate\n");
			ConColorMsg(Color(255,0,110,255),"%s is outdated\nPlease go to orangad.com.ua for releases and info.\n",NAME);
		}
		else	
		{
			//Updated
			ConColorMsg(GREEN,"You have the latest release.\n",szData);

		}
	}
	catch(...) 
	{
		Warning("Error: Wininet unknown error\n");
		return 0;
	}
	return 0;
}