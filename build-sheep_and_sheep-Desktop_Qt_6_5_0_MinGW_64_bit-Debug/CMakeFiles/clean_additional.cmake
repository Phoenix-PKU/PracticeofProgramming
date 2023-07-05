# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\sheep_and_sheep_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\sheep_and_sheep_autogen.dir\\ParseCache.txt"
  "sheep_and_sheep_autogen"
  )
endif()
