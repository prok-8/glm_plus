/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

/**
 * @file line.h
 * This header contains functions for calculating relations between lines and other geometric primitives,
 * such as distances, intersections, collisions...
 */

// TODO: Most of these functions could be constexpr.

#pragma once

#include "glm/gtc/type_precision.hpp"
#include "util.h"

namespace glm_plus {

/**
 * Calculates point to line distance.
 * The line is defined by 2 points, running in the direction from first to second.
 * The result is positive when the point is on the left of the line and negative otherwise.
 * @param x Point to test.
 * @param a1 First point on the line.
 * @param a2 Second point on the line.
 * @return Point to line distance.
 */
float dist_to_line_signed(glm::fvec2 x, glm::fvec2 a1, glm::fvec2 a2);

/**
 * Finds point on the line, closest to a point.
 * @param x Point to test.
 * @param a1 First point on the line.
 * @param a2 Second point on the line.
 * @return Point on the line closest to @p x.
 */
glm::fvec2 closest_point_on_line(glm::fvec2 x, glm::fvec2 a1, glm::fvec2 a2);

/**
 * Check if the point is in the strip.
 * The strip is limited by two parallel lines, each running through a point
 * and both being perpendicular to a line connecting those two points.
 * @param x Point to test.
 * @param p1 First strip limit point.
 * @param p2 Second strip limit point.
 * @return @c True if the point is between the two points, @c false otherwise.
 */
bool is_between_two_points(glm::fvec2 x, glm::fvec2 p1, glm::fvec2 p2);

/**
 * Check if the point is right of or on the line.
 * The line is defined by 2 points, running in the direction from first to second.
 * @warning If the point is exactly on the line, the result may be incorrect due to rounding error.
 * Consider using @ref right_of_line_with_margin.
 * @param x Point to test.
 * @param a1 First point on the line.
 * @param a2 Second point on the line.
 */
bool is_right_of_line(glm::fvec2 x, glm::fvec2 a1, glm::fvec2 a2);

/**
 * Check if the point is right of the line with margin.
 * The line is defined by 2 points, running in the direction from first to second.
 * @p margin has the same effect as shifting the line right for positive and left for negative values.
 * Use this function with a small positive @p margin value to reliably detect points that are exactly on the line,
 * but might otherwise not be detected due to rounding error.
 * @param x Point to test.
 * @param a1 First point on the line.
 * @param a2 Second point on the line.
 * @param margin Max distance from the line. Positive values make the function more strict, negative values make it less strict.
 * @return @c True if the point is right of the line with margin, @c false otherwise.
 */
bool is_right_of_line_with_margin(glm::fvec2 x, glm::fvec2 a1, glm::fvec2 a2, float margin = tiny_margin);

/**
 * Check if the point is inside a section, constructed from two lines (arms) which share a center point.
 * The section area begins at the first arm, running counter-clockwise and ending at the second arm.
 * @warning If the point is exactly on any of the arms, the result may be incorrect due to rounding error.
 * Consider using @ref is_inside_section_with_margin.
 * @param x Point to test.
 * @param center Section origin.
 * @param a Point on the first section arm.
 * @param b Point on the second section arm.
 * @return @c True if the point is inside the section, @c false otherwise.
 */
bool is_inside_section(glm::fvec2 x, glm::fvec2 center, glm::fvec2 a, glm::fvec2 b);

/**
 * Check if the point is inside a section, constructed from two lines (arms) which share a center point with margin.
 * The section area is at the first arm, running counter-clockwise and ending at the second arm.
 * @p margin has the same effect as shifting (NOT rotating) the arms inwards or outwards to expand or shrink the section area.
 * @param x Point to test.
 * @param center Section origin.
 * @param a Point on the first section arm.
 * @param b Point on the second section arm.
 * @param margin Max distance from the section. Positive values make the function more strict, negative values make it less strict.
 */
bool is_inside_section_with_margin(glm::fvec2 x, glm::fvec2 center, glm::fvec2 a, glm::fvec2 b, float margin = tiny_margin);

/**
 * Calculates the position where two lines intersect.
 * Lines are defined using 2 points.
 * If the lines coincide, the result is false.
 * @param a1 First point of the first line.
 * @param a2 Second point of the first line.
 * @param b1 First point of the second line.
 * @param b2 Second point of the second line.
 * @param result Intersection point.
 * @return @c True if lines intersect, @c false if they are parallel.
 */
bool lines_intersect(glm::fvec2 a1, glm::fvec2 a2, glm::fvec2 b1, glm::fvec2 b2, glm::vec2* result);

/**
 * Check if two lines segments intersect.
 * Both lines are defined as a pair of points.
 * @param a1 First point of the first line.
 * @param a2 Second point of the first line.
 * @param b3 First line segment point.
 * @param b4 Second line segment point.
 * @return @c True if lines coincide, @c false otherwise.
 */
bool line_segments_intersect(glm::fvec2 a1, glm::fvec2 a2, glm::fvec2 b3, glm::fvec2 b4, glm::vec2* result);

/**
 * Checks if a horizontal ray (running in positive x direction) intersects a line segment.
 * @param ray_start Ray start.
 * @param a1 First point of the line segment.
 * @param a2 Second point of the line segment.
 * @return @c True if the ray intersects the line segment, @c false otherwise.
 */
bool horizontal_ray_line_segment_intersect(glm::fvec2 ray_start, glm::fvec2 a1, glm::fvec2 a2);

/**
 * Check if two lines coincide (overlap).
 * There is a small leeway, which is necessary due to rounding errors,
 * which means that two lines that are very very nearly but not quite coincident
 * might still return @c true.
 * @param a1 First point on the first line.
 * @param a2 Second point on the first line.
 * @param b1 First point on the second line.
 * @param b2 Second point on the second line.
 * @return @c True if lines coincide, @c false otherwise.
 */
bool lines_coincide(glm::fvec2 a1, glm::fvec2 a2, glm::fvec2 b1, glm::fvec2 b2, float margin = tiny_margin);

/**
 * Check if two line segments coincide.
 * If line segments only touch, the result is @c false.
 * @param a1 First point of the first line segment.
 * @param a2 Second point of the first line segment.
 * @param b1 First point of the second line segment.
 * @param b2 Second point of the second line segment.
 * @return @c True if line segments coincide, @c false otherwise.
 */
bool line_segments_coincide(glm::fvec2 a1, glm::fvec2 a2, glm::fvec2 b1, glm::fvec2 b2);

/**
 * Check if a line intersects a circle.
 * The line is defined by 2 points, running in the direction from first to second.
 * Only the first intersection point in the line direction is returned.
 * @param center Circle center.
 * @param r Circle radius.
 * @param a1 First point on the line.
 * @param a2 Second point on the line.
 * @param result Intersection point.
 * @return \c True if line and circle intersect, \c false otherwise.
 */
bool line_circle_intersect(glm::fvec2 center, float r, glm::fvec2 a1, glm::fvec2 a2, glm::fvec2* result);

/**
 * Check if a line segment intersects a circle.
 * The line is defined by 2 points, running in the direction from first to second.
 * If there are 2 intersections, only the first one in the line direction is returned.
 * @param center Circle center.
 * @param r Circle radius.
 * @param a1 First line segment point
 * @param a2 Second line segment point.
 * @param result Intersection point.
 * @return \c True if line segment and circle intersect, \c false otherwise.
 */
bool line_segment_circle_intersect(glm::fvec2 center, float r, glm::fvec2 a1, glm::fvec2 a2, glm::fvec2* result);

}