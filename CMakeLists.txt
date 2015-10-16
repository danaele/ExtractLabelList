cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractLabelList)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractLabelList ExtractLabelList.cxx)
 
if(VTK_LIBRARIES)
  target_link_libraries(ExtractLabelList ${VTK_LIBRARIES})
else()
  target_link_libraries(ExtractLabelList vtkHybrid vtkWidgets)
endif()
