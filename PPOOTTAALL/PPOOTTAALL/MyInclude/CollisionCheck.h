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

bool rayAABB(glm::vec3 vMin, glm::vec3 vMax, glm::vec3 rayStart, glm::vec3 rayDir)
{
	float xMin = (vMin.x - rayStart.x) / rayDir.x;
	float xMax = (vMax.x - rayStart.x) / rayDir.x;
	if (xMin > xMax) {
		float temp = xMin;
		xMin = xMax;
		xMax = temp;
	}

	float yMin = (vMin.y - rayStart.y) / rayDir.y;
	float yMax = (vMax.y - rayStart.y) / rayDir.y;
	if (yMin > yMax) {
		float temp = yMin;
		yMin = yMax;
		yMax = temp;
	}

	float zMin = (vMin.z - rayStart.z) / rayDir.z;
	float zMax = (vMax.z - rayStart.z) / rayDir.z;
	if (zMin > zMax) {
		float temp = zMin;
		zMin = zMax;
		zMax = temp;
	}

	float min = (xMin > yMin) ? xMin : yMin;
	float max = (xMax < yMax) ? xMax : yMax;

	if (xMin > yMax || yMin > xMax) return false;
	if (min > zMax || zMin > max) return false;

	return true;
}