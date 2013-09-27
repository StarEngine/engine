#include "PathFindManager.h"
#include "../SceneGraph/Object.h"
#include "../StarComponents.h"
#include <algorithm>

namespace star
{
	PathFindManager* PathFindManager::m_pPathFindManager = nullptr;

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
	}

	PathFindManager* PathFindManager::GetInstance()
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

	void PathFindManager::FindPath(const vec2& currentPos, const vec2& targetPos)
	{
		FindPath(vec3(currentPos.x, currentPos.y, 0), vec3(targetPos.x, targetPos.y, 0));
	}

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
			start.m_X = static_cast<int>(currentPos.x);
			start.m_Y = static_cast<int>(currentPos.y);

			//Initiliaze end
			SearchCell end;
			end.m_X = static_cast<int>(targetPos.x);
			end.m_Y = static_cast<int>(targetPos.y);

			SetStartAndGoal(start, end);
			m_bInitializedStartGoal = true;
		}
		ContinuePath();
	}

	void PathFindManager::SetStartAndGoal(const SearchCell& start, const SearchCell& end)
	{
		m_pStartCell = new SearchCell(start.m_X, start.m_Y, NULL);
		m_pEndCell = new SearchCell(end.m_X, end.m_Y, NULL);

		m_pStartCell->m_G = 0;
		m_pStartCell->m_H = m_pStartCell->ManhattanDistance(m_pEndCell);
		m_OpenList.push_back(m_pStartCell);
	}

	SearchCell* PathFindManager::GetNextCell()
	{
		//reset values
		float bestF = 999999.0f;
		int cellIndex = -1;
		SearchCell* nextCell = nullptr;

		//find closest
		for(uint16 i=0; i<m_OpenList.size(); ++i)
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
			
			if(find(m_PositionList.begin(), m_PositionList.end(),vec3(nextCell->m_X, nextCell->m_Y, 0)) == m_PositionList.end())
			{
				Logger::GetSingleton()->Log(LogLevel::Info, _T("Position not accessible (GetNextCell())"));
				return nullptr;
			}
			
			m_VisitedList.push_back(nextCell);
			m_OpenList.erase(m_OpenList.begin() + cellIndex);
		}
		return nextCell;
	}

	void PathFindManager::PathOpened(int x, int y, float newCost, SearchCell *parent)
	{
		//check if position is accesible
		if(find(m_PositionList.begin(), m_PositionList.end(), vec3(x,y,0)) == m_PositionList.end())
		{
			return;
		}

		//check if position has been visited
		int id = y * WORLD_SIZE + x;
		for (uint16 i=0; i<m_VisitedList.size(); ++i)
		{
			if(id == m_VisitedList[i]->m_Id)
			{
				return;
			}
		}

		//Get the best next step
		SearchCell* newCell = new SearchCell(x,y, parent);
		newCell->m_G = newCost;
		newCell->m_H = parent->ManhattanDistance(m_pEndCell) -1;

		for (auto searchCell : m_OpenList)
		{
			if(id == searchCell->m_Id)
			{
				float newF = newCell->m_G + newCost + searchCell->m_H;

				//Check if it's better then the old one
				if(searchCell->GetF() > newF)
				{
					searchCell->m_G = newCell->m_G + newCost;
					searchCell->m_pParent = newCell;
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
		if(currentCell->m_Id == m_pEndCell->m_Id && !m_bFoundGoal)
		{
			m_pEndCell->m_pParent = currentCell->m_pParent;
			SearchCell* getPath;
			for(getPath = m_pEndCell; getPath != NULL; getPath = getPath->m_pParent)
			{
				vec3 temp(getPath->m_X, getPath->m_Y, 0);
				m_PathToGoal.push_back(temp);
			}
			tstringstream str;
			for(auto element : m_PathToGoal)
			{
				str << _T("(")<< element.x<< _T(", ") << element.y << _T(")\n");
			}
			Logger::GetSingleton()->Log(LogLevel::Info, str.str());

			Logger::GetSingleton()->Log(LogLevel::Info, _T("Reached the fucking end! Finished with pathfinding"));
			m_bFoundGoal = true;
			return;
		}
		//if not, let's go look for the good way
		else
		{
			//RightSide
			PathOpened(currentCell->m_X + STEP_SIZE, currentCell->m_Y, currentCell->m_G + 1, currentCell);
			//LeftSide					  
			PathOpened(currentCell->m_X - STEP_SIZE, currentCell->m_Y, currentCell->m_G + 1, currentCell);
			//TopSide
			PathOpened(currentCell->m_X, currentCell->m_Y + STEP_SIZE, currentCell->m_G + 1, currentCell);
			//DownSide										
			PathOpened(currentCell->m_X, currentCell->m_Y - STEP_SIZE, currentCell->m_G + 1, currentCell);

			//left-up diagonal
			PathOpened(currentCell->m_X - STEP_SIZE, currentCell->m_Y + STEP_SIZE, currentCell->m_G + 1.414f, currentCell);
			//right-up diagonal			  								
			PathOpened(currentCell->m_X + STEP_SIZE, currentCell->m_Y + STEP_SIZE, currentCell->m_G + 1.414f, currentCell);
			//left-down diagonal		  								
			PathOpened(currentCell->m_X - STEP_SIZE, currentCell->m_Y - STEP_SIZE, currentCell->m_G + 1.414f, currentCell);
			//right-down diagonal		  								
			PathOpened(currentCell->m_X + STEP_SIZE, currentCell->m_Y - STEP_SIZE, currentCell->m_G + 1.414f, currentCell);

			for (uint16 i=0; i<m_OpenList.size(); ++i)
			{
				if (currentCell->m_Id == m_OpenList[i]->m_Id)
				{
					m_OpenList.erase(m_OpenList.begin() +i);
				}
			}
		}
	}

	vec3 PathFindManager::NextPathPos(Object* enemy)
	{
		uint16 index = 1;

		vec3 nextPos;
		nextPos.x = m_PathToGoal[m_PathToGoal.size() - index].x;
		nextPos.y = m_PathToGoal[m_PathToGoal.size() - index].y;
		vec3 distance = nextPos - enemy->GetComponent<TransformComponent>()->GetWorldPosition();
		
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
		if (step >= m_PathToGoal.size()-1)
		{
			step = m_PathToGoal.size()-1;
		}
		return m_PathToGoal[m_PathToGoal.size() - step - 1];
	}
}
