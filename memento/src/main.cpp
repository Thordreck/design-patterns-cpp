#include <vector>
#include <iostream>

class Memento
{
    private:
        friend class BankAccount;

    public:
        Memento(int balance) : balance { balance } {}

    private:
        int balance;
};

class BankAccount
{
    public:
        BankAccount(int balance) : balance { balance } {}

        Memento deposit(int amount)
        {
            balance += amount;
            return { balance };
        }

        void restore(const Memento& memento)
        {
            balance = memento.balance;
        }

        friend std::ostream& operator<<(std::ostream& oss, const BankAccount& account)
        {
            oss << "balance: " << account.balance;
            return oss;
        }

    private:
        int balance { 0 };
};


int main()
{

    BankAccount ba { 100 };

    const auto m1 = ba.deposit(50);
    const auto m2 = ba.deposit(25);

    std::cout << ba << "\n";

    ba.restore(m1);
    std::cout << "Back to m1: " << ba << "\n";

    ba.restore(m2);
    std::cout << "Back to m2: " << ba << "\n";

    return 0;
}
