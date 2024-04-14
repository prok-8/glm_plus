# SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

project(glm_plus VERSION 1.0)

option(GLM_PLUS_BUILD_TESTS "Build the glm_plus test programs" OFF)

add_subdirectory(glm_plus)

if(GLM_PLUS_BUILD_TESTS)
	add_subdirectory(tests)
endif()
