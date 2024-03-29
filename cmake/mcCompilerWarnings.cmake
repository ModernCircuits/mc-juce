add_library(mc_compiler_warnings INTERFACE)
add_library(mc::compiler_warnings ALIAS mc_compiler_warnings)

if((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))
    target_compile_options(mc_compiler_warnings INTERFACE /W4)
    if (MC_BUILD_WERROR)
        target_compile_options(mc_compiler_warnings INTERFACE /WX)
    endif (MC_BUILD_WERROR)
else ()
    target_compile_options(mc_compiler_warnings
        INTERFACE
            -Wall
            -Wextra
            -Wpedantic

            -Wshadow
            -Wsign-compare
            -Wcast-align
            -Wnarrowing
            -Woverloaded-virtual
            -Wreorder
            -Wstrict-aliasing
            -Wswitch-enum
            -Wuninitialized
            -Wunreachable-code
            -Wunused-parameter
            -Wzero-as-null-pointer-constant
            -Wno-float-equal

            $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
                -Wbool-conversion
                -Wconditional-uninitialized
                -Wconstant-conversion
                -Wextra-semi
                -Winconsistent-missing-destructor-override
                -Wint-conversion
                -Wnullable-to-nonnull-conversion
                -Wshadow-all
                -Wshift-sign-overflow
                -Wshorten-64-to-32
                -Wunused-private-field
            >

            $<$<CXX_COMPILER_ID:AppleClang>:
                -Wno-poison-system-directories
            >

            $<$<CXX_COMPILER_ID:GNU>:
                -Wredundant-decls
                -Wno-maybe-uninitialized
                -Wno-free-nonheap-object
                $<$<VERSION_GREATER:CXX_COMPILER_VERSION,"11.0.0">:-Wno-free-nonheap-object>
            >
    )
    if (MC_BUILD_WERROR)
        target_compile_options(mc_compiler_warnings INTERFACE -Werror)
    endif (MC_BUILD_WERROR)
endif ()
