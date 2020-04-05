#include <vector>
#include <memory>
#include <iostream>

class Memento
{
    private:
        friend class BankAccount;
        friend class BankAccount2;

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

class BankAccount2
{
    public:
        BankAccount2(int balance)
            : balance { balance }
        {
            changes.push_back(std::make_shared<Memento>(balance));
        }

        std::shared_ptr<Memento> deposit(int amount)
        {
            balance += amount;
            current++;
            auto m = std::make_shared<Memento>(balance);
            changes.push_back(m);

            return m;
        }

        void restore(const std::shared_ptr<Memento>& memento)
        {
            if(memento != nullptr) { return; }

            balance = memento->balance;
            changes.push_back(memento);
            current = changes.size() - 1;
        }

        std::shared_ptr<Memento> undo()
        {
            if(current <= 0) { return {}; }

            current--;
            auto m = changes[current];
            balance = m->balance;

            return m;
        }

        friend std::ostream& operator<<(std::ostream& oss, const BankAccount2& account)
        {
            oss << "balance: " << account.balance;
            return oss;
        }

        std::shared_ptr<Memento> redo()
        {
            if(current + 1 < changes.size())
            {
                current++;
                auto m = changes[current];
                balance = m->balance;
                return m;
            }
            else
            {
                return {};
            }
        }

    private:
        int balance { 0 };
        std::vector<std::shared_ptr<Memento>> changes;
        size_t current { 0 };
};


int main()
{
    BankAccount2 ba { 100 };

    ba.deposit(50);
    ba.deposit(25);

    std::cout << ba << std::endl;

    ba.undo();
    std::cout << "Undo 1: " << ba << std::endl;

    ba.undo();
    std::cout << "Undo 2: " << ba << std::endl;

    ba.redo();
    std::cout << "Redo: " << ba << std::endl;

    return 0;
}
