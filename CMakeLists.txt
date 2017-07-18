#definit la version minimale a utiliser
cmake_minimum_required(VERSION 3.0.2)

#nom du projet
project(Indie_studio)

#definit ou l'executable sera placé
set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS -std=c++11)


#==================================
#======INCLUSION D'IRRLICHT========
#==================================

#inclure le repertoire contenant les entetes de irrlicht
include_directories(/usr/local/include/irrlicht include/ include/scenes include/objects include/weapons)

#inlude les bibliothèque compiles
link_directories(/usr/local/lib)


#ficihier du projet
file(
        GLOB_RECURSE
        sources_files
        src/*
        include/*
)


#declaration de l'executable
add_executable(
        indie_studio
        ${sources_files}
)


#liaison du programme avec la bibliothèque
target_link_libraries(
        indie_studio
        Irrlicht
	SDL
        Xxf86vm
        GL
        Xext
        X11
        Xcursor
	sfml-audio
)
