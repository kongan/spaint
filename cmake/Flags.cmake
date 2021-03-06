###############
# Flags.cmake #
###############

# If on Mac OS X:
IF(${CMAKE_SYSTEM} MATCHES "Darwin")
  # Make sure that C++11 warnings are disabled.
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++11-extensions")

  # Make sure that the template depth is sufficient.
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth=512")
ENDIF()

# If on Mac OS X 10.9 (Mavericks), make sure everything compiles and links using the correct C++ Standard Library.
IF(${CMAKE_SYSTEM} MATCHES "Darwin-13.")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libstdc++")
ENDIF()

# If on Linux:
IF(${CMAKE_SYSTEM} MATCHES "Linux")
  # Make sure that C++11 support is enabled.
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

  # Disable the annoying warnings about deprecated declarations.
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
ENDIF()

# If on Windows and using Visual Studio:
IF(MSVC_IDE)
  # Disable the annoying warnings about using secure functions (they're Microsoft-specific, so we can't use them portably).
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
  ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)

  # Prevent the definitions of min and max when including windows.h.
  ADD_DEFINITIONS(-DNOMINMAX)

  # Prevent Winsock from being included when including windows.h.
  ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)

  # Make sure that the maths constants are defined.
  ADD_DEFINITIONS(-D_USE_MATH_DEFINES)

  # Define a macro needed when using Boost.ASIO.
  ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)
ENDIF()
