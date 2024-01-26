//=========== (C) Copyright 2005 Valve, L.L.C. All rights reserved. ===========
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//=============================================================================

// No spaces in event names, max length 32
// All strings are case sensitive
//
// valid data key types are:
//   string : a zero terminated string
//   bool   : unsigned int, 1 bit
//   byte   : unsigned int, 8 bit
//   short  : signed int, 16 bit
//   long   : signed int, 32 bit
//   float  : float, 32 bit
//   local  : any data, but not networked to clients
//
// following key names are reserved:
//   local      : if set to 1, event is not networked to clients
//   unreliable : networked, but unreliable
//   suppress   : never fire this event
//   time	: firing server time
//   eventid	: holds the event ID

"ModEvents"
{
	"intro_finish"
	{
		"player"	"short"		// entindex of the player
	}

	"intro_nextcamera"
	{
		"player"	"short"		// entindex of the player
	}	

	"player_changeclass"
	{
		"userid"	"short"		// user ID who changed class
		"class"		"short"		// class that they changed to
	}

	"player_death"		// a game event, name may be 32 charaters long
	{
		// this extends the original player_death 
		"userid"	"short"   	// user ID who died				
		"attacker"	"short"	 	// user ID who killed
		"weapon"	"string" 	// weapon name killer used 
		"weaponid"	"short"		// ID of weapon killed used
		"damagebits"	"long"		// bits of type of damage
		"customkill"	"short"		// type of custom kill
		"assister"	"short"		// user ID of assister
		"weapon_logclassname"	"string" 	// weapon name that should be printed on the log
		"stun_flags"	"short"	// victim's stun flags at the moment of death
		"death_flags"	"short" //death flags.
		
	//	"dominated"	"short"		// did killer dominate victim with this kill
	//	"assister_dominated" "short"	// did assister dominate victim with this kill
	//	"revenge"	"short"		// did killer get revenge on victim with this kill
	//	"assister_revenge" "short"	// did assister get revenge on victim with this kill
	//	"first_blood"	"bool"		// was this a first blood kill
	//	"feign_death"	"bool"	// the victim is feign death
	}
	
	"object_destroyed"
	{			
		"userid"	"short"   	// user ID who died				
		"attacker"	"short"	 	// user ID who killed
		"assister"	"short"		// user ID of assister
		"weapon"	"string" 	// weapon name killer used 
		"weaponid"	"short"		// id of the weapon used
		"objecttype"	"short"		// type of object destroyed
		"index"		"short"		// index of the object destroyed
		"was_building"	"bool"		// object was being built when it died
	}

	"tf_map_time_remaining"
	{
		"seconds"	"long"
	}

	"tf_game_over"
	{
		"reason"	"string"	// why the game is over ( timelimit, winlimit )
	}
	"ctf_flag_captured"
	{
		"capping_team"			"short"
		"capping_team_score"	"short"
	}
	"controlpoint_initialized"
	{
	}
	"controlpoint_updateimages"
	{
		"index"		"short"		// index of the cap being updated
	}
	"controlpoint_updatelayout"
	{
		"index"		"short"		// index of the cap being updated
	}
	"controlpoint_updatecapping"
	{
		"index"		"short"		// index of the cap being updated
	}
	"controlpoint_updateowner"
	{
		"index"		"short"		// index of the cap being updated
	}
	"controlpoint_starttouch"
	{
		"player"	"short"		// entindex of the player
		"area"		"short"		// index of the control point area
	}

	"controlpoint_endtouch"
	{
		"player"	"short"		// entindex of the player
		"area"		"short"		// index of the control point area
	}
	
	"controlpoint_pulse_element"
	{
		"player"	"short"		// entindex of the player
	}

	"controlpoint_fake_capture"
	{
		"player"	"short"		// entindex of the player
		"int_data"	"short"
	}

	"controlpoint_fake_capture_mult"
	{
		"player"	"short"		// entindex of the player
		"int_data"	"short"
	}

	"teamplay_round_start"			// round restart
	{
		"full_reset"	"bool"		// is this a full reset of the map
	}
	
	"teamplay_round_active"			// called when round is active, players can move
	{
		// nothing for now
	}

	"teamplay_waiting_begins"
	{
		// nothing for now
	}
	
	"teamplay_waiting_ends"
	{
		// nothing for now
	}
	
	"teamplay_waiting_abouttoend"
	{
	}

	"teamplay_restart_round"
	{
		// nothing for now
	}

	"teamplay_ready_restart"
	{
		// nothing for now
	}

	"teamplay_round_restart_seconds"
	{
		"seconds"	"short"
	}

	"teamplay_team_ready"
	{
		"team"		"byte"		// which team is ready
	}

	"teamplay_round_win"
	{
		"team"		"byte"		// which team won the round
		"winreason"	"byte"		// the reason the team won
		"flagcaplimit"	"short"		// if win reason was flag cap limit, the value of the flag cap limit
		"full_round"	"short"		// was this a full round or a mini-round
		"round_time"	"float"		// elapsed time of this round
		"losing_team_num_caps"	"short"	// # of caps this round by losing team
		"was_sudden_death" "byte"	// did a team win this after entering sudden death
	}

	"teamplay_update_timer"
	{
	}

	"teamplay_round_stalemate"
	{
		"reason"	"byte"		// why the stalemate is occuring
	}
	
	"teamplay_overtime_begin"
	{
		// nothing for now
	}	
	
	"teamplay_overtime_end"
	{
		// nothing for now
	}		
	
	"teamplay_suddendeath_begin"
	{
		// nothing for now
	}
	
	"teamplay_suddendeath_end"
	{
		// nothing for now
	}	
	
	"teamplay_game_over"
	{
		"reason"	"string"	// why the game is over ( timelimit, winlimit )
	}

	"teamplay_map_time_remaining"
	{
		"seconds"	"short"
	}

	"teamplay_broadcast_audio"
	{
		"team"		"byte"		// which team should hear the broadcast. 0 will make everyone hear it.
		"sound"		"string"	//sound to play
	}

	"teamplay_timer_flash"
	{
		"time_remaining"	"short"	// how many seconds until the round ends
	}	

	"teamplay_timer_time_added"
	{
		"timer"	"short"		// entindex of the timer	
		"seconds_added"	"short"		// how many seconds were added to the round timer	
	}

	"teamplay_point_startcapture"
	{
		"cp"		"byte"			// index of the point being captured
		"cpname"	"string"		// name of the point
		"team"		"byte"			// which team currently owns the point
		"capteam"	"byte"			// which team is capping
		"cappers"	"string"		// string where each character is a player index of someone capping
		"captime"	"float"			// time between when this cap started and when the point last changed hands
	}

	"teamplay_point_captured"
	{
		"cp"		"byte"			// index of the point that was captured
		"cpname"	"string"		// name of the point
		"team"		"byte"			// which team capped
		"cappers"	"string"		// string where each character is a player index of someone that capped
	}
	
	"teamplay_capture_broken"
	{
		"cp"		"byte"
		"cpname"	"string"
		"time_remaining" "float"
	}

	"teamplay_capture_blocked"
	{
		"cp"		"byte"			// index of the point that was blocked
		"cpname"	"string"		// name of the point
		"blocker"	"byte"			// index of the player that blocked the cap
	}
	"teamplay_flag_event"
	{
		"player"	"short"			// player this event involves
		"carrier"	"short"			// the carrier if needed
		"eventtype"	"short"			// pick up, capture, defend, dropped
	}
	"teamplay_win_panel"		
	{
		"panel_style"		"byte"		// for client to determine layout		
		"winning_team"		"byte"		
		"winreason"		"byte"		// the reason the team won
		"cappers"		"string"	// string where each character is a player index of someone that capped
		"flagcaplimit"		"short"		// if win reason was flag cap limit, the value of the flag cap limit
		"blue_score"		"short"		// red team score
		"red_score"		"short"		// blue team score
		"blue_score_prev"	"short"		// previous red team score
		"red_score_prev"	"short"		// previous blue team score
		"round_complete"	"short"		// is this a complete round, or the end of a mini-round
		"rounds_remaining"	"short"		// # of rounds remaining for wining team, if mini-round
		"player_1"		"short"
		"player_1_points"	"short"
		"player_2"		"short"
		"player_2_points"	"short"
		"player_3"		"short"
		"player_3_points"	"short"
	}
	"teamplay_teambalanced_player"
	{
		"player"	"short"		// entindex of the player
		"team"		"byte"		// which team the player is being moved to
	}

	"teamplay_setup_finished"
	{
	}

	"show_freezepanel"
	{
		"killer"	"short"		// entindex of the killer entity
	}

	"hide_freezepanel"
	{
	}

	"freezecam_started"
	{
	}

	"localplayer_changeteam"
	{
	}

	"localplayer_changeclass"
	{
	}
	
	"localplayer_respawn"
	{
	}
		
	"building_info_changed"
	{
		"building_type"		"byte"
		"remove"			"byte"
	}

	"localplayer_changedisguise"
	{
		"disguised"		"bool"
	}
	
	"player_account_changed"
	{
		"old_value"		"short"
		"new_value"		"short"
	}
	
	"spy_pda_reset"
	{
	}

	"flagstatus_update"
	{
	}

	"player_stats_updated"
	{
		"forceupload"	"bool"
	}
	"playing_commentary"
	{
	}
	
	"player_chargedeployed"
	{
		"userid"	"short"		// user ID of medic who deployed charge
		"targetid"	"short"		// user ID of who the medic charged
	}
	
	"player_builtobject"
	{
		"userid"	"short"		// user ID of the builder
		"object"	"byte"
		"index"		"short"		// index of the object
	}
	
	"achievement_earned"
	{
		"player"	"byte"		// entindex of the player
		"achievement"	"short"		// achievement ID
	}
	
	"spec_target_updated"
	{
	}

	"tournament_stateupdate"
	{
		"userid"	"short"		// user ID on server
		"namechange"	"bool"
		"readystate"	"short"
		"newname"	"string"	// players new name
	}

	"player_calledformedic"
	{
		"userid"	"short"
	}

	"localplayer_becameobserver"
	{
	}
	
	"player_ignited_inv"		// sent when a player is ignited by a pyro who is being invulned, only to the medic who's doing the invulning
	{
		"pyro_entindex"		"byte"		// entindex of the pyro who ignited the victim
		"victim_entindex"	"byte"		// entindex of the player ignited by the pyro
		"medic_entindex"	"byte"		// entindex of the medic releasing the invuln
	}
	"player_ignited"			// sent when a player is ignited, only to the two players involved
	{
		"pyro_entindex"		"byte"		// entindex of the pyro who ignited the victim
		"victim_entindex"	"byte"		// entindex of the player ignited by the pyro
		"weaponid"			"byte"		// weaponid of the weapon used
	}
	
	"player_extinguished"		// sent when a burning player is extinguished by a medic
	{
		"victim"	"byte"		// entindex of the player that was extinguished
		"healer"	"byte"		// entindex of the player who did the extinguishing
	}
	
	"player_teleported"
	{
		"userid"	"short"		// userid of the player
		"builderid"	"short"		// userid of the player who built the teleporter
	}
	
	// client only
	"player_healedmediccall"	// local player heals someone who called for medic.
	{
		"userid"	"short"		// userid of person who got healed
	}
	
	// client only
	"localplayer_chargeready"		// local player has full medic charge
	{
	}
	
	"localplayer_winddown"		// local player minigun winddown
	{
	}
	
	"player_invulned"
	{
		"userid"	"short"
		"medic_userid"	"short"
	}
	
	"escort_speed"
	{
		"team"		"byte"			// which team
		"speed"		"byte"
		"players"	"byte"
	}
	
	"escort_progress"
	{
		"team"		"byte"			// which team
		"progress"	"float"
		"reset"		"bool"
	}

	"escort_recede"
	{
		"team"			"byte"		// which team
		"recedetime"	"float"
	}

	"client_loadout_changed"
	{
	}
	
	"gameui_activated"
	{
	}
	
	"gameui_hidden"
	{
	}
	
	"player_escort_score"
	{
		"player"	"byte"
		"points"	"byte"
	}

	"player_healonhit"
	{
		"amount"		"short"
		"entindex"		"byte"
	}
	
	"player_stealsandvich"
	{
		"owner"			"short"
		"target"		"short"
	}
	
	"show_class_layout"
	{
		"show"	"bool"
	}	
	
	"show_vs_panel"
	{
		"show"	"bool"
	}

	"player_damaged"
	{
		"amount"		"short"
		"type"			"long"
	}
	
	"player_hurt"
	{
		"userid" "short"
		"health" "byte"
		"attacker" "short"
		"damageamount" "short"
		"crit" "bool"
	}

	"arena_player_notification"
	{
		"player"	"byte"
		"message"	"byte"
	}

	"arena_match_maxstreak"
	{
		"team"	"byte"
		"streak"	"byte"
	}

	"arena_round_start"			// called when round is active, players can move
	{
		// nothing for now
	}
	"arena_win_panel"		
	{
		"panel_style"		"byte"		// for client to determine layout		
		"winning_team"		"byte"		
		"winreason"		"byte"		// the reason the team won
		"cappers"		"string"	// string where each character is a player index of someone that capped
		"flagcaplimit"		"short"		// if win reason was flag cap limit, the value of the flag cap limit
		"blue_score"		"short"		// red team score
		"red_score"		"short"		// blue team score
		"blue_score_prev"	"short"		// previous red team score
		"red_score_prev"	"short"		// previous blue team score
		"round_complete"	"short"		// is this a complete round, or the end of a mini-round
		"player_1"		"short"
		"player_1_damage"	"short"
		"player_1_healing"	"short"
		"player_1_lifetime"	"short"
		"player_1_kills"	"short"
		"player_2"		"short"
		"player_2_damage"	"short"
		"player_2_healing"	"short"
		"player_2_lifetime"	"short"
		"player_2_kills"	"short"
		"player_3"		"short"
		"player_3_damage"	"short"
		"player_3_healing"	"short"
		"player_3_lifetime"	"short"
		"player_3_kills"	"short"
		"player_4"		"short"
		"player_4_damage"	"short"
		"player_4_healing"	"short"
		"player_4_lifetime"	"short"
		"player_4_kills"	"short"
		"player_5"		"short"
		"player_5_damage"	"short"
		"player_5_healing"	"short"
		"player_5_lifetime"	"short"
		"player_5_kills"	"short"
		"player_6"		"short"
		"player_6_damage"	"short"
		"player_6_healing"	"short"
		"player_6_lifetime"	"short"
		"player_6_kills"	"short"
	}
	
	"inventory_updated"
	{
	}
	
	"air_dash"
	{
		"player"	"byte"
	}
	
	"landed"
	{
		"player"	"byte"
	}
	
	"player_damage_dodged"
	{
		"damage"	"short"
	}
	
	"player_stunned"
	{
		"stunner"	"short"
		"victim"	"short"
		"victim_capping"	"bool"
		"big_stun"	"bool"
	}
	
	"scout_grand_slam"
	{
		"scout_id"	"short"
		"target_id"	"short"
	}
	
	"scout_slamdoll_landed"
	{
		"target_index" "short"
		"x"	"float"
		"y"	"float"
		"z"	"float"
	}

	"scout_slamdoll_landed"
	{
		"target_index" "short"
		"x"	"float"
		"y"	"float"
		"z"	"float"
	}

	"arrow_impact"
	{
		"attachedEntity" "short"
		"shooter" "short"
		"boneIndexAttached" "short"
		"bonePositionX" "float"
		"bonePositionY" "float"
		"bonePositionZ" "float"
		"boneAnglesX" "float"
		"boneAnglesY" "float"
		"boneAnglesZ" "float"
	}
	
	"player_jarated"			// sent when a player is jarated, only to the two players involved
	{
		"thrower_entindex"	"byte"		// entindex of the player who threw the jarate
		"victim_entindex"	"byte"		// entindex of the player receiving it
	}
	"player_jarated_fade"			// sent when a player is jarated, only to the two players involved
	{
		"thrower_entindex"	"byte"		// entindex of the player who threw the jarate
		"victim_entindex"	"byte"		// entindex of the player receiving it
	}
	"player_shield_blocked"			// sent when a player is jarated, only to the two players involved
	{
		"attacker_entindex"	"byte"		// entindex of the player who threw the jarate
		"blocker_entindex"	"byte"		// entindex of the player receiving it
	}
	"player_pinned"
	{
		"pinned"	"byte"
	}
	"player_healedbymedic"
	{
		"medic"		"byte"
	}
	
	"player_spawn"
	{
		"userid"	"short"		// user ID who spawned
		"team"		"short"		// team they spawned on
		"class"		"short"		// class they spawned as
	}	
	
	"player_sapped_object"
	{
		"userid"	"short"		// user ID of the spy
		"ownerid"	"short"		// user ID of the building owner
		"object"	"byte"
	}
	
	"item_found"
	{
		"player"		"byte"		// entindex of the player
		"quality"		"byte"		// quality of the item
		"item"			"string"	// item name (unlocalized)
	}
	
	"post_inventory_application"	// sent when a player gets a whole new set of items
	{
		"userid"	"short"
	}
	
	"controlpoint_unlock_updated"
	{
		"index"	"short"		// index of the cap being updated
		"time"	"float"		// time
	}
	
	"deploy_buff_banner"
	{
		"buff_type"		"byte"		// type of buff (skin index)
		"buff_owner"	"short"		// user id of the person who gets the banner
	}
	
	"medic_death"
	{
		"userid"	"short"   	// user ID who died				
		"attacker"	"short"	 	// user ID who killed
		"healing"	"short"		// amount healed in this life
		"charged"	"bool"		// had a full ubercharge?
	}
	
	"overtime_nag"
	{
	}
	
	"teams_changed"
	{
	}
}


