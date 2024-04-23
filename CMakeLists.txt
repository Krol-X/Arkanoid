cmake_minimum_required(VERSION 3.19)

project("Arkanoid") 

set(imgui_name "imgui-1.82")
set(imgui_zip_path "${CMAKE_SOURCE_DIR}/bin/${imgui_name}.zip")
set(imgui_out_path "${CMAKE_BINARY_DIR}/${imgui_name}")

set(glfw_name "glfw-3.3.3")
set(glfw_zip_path "${CMAKE_SOURCE_DIR}/bin/${glfw_name}.zip")
set(glfw_out_path "${CMAKE_BINARY_DIR}/${glfw_name}")

set(mathfu_name "mathfu-1.1.0")
set(mathfu_zip_path "${CMAKE_SOURCE_DIR}/bin/${mathfu_name}.zip")
set(mathfu_out_path "${CMAKE_BINARY_DIR}/${mathfu_name}")

set(irrklang_version "64bit-1.6.0")
set(irrklang_name "irrKlang-${irrklang_version}")
set(irrklang_zip_path "${CMAKE_SOURCE_DIR}/bin/${irrklang_name}.zip")
set(irrklang_out_path "${CMAKE_BINARY_DIR}/${irrklang_name}")



file(ARCHIVE_EXTRACT INPUT ${imgui_zip_path})
file(ARCHIVE_EXTRACT INPUT ${glfw_zip_path})
file(ARCHIVE_EXTRACT INPUT ${mathfu_zip_path})
file(ARCHIVE_EXTRACT INPUT ${irrklang_zip_path})



# glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target") 
add_subdirectory(${glfw_out_path} glfw_binary)

# glad
add_library(glad STATIC ${glfw_out_path}/deps/glad_gl.c)
target_include_directories(glad PUBLIC ${glfw_out_path}/deps/)

# imgui with glfw + opengl3 backend
add_library(imgui STATIC
  ${imgui_out_path}/imgui.cpp
  ${imgui_out_path}/imgui_demo.cpp
  ${imgui_out_path}/imgui_draw.cpp
  ${imgui_out_path}/imgui_tables.cpp
  ${imgui_out_path}/imgui_widgets.cpp
  ${imgui_out_path}/backends/imgui_impl_glfw.cpp
  ${imgui_out_path}/backends/imgui_impl_opengl3.cpp
)

# irrklang
set(irrklang_include_dir "${irrklang_out_path}/include")

if(WIN32)
  set(irrklang_libs_dir "${irrklang_out_path}/lib/Winx64-visualStudio")
  set(irrklang_libs "${irrklang_libs_dir}/irrKlang.lib")
  set(irrklang_bin_dir "${irrklang_out_path}/bin/Winx64-visualStudio")
elseif(UNIX AND NOT APPLE)
  set(irrklang_libs_dir "${irrklang_out_path}/bin/linux-gcc-64")
  set(irrklang_libs "${irrklang_libs_dir}/libIrrKlang.so" # ${irrklang_libs_dir}/ikpMP3.so???
)
elseif(APPLE)
endif()



target_include_directories(imgui PUBLIC 
  ${imgui_out_path}
  ${imgui_out_path}/backends
)

#target_compile_definitions(imgui PUBLIC IM_VEC2_CLASS_EXTRA)
target_link_libraries(imgui glad glfw)

# game
file(GLOB srcs
  "include/*.h"
  "include/**/*.h"
  "src/*.cpp"
  "src/**/*.cpp"
)

# include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} ${srcs})

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_directory_properties(PROPERTIES VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE MATHFU_COMPILE_WITHOUT_SIMD_SUPPORT)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${mathfu_out_path}/include/)
target_link_libraries(${CMAKE_PROJECT_NAME} glad imgui ${OPENGL_LIBRARIES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/)


target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${irrklang_include_dir})
target_link_libraries(${CMAKE_PROJECT_NAME} ${irrklang_libs})

if(WIN32)
  file(COPY ${irrklang_bin_dir}/ikpFlac.dll
            ${irrklang_bin_dir}/ikpMP3.dll
            ${irrklang_bin_dir}/irrKlang.dll
       DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

  target_link_options(${CMAKE_PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
endif() 