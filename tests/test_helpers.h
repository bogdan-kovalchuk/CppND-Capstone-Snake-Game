#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <iostream>
#include <string>

static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define ASSERT_TRUE(expr)                                          \
    do {                                                           \
        tests_run++;                                               \
        if (expr) {                                                \
            tests_passed++;                                        \
        } else {                                                   \
            tests_failed++;                                        \
            std::cerr << "FAIL: " << #expr                         \
                      << " at " << __FILE__ << ":" << __LINE__     \
                      << "\n";                                     \
        }                                                          \
    } while (0)

#define ASSERT_FALSE(expr) ASSERT_TRUE(!(expr))

#define ASSERT_EQ(a, b)                                            \
    do {                                                           \
        tests_run++;                                               \
        if ((a) == (b)) {                                          \
            tests_passed++;                                        \
        } else {                                                   \
            tests_failed++;                                        \
            std::cerr << "FAIL: " << #a << " == " << #b           \
                      << " (" << (a) << " vs " << (b) << ")"      \
                      << " at " << __FILE__ << ":" << __LINE__     \
                      << "\n";                                     \
        }                                                          \
    } while (0)

inline int test_summary()
{
    std::cout << tests_run << " tests, "
              << tests_passed << " passed, "
              << tests_failed << " failed\n";
    return tests_failed > 0 ? 1 : 0;
}

#endif
