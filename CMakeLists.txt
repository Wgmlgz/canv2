cmake_minimum_required(VERSION 3.6)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(APP_NAME "canvas-lib")
project(${APP_NAME} CXX C)

set(INCLUDE
  src/logo.h
  src/bgfx_utils.h
)

set(SOURCE
  src/entry/cmd.cpp
  src/entry/cmd.h
  # src/entry/entry_html5.cpp
  src/entry/entry_p.h
  src/entry/entry.cpp
  src/entry/entry.h
  src/entry/input.cpp
  src/entry/input.h
  src/common.h
  src/main.cpp
)

add_executable(${APP_NAME}
  ${SOURCE}
)

# # target_compile_options(canvas-lib PROPERTIES LINK_FLAGS " --bind")
# set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "-sENVIRONMENT='web' -sUSE_ES6_IMPORT_META=0 -sEXPORT_NAME='WWasmModule' --std=c++20 -sEXPORTED_FUNCTIONS='[\"_malloc\", \"_free\" ]' -sEXPORTED_RUNTIME_METHODS='[\"ccall\", \"cwrap\"]' --bind")
set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "-sENVIRONMENT='web' -sALLOW_MEMORY_GROWTH --bind")

# set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "--no-entry")
# set_target_properties(${APP_NAME} PROPERTIES SUFFIX ".mjs")
set(EMSCRIPTEN $ENV{EMSCRIPTEN})

target_include_directories(${APP_NAME} PRIVATE bx/include)
target_include_directories(${APP_NAME} PRIVATE bgfx/include)
target_include_directories(${APP_NAME} PRIVATE bimg/include)

target_compile_definitions(
  ${APP_NAME}
  PUBLIC
  "BX_CONFIG_DEBUG=0"
)

set(BGFX_OUT bgfx/.build/wasm/obj/Release)

file(GLOB_RECURSE BGFX_O
  "bgfx/.build/wasm/obj/Debug/bgfx/*.o"
  "bgfx/.build/wasm/obj/Debug/bimg/*.o"
  "bgfx/.build/wasm/obj/Debug/bimg_decode/*.o"
  "bgfx/.build/wasm/obj/Debug/bx/*.o"

  # "bgfx/.build/wasm/obj/Debug/example-common/*.o"
)

# message(BGFX_O="${BGFX_O}")
target_compile_definitions(
  ${APP_NAME}
  PRIVATE "-D_CRT_SECURE_NO_WARNINGS" #
  "-D__STDC_FORMAT_MACROS" #
  "-DENTRY_CONFIG_IMPLEMENT_MAIN=1" #
)

target_link_libraries(
  ${APP_NAME}
  ${BGFX_O}
)
target_link_options(${APP_NAME} PRIVATE "-sMIN_WEBGL_VERSION=2")
