#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

enum class OutputFormat
{
    markdown,
    html
};

struct ListStrategy
{
    virtual ~ListStrategy() = default;

    virtual void start(std::ostringstream& oss) {}
    virtual void end(std::ostringstream& oss)   {}

    virtual void add_item(std::ostringstream& oss, const std::string& item) = 0;
};

struct MarkdownListStrategy : public ListStrategy
{
    void add_item(std::ostringstream& oss, const std::string& item) override
    {
        oss << "* " << item << "\n";
    }
};

struct HtmlListStrategy : public ListStrategy
{
    void start(std::ostringstream& oss) override
    {
        oss << "<ul>\n";
    }

    virtual void end(std::ostringstream& oss) override
    {
        oss << "</ul>\n";
    }

    virtual void add_item(std::ostringstream& oss, const std::string& item) override
    {
        oss << "   <li>" << item << "</li>\n";
    }
};

template<typename LS>
struct TextProcessor
{
    public:
        void clear()
        {
            oss.str("");
            oss.clear();
        }

        void append_list(const std::vector<std::string>& items)
        {
            list_strategy.start(oss);

            for(const auto& item : items)
            {
                list_strategy.add_item(oss, item);
            }

            list_strategy.end(oss);
        }

        std::string str() const { return oss.str(); }

    private:
        std::ostringstream oss;
        LS list_strategy;
};

int main()
{
    std::vector<std::string> items { "foo", "bar", "baz" };

    // markdown
    TextProcessor<MarkdownListStrategy> tpm;
    tpm.append_list(items);
    std::cout << tpm.str() << std::endl;

    // html
    TextProcessor<HtmlListStrategy> tph;
    tph.append_list(items);
    std::cout << tph.str() << std::endl;

    return 0;
}
