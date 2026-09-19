cmake_minimum_required(VERSION 3.10)
project(NavierStokes2DSolver LANGUAGES CXX)

# Ορίζουμε το πρότυπο C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Λέμε στον compiler να κοιτάζει μέσα στον φάκελο src για τα αρχεία .h
include_directories(src)


# Δημιουργία του εκτελέσιμου για το Cavity
add_executable(run_cavity
    src/NSexplicit.cpp
    src/Mesh.cpp
    src/Visual.cpp
    cases/cavity_flow/cavity.cpp
    cases/cavity_flow/cavity_boundary.cpp
)

# Δημιουργία του εκτελέσιμου για το Κανάλι
add_executable(run_channel
    src/NSexplicit.cpp
    src/Mesh.cpp
    src/Visual.cpp
    cases/channel_flow/channel_flow.cpp
    cases/channel_flow/channel_flow_boundary.cpp
)
