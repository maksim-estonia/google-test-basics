# Google Test: basics

## Setup

### Step 1: install Bazel 

Bazel is a free software tool for the automation of building and testing software.

For Ubuntu: Follow instructions [here](https://bazel.build/install/ubuntu#binary-installer) (Using the binary installer)

### Step 2: Set up a Bazel workspace

[Instructions](https://google.github.io/googletest/quickstart-bazel.html#set-up-a-bazel-workspace)

A Bazel workspace is a directory on your filesystem that you use to manage source files for the software you want to build.

1. Create a directory for your workspace.

```bash
$ mkdir my_workspace && cd my_workspace
```

2. Create a `WORKSPACE` file to specify dependencies.

```
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip"],
  strip_prefix = "googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5",
)
```

### Step 3: Create and run a binary

1. Create a file named `hello_test.cc` in your `my_workspace` directory.

```c
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
```

2. To build the code, create a file named `BUILD` in the same directory.

```c
cc_test(
  name = "hello_test",
  size = "small",
  srcs = ["hello_test.cc"],
  deps = ["@com_google_googletest//:gtest_main"],
)
```

3. Build and run.

```bash
$ bazel test --test_output=all //:hello_test
```

Working:

![images/bazel.png](/images/bazel.png)

## GoogleTest Primer

[Link](https://google.github.io/googletest/primer.html)

### 1-assertions

Working:

![images/1-assertions.png](/images/1-assertions.png)

### 2-factorial

Working:

![images/2-factorials.png](/images/2-factorials.png)

### 3-test-fixtures

If you find yourself writing two or more tests that operate on similar data, you can use a test fixture. This allows you to reuse the same configuration of objects for several different tests. 

To create a fixture:

1. Derive a class from `::testing::Test`. Start its body with `protected:`, as we'll want to access fixture members from subclasses.
2. Inside the class, declare any objects you plan to use.
3. If necessary, write a default constructor or `SetUp()` function to prepare the objects for each test. 
  
  ```cpp
  class QueueTest : public ::testing::Test {
  protected:
    void SetUp() override {
      q1_.Enqueue(1);
      q2_.Enqueue(2);
      q2_.Enqueue(3);
    }

    // void TearDown() override {}

    Queue<int> q0_;
    Queue<int> q1_;
    Queue<int> q2_;
  };
  ```

  To build:

  ```bash
  bazel build //:test-fixture
  ```

  To test:

  ```bash
  bazel test --test_output=all //:test-fixture
  ```

  Working:

  ![images/3-test-fixture.png](/images/3-test-fixture.png)

  ## Discussion

  ### Test case, test suite, test fixture

  _The definition of test case, test suite, test fixture_

Historically, googletest started to use the term _Test Case_ for grouping related tests, whereas current publications, including ISTQB materials and various textbooks on software quality, use the term _Test Suite_ for this.

The related term _Test_, as it is used in googletest, corresponds to the term _Test Case_ of ISQTB and others.

- **Test (Case)**: Tests use assertions to verify the tested code's behaviour. If a test crashes or has a failed assertion, then it _fails_; otherwise it _succeeds_.

- **Test Suite**: A test suite contains one or more tests (cases). You should group your tests into sets suites that reflect the structure of the tested code. When multiple tests in a test suite need to share common objects and subroutines, you can put them into a _test fixture_ class. 

- **Test Fixture**: If you find yourself writing two or more tests that operate on similar data, you can use a _test fixture_. This allows you to reuse the same configuration of objects for several different tests.

### EXPECT_* and ASSERT_*

The assertions come in pairs that test the same thing but have different effects on the current function. `ASSERT_*` versions generate fatal failures when they fail, and **abort the current function**. `EXPECT_*` versions generate nonfatal failures, which don't abort the current function. Usually `EXPECT_*` are preferred, as they allow more than one failure to be reported in a test. However, you should use `ASSERT_*` if it doesn't make sense to continue when the assertion in question fails.







