cmake_minimum_required( VERSION 3.0 )

project(Alien_Attack VERSION 0.1 LANGUAGES CXX)


set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -pthread -static")

# Path to the root of the source files
set(CMAKE_SOURCE_DIR				${CMAKE_CURRENT_SOURCE_DIR}/source)
# Path for output binary files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY	${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH				${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
set(CMAKE_LIBRARY_PATH				${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Creating the main goal of the project
add_executable(${PROJECT_NAME})


set(COMMON_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/common)

# Collecting the basic source code
file(GLOB_RECURSE SOURCE_EXE    ${CMAKE_SOURCE_DIR}/*.cpp)
file(GLOB COMMON_SOURCE ${COMMON_DIR}/*.cpp)

# Add compiled files to the ${PROJECT_NAME} target
target_sources(${PROJECT_NAME} PUBLIC
	${SOURCE_EXE}
	${COMMON_SOURCE})


set(INCLUDE_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add header files to the ${PROJECT_NAME} target
target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_SOURCE_DIR}
	${COMMON_DIR}
	${INCLUDE_HEADERS_DIR})


# Adding the Logger project
add_subdirectory("${CMAKE_LIBRARY_PATH}/logger")
target_link_libraries(${PROJECT_NAME}
	PUBLIC logger)

# Adding the Base64 project
add_subdirectory("${CMAKE_LIBRARY_PATH}/base64")
target_link_libraries(${PROJECT_NAME}
	PUBLIC base64)

# Adding the TinyXML project
add_subdirectory("${CMAKE_LIBRARY_PATH}/tinyxml")
target_link_libraries(${PROJECT_NAME}
	PUBLIC tinyxml)

# Adding the SDL2 library
set(SDL2_PATH "${CMAKE_LIBRARY_PATH}/SDL2")
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC
	${SDL2_LIBRARY})
target_include_directories(${PROJECT_NAME} PUBLIC
	${SDL2_INCLUDE_DIR})

# Adding the SDL2_image library
set(SDL2_IMAGE_PATH "${CMAKE_LIBRARY_PATH}/SDL2_image")
find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC
	${SDL2_IMAGE_LIBRARY})
target_include_directories(${PROJECT_NAME} PUBLIC
	${SDL2_IMAGE_INCLUDE_DIR})

# Adding the SDL2_mixer library
set(SDL2_MIXER_PATH "${CMAKE_LIBRARY_PATH}/SDL2_mixer")
find_package(SDL2_mixer REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC
	${SDL2_MIXER_LIBRARY})
target_include_directories(${PROJECT_NAME} PUBLIC
	${SDL2_MIXER_INCLUDE_DIR})

# Adding the SDL2_ttf library
set(SDL2_TTF_PATH "${CMAKE_LIBRARY_PATH}/SDL2_ttf")
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC
	${SDL2_TTF_LIBRARY})
target_include_directories(${PROJECT_NAME} PUBLIC
	${SDL2_TTF_INCLUDE_DIR})


# Adding the Zlib library
set(ZLIB_PATH "${CMAKE_LIBRARY_PATH}/zlib")
target_link_libraries(${PROJECT_NAME} PUBLIC
	"${ZLIB_PATH}/lib/libzlib.dll.a")
target_include_directories(${PROJECT_NAME} PUBLIC
	"${ZLIB_PATH}/include")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(BUILD_TYPE_DEBUG true)
	target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_TYPE_DEBUG=${BUILD_TYPE_DEBUG})
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(BUILD_TYPE_RELEASE true)
	target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_TYPE_RELEASE=${BUILD_TYPE_RELEASE})
endif()


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS_EQUAL 7.3.0)
		message("The compiler version less or equal 7.3.0 is used (GNU)!")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")
		target_link_libraries(${PROJECT_NAME} PUBLIC stdc++fs)

		set(GCC_EXPERIMENTAL true)
		target_compile_definitions(${PROJECT_NAME} PRIVATE GCC_EXPERIMENTAL=${GCC_EXPERIMENTAL})
	endif()
endif()
