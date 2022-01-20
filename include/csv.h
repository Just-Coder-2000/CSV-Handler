#pragma once
/**
 * @file csvhandler.h
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <array>

/**
 * @brief methods you can use:
 * 
 * @attention for csv reading
 * [1.1] CSV_READ_FILE(fileName, splitor, itemType, ...)
 * [1.2] CSV_READ_FILE_H(fileName, splitor, itemType, ...)
 * 
 * [2.1] CSV_READ_IFS_ALL(ifstream, splitor, itemType, ...)
 * [2.2] CSV_READ_IFS_ALL_H(ifstream, splitor, itemType, ...)
 * 
 * [3.1] CSV_READ_IFS_CER(ifstream, splitor, itemNum, itemType, ...)
 * [3.2] CSV_READ_IFS_CER_H(ifstream, splitor, itemNum, itemType, ...)
 * 
 * [4.1] CSVReader[IFS]
 * [4.2] CSVReader[FILE]
 * 
 * @attention for csv writing
 * [1.1] CSV_WRITE_OFS(ofstream, data, splitor, itemType, ...)
 * [1.2] CSV_WRITE_OFS_H(ofstream, header, data, splitor, itemType, ...)
 * 
 * [2.1] CSV_WRITE_FILE(fileName, data, splitor, itemType, ...)
 * [2.2] CSV_WRITE_FILE_H(fileName, header, data, splitor, itemType, ...)
 * 
 * [3.1] CSVWriter[OFS]
 * [3.2] CSVWriter[FILE]
 * 
 * @attention helpers:
 * [1] CSV_HEADER(...)
 */

namespace ns_csv
{

#pragma region macro apis
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
#define CSV_READ_FILE(fileName, splitor, itemType, ...) \
    ns_csv::CSVHandler::read<                           \
        itemType,                                       \
        UNPACK_FUN_TYPE(itemType, __VA_ARGS__),         \
        __VA_ARGS__>(fileName, GEN_UNPACK_FUN(itemType, __VA_ARGS__), splitor)

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
#define CSV_READ_FILE_H(fileName, splitor, itemType, ...) \
    ns_csv::CSVHandler::read<                             \
        itemType, COUNT_MACRO_VAR_ARGS(__VA_ARGS__),      \
        UNPACK_FUN_TYPE(itemType, __VA_ARGS__),           \
        __VA_ARGS__>(fileName, GEN_UNPACK_FUN(itemType, __VA_ARGS__), splitor)

    /**
     * @brief read all items in the ifstream
     * 
     * @param ifstream the input fstream
     * @param splitor the splitor
     * @param itemType the type of the item in the csv file
     * @param ... the types of the members,
     *             it's order is same as the declaration sequence of member variables.
     * 
     * @return std::vector<itemType> data
     */
#define CSV_READ_IFS_ALL(ifstream, splitor, itemType, ...) \
    ns_csv::CSVHandler::read<                              \
        itemType,                                          \
        UNPACK_FUN_TYPE(itemType, __VA_ARGS__),            \
        __VA_ARGS__>(ifstream, GEN_UNPACK_FUN(itemType, __VA_ARGS__), splitor)

    /**
     * @brief read all items in the ifstream
     * 
     * @param ifstream the input fstream
     * @param splitor the splitor
     * @param itemType the type of the item in the csv file
     * @param ... the types of the members,
     *             it's order is same as the declaration sequence of member variables.
     * 
     * @return std::pair(std::array<std::string, LabNum>, std::vector<itemType>) {header, data}
     */
#define CSV_READ_IFS_ALL_H(ifstream, splitor, itemType, ...) \
    ns_csv::CSVHandler::read<                                \
        itemType, COUNT_MACRO_VAR_ARGS(__VA_ARGS__),         \
        UNPACK_FUN_TYPE(itemType, __VA_ARGS__),              \
        __VA_ARGS__>(ifstream, GEN_UNPACK_FUN(itemType, __VA_ARGS__), splitor)

    /**
     * @brief read all items in the ifstream
     * 
     * @param ifstream the input fstream
     * @param splitor the splitor
     * @param itemType the type of the item in the csv file
     * @param itemNum the number of the items to read
     * @param ... the types of the members,
     *             it's order is same as the declaration sequence of member variables.
     * 
     * @return std::vector<itemType> data
     */
#define CSV_READ_IFS_CER(ifstream, splitor, itemNum, itemType, ...) \
    ns_csv::CSVHandler::read<                                       \
        itemType,                                                   \
        UNPACK_FUN_TYPE(itemType, __VA_ARGS__),                     \
        __VA_ARGS__>(ifstream, GEN_UNPACK_FUN(itemType, __VA_ARGS__), splitor, itemNum)

