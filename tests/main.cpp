//
// Created by XiaoLey on 2022/6/2.
//

#include "doctest/doctest.h"
#include "argsblade.hpp"

// NOLINTBEGIN

TEST_CASE("no arg sign")
{
    char *argv[] = {"argsblade", "arg1", "arg2", "arg3", "arg4", "arg5"};
    int argc = sizeof(argv) / sizeof(char *);

    ArgsBlade::Blade b(argc, argv, {"-i"});
    b.slicing();

    CHECK(b.getDirectArgCount() == argc - 1);
    CHECK(b.getSignRealCount() == 0);
    for (int i = 0; i < argc - 1; ++i) {
        CHECK(b[""][i] == argv[i + 1]);
    }
}

TEST_CASE("arg with sign")
{
    char *argv[] = {"argsblade", "-i", "arg1", "arg2", "arg3", "-o", "arg4", "arg5", "-i", "arg6", "arg7", "arg8"};
    int argc = sizeof(argv) / sizeof(char *);

    ArgsBlade::Blade b(argc, argv, {"-i", "-o", "-s"});
    b.slicing();

    CHECK(b.getDirectArgCount() == 0);
    CHECK(b.getArgCount() == argc - 3 - 1);
    CHECK(b.getSignRealCount() == 2);
    CHECK(b.contains("-i", "arg3"));
    CHECK(!b.contains("-i", "arg4"));
}

// NOLINTEND