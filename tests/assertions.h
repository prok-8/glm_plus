/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

#pragma once

#define ASSERT_VEC2_EQ(s, x_, y_) ASSERT_EQ(s.x, x_); ASSERT_EQ(s.y, y_)
#define ASSERT_RECT_EQ(r, lx, ly, sx, sy) ASSERT_VEC2_EQ(r.location, lx, ly); ASSERT_VEC2_EQ(r.size, sx, sy)
#define ASSERT_AREA_EQ(a, tlx, tly, brx, bry) ASSERT_VEC2_EQ(a.topleft, tlx, tly); ASSERT_VEC2_EQ(a.bottomright, brx, bry)
#define ASSERT_BOX_EQ(b, tlx, tly, brx, bry) ASSERT_VEC2_EQ(b.topleft, tlx, tly); ASSERT_VEC2_EQ(b.bottomright, brx, bry); ASSERT_VEC2_EQ(b.size, brx - tlx, bry - tly)
