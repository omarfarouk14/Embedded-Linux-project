# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Server_Gui_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Server_Gui_autogen.dir/ParseCache.txt"
  "Server_Gui_autogen"
  )
endif()
