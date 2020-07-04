cmake_minimum_required(VERSION 3.0.0)
project(gup_raytracer VERSION 0.1.0)

set(Qt5_DIR "C:/Packages/Qt/Qt5.14.2/5.14.2/mingw73_64/lib/cmake/Qt5")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(src)

add_executable(gup_raytracer 
    src/interfaces/raytracer.cpp 
    src/interfaces/raytracer.h 

    src/geometry/geometry.cpp 
    src/geometry/geometry.h 
    src/geometry/plane.cpp 
    src/geometry/plane.h 
    src/geometry/sphere.cpp 
    src/geometry/sphere.h 

    src/samplers/sampler.cpp
    src/samplers/sampler.h
    src/samplers/regular.cpp
    src/samplers/regular.h
    src/samplers/random.cpp
    src/samplers/random.h
    src/samplers/jittered.cpp
    src/samplers/jittered.h
    src/samplers/rooks.cpp
    src/samplers/rooks.h
    src/samplers/multi_jittered.cpp
    src/samplers/multi_jittered.h
    src/samplers/hammersley.cpp
    src/samplers/hammersley.h

    src/tracers/multiple_objects.cpp 
    src/tracers/multiple_objects.h 
    src/tracers/function.cpp 
    src/tracers/function.h 
    src/tracers/tracer.cpp
    src/tracers/tracer.h 

    src/utilities/constants.h 
    src/utilities/maths.h 
    src/utilities/matrix.cpp 
    src/utilities/matrix.h 
    src/utilities/normal.cpp 
    src/utilities/normal.h 
    src/utilities/point.cpp 
    src/utilities/point.h 
    src/utilities/ray.cpp 
    src/utilities/ray.h 
    src/utilities/rgb_color.cpp 
    src/utilities/rgb_color.h 
    src/utilities/shade_rec.cpp 
    src/utilities/shade_rec.h 
    src/utilities/vector.cpp 
    src/utilities/vector.h 

    src/world/view_plane.cpp 
    src/world/view_plane.h 
    src/world/world.cpp 
    src/world/world.h
)

target_link_libraries(gup_raytracer ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES})