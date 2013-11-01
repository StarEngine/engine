#include "HelpersMath.h"
#include "Rect.h"

namespace star
{
	float DegreesToRadians(float degrees)
	{
		return degrees * 180.0f / (float)PI;
	}

	vec2 DegreesToRadians(const vec2 & degrees)
	{
		vec2 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		return vec;
	}

	vec3 DegreesToRadians(const vec3 & degrees)
	{
		vec3 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		vec.z = DegreesToRadians(degrees.z);
		return vec;
	}

	vec4 DegreesToRadians(const vec4 & degrees)
	{
		vec4 vec;
		vec.x = DegreesToRadians(degrees.x);
		vec.y = DegreesToRadians(degrees.y);
		vec.z = DegreesToRadians(degrees.z);
		vec.w = DegreesToRadians(degrees.w);
		return vec;
	}

	float RadiansToDegrees(float radians)
	{
		return radians * (float)PI / 180.0f;
	}

	vec2 RadiansToDegrees(const vec2 & radians)
	{
		vec2 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		return vec;
	}

	vec3 RadiansToDegrees(const vec3 & radians)
	{
		vec3 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		vec.z = RadiansToDegrees(radians.z);
		return vec;
	}

	vec4 RadiansToDegrees(const vec4 & radians)
	{
		vec4 vec;
		vec.x = RadiansToDegrees(radians.x);
		vec.y = RadiansToDegrees(radians.y);
		vec.z = RadiansToDegrees(radians.z);
		vec.w = RadiansToDegrees(radians.w);
		return vec;
	}

	bool RectangleCircleCollision(const RectangleColliderComponent* collider1, 
		const CircleColliderComponent* collider2)
	{/*
		Rect rect = collider1->GetCollisionRect();
		float radius = collider2->GetRadius();

		glm::vec2 rectObjectPos = collider1->GetTransform()->GetWorldPosition().pos2D();
		glm::vec2 circleObjectPos = collider2->GetTransform()->GetWorldPosition().pos2D();

		int left = rect.GetLeft() + static_cast<int>(rectObjectPos.x);
		int right = rect.GetRight() + static_cast<int>(rectObjectPos.x);
		int top = rect.GetTop() + static_cast<int>(rectObjectPos.y); 
		int bottom = rect.GetBottom() + static_cast<int>(rectObjectPos.y);

		// Find the closest point to the circle within the rectangle
		float closestX = glm::clamp(circleObjectPos.x, static_cast<float>(left), static_cast<float>(right));
		float closestY = glm::clamp(circleObjectPos.y, static_cast<float>(top), static_cast<float>(top));

		// Calculate the distance between the circle's center and this closest point
		float distanceX = circleObjectPos.x - closestX;
		float distanceY = circleObjectPos.y - closestY;

		// If the distance is less than the circle's radius, an intersection occurs
		float doubleDistanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
		if( doubleDistanceSquared < (radius * radius))
		{
			return true;
		}*/
		return false;
	}
}
