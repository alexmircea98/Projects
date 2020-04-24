#pragma once

#include <include/glm.h>

namespace Transform2D
{
	// Translate matrix
	inline glm::mat3 Translate(float tx, float ty)
	{
		// TODO implement translate matrix
		return glm::transpose(glm::mat3(1, 0, tx,
										0, 1, ty,
										0, 0, 1)
		);
	}

	// Scale matrix
	inline glm::mat3 Scale(float sx, float sy)
	{
		// TODO implement scale matrix
		return glm::transpose(glm::mat3(sx, 0, 0,
										0, sy, 0,
										0, 0, 1)
		);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float r)
	{
		// TODO implement rotate matrix
		return glm::transpose(glm::mat3(cos(r), -sin(r), 0,
										sin(r), cos(r), 0,
										0, 0, 1)
		);
	}
}
