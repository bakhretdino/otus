#include <config.h>
#include <gtest/gtest.h>
#include <version.hpp>

TEST(VersionTest, GetVerPatch) { ASSERT_TRUE(get_ver_patch() > 0); }
