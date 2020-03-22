#include <vector>
#include <iostream>

// Curiosly recurring template pattern (CRTP)
template <typename Self>
struct SomeNeurons
{
    template <typename T>
    void connect_to(T& _other)
    {
        for(auto& from : *static_cast<Self*>(this))
        {
            for(auto& to : _other)
            {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

struct Neuron : SomeNeurons<Neuron>
{
    std::vector<Neuron*> in;
    std::vector<Neuron*> out;
    uint32_t id;

    Neuron()
    {
        static uint32_t id { 1 };
        this->id = id++;
    }

    // We need a single Neuron to behave as a collection with
    // only one element - itself.
    Neuron* begin() { return this; }
    Neuron* end()   { return this + 1; }

    friend std::ostream &operator<<(std::ostream& _os, const Neuron& _obj)
    {
        for(Neuron* n : _obj.in)
        {
            _os << n->id << "\t-->\t[" << _obj.id << "]" << std::endl;
        }

        for(Neuron* n : _obj.out)
        {
            _os << "[" << _obj.id << "]\t-->\t" << n->id << std::endl;
        }

        return _os;
    }
};

// Note: this shouldn't be done in production code, since
// STL containers do not have virtual destructors. It's here
// just for the sake of an easy demonstration of the design pattern.
struct NeuronLayer : std::vector<Neuron>, SomeNeurons<NeuronLayer>
{
    NeuronLayer(int count)
    {
        while(count --> 0)
        {
            emplace_back(Neuron{});
        }
    }

    friend std::ostream &operator<<(std::ostream& _os, const NeuronLayer& _obj)
    {
        for(auto& n : _obj)
        {
            _os << n;
        }

        return _os;
    }
};

int main()
{
    Neuron n1, n2;
    n1.connect_to(n2);

    std::cout << n1 << n2 << std::endl;

    NeuronLayer layer1 { 2 };
    NeuronLayer layer2 { 3 };

    // Without the design pattern, we would have here 4 different connection
    // scenarios - neuron to neuron, layer to layer, neuron to layer,
    // and layer to neuron. We would have here a cartesian product explosion
    n1.connect_to(layer1);
    layer2.connect_to(n2);
    layer1.connect_to(layer2);

    std::cout << layer1 << std::endl;

    return 0;
}
