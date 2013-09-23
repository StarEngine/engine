//  _____ _             ______             _            
// / ____| |           |  ____|           (_)           
//| (___ | |_ __ _ _ __| |__   _ __   __ _ _ _ __   ___ 
// \___ \| __/ _` | '__|  __| | '_ \ / _` | | '_ \ / _ \
// ____) | || (_| | |  | |____| | | | (_| | | | | |  __/
//|_____/ \__\__,_|_|  |______|_| |_|\__, |_|_| |_|\___|
//                                    __/ |             
//                                   |___/   
#pragma once
#include <vector>
#include <typeinfo>
#include "..\defines.h"
#include "..\Logger.h"
#include "..\Context.h"

class BaseComponent;
class TransformComponent;
class BaseScene;

using namespace std;

class Object
{
public:
	Object(void);
	virtual ~Object(void);

	Object* GetParent() const { return m_pParentGameObject; }

	virtual void Initialize();
	virtual void Update(const star::Context& context);
	virtual void Draw();

	virtual tstring GetName() {return m_Name;};
	virtual void SetName(const tstring& name) {m_Name = name;};

	void AddComponent(BaseComponent* pComponent);
	void RemoveComponent(const BaseComponent* pComponent);

	void AddChild(Object* pObject);
	void RemoveChild(const Object* pObject);

	//Template functions
	//-----------------------------
	template<class T> T* GetComponent(bool searchChildren = false) 
	{
		const type_info& ti = typeid(T);
		for(auto *component : m_pComponents)
		{
			if(component && typeid(*component) == ti)
			{
				tstringstream str;
				str << _T("Component found");
				star::Logger::GetSingleton()->Log(star::LogLevel::Info, str.str());
				return (T*)component;
			}
		}

		if(searchChildren)
		{
			for(auto *child : m_pChildren)
			{
				return child->GetComponent<T>(searchChildren);
			}
		}
		return nullptr;
	}
	template<class T> T* GetChild()
	{
		const type_info& ti = typeid(T);
		for(auto *child : m_pChildren)
		{
			if(child && typeid(*child) == ti)
			{
				return (T*)child;
			}
		}
		return nullptr;
	}

protected:
	bool m_bIsInitialized;
	Object* m_pParentGameObject;

	vector<BaseComponent*> m_pComponents;
	vector<Object*> m_pChildren;
	tstring m_Name;

private:

	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Object(const Object& t);
	Object& operator=(const Object& t);
};

