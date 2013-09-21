//  _____ _             ______             _            
// / ____| |           |  ____|           (_)           
//| (___ | |_ __ _ _ __| |__   _ __   __ _ _ _ __   ___ 
// \___ \| __/ _` | '__|  __| | '_ \ / _` | | '_ \ / _ \
// ____) | || (_| | |  | |____| | | | (_| | | | | |  __/
//|_____/ \__\__,_|_|  |______|_| |_|\__, |_|_| |_|\___|
//                                    __/ |             
//                                   |___/   
#pragma once
#include "..\lib\stafx.h"
#include "BaseComponent.h"
#include "..\defines.h"
#include "..\lib\Vector2D.h"

class RectangleColliderComponent: public BaseComponent
{
public:
	RectangleColliderComponent(int width, int height);
	virtual ~RectangleColliderComponent(void);

	virtual void Initialize();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void SetAsTrigger(bool isTrigger) {m_bIsTrigger = isTrigger;};
	bool IsTrigger() const {return m_bIsTrigger;};

	const RECT GetCollisionRest() const {return m_CollisionRect;};
	RECT CollisionTest(RECT& collider);

protected:
	virtual void InitializeComponent();

	int m_Width, m_Height;
	bool m_bIsTrigger;
private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	RectangleColliderComponent(const RectangleColliderComponent& t);
	RectangleColliderComponent& operator=(const RectangleColliderComponent& t);
};

