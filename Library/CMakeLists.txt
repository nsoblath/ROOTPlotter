# CMakeLists for ROOTPlotter/Library
# Author: N. Oblath

set (ROOTPLOTTER_LINKDEF_HEADERFILE ${CMAKE_CURRENT_SOURCE_DIR}/LinkDef/ROOTPlotterLinkDef.h)
set (ROOTPLOTTER_DICT_OUTFILE ${CMAKE_CURRENT_BINARY_DIR}/ROOTPlotterDict.cxx)

set (ROOTPLOTTER_HEADERFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/HelperFunctions.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TMultiPlotter.h
)

set (ROOTPLOTTER_SOURCEFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/HelperFunctions.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/TMultiPlotter.cxx
)

##################################################

ROOT_GENERATE_DICTIONARY ("${ROOTPLOTTER_DICT_HEADERFILES}" "${ROOTPLOTTER_LINKDEF_HEADERFILE}" "${ROOTPLOTTER_DICT_OUTFILE}" "${CMAKE_INCLUDE_PATH}")

add_library (ROOTPlotter ${ROOTPLOTTER_SOURCEFILES})
target_link_libraries (ROOTPlotter ${LIBS})

rootplotter_install_libraries(ROOTPlotter)
rootplotter_install_headers(${ROOTPLOTTER_HEADERFILES})
