/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

#include "line.h"

#include "vector.h"
#include "util.h"

using namespace glm_plus;
using namespace glm;

float glm_plus::dist_to_line_signed(fvec2 x, fvec2 a1, fvec2 a2) {
	return ((a2.x - a1.x) * (a1.y - x.y) - (a1.x - x.x) * (a2.y -a1.y)) / sqrt(square(a2.x - a1.x) + square(a2.y - a1.y));
}

fvec2 glm_plus::closest_point_on_line(fvec2 x, fvec2 a1, fvec2 a2) {
	fvec2 n12 = normalize(a2 - a1);
	float dist = dot(normalize(n12), x - a1);
	return a1 + n12 * dist;
}

bool glm_plus::is_between_two_points(fvec2 x, fvec2 p1, fvec2 p2) {
	fvec2 pp = p2 - p1;
	if (dot(x - p1, pp) < 0.0f)
		return false;
	pp = p1 - p2;
	if (dot(x - p2, pp) < 0.0f)
		return false;
	return true;
}

bool glm_plus::is_right_of_line(fvec2 x, fvec2 a1, fvec2 a2) {
	fvec3 a1a2(a2 - a1, 0.0f);
	fvec3 a1x(x - a1, 0.0f);
	float c = cross(a1a2, a1x).z;
	return c >= 0.0f;
}

bool glm_plus::is_right_of_line_with_margin(fvec2 x, fvec2 a1, fvec2 a2, float margin) {
	return dist_to_line_signed(x, a1, a2) < -margin;
}

bool glm_plus::is_inside_section(fvec2 x, fvec2 center, fvec2 a, fvec2 b) {
	fvec3 pca(a - center, 0.0f);
	fvec3 pcb(b - center, 0.0f);
	float c = cross(pca, pcb).z;
	return c >= 0.0f
		? is_right_of_line(x, a, center) || is_right_of_line(x, center, b)
		: is_right_of_line(x, a, center) && is_right_of_line(x, center, b);
}

bool glm_plus::is_inside_section_with_margin(fvec2 x, fvec2 center, fvec2 a, fvec2 b, float margin) {
	fvec3 pca(a - center, 0.0f);
	fvec3 pcb(b - center, 0.0f);
	float c = cross(pca, pcb).z;
	return c > 0.0f
		? is_right_of_line_with_margin(x, a, center, margin) || is_right_of_line_with_margin(x, center, b, margin)
		: is_right_of_line_with_margin(x, a, center, margin) && is_right_of_line_with_margin(x, center, b, margin);
}

bool glm_plus::lines_intersect(fvec2 a1, fvec2 a2, fvec2 b1, fvec2 b2, vec2* result) {
	float d3 = (a1.x - a2.x) * (b1.y - b2.y) - (b1.x - b2.x) * (a1.y - a2.y);
	if (d3 == 0.0f)
		return false;
	
	float d1 = a1.x * a2.y - a2.x * a1.y;
	float d2 = b1.x * b2.y - b2.x * b1.y;
	float dx = d1 * (b1.x - b2.x) - d2 * (a1.x - a2.x);
	float dy = d1 * (b1.y - b2.y) - d2 * (a1.y - a2.y);
	*result = {dx / d3, dy / d3};
	return true;
}

bool glm_plus::line_segments_intersect(fvec2 a1, fvec2 a2, fvec2 b1, fvec2 b2, vec2* result) {
	return lines_intersect(a1, a2, b1, b2, result) && is_between_two_points(*result, a1, a2) && is_between_two_points(*result, b1, b2);
}

bool glm_plus::horizontal_ray_line_segment_intersect(fvec2 ray_start, fvec2 a1, fvec2 a2) {
	fvec2 top;
	fvec2 bottom;
	if (a1.y > a2.y) {
		top = a1;
		bottom = a2;
	}
	else {
		top = a2;
		bottom = a1;
	}
	
	if (ray_start.y < bottom.y || ray_start.y > top.y)
		return false;
	
	float f = (ray_start.y - bottom.y) / (top.y - bottom.y);
	float x = f * (top.x - bottom.x) + bottom.x;
	return x >= ray_start.x;
}

bool glm_plus::lines_coincide(fvec2 a1, fvec2 a2, fvec2 b1, fvec2 b2, float margin) {
	float d1 = (a1.x - a2.x) * (b1.y - b2.y) - (b1.x - b2.x) * (a1.y - a2.y);
	float d2 = (a1.x - a2.x) * (a1.y - b1.y) - (a1.x - b1.x) * (a1.y - a2.y);
	return abs(d1) < margin && abs(d2) < margin;
}

bool glm_plus::line_segments_coincide(fvec2 a1, fvec2 a2, fvec2 b1, fvec2 b2) {
	if (!lines_coincide(a1, a2, b1, b2))
		return false;
	
	if (is_between_two_points(a1, b1, b2)) {
		if (is_between_two_points(a2, b1, b2)) {
			// Both points of section 1 are within section 2.
			return true;
		}
		else {
			if (is_overlapping(a1, b1) || is_overlapping(a1, b2)) {
				// Section 1 head is touching section 2, not overlapping.
				return false;
			}
			else {
				// Section 1 head is overlapping section 2.
				return true;
			}
		}
	}
	else if (is_between_two_points(a2, b1, b2)) {
		if (is_overlapping(a2, b1) || is_overlapping(a2, b2)) {
			// Section 1 tail is touching section 2, not overlapping.
			return false;
		}
		else {
			// Section 1 tail is overlapping section 2.
			return true;
		}
	}
	else if (is_between_two_points(b1, a1, a2)) {
		// Section 2 is completely inside section 1.
		return true;
	}
	else {
		// Sections are not touching at all.
		return false;
	}
}

bool glm_plus::line_circle_intersect(fvec2 center, float r, fvec2 a1, fvec2 a2, fvec2* result) {
	if (a1 == a2)
		return false;
	
	fvec2 closest_point = closest_point_on_line(center, a1, a2);
	float dist2 = distance2(closest_point, center);
	if (dist2 > r * r)
		return false;
	
	float dist_p = sqrt(r * r - dist2);
	*result = closest_point + set_length(a1 - a2, dist_p);
	return true;
}

bool glm_plus::line_segment_circle_intersect(fvec2 center, float r, fvec2 a1, fvec2 a2, fvec2* result) {
	return line_circle_intersect(center, r, a1, a2, result) && is_between_two_points(*result, a1, a2);
}
