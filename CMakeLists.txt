project(proj)

if (NOT EXISTS "googletest")
    execute_process(
        COMMAND git clone https://github.com/google/googletest.git
    )
endif()


add_subdirectory(src)
add_subdirectory(tests)

