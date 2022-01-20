# CSV Handler [MACRO LIB]

>__Author : csl__    
>__E-Mail : 3079625093@qq.com__

## OverView
This is a library implemented with C + + macros to read and write CSV files. It is simple and universal.


## Macroes 
+ ___CSVReader[IFS]___

+ ___CSVReader[FILE]___

+ ___CSV_READ_FILE(fileName, splitor, itemType, ...)___

+ ___CSV_READ_FILE_H(fileName, splitor, itemType, ...)___

+ ___CSV_READ_IFS_ALL(ifstream, splitor, itemType, ...)___

+ ___CSV_READ_IFS_ALL_H(ifstream, splitor, itemType, ...)___

+ ___CSV_READ_IFS_CER(ifstream, splitor, itemNum, itemType, ...)___

+ ___CSV_READ_IFS_CER_H(ifstream, splitor, itemNum, itemType, ...)___

+ ___CSVWriter[OFS]___

+ ___CSVWriter[FILE]___

+ ___CSV_HEADER(...)___

+ ___CSV_WRITE_OFS(ofstream, data, splitor, itemType, ...)___

+ ___CSV_WRITE_OFS_H(ofstream, header, data, splitor, itemType, ...)___

+ ___CSV_WRITE_FILE(fileName, data, splitor, itemType, ...)___

+ ___CSV_WRITE_FILE_H(fileName, header, data, splitor, itemType, ...)___

## Examples
+ ___CSVReader[IFS]___
```cpp
    std::ifstream ifs("../data/info.csv");
    ns_csv::CSVReader readerIFS(ifs);

    while (readerIFS.hasNext())
    {
        auto items = readerIFS.next();
        Info obj(std::stoi(items.at(0)), items.at(1), std::stof(items.at(2)));
        std::cout << obj << std::endl;
    }

    ifs.close();
```

+ ___CSVReader[FILE]___
```cpp
    ns_log::process << "using 'CSVReader[fileName]' to read items in the file 'info.csv'" << ns_log::endl;

    ns_csv::CSVReader reader("../data/info.csv");

    while (reader.hasNext())
    {
        auto items = reader.next();
        Info obj(std::stoi(items.at(0)), items.at(1), std::stof(items.at(2)));
        std::cout << obj << std::endl;
    }
        ns_log::process << "using 'CSVReader[ifstream]' to read items in the file 'info.csv'" << ns_log::endl;

```

+ ___CSV_READ_FILE(fileName, splitor, itemType, ...)___
```cpp
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

    void csv_read_file()
    {
        /**
         * @brief use macro 'CSV_READ_FILE' to read all items in the file
         */
        ns_log::process << "use macro 'CSV_READ_FILE' to read all items in the file" << ns_log::endl;

        auto info = CSV_READ_FILE("../data/info.csv", ',', Info, uint, std::string, float);

        for (const auto &elem : info)
            std::cout << elem << std::endl;
    }

```

+ ___CSV_READ_FILE_H(fileName, splitor, itemType, ...)___
```cpp
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

    void csv_read_file_h()
    {
        /**
         * @brief use macro 'CSV_READ_FILE_H' to read all items in the file
         */
        ns_log::process << "use macro 'CSV_READ_FILE_H' to read all items from file 'refpoint3f.csv'" << ns_log::endl;

        auto rps = CSV_READ_FILE_H("../data/refpoint3f.csv", ',', ns_geo::RefPoint3f, uint, float, float, float);

        std::cout << "header : ";
        for (const auto &label : rps.first)
            ns_log::info << label << ' ';
        std::cout << std::endl;

        for (const auto &elem : rps.second)
            std::cout << elem << std::endl;
    }
```

+ ___CSV_READ_IFS_ALL(ifstream, splitor, itemType, ...)___
```cpp
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


    /**
     * @brief use macro 'CSV_READ_IFS_ALL' to read all rest items
     */
    ns_log::process << "use macro 'CSV_READ_IFS_ALL' to read all rest items from file 'info.csv'" << ns_log::endl;

    auto rps2 = CSV_READ_IFS_ALL(ifs, ',', Info, uint, std::string, float);

    for (const auto &elem : rps2)
        std::cout << elem << std::endl;

    ifs.close();
```

+ ___CSV_READ_IFS_ALL_H(ifstream, splitor, itemType, ...)___
```cpp
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
    
    ns_log::process << "use macro 'CSV_READ_IFS_ALL_H' to read all rest items from file 'refpoint3f.csv'" << ns_log::endl;

    std::ifstream ifs1("../data/refpoint3f.csv", std::ios::in);
    auto rps_1 = CSV_READ_IFS_ALL_H(ifs1, ',', ns_geo::RefPoint3f, uint, float, float, float);

    std::cout << "header : ";
    for (const auto &label : rps_1.first)
        ns_log::info << label << ' ';
    std::cout << std::endl;

    for (const auto &elem : rps_1.second)
        std::cout << elem << std::endl;

    ifs1.close();
```

