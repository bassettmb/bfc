set(rts_entry_flags "")
set(rts_flags "")
set(rts_defines "")

if(NOT(NO_VERIFY_COMPILER))
  if("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
    set(rts_entry_flags "${rts_entry_flags} -g -Wall -Wextra")
    set(rts_flags "${rts_flags} -g -Wall -Wextra -fvisibility=hidden")
    set(rts_defines "${rts_defines} BFC_RTS_CLANG=1")
  elseif("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")
    if("${CMAKE_C_COMPILER_VERSION}" VERSION_GREATER 4.0)
      set(rts_entry_flags "${rts_entry_flags} -g -Wall -Wextra")
      set(rts_flags "${rts_flags} -g -Wall -Wextra -fvisibility=hidden")
      set(rts_defines "${rts_defines} BFC_RTS_GCC=1")
    else()
      message(FATAL_ERROR "C compiler must support configuring symbol visibility")
    endif()
  elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    if(NOT("${CMAKE_C_COMPILER_VERSION}" VERSION_GREATER 17))
      message(FATAL_ERROR "basic C99 support required")
    else()
      set(rts_entry_flags "${rts_entry_flags} /Wall")
      set(rts_flags "${rts_flags} /Wall")
      set(rts_defines "${rts_defines} BFC_RTS_MSVC=1")
    endif()
  else()
    message(WARNING "unexpected C compiler")
  endif()
endif()

if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
  set(rts_defines "${rts_defines} BFC_RTS_WIN=1")
endif()

# XXX: change static libraries to shared libraries?

add_library(bfcrts alloc.c assert.c exit.c heap.c init.c io.c)
set_target_properties(bfcrts
                      PROPERTIES
                      COMPILE_FLAGS "${rts_flags}"
                      COMPILE_DEFINITIONS "${rts_defines}")

target_include_directories(bfcrts PUBLIC "${CMAKE_SOURCE_DIR}")
install(TARGETS bfcrts DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(FILES rts.h DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bfc")

add_library(bfcentry start.c)
set_target_properties(bfcentry
                      PROPERTIES
                      COMPILE_FLAGS "${rts_entry_flags}")
target_include_directories(bfcentry PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
install(TARGETS bfcentry DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
