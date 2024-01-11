
set(ABSL_ENABLE_INSTALL ON)

set(CPPLOGS_GRPC_ROOT_DIR ${CPPLOGS_SOURCE_DIRECTORY}/src/third_party/grpc)

add_subdirectory(${CPPLOGS_GRPC_ROOT_DIR} third_party/grpc)