    /**
     * @brief read all items in the ifstream
     * 
     * @param ifstream the input fstream
     * @param splitor the splitor
     * @param itemType the type of the item in the csv file
     * @param itemNum the number of the items to read
     * @param ... the types of the members,
     *             it's order is same as the declaration sequence of member variables.
     * 
     * @return std::pair(std::array<std::string, LabNum>, std::vector<itemType>) {header, data}
     */
#define CSV_READ_IFS_CER_H(ifstream, splitor, itemNum, itemType, ...) \
    ns_csv::CSVHandler::read<                                         \
        itemType, COUNT_MACRO_VAR_ARGS(__VA_ARGS__),                  \
        UNPACK_FUN_TYPE(itemType, __VA_ARGS__),                       \
        __VA_ARGS__>(ifstream, GEN_UNPACK_FUN(itemType, __VA_ARGS__), splitor, itemNum)

    /**
     * @brief write data to a csv file
     * 
     * @param osftream the out fstream
     * @param data the data array
     * @param splitor the splitor
     * @param itemType the type of item
     * @param ... the [methods | member name] to get members from a item
     * 
     * @return void
     */
#define CSV_WRITE_OFS(ofstream, data, splitor, itemType, ...)            \
    ns_csv::CSVHandler::write<itemType,                                  \
                              OUTPUT_FUN_TYPE(itemType)>(ofstream, data, \
                                                         GEN_OUTPUT_FUN(itemType, splitor, __VA_ARGS__))

    /**
     * @brief write data to a csv file
     * 
     * @param osftream the out fstream
     * @param data the data array
     * @param header the header labels
     * @param splitor the splitor
     * @param itemType the type of item
     * @param ... the [methods | member name] to get members from a item
     * 
     * @return void
     */
#define CSV_WRITE_OFS_H(ofstream, header, data, splitor, itemType, ...)                   \
    ns_csv::CSVHandler::write<itemType, COUNT_MACRO_VAR_ARGS(__VA_ARGS__),                \
                              OUTPUT_FUN_TYPE(itemType)>(ofstream, header, data, splitor, \
                                                         GEN_OUTPUT_FUN(itemType, splitor, __VA_ARGS__))

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
#define CSV_WRITE_FILE(fileName, data, splitor, itemType, ...)           \
    ns_csv::CSVHandler::write<itemType,                                  \
                              OUTPUT_FUN_TYPE(itemType)>(fileName, data, \
                                                         GEN_OUTPUT_FUN(itemType, splitor, __VA_ARGS__))

    /**
     * @brief write data to a csv file
     * 
     * @param fileName the file name
     * @param header the header labels
     * @param data the data array
     * @param splitor the splitor
     * @param itemType the type of item
     * @param ... the [methods | member name] to get members from a item
     * 
     * @return void
     */
#define CSV_WRITE_FILE_H(fileName, header, data, splitor, itemType, ...)                  \
    ns_csv::CSVHandler::write<itemType, COUNT_MACRO_VAR_ARGS(__VA_ARGS__),                \
                              OUTPUT_FUN_TYPE(itemType)>(fileName, header, data, splitor, \
                                                         GEN_OUTPUT_FUN(itemType, splitor, __VA_ARGS__))
    /**
     * @brief generate the array of csv header
     * @param ... the header strings
     */
#define CSV_HEADER(...) \
    std::array<std::string, COUNT_MACRO_VAR_ARGS(__VA_ARGS__)> { __VA_ARGS__ }

#pragma endregion

#pragma region macro helpers
    /**
     * @brief define for macro 'MAKE_APIR'
     * 
     */
#define MAKE_PAIR_10(TYPE, ...) std::pair<TYPE, MAKE_PAIR_9(__VA_ARGS__)>
#define MAKE_PAIR_9(TYPE, ...) std::pair<TYPE, MAKE_PAIR_8(__VA_ARGS__)>
#define MAKE_PAIR_8(TYPE, ...) std::pair<TYPE, MAKE_PAIR_7(__VA_ARGS__)>
#define MAKE_PAIR_7(TYPE, ...) std::pair<TYPE, MAKE_PAIR_6(__VA_ARGS__)>
#define MAKE_PAIR_6(TYPE, ...) std::pair<TYPE, MAKE_PAIR_5(__VA_ARGS__)>
#define MAKE_PAIR_5(TYPE, ...) std::pair<TYPE, MAKE_PAIR_4(__VA_ARGS__)>
#define MAKE_PAIR_4(TYPE, ...) std::pair<TYPE, MAKE_PAIR_3(__VA_ARGS__)>
#define MAKE_PAIR_3(TYPE, ...) std::pair<TYPE, MAKE_PAIR_2(__VA_ARGS__)>
#define MAKE_PAIR_2(TYPE1, TYPE2) std::pair<TYPE1, TYPE2>

