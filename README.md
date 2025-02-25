# Pov-Record by Orange

> [!NOTE]
> Now open source and updated. With hope that TF2 developers sign it again. :bowing_man:
> 

## Updated to x64 arcitecture and latest tf2 sdk :tada:

[Download lastest release](https://github.com/olegKoshmeliuk/Pov-Record/releases) and run TF2 with `-insecure` flag to test it

P-REC is a TF2 plugin for Windows operating systems created by Ukraine Orange that records demos, takes screenshots and logs your killstreaks automatically.

The original guide can be found [here](https://etf2l.org/p-rec/)



# INFO
Pov-Record  2.1.0

E-mail:oleg.koshmeliuk@gmail.com

Client plugin for TF2 which starts recording PoV demos when tournament mode starts (both team set Ready flag) and stops 
recording when game ends (support user filename format see PREC.cfg ). Also it can save time of your kill streaks and set bookmarks to any moment in game. Time of streaks 
and bookmarks are logged to file (see prec_log). Also it can show SourceTV statistic (max, total and avg. clients)


# INSTALL

To install plugin just copy directories in archive to your `tf` folder and add `exec prec` to your `cfg\autoexec.cfg`.

Edit `tf\custom\prec\addons\PREC.cfg` to change plugin's sounds and phrase settings.

Edit `tf\custom\prec\cfg\PREC_Settings.cfg` to change the plugin's default settings.

# CONSOLE
```
prec_show_stv_status (command) - Show current sourcetv status

prec_tag - Custom tag (can be used in demo name format) (default "")

prec_check_update - Check for updates on startup (default 1)

prec_stv_status  - Show SourceTV statistic after the match (default 1)

prec_notify 
			0-print to console
			1-say to team chat (default)
			2-show on hud

prec_log 
		    0-don't log
		    1-log into killstreaks.txt (default)
			2-log separately for each demo.
			3-log separately for each map.

prec_screens  - Make screenshoots of scoreboard and status. (default 0)

prec_delete_useless_demo - Delete demo files without bookmarks and killstreaks. (default 0)

prec_min_streak - minimum amount of kills withour dying to save time of kill streak (default 4)

prec_mark (command) - log bookmark. bind to some key in your config, for example: bind j "prec_mark"

prec_next_demoname - set this var if you want change name of next recorded demo.  (default "")

prec_mode	
			0-turn off addon.
			1-record only curstomnamed demos.
			2-record all demos (with mp_tournament 1). (default)
			3-record all demos 

prec_min_streak - Minimum kill streak to log (default 4)

prec_kill_delay - Max delay between kill's in KillStreaks (default 15)

prec_dir - Directory to save demos (default "")

prec_sound - Play sound when start/stop recording (1 - on (default) ,0 - off)

prec_about (command) - Plugin Info

prec_version - plugin version

prec_delete_demo (command) - Delete previous recorded demo

prec_record (command) - Record a demo.

prec_info (command) - List of all commands.
```

# BUILD

Clone the repository using the following command:

`git clone https://github.com/olegKoshmeliuk/Pov-Record`

Requirements:
 - Visual Studio 2022

Inside the cloned directory run:
```bat
createallprojects.bat
```
This will generate the Visual Studio project `prec.sln` which will be used to build your prec.

Then, on the menu bar, go to `Build > Build Solution`, and wait for everything to build.

[Posted on ETF2L forum](https://etf2l.org/forum/customise/topic-6647)
