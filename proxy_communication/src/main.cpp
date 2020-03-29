#include <string>
#include <iostream>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

struct Pingable
{
    virtual std::string ping(const std::string& message) = 0;
};

struct Pong : public Pingable
{
    std::string ping(const std::string& message) override
    {
        return message + " pong";
    }
};

struct RemotePong : public Pingable
{
    std::string ping(const std::string& message) override
    {

        std::string result;

        http_client client("https://postman-echo.com/");
        uri_builder builder("/headers/");

        builder.append("?" + message);

        const auto task = client.request(methods::GET, builder.to_string())
            .then([=] (http_response r)
            {
                return r.to_string();
            });

        task.wait();

        return task.get();
    }

};

void tryit(Pingable& pp)
{
    std::cout << pp.ping("ping") << std::endl;
}

int main()
{
    //Pong pp;
    RemotePong pp;

    for(size_t i = 0; i < 3; i++)
    {
        tryit(pp);
    }

    return 0;
}
