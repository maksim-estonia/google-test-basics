#include <gtest/gtest.h>

struct BankAccount
{
    int balance = 0;

    BankAccount()
    {}

    BankAccount(const int balance): balance(balance)
    {}

    void deposit(int amount)
    {
        balance += amount;
    }

    bool withdraw(int amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
            return true;
        }
        return false;
    }
};

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

struct account_state
{
    int initial_balance;
    int withdraw_amount;
    int final_balance;
    bool success;
};

TEST_F(BankAccountTest, BankAccountStartsEmpty)
{
    EXPECT_EQ(0, account->balance);
}

TEST_F(BankAccountTest, CanDepositMoney)
{
    account->deposit(100);
    EXPECT_EQ(100, account->balance);
}

struct WithdrawAccountTest: BankAccountTest, testing::WithParamInterface<account_state>
{
    WithdrawAccountTest()
    {
        account->balance = GetParam().initial_balance;
    }
};

TEST_P(WithdrawAccountTest, FinalBalance)
{
    auto as = GetParam();
    auto success = account->withdraw(as.withdraw_amount);
    EXPECT_EQ(as.final_balance, account->balance);
    EXPECT_EQ(as.success, success);
}

INSTANTIATE_TEST_CASE_P(Default, WithdrawAccountTest,
    testing::Values(
        account_state{100,50,50,true},
        account_state{100,200,100,false}
    ));

int main (int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}