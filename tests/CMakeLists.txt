include(Fetch_doctest-2.4.8)

add_executable(${Tgt}_test)

target_sources(
  ${Tgt}_test PRIVATE
  "test.cpp"
)

target_compile_definitions(
  ${Tgt}_test PRIVATE
  DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN    # doctest main
)

target_link_libraries(${Tgt}_test PRIVATE ${Tgt} doctest)

add_test(test1 ${Tgt}_test)