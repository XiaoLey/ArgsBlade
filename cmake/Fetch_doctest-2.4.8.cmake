function(fetch_doctest_2_4_8_fnwefwflka)
    include(FetchContent)
    FetchContent_Declare(
      doctest
      GIT_REPOSITORY https://github.com/doctest/doctest.git
      GIT_TAG v2.4.8
    )
    FetchContent_MakeAvailable(doctest)
endfunction()
fetch_doctest_2_4_8_fnwefwflka()
