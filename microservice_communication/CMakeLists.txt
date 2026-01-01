# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# cmake build file for C++ helloworld example.
# Assumes protobuf and gRPC have been installed using cmake.
# See cmake_externalproject/CMakeLists.txt for all-in-one cmake build
# that automatically builds all the dependencies before building helloworld.

cmake_minimum_required(VERSION 3.16)

project(HttpData C CXX)

include(../cmake/common.cmake)

#find_package(Libevent REQUIRED)

# Proto file
get_filename_component(message_proto "message.proto" ABSOLUTE)
get_filename_component(message_proto_path "${message_proto}" PATH)

message("path: ${message_proto_path}")

# Generated sources
set(message_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/message.pb.cc")
set(message_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/message.pb.h")
set(message_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/message.grpc.pb.cc")
set(message_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/message.grpc.pb.h")

add_custom_command(
      OUTPUT "${message_proto_srcs}" "${message_proto_hdrs}" "${message_grpc_srcs}" "${message_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${message_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
         "${message_proto}"
      DEPENDS "${message_proto}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(message_grpc_proto
  ${message_grpc_srcs}
  ${message_grpc_hdrs}
  ${message_proto_srcs}
  ${message_proto_hdrs}
)

target_link_libraries(message_grpc_proto
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}
  )

foreach(_target
  sync_client sync_server)
  add_executable(${_target} "${_target}.cc")
  target_link_libraries(${_target}
    message_grpc_proto
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    )
endforeach()
