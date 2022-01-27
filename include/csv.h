#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

namespace ns_csv
{
#pragma region csv read

/**
 * @brief read all items in the ifstream
 * 
 * @param ifs the input fstream
 * @param splitor the splitor
 * @param itemType the type of the item in the csv file
 * @param ... the types of the members,
 *             it's order is same as the declaration sequence of member variables.
 * 
 * @return std::vector<itemType> data
 */
#define CSV_READ_IFS_ALL(ifs, splitor, itemType, ...)                   \
    [](std::ifstream &ifs, char spor)                                   \
        -> std::vector<itemType>                                        \
    {                                                                   \
        std::vector<itemType> data;                                     \
        std::string strLine;                                            \
        while (std::getline(ifs, strLine))                              \
        {                                                               \
            auto strVec = ns_csv::ns_priv::split(strLine, spor);        \
            data.push_back(itemType{LAMBDA_PACK(strVec, __VA_ARGS__)}); \
        }                                                               \
        return data;                                                    \
    }(ifs, splitor)

/**
 * @brief read all items in the ifstream
 * 
 * @param ifs the input fstream
 * @param splitor the splitor
 * @param itemType the type of the item in the csv file
 * @param ... the types of the members,
 *             it's order is same as the declaration sequence of member variables.
 * 
 * @return std::pair(std::array<std::string, LabNum>, std::vector<itemType>) {header, data}
 */
#define CSV_READ_IFS_ALL_H(ifs, splitor, itemType, ...)                 \
    [](std::ifstream &ifs, char spor)                                   \
        -> std::pair<ARRAY(__VA_ARGS__), std::vector<itemType>>         \
    {                                                                   \
        std::string strLine;                                            \
        std::getline(ifs, strLine);                                     \
        auto vec = ns_csv::ns_priv::split(strLine, spor);               \
        ARRAY(__VA_ARGS__)                                              \
        header;                                                         \
        for (int i = 0; i != COUNT_MACRO_VAR_ARGS(__VA_ARGS__); ++i)    \
            header.at(i) = vec.at(i);                                   \
        auto data = CSV_READ_IFS_ALL(ifs, spor, itemType, __VA_ARGS__); \
        return {header, data};                                          \
    }(ifs, splitor)

/**
 * @brief read all items in the ifstream
 * 
 * @param ifs the input fstream
 * @param splitor the splitor
 * @param itemNum the number of the items to read
 * @param itemType the type of the item in the csv file
 * @param ... the types of the members,
 *             it's order is same as the declaration sequence of member variables.
 * 
 * @return std::vector<itemType> data
 */
#define CSV_READ_IFS_CER(ifs, splitor, itemNum, itemType, ...)              \
    [](std::ifstream &ifs, char spor)                                       \
        -> std::vector<itemType>                                            \
    {                                                                       \
        std::vector<itemType> data;                                         \
        std::string strLine;                                                \
        int itemCount = 0;                                                  \
        while (itemCount++ < itemNum)                                       \
        {                                                                   \
            if (std::getline(ifs, strLine))                                 \
            {                                                               \
                auto strVec = ns_csv::ns_priv::split(strLine, spor);        \
                data.push_back(itemType{LAMBDA_PACK(strVec, __VA_ARGS__)}); \
            }                                                               \
            else                                                            \
                break;                                                      \
        }                                                                   \
        return data;                                                        \
    }(ifs, splitor)

/**
 * @brief read all items in the ifstream
 * 
 * @param ifs the input fstream
 * @param splitor the splitor
 * @param itemNum the number of the items to read
 * @param itemType the type of the item in the csv file
 * @param ... the types of the members,
 *             it's order is same as the declaration sequence of member variables.
 * 
 * @return std::pair(std::array<std::string, LabNum>, std::vector<itemType>) {header, data}
 */
#define CSV_READ_IFS_CER_H(ifs, splitor, itemNum, itemType, ...)                 \
    [](std::ifstream &ifs, char spor)                                            \
        -> std::pair<ARRAY(__VA_ARGS__), std::vector<itemType>>                  \
    {                                                                            \
        std::string strLine;                                                     \
        std::getline(ifs, strLine);                                              \
        auto vec = ns_csv::ns_priv::split(strLine, spor);                        \
        ARRAY(__VA_ARGS__)                                                       \
        header;                                                                  \
        for (int i = 0; i != COUNT_MACRO_VAR_ARGS(__VA_ARGS__); ++i)             \
            header.at(i) = vec.at(i);                                            \
        auto data = CSV_READ_IFS_CER(ifs, spor, itemNum, itemType, __VA_ARGS__); \
        return {header, data};                                                   \
    }(ifs, splitor)

/**
 * @brief read all items in the ifstream
 * 
 * @param fileName the file name
 * @param splitor the splitor
 * @param itemType the type of the item in the csv file
 * @param ... the types of the members,
 *             it's order is same as the declaration sequence of member variables.
 * 
 * @return std::vector<itemType> data
 */
#define CSV_READ_FILE(fileName, splitor, itemType, ...)            \
    [](const std::string &name, char spor)                         \
        -> std::vector<itemType>                                   \
    {                                                              \
        std::ifstream ifs(name);                                   \
        return CSV_READ_IFS_ALL(ifs, spor, itemType, __VA_ARGS__); \
    }(fileName, splitor)

/**
 * @brief read all items in the ifstream
 * 
 * @param fileName the file name
 * @param splitor the splitor
 * @param itemType the type of the item in the csv file
 * @param ... the types of the members,
 *             it's order is same as the declaration sequence of member variables.
 * 
 * @return std::pair(std::array<std::string, LabNum>, std::vector<itemType>) {header, data}
 */
#define CSV_READ_FILE_H(fileName, splitor, itemType, ...)               \
    [](const std::string &name, char spor)                              \
        -> std::pair<ARRAY(__VA_ARGS__), std::vector<itemType>>         \
    {                                                                   \
        std::ifstream ifs(name);                                        \
        std::string strLine;                                            \
        std::getline(ifs, strLine);                                     \
        auto vec = ns_csv::ns_priv::split(strLine, spor);               \
        ARRAY(__VA_ARGS__)                                              \
        header;                                                         \
        for (int i = 0; i != COUNT_MACRO_VAR_ARGS(__VA_ARGS__); ++i)    \
            header.at(i) = vec.at(i);                                   \
        auto data = CSV_READ_IFS_ALL(ifs, spor, itemType, __VA_ARGS__); \
        return {header, data};                                          \
    }(fileName, splitor)

#pragma endregion

#pragma region csv write

/**
 * @brief write data to a csv file
 * 
 * @param ofs the out fstream
 * @param data the data array
 * @param splitor the splitor
 * @param itemType the type of item
 * @param ... the [methods | member name] to get members from a item
 * 
 * @return void
 */
#define CSV_WRITE_OFS(ofs, data, splitor, itemType, ...)                        \
    [](std::ofstream &ofs, const std::vector<itemType> &d, char spor) -> void { \
        for (const auto &elem : d)                                              \
            ns_csv::ns_priv::__print__(ofs, spor, __VA_ARGS__);                 \
        return;                                                                 \
    }(ofs, data, splitor)

#define CSV_WRITE_OFS_H(ofs, header, data, splitor, itemType, ...)                                            \
    [](std::ofstream &ofs, const ARRAY(__VA_ARGS__) & h, const std::vector<itemType> &d, char spor) -> void { \
        ns_csv::ns_priv::__print__(ofs, spor, h);                                                             \
        for (const auto &elem : d)                                                                            \
            ns_csv::ns_priv::__print__(ofs, spor, __VA_ARGS__);                                               \
        return;                                                                                               \
    }(ofs, header, data, splitor)

/**
 * @brief write data to a csv file
 * 
 * @param fileName the file name
 * @param data the data array
 * @param splitor the splitor
 * @param itemType the type of item
 * @param ... the [methods | member name] to get members from a item
 * 
 * @return void
 */
#define CSV_WRITE_FILE(fileName, data, splitor, itemType, ...)                       \
    [](const std::string &name, const std::vector<itemType> &d, char spor) -> void { \
        std::ofstream ofs(name);                                                     \
        for (const auto &elem : d)                                                   \
            ns_csv::ns_priv::__print__(ofs, spor, __VA_ARGS__);                      \
        ofs.close();                                                                 \
        return;                                                                      \
    }(fileName, data, splitor)

#define CSV_WRITE_FILE_H(fileName, header, data, splitor, itemType, ...)                                           \
    [](const std::string &name, const ARRAY(__VA_ARGS__) & h, const std::vector<itemType> &d, char spor) -> void { \
        std::ofstream ofs(name);                                                                                   \
        ns_csv::ns_priv::__print__(ofs, spor, h);                                                                  \
        for (const auto &elem : d)                                                                                 \
            ns_csv::ns_priv::__print__(ofs, spor, __VA_ARGS__);                                                    \
        ofs.close();                                                                                               \
        return;                                                                                                    \
    }(fileName, header, data, splitor)

#pragma endregion

