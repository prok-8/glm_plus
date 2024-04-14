/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

/**
 * @file util.h
 * This header contains some utility functions and constants
 * used by this library.
 */

#pragma once

namespace glm_plus {

const float tiny_margin = 1.0e-5f;

template<typename T> T square(T x) { return x * x; }

}