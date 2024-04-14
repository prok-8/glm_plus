/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

/**
 * @file vector.h
 * This header contains functions relating to vectors.
 */

#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include "util.h"

namespace glm_plus {

/**
 * Checks if two points are within margin from each other.
 * Function uses Euclidean distance (NOT Manhattan).
 * @param p1 First point.
 * @param p2 Second point.
 * @param margin Max distance.
 * @return @c True if points overlap, @c false otherwise.
 */
inline bool is_overlapping(glm::fvec2 p1, glm::fvec2 p2, float margin = tiny_margin);  // TODO: Make it constexpr if glm lib makes distance2 constexpr.

/**
 * Calculates tangent vector.
 * Same as rotating input @p vec 90 degrees clockwise.
 * Resulting vector has the same magnitude as input @p vec.
 * @param vec Vector.
 * @return Tangent vector. 
 */
constexpr glm::fvec2 calc_tangent(glm::fvec2 vec);

/**
 * Returns a vector with same direction as input @p vec
 * but with specified @p length.
 * @param vec Vector.
 * @param length Length.
 * @return Vector with length @p length.
 */
constexpr glm::fvec2 set_length(glm::fvec2 vec, float length);

/**
 * Calculates a vector, as if it were mirrored
 * through a plane with a specific normal.
 * Inverting the @p normal has no effect on the result.
 * @param vec Vector.
 * @param normal Mirror plane normal. Expected to be normalized.
 * @return Mirrored vector. Has the same magnitude as input @p vec.
 */
constexpr glm::fvec2 mirror(glm::fvec2 vec, glm::fvec2 normal);

inline bool is_overlapping(glm::fvec2 p1, glm::fvec2 p2, float margin) {
	return glm::distance2(p1, p2) <= margin * margin;
}

constexpr glm::fvec2 calc_tangent(glm::fvec2 vec) {
	return glm::fvec2(-vec.y, vec.x);
}

constexpr glm::fvec2 set_length(glm::fvec2 vec, float length) {
	return vec * (length / glm::length(vec));
}

constexpr glm::fvec2 mirror(glm::fvec2 vec, glm::fvec2 normal) {
	glm::fvec2 v = normal * dot(vec, normal);
	return v * -2.0f + vec;
}

}