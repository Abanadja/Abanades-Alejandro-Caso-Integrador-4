cmake_minimum_required(VERSION 3.29)
project(Abanades_Alejandro_Caso_Integrador_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Abanades_Alejandro_Caso_Integrador_4
    main.cpp
        Variant.h
        Variant.cpp
)
        include(FetchContent)
        FetchContent_Declare(
        json11
        GIT_REPOSITORY https://github.com/dropbox/json11.git
        GIT_TAG master
)
        FetchContent_MakeAvailable(json11)
        target_link_libraries(Abanades_Alejandro_Caso_Integrador_4 json11)

