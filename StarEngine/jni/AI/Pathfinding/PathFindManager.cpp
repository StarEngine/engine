#include "PathFindManager.h"
#include "../../Objects/Object.h"
#include "../../StarComponents.h"
#include <algorithm>

namespace star
{
#ifdef STAR2D
	const pos PathFindManager::NO_PATH_AVAILBLE = pos(-123456.0f, -123456.0f);
#else
	const vec3 PathFindManager::NO_PATH_AVAILBLE = vec3(-123456.0f, -123456.0f, -123456.0f);
#endif
	PathFindManager * PathFindManager::m_pPathFindManager = nullptr;

	bool idCheckerCompare(int32 leftId, int32 rightId) 
	{
		return (leftId == rightId);
	}

	PathFindManager::PathFindManager(void):
		m_ObjectList(),
		m_PositionList(),
		m_pStartCell(nullptr),
		m_pEndCell(nullptr),
		m_OpenList(),
		m_VisitedList(),
		m_PathToGoal(),
		m_bInitializedStartGoal(false),
		m_bFoundGoal(false)
	{
	}
	
	PathFindManager::~PathFindManager(void)
	{
		for(auto cell : m_OpenList)
		{
			delete cell;
		}
		m_OpenList.clear();

		delete m_pEndCell;
		m_pEndCell = nullptr;

		for(auto cell : m_VisitedList)
		{
			delete cell;
		}
		m_VisitedList.clear();

		m_ObjectList.clear();
	}

	PathFindManager * PathFindManager::GetInstance()
	{
		if(m_pPathFindManager == nullptr)
		{
			m_pPathFindManager = new PathFindManager();
		}
		return m_pPathFindManager;
	}

	void PathFindManager::AddObject(Object* object)
	{
		if(object->GetComponent<PathFindNodeComponent>() != nullptr)
		{
			m_ObjectList.push_back(object);
		}
	}

	void PathFindManager::RemoveObject(const Object* object)
	{
		m_ObjectList.erase(find(m_ObjectList.begin(), m_ObjectList.end(), object));
	}

#ifdef STAR2D
	void PathFindManager::FindPath(const pos& currentPos, const pos& targetPos)
	{
		//Clear and refill the positionlist
		m_PositionList.clear();
		for(auto object : m_ObjectList)
		{
			pos pos = object->GetTransform()->GetWorldPosition();
			m_PositionList.push_back(pos);
		}
		
		//Check if the startpos or the targetpos are accessible
		if(find(m_PositionList.begin(), m_PositionList.end(), currentPos) == m_PositionList.end())
		{
			return;
		}
		
		//if not initialized, clear everything and initialize
		if(!m_bInitializedStartGoal)
		{
			for(auto searchCell : m_OpenList)
			{
				delete searchCell;
			}

			for(auto searchCell : m_VisitedList)
			{
				delete searchCell;
			}

			m_OpenList.clear();
			m_VisitedList.clear();
			m_PathToGoal.clear();
			
			//Initialize start
			SearchCell start;
			start.X = static_cast<int32>(currentPos.x);
			start.Y = static_cast<int32>(currentPos.y);

			//Initiliaze end
			SearchCell end;
			end.X = static_cast<int32>(targetPos.x);
			end.Y = static_cast<int32>(targetPos.y);

			SetStartAndGoal(start, end);
			m_bInitializedStartGoal = true;
		}
		ContinuePath();
	}
#else
	void PathFindManager::FindPath(const vec3& currentPos, const vec3& targetPos)
	{
		//Clear and refill the positionlist
		m_PositionList.clear();
		for(auto object : m_ObjectList)
		{
			vec3 pos = object->GetComponent<TransformComponent>()->GetWorldPosition();
			m_PositionList.push_back(pos);
		}

		//Check if the startpos or the targetpos are accessible
		if(find(m_PositionList.begin(), m_PositionList.end(), currentPos) == m_PositionList.end())
		{
			return;
		}

		//if not initialized, clear everything and initialize
		if(!m_bInitializedStartGoal)
		{
			for(auto searchCell : m_OpenList)
			{
				delete searchCell;
			}

			for(auto searchCell : m_VisitedList)
			{
				delete searchCell;
			}

			m_OpenList.clear();
			m_VisitedList.clear();
			m_PathToGoal.clear();

			//Initialize start
			SearchCell start;
			start.X = static_cast<int32>(currentPos.x);
			start.Y = static_cast<int32>(currentPos.y);

			//Initiliaze end
			SearchCell end;
			end.X = static_cast<int32>(targetPos.x);
			end.Y = static_cast<int32>(targetPos.y);

			SetStartAndGoal(start, end);
			m_bInitializedStartGoal = true;
		}
		ContinuePath();
	}
#endif

