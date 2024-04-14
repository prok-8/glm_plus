# SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
# SPDX-License-Identifier: GPL-3.0-or-later

include(FetchContent)
FetchContent_Declare(glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e)  # 0.9.9.8
FetchContent_MakeAvailable(glm)

add_library(glm_plus STATIC	line.cpp)
target_link_libraries(glm_plus PUBLIC glm)
target_include_directories(glm_plus INTERFACE ${PROJECT_SOURCE_DIR})

if(GCC)
	target_compile_options(glm_plus PRIVATE -Wall)
elseif(MSVC)
	target_compile_options(glm_plus PRIVATE /Wall)
endif()
