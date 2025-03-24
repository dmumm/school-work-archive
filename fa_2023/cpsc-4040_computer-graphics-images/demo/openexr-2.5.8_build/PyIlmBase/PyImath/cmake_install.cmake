# Install script for directory: /home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImath.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathAutovectorize.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathBasicTypes.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathBox.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathBoxArrayImpl.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathColor.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathColor3ArrayImpl.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathColor4Array2DImpl.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathColor4ArrayImpl.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathDecorators.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathEuler.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathExport.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathFixedArray.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathFixedArray2D.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathFixedMatrix.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathFixedVArray.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathFrustum.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathFun.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathLine.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathM44Array.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathMathExc.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathMatrix.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathOperators.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathPlane.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathQuat.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathRandom.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathShear.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathStringArray.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathStringArrayRegister.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathStringTable.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathTask.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathUtil.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathVec.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathVec2Impl.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathVec3ArrayImpl.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathVec3Impl.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathVec4ArrayImpl.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathVec4Impl.h"
    "/home/dmumm/4040/demo/openexr-2.5.8/PyIlmBase/PyImath/PyImathVecOperators.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so.25.0.7"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so.25"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "\$ORIGIN/../lib:/home/dmumm/4040/demo/build/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/dmumm/4040/demo/openexr-2.5.8_build/PyIlmBase/PyImath/libPyImath_Python3_8-2_5.so.25.0.7"
    "/home/dmumm/4040/demo/openexr-2.5.8_build/PyIlmBase/PyImath/libPyImath_Python3_8-2_5.so.25"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so.25.0.7"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so.25"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Imath:/home/dmumm/4040/demo/openexr-2.5.8_build/PyIlmBase/PyIex:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Half:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/IexMath:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Iex:"
           NEW_RPATH "\$ORIGIN/../lib:/home/dmumm/4040/demo/build/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so"
         RPATH "\$ORIGIN/../lib:/home/dmumm/4040/demo/build/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/dmumm/4040/demo/openexr-2.5.8_build/PyIlmBase/PyImath/libPyImath_Python3_8-2_5.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so"
         OLD_RPATH "/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Imath:/home/dmumm/4040/demo/openexr-2.5.8_build/PyIlmBase/PyIex:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Half:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/IexMath:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Iex:"
         NEW_RPATH "\$ORIGIN/../lib:/home/dmumm/4040/demo/build/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libPyImath_Python3_8-2_5.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/imath.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/imath.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/imath.so"
         RPATH "\$ORIGIN/../lib:/home/dmumm/4040/demo/build/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE MODULE FILES "/home/dmumm/4040/demo/openexr-2.5.8_build/python3_8/imath.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/imath.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/imath.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/imath.so"
         OLD_RPATH "/home/dmumm/4040/demo/openexr-2.5.8_build/PyIlmBase/PyImath:/home/dmumm/4040/demo/openexr-2.5.8_build/PyIlmBase/PyIex:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Imath:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/IexMath:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Iex:/home/dmumm/4040/demo/openexr-2.5.8_build/IlmBase/Half:"
         NEW_RPATH "\$ORIGIN/../lib:/home/dmumm/4040/demo/build/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/imath.so")
    endif()
  endif()
endif()