	void PathFindManager::SetStartAndGoal(const SearchCell& start, const SearchCell& end)
	{
		m_pStartCell = new SearchCell(start.X, start.Y, NULL);
		m_pEndCell = new SearchCell(end.X, end.Y, NULL);

		m_pStartCell->G = 0;
		m_pStartCell->H = m_pStartCell->ManhattanDistance(m_pEndCell);
		m_OpenList.push_back(m_pStartCell);
	}

	SearchCell* PathFindManager::GetNextCell()
	{
		//reset values
		float32 bestF = 999999.0f;
		int32 cellIndex = -1;
		SearchCell* nextCell = nullptr;

		//find closest
		for(uint16 i = 0; i < m_OpenList.size(); ++i)
		{
			if(m_OpenList[i]->GetF() < bestF)
			{
				bestF = m_OpenList[i]->GetF();
				cellIndex = i;
			}
		}

		if(cellIndex >= 0)
		{
			nextCell = m_OpenList[cellIndex];
			
			if(find(m_PositionList.begin(), m_PositionList.end(),pos(nextCell->X, nextCell->Y)) 
				== m_PositionList.end())
			{
				Logger::GetInstance()->Log(LogLevel::Info,
					_T("Position not accessible (GetNextCell())"),
					STARENGINE_LOG_TAG);
				return nullptr;
			}
			
			m_VisitedList.push_back(nextCell);
			m_OpenList.erase(m_OpenList.begin() + cellIndex);
		}
		return nextCell;
	}

