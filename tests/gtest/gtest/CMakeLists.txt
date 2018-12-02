set(INSTALL_GTEST OFF CACHE BOOL "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)")
set(INSTALL_GMOCK OFF CACHE BOOL "Enable installation of googlemock. (Projects embedding googlemock may want to turn this OFF.)")
set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")

add_subdirectory(googletest)
