/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

#include "glm_plus/matrix.h"

#include "gtest/gtest.h"

namespace glmp = glm_plus;

TEST(matrix, scale_move_mat) {
	glm::mat3 mat = glmp::scale_move_mat(glm::fvec2(4.0f, 5.0f), glm::fvec2(2.0f, 3.0f));
	ASSERT_EQ(mat, glm::fmat3(4.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 2.0f, 3.0f, 1.0f));
}

TEST(matrix, screen_projection_mat) {
	glm::fmat3 mat1 = glmp::screen_project_mat(glm::fvec2(10.0f, 20.0f));
	ASSERT_EQ(mat1, glm::fmat3(0.2f, 0.0f, 0.0f, 0.0f, -0.1f, 0.0f, -1.0f, 1.0f, 1.0f));
}