    /**
     * @brief count the number of the arguements, range[0, 10]
     */
#define MACRO_VAR_ARGS_IMPL_COUNT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define COUNT_MACRO_VAR_ARGS(...) MACRO_VAR_ARGS_IMPL_COUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
    /**
     * @brief combine the macro with the arguements' num
     */
#define MACRO_COMBINE_2(MACRO, ARGS_COUNT) MACRO##ARGS_COUNT
#define MACRO_COMBINE_1(MACRO, ARGS_COUNT) MACRO_COMBINE_2(MACRO, ARGS_COUNT)
#define MACRO_COMBINE(MACRO, ARGS_COUNT) MACRO_COMBINE_1(MACRO, ARGS_COUNT)

#define MAKE_PAIR(...)                                           \
    MACRO_COMBINE(MAKE_PAIR_, COUNT_MACRO_VAR_ARGS(__VA_ARGS__)) \
    (__VA_ARGS__)

    /**
     * @brief define for macro 'CONSTRUCT_PARAMS'
     * 
     */
#define CONSTRUCT_PARAMS(PACK, ...)                                     \
    MACRO_COMBINE(CONSTRUCT_PARAMS_, COUNT_MACRO_VAR_ARGS(__VA_ARGS__)) \
    (PACK)

    /**
     * @brief unpack the pair pack to params list
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
    PACK

    /**
     * @brief define for UNPACK function
     * 
     */
#define GEN_UNPACK_FUN(ITEM_TYPE, ...)                         \
    [](const MAKE_PAIR(__VA_ARGS__) & pack) -> ITEM_TYPE       \
    {                                                          \
        return ITEM_TYPE{CONSTRUCT_PARAMS(pack, __VA_ARGS__)}; \
    }

    /**
     * @brief the type of the unpack function
     */
#define UNPACK_FUN_TYPE(ITEM_TYPE, ...) \
    ITEM_TYPE(*)                        \
    (const MAKE_PAIR(__VA_ARGS__) &)

    /**
     * @brief generate the output list for each item
     */
#define OUTPUT_LIST_10(ELEM, SPLITOR, GET, ...) \
    ELEM.GET << SPLITOR << OUTPUT_LIST_9(ELEM, SPLITOR, __VA_ARGS__)

#define OUTPUT_LIST_9(ELEM, SPLITOR, GET, ...) \
    ELEM.GET << SPLITOR << OUTPUT_LIST_8(ELEM, SPLITOR, __VA_ARGS__)

#define OUTPUT_LIST_8(ELEM, SPLITOR, GET, ...) \
    ELEM.GET << SPLITOR << OUTPUT_LIST_7(ELEM, SPLITOR, __VA_ARGS__)

#define OUTPUT_LIST_7(ELEM, SPLITOR, GET, ...) \
    ELEM.GET << SPLITOR << OUTPUT_LIST_6(ELEM, SPLITOR, __VA_ARGS__)

#define OUTPUT_LIST_6(ELEM, SPLITOR, GET, ...) \
    ELEM.GET << SPLITOR << OUTPUT_LIST_5(ELEM, SPLITOR, __VA_ARGS__)

#define OUTPUT_LIST_5(ELEM, SPLITOR, GET, ...) \
    ELEM.GET << SPLITOR << OUTPUT_LIST_4(ELEM, SPLITOR, __VA_ARGS__)

#define OUTPUT_LIST_4(ELEM, SPLITOR, GET, ...) \
    ELEM.GET << SPLITOR << OUTPUT_LIST_3(ELEM, SPLITOR, __VA_ARGS__)

#define OUTPUT_LIST_3(ELEM, SPLITOR, GET, ...) \
    ELEM.GET << SPLITOR << OUTPUT_LIST_2(ELEM, SPLITOR, __VA_ARGS__)

#define OUTPUT_LIST_2(ELEM, SPLITOR, GET, ...) \
    ELEM.GET << SPLITOR << OUTPUT_LIST_1(ELEM, SPLITOR, __VA_ARGS__)

#define OUTPUT_LIST_1(ELEM, SPLITOR, GET) \
    ELEM.GET << '\n'

#define OUTPUT_LIST(ELEM, SPLITOR, ...)                            \
    MACRO_COMBINE(OUTPUT_LIST_, COUNT_MACRO_VAR_ARGS(__VA_ARGS__)) \
    (ELEM, SPLITOR, __VA_ARGS__)

