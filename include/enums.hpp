#pragma once

enum Orientation : char {
	TOP = 1,
	DOWN = 2,
	RIGHT = 3,
	LEFT = 4
};

enum GameMode : char {
	PLAYER_WAITING,
	BOAT_PLACEMENT_PLAYER_ONE,
	BOAT_PLACEMENT_PLAYER_TWO,
	PLAY_PLAYER_ONE,
	PLAY_PLAYER_TWO,
	END
};