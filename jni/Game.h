#pragma once

#include <defines.h>

namespace star
{
	struct Context;
	class SceneManager;
}

class Game
{
public:
	Game();
	~Game() {}

	status Initialize(int32 window_width, int32 window_height);
		
	status Update(const star::Context& context);
	status Draw();

	status End();
	
private:

	Game(const Game&);
	Game(Game&&);
	Game& operator=(const Game&);
};
