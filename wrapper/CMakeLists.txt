aux_source_directory(${CMAKE_CURRENT_LIST_DIR} GMDB_WRAPPER_SRCS)

add_library(gmdb_wrapper_stub
    ${GMDB_WRAPPER_SRCS}
)

target_include_directories(gmdb_wrapper_stub PUBLIC
    ${PROJECT_ROOT}
)