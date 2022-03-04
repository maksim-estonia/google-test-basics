#include <gtest/gtest.h>
#include <vector>
using std::vector;

vector<int> x {1,2,3};
vector<int> y {1,2,3};

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) 
{
    ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";

    for (int i = 0; i < (int)x.size(); ++i) 
    {
        EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
    }
}