	void PathFindManager::PathOpened(int32 x, int32 y, float32 newCost, SearchCell *parent, Direction dir)
	{
		//check if position is accesible
		if(find(m_PositionList.begin(), m_PositionList.end(), pos(x,y)) == m_PositionList.end())
		{
			return;
		}

		//check if there are no walls blocking the diagonal movement
		switch (dir)
		{
#ifdef STAR2D
			case Direction::GoingUpLeft:
			{
				if(find(m_PositionList.begin(), m_PositionList.end(), pos(x,y-1)) == m_PositionList.end())
				{
					return;
				}
				if(find(m_PositionList.begin(), m_PositionList.end(), pos(x+1,y)) == m_PositionList.end())
				{
					return;
				}
				break;
			}
			case Direction::GoingUpRight:
			{
				if(find(m_PositionList.begin(), m_PositionList.end(), pos(x,y-1)) == m_PositionList.end())
				{
					return;
				}
				if(find(m_PositionList.begin(), m_PositionList.end(), pos(x-1,y)) == m_PositionList.end())
				{
					return;
				}
				break;
			}
			case Direction::GoingDownLeft:
			{
				if(find(m_PositionList.begin(), m_PositionList.end(), pos(x,y+1)) == m_PositionList.end())
				{
					return;
				}
				if(find(m_PositionList.begin(), m_PositionList.end(), pos(x+1,y)) == m_PositionList.end())
				{
					return;
				}
				break;
			}
			case Direction::GoingDownRight:
			{
				if(find(m_PositionList.begin(), m_PositionList.end(), pos(x,y+1)) == m_PositionList.end())
				{
					return;
				}
				if(find(m_PositionList.begin(), m_PositionList.end(), pos(x-1,y)) == m_PositionList.end())
				{
					return;
				}
				break;
			}
#else
			case Direction::GoingUpLeft:
			{
				if(find(m_PositionList.begin(), m_PositionList.end(), vec3(x,y-1,0)) == m_PositionList.end())
				{
					return;
				}
				if(find(m_PositionList.begin(), m_PositionList.end(), vec3(x+1,y,0)) == m_PositionList.end())
				{
					return;
				}
				break;
			}
			case Direction::GoingUpRight:
			{
				if(find(m_PositionList.begin(), m_PositionList.end(), vec3(x,y-1,0)) == m_PositionList.end())
				{
					return;
				}
				if(find(m_PositionList.begin(), m_PositionList.end(), vec3(x-1,y,0)) == m_PositionList.end())
				{
					return;
				}
				break;
			}
			case Direction::GoingDownLeft:
			{
				if(find(m_PositionList.begin(), m_PositionList.end(), vec3(x,y+1,0)) == m_PositionList.end())
				{
					return;
				}
				if(find(m_PositionList.begin(), m_PositionList.end(), vec3(x+1,y,0)) == m_PositionList.end())
				{
					return;
				}
				break;
			}
			case Direction::GoingDownRight:
			{
				if(find(m_PositionList.begin(), m_PositionList.end(), vec3(x,y+1,0)) == m_PositionList.end())
				{
					return;
				}
				if(find(m_PositionList.begin(), m_PositionList.end(), vec3(x-1,y,0)) == m_PositionList.end())
				{
					return;
				}
				break;
			}
#endif
			default:
				break;
		}

		//check if position has been visited
		int32 id = y * WORLD_SIZE + x;
		for (uint16 i=0; i<m_VisitedList.size(); ++i)
		{
			if(id == m_VisitedList[i]->Id)
			{
				return;
			}
		}

		//Get the best next step
		SearchCell* newCell = new SearchCell(x,y, parent);
		newCell->G = newCost;
		newCell->H = parent->ManhattanDistance(m_pEndCell) -1;

		for (auto searchCell : m_OpenList)
		{
			if(id == searchCell->Id)
			{
				float32 newF = newCell->G + newCost + searchCell->H;

				//Check if it's better then the old one
				if(searchCell->GetF() > newF)
				{
					searchCell->G = newCell->G + newCost;
					searchCell->Parent = newCell;
				}
				else
				{
					delete newCell;
					return;
				}
			}
		}
		m_OpenList.push_back(newCell);
	}

