
cmake_minimum_required(VERSION 3.5)

project(Cephalopods01  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_NAME "Cephalopods_2d")

set(homeDir "/home/geotyper")

find_package(SFML 2.5.1 COMPONENTS graphics)
set (INCLUDES ${INCLUDES} ${SFML_INCLUDE_DIRS})
set (LIBS ${LIBS} ${SFML_LIBRARIES})


#Need imgui installed by this path
set (IMGUI_DIR ${homeDir}/CPP_lib/imGui/imgui-master)
find_package(ImGui-SFML REQUIRED)


include_directories(${IMGUISFML_DIR})
include_directories(${IMGUI_DIR})
include_directories(${INCLUDE_SDIR})
link_directories(${INCLUDE_SDIR})

set(Head_files

    math/cpVect.h
    math/cpBB.h
    math/chipmunk_types.h
    math/cpTransform.h

    agent/agent.hpp
    agent/appendage.hpp
    agent/body.hpp

    agent/dna/dna.hpp
    agent/dna/dnabody.hpp
    agent/dna/dnatentacle.hpp
    agent/dna/dnaaxon.hpp
    agent/dna/dnabrain.hpp
    agent/dna/dnaappendage.hpp

    agent/tentacle/segment.hpp
    agent/tentacle/segmenthead.hpp
    agent/tentacle/tentacle.hpp

    agent/brain/brain.hpp
    agent/brain/neuron.hpp
    agent/brain/axon.hpp

    mutator/mutator.hpp

    constants.hpp
    display.hpp
    mainloop.hpp

    spline_library/spline.h

    environment.hpp

    )

set(Source_files

    agent/agent.cpp
    agent/appendage.cpp
    agent/body.cpp
    agent/dna/dna.cpp
    agent/dna/dnabody.cpp
    agent/dna/dnatentacle.cpp
    agent/dna/dnaaxon.cpp
    agent/dna/dnabrain.cpp
    agent/dna/dnaappendage.cpp

    agent/tentacle/segment.cpp
    agent/tentacle/segmenthead.cpp
    agent/tentacle/tentacle.cpp

    agent/brain/brain.cpp
    agent/brain/neuron.cpp
    agent/brain/axon.cpp

    mutator/mutator.cpp

    display.cpp
    mainloop.cpp
    main.cpp

    constants.cpp


    environment.cpp

    )

set(ALL_FILES
    ${Head_files}
    ${Source_files}
    ${INCLUDES}

    )

add_executable(${EXECUTABLE_NAME} ${ALL_FILES})

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDES} )

target_link_libraries(${EXECUTABLE_NAME} sfml-graphics)
target_link_libraries(${EXECUTABLE_NAME} ImGui-SFML::ImGui-SFML)
