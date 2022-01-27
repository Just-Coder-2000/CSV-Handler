/**
 * @file main.cpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 */

#include "csv.h"
#include "artwork/logger/logger.h"

#pragma region helpers

struct Info
{
private:
    /**
     * @brief the members
     */
    int _id;
    std::string _name;
    float _score;

public:
    /**
     * @brief construct a new Info object
     */
    Info(const int &id, const std::string &name, const float &score)
        : _id(id), _name(name), _score(score) {}

    inline int &id() { return this->_id; }
    inline const int &id() const { return this->_id; }

    inline std::string &name() { return this->_name; }
    inline const std::string &name() const { return this->_name; }

    inline float &score() { return this->_score; }
    inline const float &score() const { return this->_score; }
};
/**
 * @brief override operator '<<' for type 'Info'
 */
std::ostream &operator<<(std::ostream &os, const Info &obj)
{
    os << '{';
    os << "'id': " << obj.id() << ", 'name': " << obj.name() << ", 'score': " << obj.score();
    os << '}';
    return os;
}

template <typename ElemType>
void vecOutput(const std::vector<ElemType> &vec)
{
    for (const auto &elem : vec)
        std::cout << elem << '\n';
}

#pragma endregion

void test_CSV_READ_IFS_ALL()
{
    INFO("test the macro 'CSV_READ_IFS_ALL', file '../data/info.csv'");
    std::ifstream ifs("../data/info.csv");
    auto data = CSV_READ_IFS_ALL(ifs, ',', Info, int, std::string, float);
    vecOutput(data);
    ifs.close();
}

void test_CSV_READ_IFS_CER()
{
    INFO("test the macro 'CSV_READ_IFS_CER', file '../data/info.csv'");
    std::ifstream ifs("../data/info.csv");
    auto data = CSV_READ_IFS_CER(ifs, ',', 4, Info, int, std::string, float);
    vecOutput(data);
    ifs.close();
}

int main(int argc, char const *argv[])
{
    ::test_CSV_READ_IFS_ALL();
    ::test_CSV_READ_IFS_CER();
    return 0;
}
