# For each test file, create an executable, ensure it links properly and
# then add it to the test set with add_test. From the build directory, we
# can run it with make test (detailed output with ARGS=-V)

# Example:
   add_executable(run_tests lexer_test.cpp)
   add_executable(run_tests parser_test.cpp)
   target_link_libraries(run_tests gtest gtest_main)
   add_test(run_tests run_tests)
