set(SOURCES
    iteration_extremum_finder.cpp
    vec.cpp
    matrix.cpp
    danylevsky_matrix_eihen_vv.cpp
    rotation_matrix_eigen_vv.cpp
    eigen_finder.cpp
    utils.cpp
)

add_library(${PROJECT_NAME}_logic STATIC ${SOURCES})