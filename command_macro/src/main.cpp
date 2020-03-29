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

    bool withdraw(int amount)
    {
        if(balance - amount >= overdraft_limit)
        {
            balance -= amount;
            std::cout << "withdrew "         << amount
                      << ", balance is now " << balance << std::endl;

            return true;
        }

        return false;
    }

    friend std::ostream& operator<<(std::ostream& oss, const BankAccount& account)
    {
        return oss << "Balance: " << account.balance;
    }
};

struct Command
{
    virtual void call() = 0;
    virtual void undo() = 0;

    bool succeeded;
};

struct BankAccountCommand : public Command
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;

    BankAccountCommand(BankAccount& account, Action action, int amount)
        : account   { account }
        , action    { action  }
        , amount    { amount  }
    {
        succeeded = false;
    }

    void call() override
    {
        switch(action)
        {
            case deposit:
                account.deposit(amount);
                succeeded = true;
                break;
            case withdraw:
                succeeded = account.withdraw(amount);
                break;
        }
    }

    void undo() override
    {
        if(!succeeded) { return; }

        switch(action)
        {
            case deposit:
                account.withdraw(amount);
                break;
            case withdraw:
                account.deposit(amount);
                break;
        }
    }
};

struct CompositeBankAccountCommand : public Command
{
    std::vector<BankAccountCommand> commands;

    void call() override
    {
        for(auto& cmd : commands)
        {
            cmd.call();
        }
    }

    void undo() override
    {
        for(auto it = commands.rbegin(); it != commands.rend(); ++it)
        {
            it->undo();
        }
    }
};

struct BadMoneyTransferCommand : public CompositeBankAccountCommand
{
    BadMoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
    {
        commands.push_back( { from, BankAccountCommand::withdraw, amount } );
        commands.push_back( { to,   BankAccountCommand::deposit,  amount } );
    }
};

struct DependentCompositeCommand : public CompositeBankAccountCommand
{
    void call() override
    {
        bool ok = true;

        for(auto& cmd : commands)
        {
            if(ok)
            {
                cmd.call();
                ok = cmd.succeeded;
            }
            else
            {
                cmd.succeeded = false;
            }
        }
    }

    void undo() override
    {
        for(auto it = commands.rbegin(); it != commands.rend(); ++it)
        {
            it->undo();
        }
    }
};

struct MoneyTransferCommand : public DependentCompositeCommand
{
    MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
    {
        commands.push_back( { from, BankAccountCommand::withdraw, amount } );
        commands.push_back( { to,   BankAccountCommand::deposit,  amount } );
    }
};

int main()
{
    BankAccount account_from;
    BankAccount account_to;

    account_from.deposit(100);

    // This one works fine
    BadMoneyTransferCommand transfer_command { account_from, account_to, 50 };

    transfer_command.call();

    std::cout << "From: " << account_from << ". To: " << account_to << std::endl;
    
    transfer_command.undo();

    std::cout << "From: " << account_from << ". To: " << account_to << std::endl;

    std::cout << "-----------------------\n";

    // Uh oh...
    BadMoneyTransferCommand wrong_transfer_command { account_from, account_to, 5000 };

    wrong_transfer_command.call();

    std::cout << "From: " << account_from << ". To: " << account_to << std::endl;

    wrong_transfer_command.undo();

    std::cout << "-----------------------\n";

    // This one works correctly
    MoneyTransferCommand correct_transfer_command { account_from, account_to, 5000 };

    correct_transfer_command.call();

    std::cout << "From: " << account_from << ". To: " << account_to << std::endl;

    return 0;
}
