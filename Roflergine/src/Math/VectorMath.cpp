#include "VectorMath.h"

glm::dmat4 vectorToRotationMatrix(glm::dvec3 rotation) {
	glm::dmat4 result = glm::mat4(1.0);

	result = glm::rotate(result, rotation.x, glm::dvec3(1.0f, 0, 0));
	result = glm::rotate(result, rotation.y, glm::dvec3(0, 1.0f, 0));
	result = glm::rotate(result, rotation.z, glm::dvec3(0, 0, 1.0f));

	return result;
}