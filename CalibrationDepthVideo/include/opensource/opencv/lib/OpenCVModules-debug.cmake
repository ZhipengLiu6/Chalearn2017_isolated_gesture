#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "opencv_core" for configuration "Debug"
set_property(TARGET opencv_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_core PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_core248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG ""
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_core248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_core )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_core "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_core248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_core248d.dll" )

# Import target "opencv_flann" for configuration "Debug"
set_property(TARGET opencv_flann APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_flann PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_flann248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_flann248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_flann )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_flann "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_flann248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_flann248d.dll" )

# Import target "opencv_imgproc" for configuration "Debug"
set_property(TARGET opencv_imgproc APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_imgproc PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_imgproc248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_imgproc248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_imgproc )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_imgproc "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_imgproc248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_imgproc248d.dll" )

# Import target "opencv_highgui" for configuration "Debug"
set_property(TARGET opencv_highgui APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_highgui PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_highgui248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_imgproc"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_highgui248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_highgui )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_highgui "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_highgui248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_highgui248d.dll" )

# Import target "opencv_features2d" for configuration "Debug"
set_property(TARGET opencv_features2d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_features2d PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_features2d248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_features2d248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_features2d )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_features2d "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_features2d248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_features2d248d.dll" )

# Import target "opencv_calib3d" for configuration "Debug"
set_property(TARGET opencv_calib3d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_calib3d PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_calib3d248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui;opencv_features2d"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_calib3d248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_calib3d )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_calib3d "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_calib3d248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_calib3d248d.dll" )

# Import target "opencv_ml" for configuration "Debug"
set_property(TARGET opencv_ml APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_ml PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_ml248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_ml248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_ml )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_ml "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_ml248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_ml248d.dll" )

# Import target "opencv_video" for configuration "Debug"
set_property(TARGET opencv_video APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_video PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_video248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_imgproc"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_video248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_video )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_video "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_video248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_video248d.dll" )

# Import target "opencv_legacy" for configuration "Debug"
set_property(TARGET opencv_legacy APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_legacy PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_legacy248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui;opencv_features2d;opencv_calib3d;opencv_ml;opencv_video"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_legacy248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_legacy )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_legacy "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_legacy248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_legacy248d.dll" )

# Import target "opencv_objdetect" for configuration "Debug"
set_property(TARGET opencv_objdetect APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_objdetect PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_objdetect248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_imgproc;opencv_highgui"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_objdetect248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_objdetect )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_objdetect "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_objdetect248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_objdetect248d.dll" )

# Import target "opencv_photo" for configuration "Debug"
set_property(TARGET opencv_photo APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_photo PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_photo248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_imgproc"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_photo248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_photo )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_photo "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_photo248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_photo248d.dll" )

# Import target "opencv_gpu" for configuration "Debug"
set_property(TARGET opencv_gpu APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_gpu PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_gpu248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui;opencv_features2d;opencv_calib3d;opencv_ml;opencv_video;opencv_legacy;opencv_objdetect;opencv_photo"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_gpu248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_gpu )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_gpu "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_gpu248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_gpu248d.dll" )

# Import target "opencv_ocl" for configuration "Debug"
set_property(TARGET opencv_ocl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_ocl PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_ocl248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui;opencv_features2d;opencv_calib3d;opencv_ml;opencv_objdetect;opencv_video"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_ocl248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_ocl )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_ocl "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_ocl248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_ocl248d.dll" )

# Import target "opencv_nonfree" for configuration "Debug"
set_property(TARGET opencv_nonfree APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_nonfree PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_nonfree248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui;opencv_features2d;opencv_calib3d;opencv_ml;opencv_video;opencv_legacy;opencv_objdetect;opencv_photo;opencv_gpu;opencv_ocl"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_nonfree248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_nonfree )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_nonfree "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_nonfree248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_nonfree248d.dll" )

# Import target "opencv_contrib" for configuration "Debug"
set_property(TARGET opencv_contrib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_contrib PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_contrib248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui;opencv_features2d;opencv_calib3d;opencv_ml;opencv_video;opencv_legacy;opencv_objdetect;opencv_photo;opencv_gpu;opencv_ocl;opencv_nonfree"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_contrib248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_contrib )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_contrib "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_contrib248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_contrib248d.dll" )

# Import target "opencv_stitching" for configuration "Debug"
set_property(TARGET opencv_stitching APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_stitching PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_stitching248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui;opencv_features2d;opencv_calib3d;opencv_ml;opencv_video;opencv_legacy;opencv_objdetect;opencv_photo;opencv_gpu;opencv_ocl;opencv_nonfree"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_stitching248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_stitching )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_stitching "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_stitching248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_stitching248d.dll" )

# Import target "opencv_superres" for configuration "Debug"
set_property(TARGET opencv_superres APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_superres PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_superres248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui;opencv_features2d;opencv_calib3d;opencv_ml;opencv_video;opencv_legacy;opencv_objdetect;opencv_photo;opencv_gpu;opencv_ocl"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_superres248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_superres )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_superres "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_superres248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_superres248d.dll" )

# Import target "opencv_ts" for configuration "Debug"
set_property(TARGET opencv_ts APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_ts PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui;opencv_features2d"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_ts248d.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_ts )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_ts "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_ts248d.lib" )

# Import target "opencv_videostab" for configuration "Debug"
set_property(TARGET opencv_videostab APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(opencv_videostab PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_videostab248d.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "opencv_core;opencv_flann;opencv_imgproc;opencv_highgui;opencv_features2d;opencv_calib3d;opencv_ml;opencv_video;opencv_legacy;opencv_objdetect;opencv_photo;opencv_gpu"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_videostab248d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS opencv_videostab )
list(APPEND _IMPORT_CHECK_FILES_FOR_opencv_videostab "${_IMPORT_PREFIX}/x86/vc11/lib/opencv_videostab248d.lib" "${_IMPORT_PREFIX}/x86/vc11/bin/opencv_videostab248d.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