    /**
     * @brief define for output fun
     * 
     */
#define GEN_OUTPUT_FUN(ITEM_TYPE, SPLITOR, ...)             \
    [](std::ofstream &ofs, const ITEM_TYPE &item) -> void { \
        ofs << OUTPUT_LIST(item, SPLITOR, __VA_ARGS__);     \
        return;                                             \
    }

    /**
     * @brief the type of the output function
     */
#define OUTPUT_FUN_TYPE(ITEM_TYPE) \
    void (*)(std::ofstream &, const ITEM_TYPE &)

    /**
     * @brief for type trans throw std::stringstream
     * 
     */
    static std::stringstream stream;

#define STRTO(STR, VAL) \
    stream << STR;      \
    stream >> VAL;      \
    stream.clear();

#pragma endregion

#pragma region variable template params
    template <typename... Args>
    struct __ElemTypeTrait;

    template <typename First, typename... Rest>
    struct __ElemTypeTrait<First, Rest...>
    {
        /**
         * @brief convert current string to type 'First'
         */
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
        /**
         * @brief convert current string to type 'Last'
         */
        static auto gen(std::vector<std::string>::iterator iter)
        {
            Last val;
            STRTO(*iter, val);
            return val;
        }
    };

#pragma endregion

#pragma region main class

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

    class CSVHandler
    {
    private:
        CSVHandler() = delete;

    public:
        /**
         * @brief for 'CSV_READ_IFS'
         */
        template <typename ItemType, typename UnpackFunType, typename... ElemTypes>
        static std::vector<ItemType> read(std::ifstream &ifs, const UnpackFunType &unpackFun, char splitor, int itemNum = INT32_MAX)
        {
            std::vector<ItemType> data;
            std::string strline;
            int itemCount = 0;
            while (itemCount < itemNum)
            {
                if (std::getline(ifs, strline))
                {
                    auto strVec = split(strline, splitor);
                    auto params = __ElemTypeTrait<ElemTypes...>::gen(strVec.begin());
                    data.push_back(unpackFun(params));
                    ++itemCount;
                }
                else
                    break;
            }
            return data;
        }
        /**
         * @brief for 'CSV_READ_IFS_H'
         */
        template <typename ItemType, std::size_t LabelNum, typename UnpackFunType, typename... ElemTypes>
        static std::pair<std::array<std::string, LabelNum>, std::vector<ItemType>>
        read(std::ifstream &ifs, const UnpackFunType &unpackFun, char splitor, int itemNum = INT32_MAX)
        {
            auto header = ns_csv::CSVHandler::readHeader<LabelNum>(ifs, splitor);
            std::vector<ItemType> data;
            std::string strline;
            int itemCount = 0;
            while (itemCount < itemNum)
            {
                if (std::getline(ifs, strline))
                {
                    auto strVec = split(strline, splitor);
                    auto params = __ElemTypeTrait<ElemTypes...>::gen(strVec.begin());
                    data.push_back(unpackFun(params));
                    ++itemCount;
                }
                else
                    break;
            }
            return {header, data};
        }

        /**
         * @brief for 'CSV_READ_FILE'
         */
        template <typename ItemType, typename UnpackFunType, typename... ElemTypes>
        static std::vector<ItemType> read(const std::string &fileName, const UnpackFunType &unpackFun, char splitor)
        {
            std::ifstream ifs(fileName);
            std::vector<ItemType> data;
            std::string strline;
            while (std::getline(ifs, strline))
            {
                auto strVec = split(strline, splitor);
                auto params = __ElemTypeTrait<ElemTypes...>::gen(strVec.begin());
                data.push_back(unpackFun(params));
            }
            ifs.close();
            return data;
        }
        /**
         * @brief for 'CSV_READ_FILE_H'
         */
        template <typename ItemType, std::size_t LabelNum, typename UnpackFunType, typename... ElemTypes>
        static std::pair<std::array<std::string, LabelNum>, std::vector<ItemType>>
        read(const std::string &fileName, const UnpackFunType &unpackFun, char splitor)
        {
            std::ifstream ifs(fileName);
            auto header = ns_csv::CSVHandler::readHeader<LabelNum>(ifs, splitor);
            std::vector<ItemType> data;
            std::string strline;
            while (std::getline(ifs, strline))
            {
                auto strVec = split(strline, splitor);
                auto params = __ElemTypeTrait<ElemTypes...>::gen(strVec.begin());
                data.push_back(unpackFun(params));
            }
            ifs.close();
            return {header, data};
        }

