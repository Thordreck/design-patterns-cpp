#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>

// Ignore this. Just a workaround to the get the path to the db file
static std::string path_to_db { std::filesystem::current_path().string() };

class Database
{
    public:
        virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase : public Database
{
    public:
        SingletonDatabase(const SingletonDatabase&) = delete;
        void operator=(const SingletonDatabase&)    = delete;

        static SingletonDatabase& get()
        {
            static SingletonDatabase db;
            return db;
        }

        int get_population(const std::string& name) override
        {
            return capitals.at(name);
        }

    private:
        SingletonDatabase()
        {
            std::cout << "Initializing database. Path to db: " << path_to_db << "\n";

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

class DummyDatabase : public Database
{
    public:
        DummyDatabase()
        {
            capitals["alpha"] = 1;
            capitals["beta"]  = 2;
            capitals["gamma"] = 3;
        }

        int get_population(const std::string& name) override
        {
            return capitals.at(name);
        }

    private:
        std::map<std::string, int> capitals;
};

struct SingletonRecordFinder
{
    int total_population(const std::vector<std::string>& names)
    {
        int result { 0 };

        for(const auto& name : names)
        {
            result += SingletonDatabase::get().get_population(name);
        }

        return result;
    }
};

struct ConfigurableRecordFinder
{
    public:
        ConfigurableRecordFinder(Database& db) : db(db) {}

        int total_population(std::vector<std::string> names)
        {
            int result { 0 };

            for(const auto& name : names)
            {
                result += db.get_population(name);
            }

            return result;
        }

    private:
        Database& db;
};

TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
    SingletonRecordFinder rf;
    std::vector<std::string> names { "Seoul", "Mexico City" };

    const int tp = rf.total_population(names);
    EXPECT_EQ(17500000 + 17400000, tp);
}

TEST(RecordFinderTests, DependantTotalPopulationTest)
{
    DummyDatabase db;
    ConfigurableRecordFinder rf { db };

    EXPECT_EQ( 4, rf.total_population({ "alpha", "gamma" }) );
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    const std::string exeutable_path   ( argv[0] );
    const std::string exeutable_folder ( exeutable_path.data(), exeutable_path.find_last_of('/') );

    path_to_db += "/" + exeutable_folder + "/resources";

    return RUN_ALL_TESTS();
}
