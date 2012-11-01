# CMakeFiles.txt for CImg
#
# Haz-Edine Assemlal <assemlal@gmail.com>

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(CIMG_PACKAGE_VERSION_MAJOR 1)
set(CIMG_PACKAGE_VERSION_MINOR 5)
set(CIMG_PACKAGE_VERSION_PATCH 0)

# register local modules
SET(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake-modules")


PROJECT(CIMG)
#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")
ENABLE_TESTING()
include(CTest)

# Packaging defines
set(CPACK_GENERATOR TGZ)
set(CPACK_PACKAGE_VERSION_MAJOR ${CIMG_PACKAGE_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${CIMG_PACKAGE_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${CIMG_PACKAGE_VERSION_PATCH})
include(CPack)

set(PACKAGE "CImg")
set(PACKAGE_BUGREPORT "david.tschumperle@greyc.ensicaen.fr")
set(PACKAGE_NAME "CImg")
set(PACKAGE_VERSION "${CIMG_PACKAGE_VERSION_MAJOR}.${CIMG_PACKAGE_VERSION_MINOR}.${CIMG_PACKAGE_VERSION_PATCH}")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")


option(BUILD_EXAMPLES	  "Build examples" ON)
option(BUILD_GIMP	  "Build GIMP plug-ins" OFF)
option(BUILD_GMIC	  "Build GMIC" ON)
option(WITH_VT100	  "Enable color output messages " ON)
option(WITH_CIMG_DISPLAY  "Use CImg display capabilities" ON)
option(WITH_OPENMP	  "Use OpenMP parallel core instructions" ON)
option(WITH_OPENCV	  "Use OpenCV library"     OFF)
option(WITH_XRANDR	  "Use XRandR library" ON)
option(WITH_PNG		  "Use PNG library" ON)
option(WITH_JPEG	  "Use JPEG library" ON)
option(WITH_TIFF	  "Use TIFF library" ON)
option(WITH_OPENEXR	  "Use OpenEXR library" OFF)
option(WITH_FFMPEG	  "Use FFMPEG library" OFF)
option(WITH_ZLIB	  "Use Zlib library" ON)
option(WITH_MAGICK	  "Use Magick library" OFF)
option(WITH_FFTW3	  "Use FFTW3 library" ON)
option(WITH_LAPACK	  "Use LAPACK library" ON)
option(WITH_BOARD	  "Use BOARD library" OFF)
option(WITH_MINC2	  "Use MINC2 library" ON)


if(WITH_VT100)
  add_definitions(-Dcimg_use_vt100)
endif(WITH_VT100)

if( WITH_CIMG_DISPLAY )
  if(UNIX OR APPLE)
    if( CMAKE_SYSTEM_NAME MATCHES "(Solaris|SunOS)" )
       list( APPEND DEPENDENCIES_LIBRARIES "-R$(X11PATH)/lib -lrt -lnsl -lsocket" )
     else()
       find_package( X11 REQUIRED )
       include_directories( ${X11_INCLUDE_DIR} )
       list( APPEND DEPENDENCIES_LIBRARIES ${X11_LIBRARIES} )
     endif()
  elseif(WIN32)
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows" )
    list( APPEND DEPENDENCIES_LIBRARIES "-lgdi32" )
  endif()
else(WITH_CIMG_DISPLAY)
  add_definitions(-Dcimg_display=0)
endif(WITH_CIMG_DISPLAY)

if(WITH_OPENMP)
  find_package( OpenMP REQUIRED )
  add_definitions(-Dcimg_use_openmp)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif(WITH_OPENMP)

if(WITH_OPENCV)
  find_package( OpenCV REQUIRED )
  add_definitions(-Dcimg_use_opencv)
  include_directories( ${OpenCV_INCLUDE_DIR} )
  list( APPEND DEPENDENCIES_LIBRARIES ${OpenCV_LIBS} )
endif(WITH_OPENCV)

if(WITH_XRANDR)
  if(NOT X11_Xrandr_INCLUDE_PATH)
    message(FATAL_ERROR "Failed to find X11 XrandR which is required")
  endif(NOT X11_Xrandr_INCLUDE_PATH)
endif(WITH_XRANDR)

if(WITH_PNG)
  find_package( PNG REQUIRED )
  add_definitions(-Dcimg_use_png ${PNG_DEFINITIONS})
  include_directories( ${PNG_INCLUDE_DIRS} )
  list( APPEND DEPENDENCIES_LIBRARIES ${PNG_LIBRARIES} )
endif(WITH_PNG)

if(WITH_JPEG)
  find_package( JPEG REQUIRED )
  add_definitions( -Dcimg_use_jpeg )
  include_directories( ${JPEG_INCLUDE_DIR} )
  list( APPEND DEPENDENCIES_LIBRARIES ${JPEG_LIBRARIES} )
endif(WITH_JPEG)

if(WITH_TIFF)
  find_package( TIFF REQUIRED )
  add_definitions( -Dcimg_use_tiff )
  include_directories( ${TIFF_INCLUDE_DIR} )
  list( APPEND DEPENDENCIES_LIBRARIES ${TIFF_LIBRARIES} )
endif(WITH_TIFF)

if(WITH_EXR)
  find_package( OpenEXR REQUIRED )
  add_definitions( -Dcimg_use_openexr )
  include_directories( ${OpenEXR_INCLUDE_DIR} )
  list( APPEND DEPENDENCIES_LIBRARIES ${OPENEXR_LIBRARIES} )
endif(WITH_EXR)

# TODO
# if(WITH_FFMPEG)
#   find_package( Test REQUIRED )
#   add_definitions( -Dcimg_use_ffmpeg ${FFMPEG_DEFINITIONS} )
#   include_directories( ${FFMPEG_INCLUDE_DIRS} )
#   list( APPEND DEPENDENCIES_LIBRARIES ${FFMPEG_LIBRARIES} )
# endif(WITH_FFMPEG)

if(WITH_ZLIB)
  find_package( ZLIB REQUIRED )
  add_definitions( -Dcimg_use_zlib )
  include_directories( ${ZLIB_INCLUDE_DIR} )
  list( APPEND DEPENDENCIES_LIBRARIES ${ZLIB_LIBRARIES} )
endif(WITH_ZLIB)

if(WITH_MAGICK)
  find_package( ImageMagick REQUIRED COMPONENTS Magick++ convert)
  add_definitions( -Dcimg_use_magick )
  include_directories( ${ImageMagick_INCLUDE_DIRS} )
  list( APPEND DEPENDENCIES_LIBRARIES ${ImageMagick_LIBRARIES} )
endif(WITH_MAGICK)

if(WITH_FFTW3)
  find_package( FFTW3 REQUIRED )
  add_definitions( -Dcimg_use_fftw3 )
  include_directories( ${FFTW3_INCLUDE_DIRS} )
  list( APPEND DEPENDENCIES_LIBRARIES ${FFTW3_LIBRARIES} )
endif(WITH_FFTW3)

if(WITH_LAPACK)
  find_package( LAPACK REQUIRED )
  add_definitions( -Dcimg_use_lapack )
  include_directories( ${LAPACK_INCLUDE_DIRS} )
  list( APPEND DEPENDENCIES_LIBRARIES ${LAPACK_LIBRARIES} )
endif(WITH_LAPACK)

if(WITH_BOARD)
  find_package( BOARD REQUIRED )
  add_definitions( -Dcimg_use_board )
  include_directories( ${BOARD_INCLUDE_DIR} )
  list( APPEND DEPENDENCIES_LIBRARIES ${BOARD_LIBRARIES} )
endif(WITH_BOARD)

if(WITH_MINC2)
  find_package( NetCDF REQUIRED )
  find_package( HDF5 REQUIRED )
  find_package( MINC REQUIRED )
  find_package( EZMINC REQUIRED )
  add_definitions( -Dcimg_use_minc2 ${HDF5_DEFINITIONS} )
  include_directories( ${NetCDF_INCLUDE_DIR} ${HDF5_INCLUDE_DIRS} ${MINC_INCLUDE_DIR} ${EZMINC_INCLUDE_DIR} )
  list( APPEND DEPENDENCIES_LIBRARIES ${NetCDF_C_LIBRARY} ${HDF5_C_LIBRARIES} ${MINC_LIBRARIES} ${EZMINC_LIBRARIES} )
endif(WITH_MINC2)

if(BUILD_GIMP)
  find_package( GTK2 REQUIRED COMPONENTS gtk)
  include_directories( ${GTK2_INCLUDE_DIRS} )
  list( APPEND DEPENDENCIES_LIBRARIES ${GTK2_LIBRARIES} )
endif(BUILD_GIMP)

if(BUILD_GMIC)
  include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/examples )
  add_definitions( -Dcmake_build -Dgmic_main )
endif(BUILD_GMIC)

# aliases
set(VERSION "${PACKAGE_VERSION}")
include_directories(  ${CMAKE_CURRENT_SOURCE_DIR} )
LINK_LIBRARIES( ${DEPENDENCIES_LIBRARIES} )

if( BUILD_EXAMPLES )
  add_subdirectory(examples)
endif( BUILD_EXAMPLES )

# INSTALL(TARGETS 
#  correct_field evaluate_field extracttag sharpen_hist spline_smooth volume_hist volume_stats
#   DESTINATION bin)

# INSTALL(PROGRAMS
#   ${CMAKE_CURRENT_BINARY_DIR}/field2imp
#   ${CMAKE_CURRENT_BINARY_DIR}/imp2field
#   ${CMAKE_CURRENT_BINARY_DIR}/make_template
#   ${CMAKE_CURRENT_BINARY_DIR}/nu_estimate
#   ${CMAKE_CURRENT_BINARY_DIR}/nu_estimate_np_and_em
#   ${CMAKE_CURRENT_BINARY_DIR}/nu_evaluate
#   ${CMAKE_CURRENT_BINARY_DIR}/resample_labels
#   ${CMAKE_CURRENT_BINARY_DIR}/sharpen_volume
#   PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ  WORLD_EXECUTE WORLD_READ
#    DESTINATION bin )

# INSTALL(PROGRAMS
#   ${CMAKE_CURRENT_BINARY_DIR}/nu_estimate
#   PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ  WORLD_EXECUTE WORLD_READ
#    DESTINATION bin 
#   RENAME nu_correct )

# Generate an install target
#install(TARGETS RUNTIME DESTINATION bin)

# testing
if(BUILD_TESTING)
  #ADD_SUBDIRECTORY( testing )
endif(BUILD_TESTING)
