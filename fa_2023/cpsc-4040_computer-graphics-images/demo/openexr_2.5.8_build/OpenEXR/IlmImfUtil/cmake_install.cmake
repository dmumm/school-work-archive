# Install script for directory: /home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil

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
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so.26.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so.26"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "\$ORIGIN/../lib:/usr/local/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/OpenEXR/IlmImfUtil/libIlmImfUtil-2_5.so.26.0.0"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/OpenEXR/IlmImfUtil/libIlmImfUtil-2_5.so.26"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so.26.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so.26"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/OpenEXR/IlmImf:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Imath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Half:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IexMath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IlmThread:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Iex:"
           NEW_RPATH "\$ORIGIN/../lib:/usr/local/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so"
         RPATH "\$ORIGIN/../lib:/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/OpenEXR/IlmImfUtil/libIlmImfUtil-2_5.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so"
         OLD_RPATH "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/OpenEXR/IlmImf:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Imath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Half:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IexMath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IlmThread:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Iex:"
         NEW_RPATH "\$ORIGIN/../lib:/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImfUtil-2_5.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfImageChannel.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfFlatImageChannel.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfDeepImageChannel.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfSampleCountChannel.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfImageLevel.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfFlatImageLevel.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfDeepImageLevel.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfImage.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfFlatImage.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfDeepImage.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfImageIO.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfFlatImageIO.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfDeepImageIO.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfImageDataWindow.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfImageChannelRenaming.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImfUtil/ImfUtilExport.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND /usr/bin/cmake -E chdir "$ENV{DESTDIR}/usr/local/lib" /usr/bin/cmake -E create_symlink libIlmImfUtil-2_5.so libIlmImfUtil.so)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  message("-- Creating symlink in  libIlmImfUtil.so -> libIlmImfUtil-2_5.so")
endif()

