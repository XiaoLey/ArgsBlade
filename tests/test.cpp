//
// Created by XiaoLey on 2022/6/2.
//

#include "argsblade.hpp"
#include "doctest/doctest.h"

// NOLINTBEGIN

TEST_CASE("constructors")
{
    char *argv[] = {"argsblade", "arg1"};
    int argc     = sizeof(argv) / sizeof(char *);

    ArgsBlade::Blade b1(1, argv);
    ArgsBlade::Blade b2(argc, argv);
    ArgsBlade::Blade b3(std::move(ArgsBlade::Blade(argc, argv)));
    ArgsBlade::Blade b4(1, argv, {"-h"});

    CHECK_FALSE(b1.getSignRealCount());
    CHECK_FALSE(b1.getDirectArgCount());
    CHECK_NOTHROW(b2.setSigns({"-h", "help"}));
    CHECK_NOTHROW(b1.slicing());
    CHECK_NOTHROW(b3.slicing());
}

TEST_CASE("no arg sign")
{
    char *argv[] = {"argsblade", "arg1", "arg2", "arg3", "arg4", "arg5"};
    int argc     = sizeof(argv) / sizeof(char *);

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
    int argc     = sizeof(argv) / sizeof(char *);

    ArgsBlade::Blade b(argc, argv, {"-i", "-o", "-s"});
    b.slicing();

    CHECK(b.getDirectArgCount() == 0);
    CHECK(b.getArgCount() == argc - 3 - 1);
    CHECK(b.getSignRealCount() == 2);
    CHECK(b.contains("-i", "arg3"));
    CHECK_FALSE(b.contains("-i", "arg4"));
    CHECK_FALSE(b.contains("-u", "arg9"));
    CHECK(b.containsSign("-o"));
    CHECK_FALSE(b.containsSign("-h"));
}

// NOLINTEND