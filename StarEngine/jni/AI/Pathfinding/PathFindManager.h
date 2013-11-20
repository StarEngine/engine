#pragma once
#include <vector>
#include "SearchCell.h"
#include "../../defines.h"

namespace star
{
	struct Context;
	class Object;

	enum Direction
	{
		GoingUp,
		GoingLeft,
		GoingDown,
		GoingRight,
		GoingUpLeft,
		GoingUpRight,
		GoingDownLeft,
		GoingDownRight
	};

	class PathFindManager
	{
	public:
		~PathFindManager(void);
		static PathFindManager * GetInstance();

		void AddObject(Object* object);
		void RemoveObject(const Object* object);
		
		void AddObstacle(Object* object);

#ifdef STAR2D
		void FindPath(const pos& currentPos, const pos& targetPos);
		const pos & NextPathPos(Object* enemy);
		const pos & GetStep(uint16 step) const;
#else
		void FindPath(const vec3& currentPos, const vec3& targetPos);
		const vec3 & NextPathPos(Object* enemy);
		const vec3 & GetStep(uint16 step) const;
#endif

		void ClearOpenList();
		void ClearVisitedList();
		void ClearPathToGoal();
		bool GetInitializedGoal() const;
		bool GetFoundGoal() const;

	private:
		PathFindManager(void);
		void SetStartAndGoal(const SearchCell& start, const SearchCell& end);
		void PathOpened(int32 x, int32 y, float32 newCost, SearchCell *parent, Direction dir);
		SearchCell *GetNextCell();
		void ContinuePath();

		static PathFindManager * m_pPathFindManager;
		
		//Contains the object* and positions where you can walk on
		std::vector<Object*> m_ObjectList;

#ifdef STAR2D
		std::vector<pos> m_PositionList;
#else
		std::vector<vec3> m_PositionList;
#endif

		//Containers for a* algorithm
		// [COMMENT] why are you making pointers of these variables?
		// why not just use them as value objects?! (prevents the change 
		// of getting memory leaks )
		SearchCell *m_pStartCell, *m_pEndCell;
		std::vector<SearchCell*> m_OpenList;
		std::vector<SearchCell*> m_VisitedList;

#ifdef STAR2D
		std::vector<pos> m_PathToGoal;
#else
		std::vector<vec3> m_PathToGoal;
#endif

		bool m_bInitializedStartGoal;
		bool m_bFoundGoal;

		static const int32 WORLD_SIZE = 100;
		static const int32 STEP_SIZE = 1;

#ifdef STAR2D
		static const pos NO_PATH_AVAILBLE;
#else
		static const vec3 NO_PATH_AVAILBLE;
#endif

		PathFindManager(const PathFindManager& yRef);
		PathFindManager(PathFindManager&& yRef);
		PathFindManager& operator=(const PathFindManager& yRef);
	};
}

