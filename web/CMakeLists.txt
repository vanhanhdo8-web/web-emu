cmake_minimum_required(VERSION 3.16)
project(CasioEmuWeb)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXECUTABLE_SUFFIX ".html")

# Source files from app/jni/src
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../app/jni/src)

include_directories(
    ${SRC_DIR}
    ${SRC_DIR}/Ext
    ${SRC_DIR}/Dcl
    ${SRC_DIR}/Chipset
    ${SRC_DIR}/Containers
    ${SRC_DIR}/Gui
    ${SRC_DIR}/Gui/imgui
    ${SRC_DIR}/Peripheral
    ${SRC_DIR}/StartupUi
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Emscripten flags
set(EMSCRIPTEN_LINK_FLAGS
    "-s USE_SDL=2"
    "-s USE_SDL_IMAGE=2"
    "-s SDL2_IMAGE_FORMATS=[png]"
    "-s USE_WEBGL2=1"
    "-s FULL_ES3=1"
    "-s WASM=1"
    "-s ALLOW_MEMORY_GROWTH=1"
    "-s INITIAL_MEMORY=134217728"
    "-s MAXIMUM_MEMORY=536870912"
    "-s EXPORTED_FUNCTIONS=[_main,_malloc,_free]"
    "-s EXPORTED_RUNTIME_METHODS=[ccall,cwrap,FS,PATH,stringToUTF8,UTF8ToString,lengthBytesUTF8]"
    "-s MODULARIZE=1"
    "-s EXPORT_NAME='CasioEmuModule'"
    "-s ASYNCIFY=1"
    "-s ASYNCIFY_IMPORTS=[emscripten_sleep]"
    "-s NO_EXIT_RUNTIME=1"
    "-s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0"
    "-O3"
    "--shell-file ${CMAKE_CURRENT_SOURCE_DIR}/shell.html"
)

# Collect all cpp files
file(GLOB_RECURSE SOURCES 
    ${SRC_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/*.cpp
)

# Remove platform-specific files not needed for web
list(FILTER SOURCES EXCLUDE REGEX ".*android.*")

add_executable(casioemu_web ${SOURCES})

target_compile_definitions(casioemu_web PRIVATE __EMSCRIPTEN__=1 SINGLE_WINDOW=1 IMGUI_API=)
target_compile_options(casioemu_web PRIVATE -O3 -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -fdeclspec)

target_link_options(casioemu_web PRIVATE ${EMSCRIPTEN_LINK_FLAGS})

# Preload assets if they exist
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    target_link_options(casioemu_web PRIVATE "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets@/assets")
endif()

