# PlayerCameraRotateFromPoint
A San Andreas Multiplayer include to let the camera of a player rotate around a position.

# Functions
```PAWN
native PlayerCameraRotateFromPoint(playerid, Float:x, Float:y, Float:z, Float:range, cam_speed = 3, bool: cam_overview = false, Float: cam_overview_height = 20.0);
native StopPlayerCameraRotate(playerid, bool:set_camera_behind = true);
native ContinuePlayerCameraRotate(playerid);
native SetPlayerCameraRotateToLeft(playerid);
native SetPlayerCameraRotateToRight(playerid);
```

## Clarification

### PlayerCameraRotateFromPoint
* playerid - the id of the player to set the camera rotation
* Float:x, Float:y, Float:z - the x, y and z position in-game.
* Float: range - how far the camera should rotate from the position aka range.
* cam_speed - the speed (in seconds) of the moving camera from stop to stop (Optional / Default = 3 seconds)
* cam_overview - should the camera act like an "overview", meaning it'll look down to the position instead of otherwise. (Optional / Default = no)
* cam_overview_height - the height of the camera that has to be added to the z position (so it can look down) (Optional / Default = 20)

### StopPlayerCameraRotate
* playerid - the id of the player to stop the camera rotation
* bool: set_camera_behind - set camera behind player (Default = yes)

### ContinuePlayerCameraRotate
* playerid - the id of the player to continue the camera rotation

### SetPlayerCameraRotateToLeft
* playerid - the id of the player to set the camera rotation to left

### SetPlayerCameraRotateToRight
* playerid - the id of the player to set the camera rotation to right

# Example/Installation
* An example is located at ``example.pwn`` - just an edited ``bare.pwn``
* Download it manually or use sampctl: `sampctl package install MichaelBelgium/PlayerCameraRotateFromPoint`

## Video

<a href="https://www.youtube.com/watch?v=A9_IA5tzcAg">Here</a>

# Extra credits
* robin_be for helping
