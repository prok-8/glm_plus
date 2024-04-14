/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

#include "glm_plus/vector.h"

#include "gtest/gtest.h"

namespace glmp = glm_plus;

TEST(vector, is_overlapping) {
	ASSERT_TRUE(glmp::is_overlapping(glm::fvec2(1.0f, 2.0f), glm::fvec2(1.0f, 2.0f)));
	ASSERT_FALSE(glmp::is_overlapping(glm::fvec2(1.0f, 2.0f), glm::fvec2(1.0f, 3.0f)));
	ASSERT_TRUE(glmp::is_overlapping(glm::fvec2(1.0f, 2.0f), glm::fvec2(1.0f, 2.9f), 1.0f));
}

TEST(vector, calc_tangent) {
	glm::fvec2 v = glmp::calc_tangent(glm::fvec2(2.0f, 1.0f));
	ASSERT_EQ(v, glm::fvec2(-1.0f, 2.0f));
}

TEST(vector, set_length) {
	glm::fvec2 v = glmp::set_length(glm::fvec2(3.0f, 4.0f), 10.0f);
	ASSERT_EQ(v, glm::fvec2(6.0f, 8.0f));
}

TEST(vector, mirror) {
	glm::fvec2 v1 = glmp::mirror(glm::fvec2(1.0f, 3.0f), glm::fvec2(1.0f, 0.0f));
	glm::fvec2 v2 = glmp::mirror(glm::fvec2(1.0f, 3.0f), glm::fvec2(-1.0f, 0.0f));
	EXPECT_EQ(v1, glm::fvec2(-1.0f, 3.0f));
	EXPECT_EQ(v2, glm::fvec2(-1.0f, 3.0f));
}