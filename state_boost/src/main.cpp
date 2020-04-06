#include <iostream>
#include <vector>
#include <string>

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

using namespace msm::front;

// Triggers
struct CallDialed          {};
struct HungUp              {};
struct CallConnected       {};
struct PlacedOnHold        {};
struct TakenOffHold        {};
struct LeftMessage         {};
struct PhoneThrownIntoWall {};

const std::vector<std::string> state_names
{
    "off hook",
    "connecting",
    "connected",
    "on hold",
    "destroyed",
};

// State machine
struct PhoneStateMachine : public state_machine_def<PhoneStateMachine>
{
    bool angry { true };

    struct OffHook    : public state<> {};
    struct Connecting : public state<>
    {
        template <class Event, class FSM>
        void on_entry(const Event&, FSM& fsm)
        {
            std::cout << "We are connecting...\n";
        }
    };

    struct Connected      : public state<> {};
    struct OnHold         : public state<> {};
    struct PhoneDestroyed : public state<> {};

    struct PhoneBeingDestroyed
    {
        template <class EVT, class FSM, class SourceState, class TargetState>
        void operator()(const EVT&, FSM&, SourceState&, TargetState&)
        {
            std::cout << "Phone breaks into a million pieces\n";
        }
    };

    struct CanDestroyPhone
    {
        template <class EVT, class FSM, class SourceState, class TargetState>
        bool operator()(const EVT&, FSM& fsm, SourceState&, TargetState&)
        {
            return fsm.angry;
        }
    };

    // Transition rules
    struct transition_table : public mpl::vector <
        Row<OffHook,    CallDialed,          Connecting>,
        Row<Connecting, CallConnected,       Connected>,
        Row<Connected,  PlacedOnHold,        OnHold>,
        Row<OnHold,     PhoneThrownIntoWall, PhoneDestroyed,
                        PhoneBeingDestroyed, CanDestroyPhone>
    > {};

    using initial_state = OffHook;

    template <class FSM, class Event>
    void no_transition(const Event& e, FSM&, int state)
    {
        std::cout << "No transition from state " << state_names[state]
                  << " on event "                << typeid(e).name()
                  << std::endl;
    }
};

int main()
{
    msm::back::state_machine<PhoneStateMachine> phone;

    auto info = [&] ()
    {
        const auto i = phone.current_state()[0];
        std::cout << "The phone is currently " << state_names[i] << "\n";
    };

    info();
    phone.process_event(CallDialed{});
    info();
    phone.process_event(CallConnected{});
    info();
    phone.process_event(PlacedOnHold{});
    info();
    phone.process_event(PhoneThrownIntoWall{});
    info();

    phone.process_event(CallDialed{});

    return 0;
}
