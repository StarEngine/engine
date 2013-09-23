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
#include "..\Helpers\glm\glm.h"
#include "..\Helpers\glm\ext.hpp"
#include "BaseComponent.h"

using namespace glm;

class TransformComponent: public BaseComponent
{
public:

	enum TransformChanged
	{
		NONE = 0x00,
		TRANSLATION = 0x01,
		ROTATION = 0x02,
		SCALE = 0x03,
	};

	TransformComponent(void);
	TransformComponent(Object* parent);
	~TransformComponent(void);

	void Update(const star::Context& context);
	void Draw(){}

	void Translate(vec3 translation);
	void Translate(float x, float y, float z);

	void Rotate(quat rotation);
	//void Rotate(float x, float y, float z);

	void Scale(vec3 scale);
	void Scale(float x, float y, float z);

	vec3 GetWorldPosition() { CheckForUpdate(); return m_WorldPosition;}
	vec3 GetLocalPosition() const { return m_LocalPosition; }
	quat GetWorldRotation() { CheckForUpdate(); return m_WorldRotation;}
	quat GetLocalRotation() const { return m_LocalRotation; }
	vec3 GetWorldScale() { CheckForUpdate(); return m_WorldScale; }
	vec3 GetLocalScale() const { return m_LocalScale; }
	mat4x4 GetWorldMatrix() { CheckForUpdate(); return m_World; }

protected:
	void InitializeComponent();

private:

	unsigned char m_IsChanged;
	bool m_Invalidate;
	vec3 m_WorldPosition, m_LocalPosition;
	quat m_WorldRotation, m_LocalRotation;
	vec3 m_WorldScale, m_LocalScale;
	mat4x4 m_World;

	void CheckForUpdate(const bool force = false);
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	TransformComponent(const TransformComponent& yRef);									
	TransformComponent& operator=(const TransformComponent& yRef);
};

