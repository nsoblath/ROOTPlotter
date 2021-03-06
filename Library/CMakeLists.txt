# CMakeLists for ROOTPlotter/Library
# Author: N. Oblath

set (ROOTPLOTTER_LINKDEF_HEADERFILE ${CMAKE_CURRENT_SOURCE_DIR}/LinkDef/ROOTPlotterLinkDef.h)
set (ROOTPLOTTER_DICT_OUTFILE ${CMAKE_CURRENT_BINARY_DIR}/ROOTPlotterDict.cxx)

set (ROOTPLOTTER_UTILITY_HEADERFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility/Destroyer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility/Singleton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Utility/TIFactory.h
)

set (ROOTPLOTTER_HEADERFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/HelperFunctions.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TMultiPlotter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TPlottable.h
)

set (ROOTPLOTTER_SOURCEFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/HelperFunctions.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/TMultiPlotter.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/TPlottable.cxx
)

##################################################

#ROOT_GENERATE_DICTIONARY ("${ROOTPLOTTER_HEADERFILES}" "${ROOTPLOTTER_LINKDEF_HEADERFILE}" "${ROOTPLOTTER_DICT_OUTFILE}" "${CMAKE_INCLUDE_PATH}")
ROOT_GENERATE_DICTIONARY (${ROOTPLOTTER_DICT_OUTFILE} ${ROOTPLOTTER_HEADERFILES} LINKDEF ${ROOTPLOTTER_LINKDEF_HEADERFILE} OPTIONS ${ROOT_DICT_FLAGS})

add_library (ROOTPlotter ${ROOTPLOTTER_SOURCEFILES} ${ROOTPLOTTER_DICT_OUTFILE})
target_link_libraries (ROOTPlotter ${LIBS})

pbuilder_install_libraries(ROOTPlotter)
pbuilder_install_headers(${ROOTPLOTTER_HEADERFILES} ${ROOTPLOTTER_UTILITY_HEADERFILES})
