//  _____ _             ______             _            
// / ____| |           |  ____|           (_)           
//| (___ | |_ __ _ _ __| |__   _ __   __ _ _ _ __   ___ 
// \___ \| __/ _` | '__|  __| | '_ \ / _` | | '_ \ / _ \
// ____) | || (_| | |  | |____| | | | (_| | | | | |  __/
//|_____/ \__\__,_|_|  |______|_| |_|\__, |_|_| |_|\___|
//                                    __/ |             
//                                   |___/             
#pragma once
#include "..\defines.h"
#include "..\Logger.h"
#include "..\Context.h"
#include "..\SceneGraph\Object.h"

class BaseComponent
{
public:
	BaseComponent(void);
	virtual ~BaseComponent(void);

	virtual void Initialize();
	virtual void Update(const star::Context& context) = 0;
	virtual void Draw() = 0;

	bool IsInitialized() const {return m_bInitialized;};
	
	Object* GetParent() const {return m_pParentObject;};
	void SetParent(Object* parent) {m_pParentObject = parent;};

protected:

	virtual void InitializeComponent() = 0;
	
	Object* m_pParentObject;
	bool m_bInitialized;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BaseComponent(const BaseComponent& t);
	BaseComponent& operator=(const BaseComponent& t);
};
