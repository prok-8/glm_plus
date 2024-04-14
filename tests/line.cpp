/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

#include "glm_plus/line.h"

#include "gtest/gtest.h"
#include "assertions.h"

namespace glmp = glm_plus;

TEST(line, dist_to_line_signed) {
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(1.0f, 0.0f);
	ASSERT_EQ(glmp::dist_to_line_signed(glm::fvec2(2.0f, 5.0f), p1, p2), -5.0f);
	ASSERT_EQ(glmp::dist_to_line_signed(glm::fvec2(2.0f, -3.0f), p1, p2), 3.0f);
}

TEST(line, closest_point_on_line) {
	ASSERT_EQ(glmp::closest_point_on_line(glm::fvec2(4.0f, 3.0f), glm::fvec2(0.0f, 0.0f), glm::fvec2(1.0f, 0.0f)), glm::fvec2(4.0f, 0.0f));
}

TEST(line, is_between_two_points) {
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(2.0f, 0.0f);
	ASSERT_TRUE(glmp::is_between_two_points(glm::fvec2(1.0f, 10.0f), p1, p2));
	ASSERT_TRUE(glmp::is_between_two_points(glm::fvec2(1.0f, 10.0f), p2, p1));
	ASSERT_FALSE(glmp::is_between_two_points(glm::fvec2(-2.0f, 0.0f), p2, p1));
	ASSERT_FALSE(glmp::is_between_two_points(glm::fvec2(3.0f, 0.0f), p2, p1));
}

TEST(line, is_right_of_line) {
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(1.0f, 0.0f);
	ASSERT_TRUE(glmp::is_right_of_line(glm::fvec2(0.0f, 1.0f), p1, p2));
	ASSERT_FALSE(glmp::is_right_of_line(glm::fvec2(0.0f, -1.0f), p1, p2));
}

TEST(line, is_right_of_line_with_margin) {
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(1.0f, 0.0f);
	
	ASSERT_TRUE(glmp::is_right_of_line_with_margin(glm::fvec2(0.0f, 1.0f), p1, p2));
	ASSERT_TRUE(glmp::is_right_of_line_with_margin(glm::fvec2(0.0f, 0.0f), p1, p2, -0.1f));
	ASSERT_FALSE(glmp::is_right_of_line_with_margin(glm::fvec2(0.0f, -1.0f), p1, p2));
	ASSERT_FALSE(glmp::is_right_of_line_with_margin(glm::fvec2(0.0f, 0.0f), p1, p2, 0.1f));
}

TEST(line, is_inside_section) {
	glm::fvec2 p(0.0f, 0.0f);
	glm::fvec2 a(1.0f, 1.0f);
	glm::fvec2 b(1.0f, 0.0f);
	
	ASSERT_TRUE(glmp::is_inside_section(glm::fvec2(1.0f, 0.5f), p, a, b));
	ASSERT_FALSE(glmp::is_inside_section(glm::fvec2(1.0f, 2.0f), p, a, b));
	ASSERT_TRUE(glmp::is_inside_section(glm::fvec2(1.0f, 2.0f), p, b, a));
	ASSERT_FALSE(glmp::is_inside_section(glm::fvec2(1.0f, 0.5f), p, b, a));
}

TEST(line, is_inside_section_with_margin) {
	glm::fvec2 p(0.0f, 0.0f);
	glm::fvec2 a(1.0f, 1.0f);
	glm::fvec2 b(1.0f, 0.0f);
	
	ASSERT_TRUE(glmp::is_inside_section_with_margin(glm::fvec2(1.0f, 0.5f), p, a, b));
	ASSERT_FALSE(glmp::is_inside_section_with_margin(glm::fvec2(1.0f, 2.0f), p, a, b));
	ASSERT_TRUE(glmp::is_inside_section_with_margin(glm::fvec2(1.0f, -0.1f), p, a, b, -0.5f));
	ASSERT_FALSE(glmp::is_inside_section_with_margin(glm::fvec2(1.0f, 0.1f), p, a, b, 0.5f));
	
	ASSERT_TRUE(glmp::is_inside_section_with_margin(glm::fvec2(1.0f, 2.0f), p, b, a));
	ASSERT_FALSE(glmp::is_inside_section_with_margin(glm::fvec2(1.0f, 0.5f), p, b, a));
	ASSERT_TRUE(glmp::is_inside_section_with_margin(glm::fvec2(1.0f, 0.1f), p, b, a, -0.5));
	ASSERT_FALSE(glmp::is_inside_section_with_margin(glm::fvec2(1.0f, -0.1f), p, b, a, 0.5));
}

TEST(line, lines_intersect) {
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(2.0f, 4.0f);
	glm::fvec2 p3(0.0f, 5.0f);
	glm::fvec2 p4(4.0f, 3.0f);
	glm::fvec2 p5(1.0f, 2.0f);
	
	glm::fvec2 r;
	ASSERT_TRUE(glmp::lines_intersect(p1, p2, p3, p4, &r));
	ASSERT_VEC2_EQ(r, 2.0f, 4.0f);
	ASSERT_TRUE(glmp::lines_intersect(p1, p5, p3, p4, &r));
	ASSERT_VEC2_EQ(r, 2.0f, 4.0f);
	ASSERT_FALSE(glmp::lines_intersect(p1, p2, p1, p5, &r));
}

