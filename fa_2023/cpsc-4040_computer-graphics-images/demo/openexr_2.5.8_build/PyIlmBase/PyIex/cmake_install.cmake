# Install script for directory: /home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/PyIlmBase/PyIex

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/PyIlmBase/PyIex/PyIex.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/PyIlmBase/PyIex/PyIexExport.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/PyIlmBase/PyIex/PyIexTypeTranslator.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so.25.0.7"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so.25"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "\$ORIGIN/../lib:/usr/local/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/PyIlmBase/PyIex/libPyIex_Python3_10-2_5.so.25.0.7"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/PyIlmBase/PyIex/libPyIex_Python3_10-2_5.so.25"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so.25.0.7"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so.25"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IexMath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Iex:"
           NEW_RPATH "\$ORIGIN/../lib:/usr/local/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so"
         RPATH "\$ORIGIN/../lib:/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/PyIlmBase/PyIex/libPyIex_Python3_10-2_5.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so"
         OLD_RPATH "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IexMath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Iex:"
         NEW_RPATH "\$ORIGIN/../lib:/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyIex_Python3_10-2_5.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/iex.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/iex.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/iex.so"
         RPATH "\$ORIGIN/../lib:/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE MODULE FILES "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/python3_10/iex.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/iex.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/iex.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/iex.so"
         OLD_RPATH "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/PyIlmBase/PyIex:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IexMath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Iex:"
         NEW_RPATH "\$ORIGIN/../lib:/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/iex.so")
    endif()
  endif()
endif()

