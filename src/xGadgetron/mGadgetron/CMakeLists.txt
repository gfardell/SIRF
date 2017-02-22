#========================================================================
# Author: Kris Thielemans
# Copyright 2017 University College London
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#=========================================================================

if(BUILD_MATLAB)

  find_package(Boost COMPONENTS system thread filesystem REQUIRED)

  set(CMAKE_POSITION_INDEPENDENT_CODE True)

  include_directories("${MATLAB_INCLUDE_DIR}")
  add_definitions(${MATLAB_CXXFLAGS})


  add_library(mgadgetron SHARED mgadgetron.c)
  # fix output name and link flags
  SET_TARGET_PROPERTIES(mgadgetron PROPERTIES
        SUFFIX ".${MATLAB_MEX_EXT}" PREFIX "${MATLAB_PREFIX}"
        LINK_FLAGS "${MATLAB_CXXLINKER_FLAGS}") 
  target_link_libraries(mgadgetron  cgt iutil ${FFTW3_LIBRARY} ${ISMRMRD_LIBRARIES} ${Boost_LIBRARIES} ${MATLAB_LIBRARIES} )

  INSTALL(TARGETS mgadgetron DESTINATION "${MATLAB_DEST}")
  INSTALL(FILES mgadgetron.h DESTINATION "${MATLAB_DEST}")
  INSTALL(DIRECTORY +mGadgetron DESTINATION "${MATLAB_DEST}")
  file(GLOB MatlabFiles "${CMAKE_CURRENT_LIST_DIR}/*.m")
  INSTALL(FILES ${MatlabFiles} DESTINATION "${MATLAB_DEST}")


endif(BUILD_MATLAB)