#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

/**
 * @file pong-tests.cpp
 * @author your name (you@domain.com)
 * @brief Test file for the pong game
 * @version 0.1
 * @date 2023-10-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "pong-paddle.h"

/**
 * \brief This test checks that the left paddle is constructed correctly
 **/
TEST_CASE("testing the left paddle")
{
    auto lp = makeLeftPaddle();
    CHECK(lp.getOutlineThickness() == 3);
}
