#pragma once

#include "defines.h"

namespace star
{
	struct Context;

	class BaseGame
	{
	public:
		BaseGame() {}
		virtual ~BaseGame() {}

		virtual void Initialize(int32, int32) = 0;

		virtual void Draw() = 0;
		virtual void Update(const Context &) = 0;

		virtual void End() = 0;

	private:
		BaseGame & operator=(const BaseGame&);
		BaseGame & operator=(BaseGame&&);
		BaseGame(const BaseGame &);
		BaseGame(BaseGame &&);
	};
}