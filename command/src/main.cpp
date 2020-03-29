#include <vector>
#include <iostream>

struct BankAccount
{
    int balance { 0 };
    int overdraft_limit { -500 };

    void deposit(int amount)
    {
        balance += amount;
        std::cout << "deposited "        << amount
                  << ", balance is now " << balance << std::endl;
    }

    void withdraw(int amount)
    {
        if(balance - amount >= overdraft_limit)
        {
            balance -= amount;
            std::cout << "withdrew "         << amount
                      << ", balance is now " << balance << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& oss, const BankAccount& account)
    {
        return oss << "Balance: " << account.balance;
    }
};

struct Command
{
    virtual void call() = 0;
};

struct BankAccountCommand : public Command
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;

    BankAccountCommand(BankAccount& account, Action action, int amount)
        : account { account }
        , action  { action  }
        , amount  { amount  }
    {}

    void call() override
    {
        switch(action)
        {
            case deposit:
                account.deposit(amount);
                break;
            case withdraw:
                account.withdraw(amount);
                break;
        }
    }
};

int main()
{
    BankAccount account;

    std::vector<BankAccountCommand> commands;

    commands.push_back( { account, BankAccountCommand::deposit,  100 } );
    commands.push_back( { account, BankAccountCommand::withdraw, 200 } );

    for(auto& cmd : commands)
    {
        cmd.call();
    }

    std::cout << account << std::endl;

    return 0;
}
