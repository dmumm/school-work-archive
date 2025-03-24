# Install script for directory: /home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/dmumm/4040/demo/build")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so.25.0.7"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so.25"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "\$ORIGIN/../lib:/home/dmumm/4040/demo/build/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Imath/libImath-2_5.so.25.0.7"
    "/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Imath/libImath-2_5.so.25"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so.25.0.7"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so.25"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Half:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/IexMath:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Iex:"
           NEW_RPATH "\$ORIGIN/../lib:/home/dmumm/4040/demo/build/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so"
         RPATH "\$ORIGIN/../lib:/home/dmumm/4040/demo/build/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Imath/libImath-2_5.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so"
         OLD_RPATH "/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Half:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/IexMath:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Iex:"
         NEW_RPATH "\$ORIGIN/../lib:/home/dmumm/4040/demo/build/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libImath-2_5.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathBoxAlgo.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathBox.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathColorAlgo.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathColor.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathEuler.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathExc.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathExport.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathForward.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathFrame.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathFrustum.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathFrustumTest.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathFun.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathGL.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathGLU.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathHalfLimits.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathInt64.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathInterval.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathLimits.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathLineAlgo.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathLine.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathMath.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathMatrixAlgo.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathMatrix.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathNamespace.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathPlane.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathPlatform.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathQuat.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathRandom.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathRoots.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathShear.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathSphere.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathVecAlgo.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/IlmBase/Imath/ImathVec.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND /usr/bin/cmake -E chdir "$ENV{DESTDIR}/home/dmumm/4040/demo/build/lib" /usr/bin/cmake -E create_symlink libImath-2_5.so libImath.so)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  message("-- Creating symlink in /home/dmumm/4040/demo/build/lib libImath.so -> libImath-2_5.so")
endif()

