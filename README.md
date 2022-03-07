# Google Test: basics

- [Google Test: basics](#google-test-basics)
  - [Setup (Bazel)](#setup-bazel)
    - [Step 1: install Bazel](#step-1-install-bazel)
    - [Step 2: Set up a Bazel workspace](#step-2-set-up-a-bazel-workspace)
    - [Step 3: Create and run a binary](#step-3-create-and-run-a-binary)
  - [GoogleTest Primer](#googletest-primer)
    - [1-assertions](#1-assertions)
    - [2-factorial](#2-factorial)
    - [3-test-fixtures](#3-test-fixtures)
  - [Discussion](#discussion)
    - [Test case, test suite, test fixture](#test-case-test-suite-test-fixture)
    - [EXPECT_* and ASSERT_*](#expect_-and-assert_)
  - [Setup (CMake)](#setup-cmake)
    - [4-cmake](#4-cmake)
  - [C++ Unit testing](#c-unit-testing)
  - [5-google-test-demo](#5-google-test-demo)

## Setup (Bazel)

[Link](https://google.github.io/googletest/quickstart-bazel.html)

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

Historically, googletest started to use the term _Test Case_ for grouping related tests, whereas current publications, including ISTQB materials and various textbooks on software quality, use the term _Test Suite_ for this.

The related term _Test_, as it is used in googletest, corresponds to the term _Test Case_ of ISQTB and others.

- **Test (Case)**: Tests use assertions to verify the tested code's behaviour. If a test crashes or has a failed assertion, then it _fails_; otherwise it _succeeds_.

- **Test Suite**: A test suite contains one or more tests (cases). You should group your tests into sets suites that reflect the structure of the tested code. When multiple tests in a test suite need to share common objects and subroutines, you can put them into a _test fixture_ class. 

- **Test Fixture**: If you find yourself writing two or more tests that operate on similar data, you can use a _test fixture_. This allows you to reuse the same configuration of objects for several different tests.

### EXPECT_* and ASSERT_*

The assertions come in pairs that test the same thing but have different effects on the current function. `ASSERT_*` versions generate fatal failures when they fail, and **abort the current function**. `EXPECT_*` versions generate nonfatal failures, which don't abort the current function. Usually `EXPECT_*` are preferred, as they allow more than one failure to be reported in a test. However, you should use `ASSERT_*` if it doesn't make sense to continue when the assertion in question fails.

## Setup (CMake)

[Link](https://google.github.io/googletest/quickstart-cmake.html)

### 4-cmake

1. Create a file named CMakeLists.txt:

  ```
  cmake_minimum_required(VERSION 3.14)
  project(my_project)

  # GoogleTest requires at least C++11
  set(CMAKE_CXX_STANDARD 11)

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  ```

2. With GoogleTest declared as a dependency, you can use GoogleTest code within your own project

3. To build the code, add the following to the end of your `CMakeLists.txt` file:

  ```
  enable_testing()

  add_executable(
    hello_test
    hello_test.cc
  )
  target_link_libraries(
    hello_test
    gtest_main
  )

  include(GoogleTest)
  gtest_discover_tests(hello_test)
  ```

4. Now build and run:

  ```
  cmake -S . -B build

  cmake --build build

  cd build && ctest
  ```

## C++ Unit testing

## 5-google-test-demo

Based on [video](https://www.youtube.com/watch?v=16FI1-d2P4E)

1. Setup

  - create `BUILD` file

  ```
  cc_test(
  name = "GoogleTestDemo",
  size = "small",
  srcs = ["GoogleTestDemo.cpp"],
  deps = ["@com_google_googletest//:gtest_main"],
  )
  ```

  - create `WORKSPACE` file

  ```
  load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

  http_archive(
    name = "com_google_googletest",
    urls = ["https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip"],
    strip_prefix = "googletest-e2239ee6043f73722e7aa812a459f54a28552929",
  )
  ```

  - create GoogleTestDemo.cpp

  ```cpp
  #include <gtest/gtest.h>

  struct BankAccount
  {
      int balance;

      BankAccount()
      {}

      BankAccount(const int balance): balance(balance)
      {}
  };

  TEST(AccountTest, BankAccountStartsEmpty)
  {
      BankAccount account;
      EXPECT_EQ(0, account.balance);
  }

  int main (int argc, char* argv[])
  {
      testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
  }
  ```

  In its current form the code should return an error:

  ![images/empty-error.png](/images/empty-error.png)

2. Initialize `balance` to 0

  ```cpp
  struct BankAccount
  {
      int balance = 0;

      BankAccount()
      {}

      BankAccount(const int balance): balance(balance)
      {}
  };
  ```

  Running test again:

  ![images/empty-true.png](/images/empty-true.png)

3. To avoid creating a `BankAccount` for every test, we will set up a test fixture:

  ```cpp
  struct BankAccountTest: testing::Test
  {
    BankAccount* account;

    BankAccountTest()
    {
      account = new BankAccount;
    }

    ~BankAccountTest()
    {
      delete account;
    }
  };
  ```

4. Change from `TEST` to `TEST_F` and change first argument to text fixture

  ```cpp
  TEST_F(BankAccountTest, BankAccountStartsEmpty)
  {
      EXPECT_EQ(0, account->balance);
  }
  ```

  Running test again:

  ![images/test-fixture.png](/images/test-fixture.png)

5. Add new test `CanDepositMoney`

  ```cpp
  TEST_F(BankAccountTest, CanDepositMoney)
  {
      account->deposit(100);
      EXPECT_EQ(100, account->balance);
  }
  ```

6. Add deposit functionality to `BankAccount`

  ```cpp
  void deposit(int amount)
  {
    balance += amount;
  }
  ```

  Running test:

  ![images/can-deposit.png](/images/can-deposit.png)

7. Add parametrized test
   
   - Add `account_state` structure

    ```cpp
    struct account_state
    {
      int initial_balance;
      int withdraw_amount;
      int final_balance;
      bool success;
    }
    ```

  - Add `WithdrawAccountTest`

    ```cpp
    struct WithdrawAccountTest: BankAccountTest, testing::WithParamInterface<account_state>
    {
      WithdrawAccountTest()
      {
        account->balance = GetParam().initial_balance;
      }
    }
    ```
  
  - Add parametrized test

    ```cpp
    TEST_P(WithdrawAccountTest, FinalBalance)
    {
      auto as = GetParam();
      auto success = account->withdraw(as.withdraw_amount);
      EXPECT_EQ(as.final_balance, account->balance);
      EXPECT_EQ(as.success, success);
    }
    ```

8. Add withdraw functionality to `BankAccount`

  ```cpp
  bool withdraw(int amount)
  {
    if (amount <= balance)
    {
      balance -= amount;
      return true;
    }
    return false;
  }
  
  ```

9. Provide data to run test

  ```cpp
  INSTANTIATE_TEST_CASE_P(Default, WithdrawAccountTest,
    testing::Values(
      account_state{100,50,50,true},
      account_state{100,200,100,false}
    ));
  ```

Running test:

![images/parametrized-test.png](/images/parametrized-test.png)



