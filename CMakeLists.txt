cmake_minimum_required(VERSION 3.10)

project(quinze
	VERSION 1.0
        LANGUAGES CXX)

find_package(Curses REQUIRED)

include_directories(
	${CURSES_INCLUDE_DIR}
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/source
)

file(GLOB all_SRCS
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
	"${PROJECT_SOURCE_DIR}/source/*.cpp"
)

add_executable(quinze ${all_SRCS})
target_link_libraries(quinze ${CURSES_LIBRARIES})
install(TARGETS quinze DESTINATION /usr/local/bin)
