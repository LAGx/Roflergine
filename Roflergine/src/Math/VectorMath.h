#pragma once
#include <glm/glm.hpp>
#include <glm\ext\matrix_transform.hpp>

// x y z order
glm::dmat4 vectorToRotationMatrix(glm::dvec3 rotation);