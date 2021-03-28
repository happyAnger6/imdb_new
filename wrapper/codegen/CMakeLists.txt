aux_source_directory(${CMAKE_CURRENT_LIST_DIR} VRF_CLASS_DATA_SRCS)

add_library(db_vrf_stub
    ${VRF_CLASS_DATA_SRCS})

target_include_directories(db_vrf_stub PUBLIC
    ${PROJECT_ROOT}
    ${PROJECT_ROOT}/wrapper
    ${PROJECT_ROOT}/wrapper/codegen
)