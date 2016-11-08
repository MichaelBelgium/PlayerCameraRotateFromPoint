#include <a_samp>
#include <zcmd>
#include <sscanf2>
#include <[MV]_PlayerCameraRotate>

main()
{
	print("\n----------------------------------");
	print("  Bare Script\n");
	print("----------------------------------\n");
}

public OnPlayerConnect(playerid)
{
	GameTextForPlayer(playerid,"~w~SA-MP: ~r~Bare Script",5000,5);
	return 1;
}

CMD:test(playerid,params[])
{
	new id, Float:x, Float:y, Float:z;
	if(sscanf(params,"i",id)) return 0;

	GetPlayerPos(playerid, x, y, z);

	switch(id)
	{
		case 0: PlayerCameraRotateFromPoint(playerid, x, y, z, 20.0, 1);
		case 1: PlayerCameraRotateFromPoint(playerid, x, y, z, 20.0, 1, true);
		default: PlayerCameraRotateFromPoint(playerid, 1448.3398,1518.5872,76.0976, 50.0, 3, true, 25.0);
	}
	return 1;
}

CMD:stop(playerid,params[])
{
	StopPlayerCameraRotate(playerid);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	StopPlayerCameraRotate(playerid);
	SetPlayerInterior(playerid,0);
	TogglePlayerClock(playerid,0);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
   	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	PlayerCameraRotateFromPoint(playerid, 1448.3398,1518.5872,76.0976, 50.0, 3, true, 25.0);
	return 1;
}

public OnGameModeInit()
{
	SetGameModeText("Bare Script");
	ShowPlayerMarkers(1);
	ShowNameTags(1);
	AllowAdminTeleport(1);

	AddPlayerClass(265,1958.3783,1343.1572,15.3746,270.1425,0,0,0,0,-1,-1);

	return 1;
}
