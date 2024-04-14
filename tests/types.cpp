/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

#include "glm_plus/types.h"

#include "gtest/gtest.h"
#include "assertions.h"

namespace glmp = glm_plus;

TEST(types, size_construct) {
	glmp::fsize s1;
	glmp::fsize s2(5.0f);
	glmp::fsize s3(glm::fvec2(1.0f, 2.0f));
	glmp::fsize s4(10.0f, 11.0f);
	
	ASSERT_VEC2_EQ(s2, 5.0f, 5.0f);
	ASSERT_VEC2_EQ(s3, 1.0f, 2.0f);
	ASSERT_VEC2_EQ(s4, 10.0f, 11.0f);
}

TEST(types, size_operator_overloads) {
	glmp::fsize s1(1.0f, 2.0f);
	glmp::fsize s2(3.0f, 8.0f);
	glmp::fsize s3 = s1 + s2;
	glmp::fsize s4 = s2 - s1;
	
	ASSERT_VEC2_EQ(s3, 4.0f, 10.0f);
	ASSERT_VEC2_EQ(s4, 2.0f, 6.0f);
}

TEST(types, pos_construct) {
	glmp::fpos s1;
	glmp::fpos s2(5.0f);
	glmp::fpos s3(glm::fvec2(1.0f, 2.0f));
	glmp::fpos s4(10.0f, 11.0f);
	
	ASSERT_VEC2_EQ(s2, 5.0f, 5.0f);
	ASSERT_VEC2_EQ(s3, 1.0f, 2.0f);
	ASSERT_VEC2_EQ(s4, 10.0f, 11.0f);
}

TEST(types, pos_operator_overloads) {
	glmp::fpos s1(1.0f, 2.0f);
	glmp::fpos s2(3.0f, 8.0f);
	glmp::fpos s3 = s1 + s2;
	glmp::fpos s4 = s2 - s1;
	
	ASSERT_VEC2_EQ(s3, 4.0f, 10.0f);
	ASSERT_VEC2_EQ(s4, 2.0f, 6.0f);
}

TEST(types, rect_constructor) {
	glmp::frect r1;
	glmp::frect r2(glmp::fsize(1.0f, 2.0f));
	glmp::frect r3(glmp::fpos(5.0f, 10.0f), glmp::fsize(1.0f, 2.0f));
	
	ASSERT_RECT_EQ(r1, 0.0f, 0.0f, 0.0f, 0.0f);
	ASSERT_RECT_EQ(r2, 0.0f, 0.0f, 1.0f, 2.0f);
	ASSERT_RECT_EQ(r3, 5.0f, 10.0f, 1.0f, 2.0f);
}

TEST(types, area_constructor) {
	glmp::farea a1;
	glmp::farea a2(glmp::fpos(1.0f, 2.0f), glmp::fpos(5.0f, 10.0f));
	glmp::farea a3(glmp::fpos(1.0f, 2.0f), glmp::fsize(4.0f, 5.0f));
	
	ASSERT_AREA_EQ(a1, 0.0f, 0.0f, 0.0f, 0.0f);
	ASSERT_AREA_EQ(a2, 1.0f, 2.0f, 5.0f, 10.0f);
	ASSERT_AREA_EQ(a3, 1.0f, 2.0f, 5.0f, 7.0f);
}

TEST(types, area_getters) {
	glmp::farea a(glmp::fpos(1.0f, 2.0f), glmp::fpos(5.0f, 10.0f));
	glmp::fpos tr = a.get_topright();
	glmp::fpos bl = a.get_bottomleft();
	
	ASSERT_VEC2_EQ(tr, 5.0f, 2.0f);
	ASSERT_VEC2_EQ(bl, 1.0f, 10.0f);
}

TEST(types, box_constructor) {
	glmp::fbox b1;
	glmp::fbox b2(glmp::fpos(1.0f, 2.0f), glmp::fpos(5.0f, 10.0f));
	glmp::fbox b3(glmp::fpos(1.0f, 2.0f), glmp::fsize(5.0f, 10.0f));
	glmp::fbox b4(glmp::fsize(5.0f, 10.0f));
	
	ASSERT_BOX_EQ(b1, 0.0f, 0.0f, 0.0f, 0.0f);
	ASSERT_BOX_EQ(b2, 1.0f, 2.0f, 5.0f, 10.0f);
	ASSERT_BOX_EQ(b3, 1.0f, 2.0f, 6.0f, 12.0f);
	ASSERT_BOX_EQ(b4, 0.0f, 0.0f, 5.0f, 10.0f);
}

TEST(types, box_conversion_overloads) {
	glmp::fbox b(glmp::fpos(1.0f, 2.0f), glmp::fpos(5.0f, 10.0f));
	glmp::frect r = b;
	glmp::farea a = b;
	
	ASSERT_RECT_EQ(r, 1.0f, 2.0f, 4.0f, 8.0f);
	ASSERT_AREA_EQ(a, 1.0f, 2.0f, 5.0f, 10.0f);
}