	void PathFindManager::ContinuePath()
	{
		if(m_OpenList.empty())
		{
			return;
		}

		SearchCell* currentCell = GetNextCell();
		if(currentCell == nullptr)
		{
			return;
		}

		//Reached the end?
		if(currentCell->Id == m_pEndCell->Id && !m_bFoundGoal)
		{
			m_pEndCell->Parent = currentCell->Parent;
			SearchCell* getPath;
			for(getPath = m_pEndCell; getPath != NULL; getPath = getPath->Parent)
			{
#ifdef STAR2D
				vec2 temp(getPath->X, getPath->Y);
#else
				vec3 temp(getPath->X, getPath->Y, 0);
#endif
				m_PathToGoal.push_back(pos(temp));
			}
			
			tstringstream str;
			for(auto element : m_PathToGoal)
			{
				str << _T("(")<< element.x<< _T(", ") << element.y << _T(")\n");
			}

			m_bFoundGoal = true;
			return;
		}
		//if not, let's go look for the good way
		else
		{
			//RightSide
			PathOpened(currentCell->X + STEP_SIZE, currentCell->Y, currentCell->G + 1,
				currentCell, Direction::GoingRight);
			//LeftSide				  
			PathOpened(currentCell->X - STEP_SIZE, currentCell->Y, currentCell->G + 1,
				currentCell, Direction::GoingLeft);
			//TopSide
			PathOpened(currentCell->X, currentCell->Y + STEP_SIZE, currentCell->G + 1,
				currentCell, Direction::GoingUp);
			//DownSide								
			PathOpened(currentCell->X, currentCell->Y - STEP_SIZE, currentCell->G + 1,
				currentCell, Direction::GoingDown);

			//left-up diagonal
			PathOpened(currentCell->X - STEP_SIZE, currentCell->Y + STEP_SIZE, currentCell->G + 1.414f,
				currentCell, Direction::GoingUpLeft);
			//right-up diagonal		  								
			PathOpened(currentCell->X + STEP_SIZE, currentCell->Y + STEP_SIZE, currentCell->G + 1.414f,
				currentCell, Direction::GoingUpRight);
			//left-down diagonal	  								
			PathOpened(currentCell->X - STEP_SIZE, currentCell->Y - STEP_SIZE, currentCell->G + 1.414f,
				currentCell, Direction::GoingDownLeft);
			//right-down diagonal	  								
			PathOpened(currentCell->X + STEP_SIZE, currentCell->Y - STEP_SIZE, currentCell->G + 1.414f,
				currentCell, Direction::GoingDownRight);
			
			for (uint16 i = 0 ; i < m_OpenList.size() ; ++i)
			{
				int32 id = m_OpenList[i]->Id;
				m_OpenList.erase(std::remove_if(m_OpenList.begin(), m_OpenList.end(),
					[&id](SearchCell * currentCell)
					{
						if(currentCell->Id == id)
						{
							delete currentCell;
							return true;
						}
						return false;
					}), m_OpenList.end());
			}
		}
	}

#ifdef STAR2D
	const pos & PathFindManager::NextPathPos(Object* enemy)
	{
		uint16 index = 1;

		pos & nextPos = m_PathToGoal[m_PathToGoal.size() - index];
		pos distance = nextPos - enemy->GetTransform()->GetWorldPosition();
		
		if(index < m_PathToGoal.size())
		{
			if(distance.length() < 10)//[TODO] Radius->enemy awareness radius ::put variable in here instead of number)
			{
				m_PathToGoal.erase(m_PathToGoal.end() - index);
			}
		}
		return nextPos;
	}

	const pos & PathFindManager::GetStep(uint16 step) const
	{
		if(m_PathToGoal.size() == 0)
		{
			Logger::GetInstance()->Log(LogLevel::Warning,
				_T("There is no path availble."),
				STARENGINE_LOG_TAG);
			return NO_PATH_AVAILBLE;
		}

		if (step >= m_PathToGoal.size() - 1)
		{
			step = m_PathToGoal.size() - 1;
		}
		return m_PathToGoal[m_PathToGoal.size() - step - 1];
	}
#else
	const vec3 & PathFindManager::NextPathPos(Object* enemy)
	{
		uint16 index = 1;

		vec3 & nextPos = m_PathToGoal[m_PathToGoal.size() - index];
		vec3 distance = nextPos - enemy->GetTransform()->GetWorldPosition();
		
		if(index < m_PathToGoal.size())
		{
			if(distance.length() < 10)//[TODO] Radius->enemy awareness radius ::put variable in here instead of number)
			{
				m_PathToGoal.erase(m_PathToGoal.end() - index);
			}
		}
		return nextPos;
	}

	vec3 PathFindManager::GetStep(uint16 step)
	{
		if(m_PathToGoal.size() == 0)
		{
			Logger::GetInstance()->Log(LogLevel::Info,
				_T("There is no path availble."), STARENGINE_LOG_TAG);
			return NO_PATH_AVAILBLE;
		}

		if (step >= m_PathToGoal.size() - 1)
		{
			step = m_PathToGoal.size() - 1;
		}
		return m_PathToGoal[m_PathToGoal.size() - step - 1];
	}
#endif

	void PathFindManager::ClearOpenList()
	{
		m_OpenList.clear();
	}

	void PathFindManager::ClearVisitedList()
	{
		m_VisitedList.clear();
	}

	void PathFindManager::ClearPathToGoal()
	{
		m_PathToGoal.clear();
	}

	bool PathFindManager::GetInitializedGoal() const
	{
		return m_bInitializedStartGoal;
	}

	bool PathFindManager::GetFoundGoal() const
	{
		return m_bFoundGoal;
	}
}
