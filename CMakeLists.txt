# определяем минимальную версию для компиляции
cmake_minimum_required(VERSION 3.5)

# НАЗНАЧАЕМ ИМЯ ПРОЕКТУ И УСТАНАВЛИВАЕМ НОМЕР ВЕРСИИ------------------------
# если определена среда сборки Travis то выставляем номер сборки из Travis
if($ENV{TRAVIS_BUILD_NUMBER})
project(kkmeans VERSION 1.1.$ENV{TRAVIS_BUILD_NUMBER})

# если среда не найдена то ставим номер сборки указанный ниже
else()
project(kkmeans VERSION 1.1.5)
endif()

find_package(dlib REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads)

include_directories(${GTEST_INCLUDE_DIRS})

# Генерируем файл version.h при сборке из файла с уловиями version.h.in
configure_file(${CMAKE_SOURCE_DIR}/include/version.h.in ${CMAKE_SOURCE_DIR}/include/version.h)


add_executable(kkmeans ${CMAKE_SOURCE_DIR}/source/kkmeans_ex.cpp ${CMAKE_SOURCE_DIR}/source/arg.cpp)
add_executable(points ${CMAKE_SOURCE_DIR}/source/create_points.cpp)
add_library(versionlib ${CMAKE_SOURCE_DIR}/source/version_lib.cpp)
add_executable(gtest  ${CMAKE_SOURCE_DIR}/source/gtest.cpp)


set_target_properties(kkmeans points versionlib gtest PROPERTIES
CXX_STANDARD 14
CXX_STANDARD_REQUIRED ON
)

target_include_directories(kkmeans
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)
target_include_directories(points
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)
target_include_directories(versionlib
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)
target_include_directories(gtest
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(points PRIVATE
dlib::dlib
)
target_link_libraries(kkmeans PRIVATE
dlib::dlib
versionlib
)
target_link_libraries(gtest
${GTEST_LIBRARIES}
${CMAKE_THREAD_LIBS_INIT}
versionlib
)

# СВОЙСТВА ДЛЯ КОМПИЛЯТОРОВ (ЛЮБЫЕ ПРЕДУПРЕЖДЕНИЯ ТРАКТОВАТЬ КАК ОШИБКИ)
if (MSVC)
target_compile_options(kkmeans PRIVATE
        /W4
)
target_compile_options(points PRIVATE
        /W4
)
target_compile_options(versionlib PRIVATE
        /W4
)
target_compile_options(gtest PRIVATE
        /W4
)
else ()
    target_compile_options(kkmeans PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(points PRIVATE
    -Wall -Wextra -pedantic -Werror
    )

    target_compile_options(versionlib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(gtest PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif()

# ----------------------------------------------------------------------

install(TARGETS kkmeans points RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT sise07@gmail.com)

include(CPack)

enable_testing()

add_test(version_test_case ${CMAKE_PROJECT_NAME})

