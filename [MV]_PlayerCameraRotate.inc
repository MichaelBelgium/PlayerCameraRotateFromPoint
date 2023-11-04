/*
							PlayerCameraRotateFromPoint
	A San Andreas Multiplayer include to let the camera of a player rotate around a position.

	Author: 
		MichaelBelgium

	Github repository: 
		https://github.com/MichaelBelgium/PlayerCameraRotateFromPoint

	Contributors: 
		MichaelBelgium
		adib-yg

	--------------------------------------------------------------------------------

	# Log change:

		## 2023-11-04 [4 Nov 2023]

			### New functions:
				* ContinuePlayerCameraRotate(playerid);
				* SetPlayerCameraRotateToLeft(playerid);
				* SetPlayerCameraRotateToRight(playerid);

			### New function parameters:
				* StopPlayerCameraRotate(playerid, bool:set_camera_behind = true);

			### Fixes:
				* Fixed 'OnPlayerConnect' hook
*/

#include <a_samp>

#if !defined MAX_CAM_STOPS
	#define MAX_CAM_STOPS 8
	// it's not possible to have the players camera rotate in a fill circle. 
	// Instead we work with stops. (Which means a polygon structure)
#endif
#if !defined CAM_DELAY
	#define CAM_DELAY 2000
	// set to 0 to have no delay between camera stops
#endif

static enum pCamData
{
	Float:CamPos[3],
	Float:Height,
	Speed,
	bool:Rotating,
	bool:Overview,
	CurrentID,
	RotateDirection // 1 = Left | 0 = Right
};

static g_pCamera[MAX_PLAYERS][pCamData], Float:g_CameraPositions[MAX_PLAYERS][MAX_CAM_STOPS][2];

forward MoveCamera(playerid,id);
forward Float:GetCameraPositionsFromPoint(Float:x, Float:y, Float:radius);

stock PlayerCameraRotateFromPoint(playerid, Float:x, Float:y, Float:z, Float:range, cam_speed = 3, bool: cam_overview = false, Float: cam_overview_height = 20.0)
{
	if(g_pCamera[playerid][Rotating]) return 0;

	g_pCamera[playerid][CamPos][0] = x;
	g_pCamera[playerid][CamPos][1] = y;
	g_pCamera[playerid][CamPos][2] = z;
	g_pCamera[playerid][Height] = cam_overview_height;
	g_pCamera[playerid][Speed] = cam_speed*1000;
	g_pCamera[playerid][Overview] = cam_overview;

	g_CameraPositions[playerid] = GetCameraPositionsFromPoint(g_pCamera[playerid][CamPos][0], g_pCamera[playerid][CamPos][1], range);
	g_pCamera[playerid][Rotating] = true;

	MoveCamera(playerid, (g_pCamera[playerid][RotateDirection] == 1 ? MAX_CAM_STOPS-1 : 0));
	return 1;
}

stock StopPlayerCameraRotate(playerid, bool:set_camera_behind = true)
{
	if (g_pCamera[playerid][Rotating]) {
		g_pCamera[playerid][Rotating] = false;
		if(set_camera_behind) SetCameraBehindPlayer(playerid);
	}
}

stock ContinuePlayerCameraRotate(playerid)
{
	if (!g_pCamera[playerid][Rotating] && g_pCamera[playerid][Speed] != 0)
	{ 
		g_pCamera[playerid][Rotating] = true;
		MoveCamera(playerid, g_pCamera[playerid][CurrentID]);
	}
}

stock SetPlayerCameraRotateToLeft(playerid)
{
	g_pCamera[playerid][RotateDirection] = 1;
}

stock SetPlayerCameraRotateToRight(playerid)
{
	g_pCamera[playerid][RotateDirection] = 0;
}

public MoveCamera(playerid,id)
{
	if(g_pCamera[playerid][Rotating])
	{
		new oID = id, nID;

		if (g_pCamera[playerid][RotateDirection] == 1) 
			nID = --id % MAX_CAM_STOPS; // Left
		else
			nID = ++id % MAX_CAM_STOPS; // Right
		
		g_pCamera[playerid][CurrentID] = nID;

		if(!g_pCamera[playerid][Overview])
			InterpolateCameraPos(playerid, g_CameraPositions[playerid][oID][0], g_CameraPositions[playerid][oID][1], g_pCamera[playerid][CamPos][2], g_CameraPositions[playerid][nID][0], g_CameraPositions[playerid][nID][1],  g_pCamera[playerid][CamPos][2], g_pCamera[playerid][Speed], CAMERA_MOVE);
		else
			InterpolateCameraPos(playerid, g_CameraPositions[playerid][oID][0], g_CameraPositions[playerid][oID][1], g_pCamera[playerid][CamPos][2]+g_pCamera[playerid][Height], g_CameraPositions[playerid][nID][0], g_CameraPositions[playerid][nID][1],  g_pCamera[playerid][CamPos][2]+g_pCamera[playerid][Height], g_pCamera[playerid][Speed], CAMERA_MOVE);			
		InterpolateCameraLookAt(playerid, g_pCamera[playerid][CamPos][0], g_pCamera[playerid][CamPos][1], g_pCamera[playerid][CamPos][2], g_pCamera[playerid][CamPos][0], g_pCamera[playerid][CamPos][1], g_pCamera[playerid][CamPos][2], g_pCamera[playerid][Speed], CAMERA_MOVE);

		SetTimerEx("MoveCamera", g_pCamera[playerid][Speed]+CAM_DELAY, false, "ii", playerid, nID);
	}
}

stock Float:GetCameraPositionsFromPoint(Float:x, Float:y, Float:radius)
{
	new Float:campos[MAX_CAM_STOPS][2];
	new Float:x2, Float:y2, Float:angle = 360/MAX_CAM_STOPS, Float:a = 0.0;
	for(new i=0; i<MAX_CAM_STOPS; i++)
	{
		x2 = x + floatcos(a,degrees) * radius;
		y2 = y + floatsin(a,degrees) * radius;
		a += angle;
		campos[i][0] = x2;
		campos[i][1] = y2;
	}
	return campos;
}

public OnPlayerConnect(playerid)
{
	g_pCamera[playerid][Rotating] = false;
	g_pCamera[playerid][RotateDirection] = 0;

	#if defined CameraRotate_OnPlayerConnect
		return CameraRotate_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect CameraRotate_OnPlayerConnect
#if defined CameraRotate_OnPlayerConnect
	forward CameraRotate_OnPlayerConnect(playerid);
#endif
