//  _____ _             ______             _            
// / ____| |           |  ____|           (_)           
//| (___ | |_ __ _ _ __| |__   _ __   __ _ _ _ __   ___ 
// \___ \| __/ _` | '__|  __| | '_ \ / _` | | '_ \ / _ \
// ____) | || (_| | |  | |____| | | | (_| | | | | |  __/
//|_____/ \__\__,_|_|  |______|_| |_|\__, |_|_| |_|\___|
//                                    __/ |             
//                                   |___/   
#pragma once
#include "BaseComponent.h"
#include "..\defines.h"
#include "..\Helpers\glm\glm.h"
#include "..\Helpers\Rect.h"
#include <math.h>

class RectangleColliderComponent: public BaseComponent
{
public:
	RectangleColliderComponent(int width, int height);
	~RectangleColliderComponent(void);

	void Initialize();
	void Update(const star::Context& context);
	void Draw();

	void SetAsTrigger(bool isTrigger) {m_bIsTrigger = isTrigger;};
	bool IsTrigger() const {return m_bIsTrigger;};

	const  Rect GetCollisionRect() const {return m_CollisionRect;};
	Rect CollisionTest(const Rect& collider);

protected:
	virtual void InitializeComponent();

	bool m_bIsTrigger;
	Rect m_CollisionRect;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	RectangleColliderComponent(const RectangleColliderComponent& t);
	RectangleColliderComponent& operator=(const RectangleColliderComponent& t);
};

