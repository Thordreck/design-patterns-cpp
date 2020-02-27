#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <boost/lexical_cast.hpp>

// Ignore this. Just a workaround to the get the path to the db file
static std::string path_to_db { std::filesystem::current_path().string() };

class SingletonDatabase
{
    public:
        SingletonDatabase(const SingletonDatabase&) = delete;
        void operator=(const SingletonDatabase&)    = delete;

        static SingletonDatabase& get()
        {
            static SingletonDatabase db;
            return db;
        }

        int get_population(const std::string& name)
        {
            return capitals.at(name);
        }

    private:
        SingletonDatabase()
        {
            std::cout << "Initializing database\n";

            std::ifstream ifs(path_to_db + "/capitals.txt");
            std::string s, s2;

            while(std::getline(ifs, s))
            {
                std::getline(ifs, s2);

                int pop = boost::lexical_cast<int>(s2);

                capitals[s] = pop;
            }
        }

    private:
        std::map<std::string, int> capitals;
};

int main(int argc, char* argv[])
{
    const std::string executable_path   ( argv[0] );
    const std::string executable_folder ( executable_path.data(), executable_path.find_last_of('/') );

    path_to_db += "/" + executable_folder + "/resources";

    std::string city = "Tokyo";

    std::cout << city << " has population "
        << SingletonDatabase::get().get_population(city) << std::endl;

    return 0;
}