        /**
         * @brief for 'CSV_WRITE_OFS'
         */
        template <typename ItemType, typename OutputFunType>
        static void write(std::ofstream &ofs, const std::vector<ItemType> &data, const OutputFunType &outputFun)
        {
            for (const auto &elem : data)
                outputFun(ofs, elem);
            return;
        }

        /**
         * @brief for 'CSV_WRITE_OFS_H'
         */
        template <typename ItemType, std::size_t LabelNum, typename OutputFunType>
        static void write(std::ofstream &ofs, const std::array<std::string, LabelNum> &header,
                          const std::vector<ItemType> &data, char splitor, const OutputFunType &outputFun)
        {
            ns_csv::CSVHandler::writeHeader(ofs, header, splitor);
            for (const auto &elem : data)
                outputFun(ofs, elem);
            return;
        }

        /**
         * @brief for 'CSV_WRITE_FILE'
         */
        template <typename ItemType, typename OutputFunType>
        static void write(const std::string &fileName, const std::vector<ItemType> &data, const OutputFunType &outputFun)
        {
            std::ofstream ofs(fileName);
            for (const auto &elem : data)
                outputFun(ofs, elem);
            ofs.close();
            return;
        }

        /**
         * @brief for 'CSV_WRITE_FILE_H'
         */
        template <typename ItemType, std::size_t LabelNum, typename OutputFunType>
        static void write(const std::string &fileName, const std::array<std::string, LabelNum> &header,
                          const std::vector<ItemType> &data, char splitor, const OutputFunType &outputFun)
        {
            std::ofstream ofs(fileName);
            ns_csv::CSVHandler::writeHeader(ofs, header, splitor);
            for (const auto &elem : data)
                outputFun(ofs, elem);
            ofs.close();
            return;
        }

        /**
         * @brief read the header's leabes
         */
        template <std::size_t LabelNum>
        static std::array<std::string, LabelNum> readHeader(std::ifstream &ifs, char splitor)
        {
            std::array<std::string, LabelNum> header;
            std::string str;
            std::getline(ifs, str);
            auto vec = split(str, splitor);
            for (int i = 0; i != LabelNum; ++i)
                header[i] = vec.at(i);
            return header;
        }

        /**
         * @brief write the header's leabes
         */
        template <std::size_t LabelNum>
        static void writeHeader(std::ofstream &ofs, const std::array<std::string, LabelNum> &header, char splitor)
        {
            for (int i = 0; i != LabelNum - 1; ++i)
                ofs << header[i] << splitor;
            ofs << header[LabelNum - 1] << '\n';
            return;
        }
    };

    class CSVReader
    {
    private:
        std::string _curStr;
        std::ifstream *_ifs;
        bool _isNewIFS;

    public:
        CSVReader() = delete;

        CSVReader(const std::string &fileName)
        {
            this->_ifs = new std::ifstream(fileName);
            this->_isNewIFS = true;
        }

        CSVReader(std::ifstream &ifs) : _ifs(&ifs) { this->_isNewIFS = false; }

        CSVReader(const CSVReader &) = delete;

        ~CSVReader()
        {
            if (this->_isNewIFS)
            {
                this->_ifs->close();
                delete this->_ifs;
            }
        }
        /**
         * @brief judge whether there is another item next
         */
        bool hasNext() { return static_cast<bool>(std::getline(*(this->_ifs), this->_curStr)); }

        /**
         * @brief get next std::string vector
         */
        std::vector<std::string> next(char splitor = ',') const { return split(this->_curStr, splitor); }
    };

    class CSVWriter
    {
    private:
        std::ofstream *_ofs;
        bool _isNewOFS;

    public:
        CSVWriter() = delete;

        CSVWriter(const std::string &fileName)
        {
            this->_ofs = new std::ofstream(fileName);
            this->_isNewOFS = true;
        }

        CSVWriter(std::ofstream &ofs) : _ofs(&ofs) { this->_isNewOFS = false; }

        CSVWriter(const CSVWriter &) = delete;

        ~CSVWriter()
        {
            if (this->_isNewOFS)
            {
                this->_ofs->close();
                delete this->_ofs;
            }
        }

        /**
         * @brief use variable template parameters to write any num arguements
         */
        template <typename Type, typename... Else>
        void writeItems(char splitor, const Type &argv, const Else &...argvs)
        {
            *(this->_ofs) << argv << splitor;
            this->writeItems(splitor, argvs...);
            return;
        }

        template <typename Type>
        void writeItems(char splitor, const Type &argv)
        {
            *(this->_ofs) << argv << '\n';
            return;
        }

        void writeItems()
        {
            return;
        }
    };
#pragma endregion
} // namespace ns_csv
