add_subdirectory(example-tensor-method)

add_executable(client_test client.cpp)
add_executable(server_test server.cpp)

target_include_directories(client_test
                           PRIVATE ${CUDA_INCLUDE_DIRS}
                                   ${CMAKE_SOURCE_DIR}/tpls/ExaTensor/include
                                   ${CMAKE_SOURCE_DIR}/tpls/antlr/runtime/src
                                   ${MPI_CXX_INCLUDE_DIRS}
                                   ${CMAKE_SOURCE_DIR}/src/driver-rpc
                                   ${CMAKE_SOURCE_DIR}/src/parser
                                   ${CMAKE_SOURCE_DIR}/src)
target_include_directories(server_test
                           PRIVATE ${CUDA_INCLUDE_DIRS}
                                   ${CMAKE_SOURCE_DIR}/tpls/ExaTensor/include
                                   ${CMAKE_SOURCE_DIR}/tpls/antlr/runtime/src
                                   ${MPI_CXX_INCLUDE_DIRS}
                                   ${CMAKE_SOURCE_DIR}/src/driver-rpc
                                   ${CMAKE_SOURCE_DIR}/src/parser
                                   ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(client_test PUBLIC exatn ${MPI_CXX_LIBRARIES})
set_target_properties(client_test PROPERTIES FOLDER tests)
target_link_libraries(client_test PRIVATE gtest gmock gtest_main)
target_link_libraries(server_test PUBLIC exatn ${MPI_CXX_LIBRARIES})
set_target_properties(server_test PROPERTIES FOLDER tests)
target_link_libraries(server_test PRIVATE gtest gmock gtest_main)

if(NOT APPLE)
  get_filename_component(MPI_BIN_PATH ${MPI_CXX_COMPILER} DIRECTORY)
  # FIXME if OPENMPI and WHOAMI is ROOT, add --allow-run-as-root add_test(NAME
  # client_server_test COMMAND ${MPI_BIN_PATH}/mpirun -np 1 ./server_test : -np
  # 1 ./client_test)
endif()
add_dependencies(client_test exatensor-build)
add_dependencies(server_test exatensor-build)
