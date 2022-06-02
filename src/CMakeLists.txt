add_library(${Tgt} INTERFACE)

target_compile_features(
  ${Tgt}
  INTERFACE
  cxx_std_17
)

target_include_directories(
  ${Tgt}
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)