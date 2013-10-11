#pragma once
#include "BaseComponent.h"
#include "..\defines.h"
#include "..\Helpers\Rect.h"

namespace star
{
	struct Context;

	class PathFindNodeComponent final: public BaseComponent
	{
	public:
		PathFindNodeComponent();
		~PathFindNodeComponent(void);

		void Update(const Context& context);
		void Draw();

	private:
		void InitializeComponent();

		PathFindNodeComponent(const PathFindNodeComponent& t);
		PathFindNodeComponent(PathFindNodeComponent&& t);
		PathFindNodeComponent& operator=(const PathFindNodeComponent& t);
	};
}
