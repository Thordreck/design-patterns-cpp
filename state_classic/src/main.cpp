#include <iostream>

class LightSwitch;

struct State
{
    virtual ~State() = default;

    virtual void on(LightSwitch* lhs)
    {
        std::cout << "Light is already on\n";
    }

    virtual void off(LightSwitch* lhs)
    {
        std::cout << "Light is already off\n";
    }
};

struct OnState : public State
{
    OnState()
    {
        std::cout << "Light is turned on\n";
    }

    void off(LightSwitch* lhs) override;
};

struct OffState : public State
{
    OffState()
    {
        std::cout << "Light is turned off\n";
    }

    void on(LightSwitch* lhs) override;
};

class LightSwitch
{
    public:
        LightSwitch()
        {
            state = new OffState();
        }

        void set_state(State* state)
        {
            this->state = state;
        }

        void on()
        {
            state->on(this);
        };

        void off()
        {
            state->off(this);
        };

    private:
        State* state;
};

void OnState::off(LightSwitch* lhs)
{
    std::cout << "Switching light off...\n";
    lhs->set_state(new OffState());
    delete this;
}

void OffState::on(LightSwitch* lhs)
{
    std::cout << "Switching light on...\n";
    lhs->set_state(new OnState());
    delete this;
}

int main()
{
    LightSwitch ls;
    ls.on();
    ls.off();
    ls.off();
    ls.on();
    ls.on();
    ls.off();

    return 0;
}