TEST(line, line_segments_intersect) {
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(2.0f, 4.0f);
	glm::fvec2 p3(0.0f, 5.0f);
	glm::fvec2 p4(4.0f, 3.0f);
	glm::fvec2 p5(1.0f, 2.0f);
	
	glm::fvec2 r;
	ASSERT_TRUE(glmp::line_segments_intersect(p1, p2, p3, p4, &r));
	ASSERT_VEC2_EQ(r, 2.0f, 4.0f);
	ASSERT_FALSE(glmp::line_segments_intersect(p1, p5, p3, p4, &r));
	ASSERT_FALSE(glmp::line_segments_intersect(p1, p2, p1, p5, &r));
}

TEST(line, horizontal_ray_intersect) {
	glm::fvec2 c(5.0f, 5.0f);
	
	ASSERT_TRUE(glmp::horizontal_ray_line_segment_intersect(c, glm::fvec2(5.0f, 7.0f), glm::fvec2(6.0f, 3.0f)));
	ASSERT_FALSE(glmp::horizontal_ray_line_segment_intersect(c, glm::fvec2(5.0f, 7.0f), glm::fvec2(7.0f, 6.0f)));
	ASSERT_FALSE(glmp::horizontal_ray_line_segment_intersect(c, glm::fvec2(5.0f, 4.0f), glm::fvec2(7.0f, 3.0f)));
	ASSERT_FALSE(glmp::horizontal_ray_line_segment_intersect(c, glm::fvec2(4.0f, 7.0f), glm::fvec2(5.0f, 3.0f)));
}

TEST(line, lines_coincide) {
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(2.0f, 1.0f);
	glm::fvec2 p3(4.0f, 2.0f);
	glm::fvec2 p4(6.0f, 3.0f);
	glm::fvec2 p5(6.0f, 2.0f);
	
	ASSERT_TRUE(glmp::lines_coincide(p1, p2, p3, p4));
	ASSERT_FALSE(glmp::lines_coincide(p1, p2, p3, p5));
}

TEST(line, line_segments_coincide) {
	glm::fvec2 p1(0.0f, 0.0f);
	glm::fvec2 p2(4.0f, 2.0f);
	glm::fvec2 p3(2.0f, 1.0f);
	glm::fvec2 p4(6.0f, 3.0f);
	glm::fvec2 p5(6.0f, 4.0f);
	
	ASSERT_TRUE(glmp::line_segments_coincide(p1, p2, p3, p4));
	ASSERT_FALSE(glmp::line_segments_coincide(p1, p2, p2, p4));
	ASSERT_FALSE(glmp::line_segments_coincide(p1, p2, p3, p5));
}

TEST(line, line_circle_intersect) {
	glm::fvec2 c(8.0f, 8.0f);
	glm::fvec2 r;
	
	ASSERT_TRUE(glmp::line_circle_intersect(c, 2.0f, glm::fvec2(0.0f, 8.0f), glm::fvec2(1.0f, 8.0f), &r));
	ASSERT_VEC2_EQ(r, 6.0f, 8.0f);
	ASSERT_TRUE(glmp::line_circle_intersect(c, 2.0f, glm::fvec2(0.0f, 10.0f), glm::fvec2(1.0f, 10.0f), &r));
	ASSERT_VEC2_EQ(r, 8.0f, 10.0f);
	ASSERT_FALSE(glmp::line_circle_intersect(c, 2.0f, glm::fvec2(0.0f, 8.0f), glm::fvec2(2.0f, 10.0f), &r));
}

TEST(line, line_segment_circle_intersect) {
	glm::fvec2 c(8.0f, 8.0f);
	glm::fvec2 r;
	
	ASSERT_TRUE(glmp::line_segment_circle_intersect(c, 2.0f, glm::fvec2(0.0f, 8.0f), glm::fvec2(12.0f, 8.0f), &r));
	ASSERT_VEC2_EQ(r, 6.0f, 8.0f);
	ASSERT_TRUE(glmp::line_segment_circle_intersect(c, 2.0f, glm::fvec2(0.0f, 8.0f), glm::fvec2(9.0f, 8.0f), &r));
	ASSERT_VEC2_EQ(r, 6.0f, 8.0f);
	ASSERT_TRUE(glmp::line_segment_circle_intersect(c, 2.0f, glm::fvec2(0.0f, 10.0f), glm::fvec2(9.0f, 10.0f), &r));
	ASSERT_VEC2_EQ(r, 8.0f, 10.0f);
	ASSERT_FALSE(glmp::line_segment_circle_intersect(c, 2.0f, glm::fvec2(0.0f, 8.0f), glm::fvec2(5.0f, 8.0f), &r));
	ASSERT_FALSE(glmp::line_segment_circle_intersect(c, 2.0f, glm::fvec2(0.0f, 8.0f), glm::fvec2(2.0f, 10.0f), &r));
}
