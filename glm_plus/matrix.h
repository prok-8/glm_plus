/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

/**
 * @file matrix.h
 * This header contains helper functions for creating transformation matrices.
 */

#pragma once

#include "glm/glm.hpp"

namespace glm_plus {

/**
 * Returns a 2D transformation matrix that scales and moves.
 * @param scale Scale.
 * @param move Move.
 * @return 2D transformation matrix.
 */
constexpr glm::fmat3 scale_move_mat(glm::fvec2 scale, glm::fvec2 move);

/**
 * Returns a 2D transformation matrix that
 * mapps canvas of size @p canvas_size
 * to coordinates from {-1.0, -1.0} to {1.0, 1.0}.
 * @param canvas_size  Canvas size.
 * @return 2D transformation matrix.
 */
constexpr glm::fmat3 screen_project_mat(glm::fvec2 canvas_size);

/**
 * Returns a 2D transformation matrix that
 * mapps canvas of size @p canvas_size
 * to coordinates from {-1.0, -1.0} to {1.0, 1.0}
 * and offsets it by @p canvas_offset.
 * Offsetting the canvas for half it's size will
 * effectively offset it by 1 unit in the transformed coordinate system.
 * @param canvas_size Canvas size.
 * @param canvas_offset Canvas offset.
 * @return 2D transformation matrix.
 */
constexpr glm::fmat3 screen_project_mat(glm::fvec2 canvas_size, glm::fvec2 canvas_offset);

constexpr glm::fmat3 scale_move_mat(glm::fvec2 scale, glm::fvec2 move) {
	return {
		scale.x, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f,
		move.x, move.y, 1.0f
	};
}

constexpr glm::fmat3 screen_project_mat(glm::fvec2 canvas_size) {
	return {
		2.0f / canvas_size.x, 0.0f, 0.0f,
		0.0f, -2.0f / canvas_size.y, 0.0f,
		-1.0f, 1.0f, 1.0f};
}

constexpr glm::fmat3 screen_project_mat(glm::fvec2 canvas_size, glm::fvec2 canvas_offset) {
	return {
		2.0f / canvas_size.x, 0.0f, 0.0f,
		0.0f, -2.0f / canvas_size.y, 0.0f,
		-2.0f * canvas_offset.x / canvas_size.x - 1.0f, 2.0f * canvas_offset.y / canvas_size.y + 1.0f, 1.0f};
}

}