+ ___CSV_READ_IFS_CER(ifstream, splitor, itemNum, itemType, ...)___
```cpp
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
    
    /**
     * @brief use macro 'CSV_READ_IFS_CER' to read certain items
     */
    ns_log::process << "use macro 'CSV_READ_IFS_CER' to read certain items from file 'info.csv'" << ns_log::endl;

    std::ifstream ifs("../data/info.csv");
    auto rps1 = CSV_READ_IFS_CER(ifs, ',', 5, Info, uint, std::string, float);

    for (const auto &elem : rps1)
        std::cout << elem << std::endl;

```

+ ___CSV_READ_IFS_CER_H(ifstream, splitor, itemNum, itemType, ...)___
```cpp
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
    
    ns_log::process << "use macro 'CSV_READ_IFS_CER_H' to read all rest items from file 'refpoint3f.csv'" << ns_log::endl;

    std::ifstream ifs2("../data/refpoint3f.csv", std::ios::in);
    auto rps_2 = CSV_READ_IFS_CER_H(ifs2, ',', 4, ns_geo::RefPoint3f, uint, float, float, float);

    std::cout << "header : ";
    for (const auto &label : rps_2.first)
        ns_log::info << label << ' ';
    std::cout << std::endl;

    for (const auto &elem : rps_2.second)
        std::cout << elem << std::endl;

    ifs2.close();
```

+ ___CSVWriter[OFS]___
```cpp
    ns_log::process << "using 'CSVWriter[ofstream]' to write items to the file 'point3f.csv'" << ns_log::endl;
    
    std::ofstream ofs("../data/point3f.csv");
    ns_csv::CSVWriter writerOFS(ofs);
    
    for (const auto &p : ps)
        writerOFS.writeItems(',', p.x(), p.y(), p.z());

    ofs.close();
```

+ ___CSVWriter[FILE]___
```cpp
    ns_log::process << "using 'CSVWriter[fileName]' to write items to the file 'point3f.csv'" << ns_log::endl;
    
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    ns_csv::CSVWriter writer("../data/point3f.csv");
    
    for (const auto &p : ps)
        writer.writeItems(',', p.x(), p.y(), p.z());
```

+ ___CSV_HEADER(...)___
```cpp
    /**
     * @brief generate the array of csv header
     * @param ... the header strings
     */
    
    CSV_HEADER("x", "y", "z")
    std::array<std::string, 3>{"x", "y", "z"}
```

+ ___CSV_WRITE_OFS(ofstream, data, splitor, itemType, ...)___
```cpp
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
    
    void csv_write_ofs()
    {
        /**
         * @brief use macro 'CSV_WRITE_OFS' to write items
         */
        ns_log::process << "use macro 'CSV_WRITE_OFS' to write items to file 'point3f.csv'" << ns_log::endl;

        /**
         * @brief gen random point2f set
         */
        auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
        std::ofstream ofs("../data/point3f.csv");

        CSV_WRITE_OFS(ofs, ps, ',', ns_geo::Point3f, x(), y(), z());

        ofs.close();
    }
```

+ ___CSV_WRITE_OFS_H(ofstream, header, data, splitor, itemType, ...)___
```cpp
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
    
    void csv_write_ofs_h()
    {
        /**
         * @brief use macro 'CSV_WRITE_OFS' to write items
         */
        ns_log::process << "use macro 'CSV_WRITE_OFS_H' to write header and items to file 'point3f_h.csv'" << ns_log::endl;

        std::ofstream ofs("../data/point3f_h.csv");
        /**
         * @brief gen random point2f set
         */
        auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

        CSV_WRITE_OFS_H(ofs, CSV_HEADER("x", "y", "z"), ps, ',', ns_geo::Point3f, x(), y(), z());

        ofs.close();
    }
```

+ ___CSV_WRITE_FILE(fileName, data, splitor, itemType, ...)___
```cpp
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
    

    void csv_write_file()
    {
        /**
         * @brief use macro 'CSV_WRITE_FILE' to write items
         */
        ns_log::process << "use macro 'CSV_WRITE_FILE' to write items to file 'point3f.csv'" << ns_log::endl;

        /**
         * @brief gen random point2f set
         */
        auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

        CSV_WRITE_FILE("../data/point3f.csv", ps, ',', ns_geo::Point3f, x(), y(), z());
    }
```

+ ___CSV_WRITE_FILE_H(fileName, header, data, splitor, itemType, ...)___
```cpp
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
    
    void csv_write_file_h()
    {
        /**
         * @brief use macro 'CSV_WRITE_FILE' to write items
         */
        ns_log::process << "use macro 'CSV_WRITE_FILE_H' to write herader and items to file 'point3f_h.csv'" << ns_log::endl;

        /**
         * @brief gen random point2f set
         */
        auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
        CSV_WRITE_FILE_H("../data/point3f_h.csv", CSV_HEADER("x", "y", "z"), ps, ',', ns_geo::Point3f, x(), y(), z());
    }
```