# Install script for directory: /home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf

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
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so.26.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so.26"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "\$ORIGIN/../lib:/usr/local/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/OpenEXR/IlmImf/libIlmImf-2_5.so.26.0.0"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/OpenEXR/IlmImf/libIlmImf-2_5.so.26"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so.26.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so.26"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Imath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IlmThread:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Half:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IexMath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Iex:"
           NEW_RPATH "\$ORIGIN/../lib:/usr/local/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so"
         RPATH "\$ORIGIN/../lib:/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/OpenEXR/IlmImf/libIlmImf-2_5.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so"
         OLD_RPATH "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Imath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IlmThread:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Half:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/IexMath:/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr_2.5.8_build/IlmBase/Iex:"
         NEW_RPATH "\$ORIGIN/../lib:/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libIlmImf-2_5.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfForward.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfExport.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfBoxAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfCRgbaFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfChannelList.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfChannelListAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfCompressionAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDoubleAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfFloatAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfFrameBuffer.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfHeader.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfIO.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfInputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfIntAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfLineOrderAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfMatrixAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfOpaqueAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfOutputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfRgbaFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfStringAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfVecAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfHuf.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfWav.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfLut.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfArray.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfCompression.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfLineOrder.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfName.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfPixelType.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfVersion.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfXdr.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfConvert.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfPreviewImage.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfPreviewImageAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfChromaticities.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfChromaticitiesAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfKeyCode.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfKeyCodeAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfTimeCode.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfTimeCodeAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfRational.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfRationalAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfFramesPerSecond.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfStandardAttributes.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfStdIO.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfEnvmap.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfEnvmapAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfInt64.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfRgba.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfTileDescription.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfTileDescriptionAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfTiledInputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfTiledOutputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfTiledRgbaFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfRgbaYca.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfTestFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfThreading.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfB44Compressor.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfStringVectorAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfMultiView.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfAcesFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfMultiPartOutputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfGenericOutputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfMultiPartInputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfGenericInputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfPartType.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfPartHelper.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfOutputPart.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfTiledOutputPart.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfInputPart.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfTiledInputPart.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepScanLineOutputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepScanLineOutputPart.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepScanLineInputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepScanLineInputPart.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepTiledInputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepTiledInputPart.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepTiledOutputFile.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepTiledOutputPart.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepFrameBuffer.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepCompositing.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfCompositeDeepScanLine.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfNamespace.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepImageState.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfDeepImageStateAttribute.h"
    "/home/dmumm/dev/school/fa_2023/cpsc_4040/demo/openexr-2.5.8/OpenEXR/IlmImf/ImfFloatVectorAttribute.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND /usr/bin/cmake -E chdir "$ENV{DESTDIR}/usr/local/lib" /usr/bin/cmake -E create_symlink libIlmImf-2_5.so libIlmImf.so)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  message("-- Creating symlink in  libIlmImf.so -> libIlmImf-2_5.so")
endif()

