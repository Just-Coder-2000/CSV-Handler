#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

namespace ns_csv
{

    /**
     * @attention change the value of  macro 'STRUCT_MEMBER_NUM' before make the program
     * @param VAL the number of structure member variables
     * for example :
     * struct{ uint _m1; float _m2; float _m3; std::string _m4; },
     * setthe macro 'STRUCT_MEMBER_NUM' 4
     */

#define STRUCT_MEMBER_NUM 4

    /**
     * @attention
     */

#define CONSTRUCT_PARAMS_10(PACK) \
    PACK.first, CONSTRUCT_PARAMS_9(PACK.second)

#define CONSTRUCT_PARAMS_9(PACK) \
    PACK.first, CONSTRUCT_PARAMS_8(PACK.second)

#define CONSTRUCT_PARAMS_8(PACK) \
    PACK.first, CONSTRUCT_PARAMS_7(PACK.second)

#define CONSTRUCT_PARAMS_7(PACK) \
    PACK.first, CONSTRUCT_PARAMS_6(PACK.second)

#define CONSTRUCT_PARAMS_6(PACK) \
    PACK.first, CONSTRUCT_PARAMS_5(PACK.second)

#define CONSTRUCT_PARAMS_5(PACK) \
    PACK.first, CONSTRUCT_PARAMS_4(PACK.second)

#define CONSTRUCT_PARAMS_4(PACK) \
    PACK.first, CONSTRUCT_PARAMS_3(PACK.second)

#define CONSTRUCT_PARAMS_3(PACK) \
    PACK.first, CONSTRUCT_PARAMS_2(PACK.second)

#define CONSTRUCT_PARAMS_2(PACK) \
    PACK.first, CONSTRUCT_PARAMS_1(PACK.second)

#define CONSTRUCT_PARAMS_1(PACK) \
    PACK.first, PACK.second

#define CONSTRUCT_PARAMS_0(PACK) \
    PACK

    static std::stringstream stream;

#define STRTO(STR, VAL) \
    stream << STR;      \
    stream >> VAL;      \
    stream.clear();

    template <typename... Args>
    struct __ElemTypeTrait;

    template <typename First, typename... Rest>
    struct __ElemTypeTrait<First, Rest...>
    {
        static auto gen(std::vector<std::string>::iterator iter)
        {
            First val;
            STRTO(*iter, val);
            return std::make_pair(val, __ElemTypeTrait<Rest...>::gen(++iter));
        }
    };

    template <typename Last>
    struct __ElemTypeTrait<Last>
    {
        static auto gen(std::vector<std::string>::iterator iter)
        {
            Last val;
            STRTO(*iter, val);
            return val;
        }
    };

    class CSVHandler
    {
    public:
        CSVHandler() = delete;

    public:
        template <typename ItemType, typename... ElemTypes>
        static std::vector<ItemType> read(std::ifstream &ifs, char splitor = ',', int itemNum = INT32_MAX)
        {
            std::vector<ItemType> data;
            std::string strline;
            int itemCount = 0;
            while (std::getline(ifs, strline) && itemCount < itemNum)
            {
                auto strVec = CSVHandler::split(strline, splitor);
                auto params = __ElemTypeTrait<ElemTypes...>::gen(strVec.begin());

#if STRUCT_MEMBER_NUM == 1
                data.push_back(ItemType(CONSTRUCT_PARAMS_0(params)));
#elif STRUCT_MEMBER_NUM == 2
                data.push_back(ItemType(CONSTRUCT_PARAMS_1(params)));
#elif STRUCT_MEMBER_NUM == 3
                data.push_back(ItemType(CONSTRUCT_PARAMS_2(params)));
#elif STRUCT_MEMBER_NUM == 4
                data.push_back(ItemType(CONSTRUCT_PARAMS_3(params)));
#elif STRUCT_MEMBER_NUM == 5
                data.push_back(ItemType(CONSTRUCT_PARAMS_4(params)));
#elif STRUCT_MEMBER_NUM == 6
                data.push_back(ItemType(CONSTRUCT_PARAMS_5(params)));
#elif STRUCT_MEMBER_NUM == 7
                data.push_back(ItemType(CONSTRUCT_PARAMS_6(params)));
#elif STRUCT_MEMBER_NUM == 8
                data.push_back(ItemType(CONSTRUCT_PARAMS_7(params)));
#elif STRUCT_MEMBER_NUM == 9
                data.push_back(ItemType(CONSTRUCT_PARAMS_8(params)));
#elif STRUCT_MEMBER_NUM == 10
                data.push_back(ItemType(CONSTRUCT_PARAMS_9(params)));
#endif
                ++itemCount;
            }

            return data;
        }

    private:
        /**
         * \brief a function to split a string to some string elements according the splitor
         * \param str the string to be splited
         * \param splitor the splitor char
         * \param ignoreEmpty whether ignoring the empty string element or not
         * \return the splited string vector
         */
        static std::vector<std::string> split(const std::string &str, char splitor, bool ignoreEmpty = true)
        {
            std::vector<std::string> vec;
            auto iter = str.cbegin();
            while (true)
            {
                auto pos = std::find(iter, str.cend(), splitor);
                auto elem = std::string(iter, pos);
                if ((!ignoreEmpty) || (ignoreEmpty && !elem.empty()))
                    vec.push_back(elem);
                if (pos == str.cend())
                    break;
                iter = ++pos;
            }
            return vec;
        }
    };
} // namespace ns_csv
