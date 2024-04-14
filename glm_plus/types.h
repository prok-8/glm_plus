/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

/**
 * @file types.h
 * This header contains types that represent geometric primitives
 * and some functions relating to those.
 */

#pragma once

#include "glm/glm.hpp"

namespace glm_plus {

/**
 * Wraps @ref "glm::vec<T, 2>".
 * Used to distinguish position arguments from size arguments.
 */
template<typename T>
struct size : public glm::vec<2, T> {
	size() = default;
	explicit constexpr size(T x) : glm::vec<2, T>(x) {};
	explicit size(glm::vec<2, T> vec) : glm::vec<2, T>(vec) {}
	size(T x, T y) : glm::vec<2, T>(x, y) {};
	size<T> operator+(const glm::vec<2, T>& other) { return size<T>(this->x + other.x, this->y + other.y); }
	size<T> operator-(const glm::vec<2, T>& other) { return size<T>(this->x - other.x, this->y - other.y); }
};

/**
 * Wraps @ref "glm::vec<T, 2>".
 * Used to distinguish position arguments from size arguments.
 */
template<typename T>
struct pos : public glm::vec<2, T> {
	pos() = default;
	explicit pos(T x) : glm::vec<2, T>(x) {};
	explicit pos(glm::vec<2, T> vec) : glm::vec<2, T>(vec) {}
	pos(T x, T y) : glm::vec<2, T>(x, y) {}
	pos<T> operator+(const glm::vec<2, T>& other) { return pos<T>(this->x + other.x, this->y + other.y); }
	pos<T> operator-(const glm::vec<2, T>& other) { return pos<T>(this->x - other.x, this->y - other.y); }
};

/**
 * Represents a rectangle by its location (corner with smallest coordinates) and size.
 */
template<typename T>
struct rect {
	rect() = default;
	explicit rect(const size<T> size) :
			size(size) {}
	rect(const pos<T> location, const size<T> size) :
			location(location),
			size(size) {}
	
	pos<T> location = {};
	glm_plus::size<T> size = {};
};

/**
 * Represents a rectangle by it's opposite corners.
 */
template<typename T>
struct area {
	area() = default;
	area(const pos<T> tl, const pos<T> br) :
			topleft(tl),
			bottomright(br) {}
	area(const pos<T> tl, const size<T> sz) :
			topleft(tl),
			bottomright(tl + sz) {}
			
	pos<T> topleft = {};
	pos<T> bottomright = {};
	[[nodiscard]] pos<T> get_topright() { return {bottomright.x, topleft.y}; }
	[[nodiscard]] pos<T> get_bottomleft() { return {topleft.x, bottomright.y}; }
};

/**
 * Represents a rectangle by it's opposite corners and size.
 */
template<typename T>
struct box {
	box() = default;
	box(const pos<T> tl, const pos<T> br) :
			topleft(tl),
			bottomright(br),
			size(bottomright - topleft) {}
	box(const pos<T> tl, const size<T> sz) :
			topleft(tl),
			bottomright(tl + sz),
			size(sz) {}
	explicit box(const size<T> sz) :
			topleft(0.0f),
			bottomright(sz),
			size(sz) {}
	
	operator rect<T>() const { return rect<T>(topleft, size); }
	operator area<T>() const { return area<T>(topleft, bottomright); }
	
	pos<T> topleft = {};
	pos<T> bottomright = {};
	glm_plus::size<T> size = {};
};

inline bool inside_rect(glm::fvec2 pos, glm::fvec2 topleft, glm::fvec2 bottomright) {
	return pos.x >= topleft.x && pos.x <= bottomright.x && pos.y >= topleft.y && pos.y <= bottomright.y;
}

template<typename T>
bool inside_rect(glm::vec<2, T> pos, area<T> area) {
	return pos.x >= area.topleft.x && pos.x <= area.bottomright.x && pos.y >= area.topleft.y && pos.y <= area.bottomright.y;
}

typedef size<float> fsize;
typedef size<int> isize;
typedef pos<float> fpos;
typedef pos<int> ipos;
typedef rect<float> frect;
typedef rect<int> irect;
typedef area<float> farea;
typedef area<int> iarea;
typedef box<float> fbox;

}