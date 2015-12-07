# For each test file, create an executable, ensure it links properly and
# then add it to the test set with add_test. Additionally, add it as a
# dependency to the check goal so that running 'make check' builds and runs
# the test case.

# Example:
   add_executable(run_lexer lexer_test.cpp)
   add_executable(run_parser parser_test.cpp)
   target_link_libraries(run_lexer gtest gtest_main)
   target_link_libraries(run_parser gtest gtest_main)
   add_test(run_lexer run_lexer)
   add_test(run_parser run_parser)
   add_dependencies(check run_lexer run_parser)
#   add_executable(run_tests test.cpp)
#   target_link_libraries(run_tests gtest gtest_main)
#   add_test(run_tests run_tests)
#   add_dependencies(check run_tests)
