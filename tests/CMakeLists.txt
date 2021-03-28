aux_source_directory(. TESTS_SRCS)

add_executable(test_all ${TESTS_SRCS})

target_include_directories(test_all PUBLIC
        ${PROJECT_ROOT}
        ${PROJECT_ROOT}/wrapper
        ${PROJECT_ROOT}/codegen
)

target_link_libraries(test_all PUBLIC
        gmdb_wrapper_stub
        db_vrf_stub
        gtest
        gtest_main
)

add_test(
    NAME gtest
    COMMAND $<TARGET_FILE:test_all>)