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

		virtual status Initialize(int32, int32) = 0;

		virtual status Draw() = 0;
		virtual status Update(const Context &) = 0;

		virtual status End() = 0;

	private:
		BaseGame & operator=(const BaseGame&);
		BaseGame(const BaseGame &);
		BaseGame(BaseGame &&);
	};
}