    namespace ns_priv
    {

        /**
         * \brief a function to split a string to some string elements according the splitor
         * \param str the string to be splited
         * \param splitor the splitor char
         * \param ignoreEmpty whether ignoring the empty string element or not
         * \return the splited string vector
         */
        std::vector<std::string> split(const std::string &str, char splitor, bool ignoreEmpty = true)
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

        static std::stringstream strStream;

        template <std::size_t Size>
        void __print__(std::ofstream &ofs, char splitor, const std::array<std::string, Size> &header)
        {
            for (int i = 0; i != Size - 1; ++i)
                ofs << header.at(i) << splitor;
            ofs << header.at(Size - 1) << '\n';
        }

        template <typename ArgvType>
        void __print__(std::ofstream &ofs, char splitor, const ArgvType &argv)
        {
            ofs << argv << '\n';
            return;
        }

        template <typename ArgvType, typename... ArgvsType>
        void __print__(std::ofstream &ofs, char splitor, const ArgvType &argv, const ArgvsType &...argvs)
        {
            ofs << argv << splitor;
            return __print__(ofs, splitor, argvs...);
        }

    } // namespace ns_priv

#pragma region help macroes

#define MACRO_VAR_ARGS_IMPL_COUNT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define COUNT_MACRO_VAR_ARGS(...) MACRO_VAR_ARGS_IMPL_COUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define MACRO_COMBINE_2(MACRO, ARGS_COUNT) MACRO##ARGS_COUNT
#define MACRO_COMBINE_1(MACRO, ARGS_COUNT) MACRO_COMBINE_2(MACRO, ARGS_COUNT)
#define MACRO_COMBINE(MACRO, ARGS_COUNT) MACRO_COMBINE_1(MACRO, ARGS_COUNT)

#define ARRAY(...) std::array<std::string, COUNT_MACRO_VAR_ARGS(__VA_ARGS__)>

#define ELEM_ON(method) elem.method

#define HEADER(...) \
    ARRAY(__VA_ARGS__) { __VA_ARGS__ }

#pragma endregion

#pragma region read macroes

#define STR_TRANS(strStream, str, val) \
    strStream << str;                  \
    strStream >> val;                  \
    strStream.clear();

#define LAMBDA_TRANS(srcStr, dstType)                                     \
    [](std::stringstream &strStream, const std::string &str) -> dstType { \
        dstType val;                                                      \
        STR_TRANS(strStream, str, val);                                   \
        return val;                                                       \
    }(ns_csv::ns_priv::strStream, srcStr)

#define LAMBDA_PACK(strVec, ...)                                   \
    MACRO_COMBINE(LAMBDA_PACK_, COUNT_MACRO_VAR_ARGS(__VA_ARGS__)) \
    (strVec, __VA_ARGS__)

#define LAMBDA_PACK_10(strVec, dstType, ...) LAMBDA_TRANS(strVec.at(strVec.size() - 10), dstType), LAMBDA_PACK_9(strVec, __VA_ARGS__)
#define LAMBDA_PACK_9(strVec, dstType, ...) LAMBDA_TRANS(strVec.at(strVec.size() - 9), dstType), LAMBDA_PACK_8(strVec, __VA_ARGS__)
#define LAMBDA_PACK_8(strVec, dstType, ...) LAMBDA_TRANS(strVec.at(strVec.size() - 8), dstType), LAMBDA_PACK_7(strVec, __VA_ARGS__)
#define LAMBDA_PACK_7(strVec, dstType, ...) LAMBDA_TRANS(strVec.at(strVec.size() - 7), dstType), LAMBDA_PACK_6(strVec, __VA_ARGS__)
#define LAMBDA_PACK_6(strVec, dstType, ...) LAMBDA_TRANS(strVec.at(strVec.size() - 6), dstType), LAMBDA_PACK_5(strVec, __VA_ARGS__)
#define LAMBDA_PACK_5(strVec, dstType, ...) LAMBDA_TRANS(strVec.at(strVec.size() - 5), dstType), LAMBDA_PACK_4(strVec, __VA_ARGS__)
#define LAMBDA_PACK_4(strVec, dstType, ...) LAMBDA_TRANS(strVec.at(strVec.size() - 4), dstType), LAMBDA_PACK_3(strVec, __VA_ARGS__)
#define LAMBDA_PACK_3(strVec, dstType, ...) LAMBDA_TRANS(strVec.at(strVec.size() - 3), dstType), LAMBDA_PACK_2(strVec, __VA_ARGS__)
#define LAMBDA_PACK_2(strVec, dstType, ...) LAMBDA_TRANS(strVec.at(strVec.size() - 2), dstType), LAMBDA_PACK_1(strVec, __VA_ARGS__)
#define LAMBDA_PACK_1(strVec, dstType) LAMBDA_TRANS(strVec.at(strVec.size() - 1), dstType)

#pragma endregion

} // namespace ns_csv
