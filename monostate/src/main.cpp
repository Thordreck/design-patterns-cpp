#include <iostream>

class Printer
{
    public:
        int get_id() const { return id; }
        void set_id(int value) { id = value; }

    private:
        static int id;
};

int Printer::id = 0;

int main(int argc, char* argv[])
{
    Printer p1;
    p1.set_id(0);

    std::cout << "P1 id: " << p1.get_id() << std::endl;

    Printer p2;
    p2.set_id(1);

    std::cout << "P2 id: " << p2.get_id() << std::endl;
    std::cout << "P1 id: " << p1.get_id() << std::endl;

    return 0;
}
