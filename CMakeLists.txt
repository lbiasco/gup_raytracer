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

    src/brdfs/brdf.h
    src/brdfs/blinn.cpp
    src/brdfs/blinn.h
    src/brdfs/lambertian.cpp
    src/brdfs/lambertian.h
    src/brdfs/phong.cpp
    src/brdfs/phong.h

    src/cameras/camera.cpp 
    src/cameras/camera.h 
    src/cameras/fisheye.cpp 
    src/cameras/fisheye.h 
    src/cameras/pinhole.cpp 
    src/cameras/pinhole.h 
    src/cameras/spherical.cpp 
    src/cameras/spherical.h 
    src/cameras/thin_lens.cpp 
    src/cameras/thin_lens.h 

    src/geometry/geometry.cpp 
    src/geometry/geometry.h 
    src/geometry/plane.cpp 
    src/geometry/plane.h 
    src/geometry/rectangle.cpp
    src/geometry/rectangle.h
    src/geometry/sphere.cpp 
    src/geometry/sphere.h 

    src/lights/light.h
    src/lights/ambient.cpp
    src/lights/ambient.h
    src/lights/ambient_occluder.cpp
    src/lights/ambient_occluder.h
    src/lights/area.cpp
    src/lights/area.h
    src/lights/directional.cpp
    src/lights/directional.h
    src/lights/point.cpp
    src/lights/point.h

    src/materials/material.h
    src/materials/emissive.cpp
    src/materials/emissive.h
    src/materials/matte.cpp
    src/materials/matte.h
    src/materials/glossy.cpp
    src/materials/glossy.h
    src/materials/plastic.cpp
    src/materials/plastic.h

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

    src/tracers/tracer.cpp
    src/tracers/tracer.h
    src/tracers/area_lighting.cpp
    src/tracers/area_lighting.h
    src/tracers/function.cpp 
    src/tracers/function.h
    src/tracers/raycast.cpp
    src/tracers/raycast.h

    src/utilities/constants.h 
    src/utilities/maths.h 
    src/utilities/matrix.cpp 
    src/utilities/matrix.h
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