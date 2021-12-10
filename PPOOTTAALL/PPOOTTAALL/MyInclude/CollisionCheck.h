#pragma once

bool aabbCollideCheck(const glm::vec3& aMin, const glm::vec3& aMax, const glm::vec3& bMin, const glm::vec3& bMax)
{
	return (
		aMin.x <= bMax.x && aMax.x >= bMin.x &&
		aMin.y <= bMax.y && aMax.y >= bMin.y &&
		aMin.z <= bMax.z && aMax.z >= bMin.z);
}

bool sphereAndAabbCollideCheck(const glm::vec3& sphere, const float& radius, const glm::vec3& aabbMin, const glm::vec3& aabbMax)
{
	glm::vec3 temp = glm::max(aabbMin, glm::min(sphere, aabbMax));

	float dist = glm::length(temp - sphere);

	//if (dist - radius <= 100.0f)	printf("%f", dist - radius);
	return dist < radius;
}

bool sphereAndSphereCollideCheck(const glm::vec3& aSphere, const float& aRadius, const glm::vec3& bSphere, const float& bRadius)
{
	return glm::length(aSphere - bSphere) < aRadius + bRadius;
}

bool obbCollideCheck()
{
	return false;
}
