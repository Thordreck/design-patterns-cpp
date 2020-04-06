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
            list_strategy->start(oss);

            for(const auto& item : items)
            {
                list_strategy->add_item(oss, item);
            }

            list_strategy->end(oss);
        }

        void set_output_format(const OutputFormat& format)
        {
            switch(format)
            {
                case OutputFormat::markdown:
                    list_strategy = std::make_unique<MarkdownListStrategy>();
                    break;
                case OutputFormat::html:
                    list_strategy = std::make_unique<HtmlListStrategy>();
                    break;
            }
        }

        std::string str() const { return oss.str(); }

    private:
        std::ostringstream oss;
        std::unique_ptr<ListStrategy> list_strategy;
};

int main()
{
    std::vector<std::string> items { "foo", "bar", "baz" };

    TextProcessor tp;
    tp.set_output_format(OutputFormat::markdown);
    tp.append_list(items);

    std::cout << tp.str() << std::endl;

    tp.set_output_format(OutputFormat::html);
    tp.clear();
    tp.append_list(items);
    
    std::cout <<  tp.str() << std::endl;

    return 0;
}
