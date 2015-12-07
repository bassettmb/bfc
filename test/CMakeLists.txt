# For each test file, create an executable, ensure it links properly and
# then add it to the test set with add_test. Additionally, add it as a
# dependency to the check goal so that running 'make check' builds and runs
# the test case.

# Example
#   add_executable(run_tests test.cpp)
#   target_link_libraries(run_tests gtest gtest_main)
#   add_test(run_tests run_tests)
#   add_dependencies(check run_tests)

macro(define_test exec_file source_file)
  add_executable("${exec_file}" "${source_file}")
  target_link_libraries("${exec_file}" gtest gtest_main)
  add_test("${exec_file}" "${exec_file}")
  add_dependencies(check "${exec_file}")
endmacro(define_test)

   add_executable(run_tests lexer_test.cpp)
   add_executable(run_tests parser_test.cpp)
   target_link_libraries(run_tests gtest gtest_main)
   add_test(run_tests run_tests)
