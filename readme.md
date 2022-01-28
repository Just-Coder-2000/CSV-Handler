# CSV Handler [MACRO LIB]

>___Author : csl___    

>___E-Mail : 3079625093@qq.com___

## OverView
This is a library implemented with cpp macros to read and write CSV files. It is simple and universal.
```txt
                        ____ ______     __  _   _                 _ _           
                        / ___/ ___\ \   / / | | | | __ _ _ __   __| | | ___ _ __ 
                        | |   \___ \\ \ / /  | |_| |/ _` | '_ \ / _` | |/ _ \ '__|
                        | |___ ___) |\ V /   |  _  | (_| | | | | (_| | |  __/ |   
                        \____|____/  \_/    |_| |_|\__,_|_| |_|\__,_|_|\___|_|   
```

## Macroes 

+ ___CSVReader[IFS]___

```cpp
void test_CSVReader_IFS()
{
    INFO("test the ns_csv::CSVReader[IFS], file '../data/info.csv'");

    std::ifstream ifs("../data/info.csv");
    ns_csv::CSVReader readerIFS(ifs);

    while (readerIFS.hasNext())
    {
        auto items = readerIFS.next();
        Info obj(std::stoi(items.at(0)), items.at(1), std::stof(items.at(2)));
        std::cout << obj << std::endl;
    }
    ifs.close();
}
```

+ ___CSVReader[FILE]___

```cpp
void test_CSVReader_FILE()
{
    INFO("test the ns_csv::CSVReader[FILE], file '../data/info.csv'");

    ns_csv::CSVReader reader("../data/info.csv");
    while (reader.hasNext())
    {
        auto items = reader.next();
        Info obj(std::stoi(items.at(0)), items.at(1), std::stof(items.at(2)));
        std::cout << obj << std::endl;
    }
}
```

+ ___CSV_READ_FILE(fileName, splitor, itemType, ...)___

|param|describe|
|---|---|
|fileName|the file name|
|splitor|the splitor|
|itemType|the type of the item in the csv file|
|...|the types of the members, it's order is same as the declaration sequence of member variables.|
|return|std::vector<itemType> data|

```cpp
void test_CSV_READ_FILE()
{
    INFO("test the macro 'CSV_READ_FILE', file '../data/info.csv'");
    auto data = CSV_READ_FILE("../data/info.csv", ',', Info, int, std::string, float);
    vecOutput(data);
}
```

+ ___CSV_READ_FILE_H(fileName, splitor, itemType, ...)___

|param|describe|
|---|---|
|fileName|the file name|
|splitor|the splitor|
|itemType|the type of the item in the csv file|
|...|the types of the members, it's order is same as the declaration sequence of member variables.|
|return|std::pair(std::array<std::string, LabNum>, std::vector<itemType>) {header, data}|

```cpp
void test_CSV_READ_FILE_H()
{
    INFO("test the macro 'CSV_READ_FILE_H', file '../data/refpoint3f.csv'");
    auto data = CSV_READ_FILE_H("../data/refpoint3f.csv", ',', ns_geo::RefPoint3f, uint, float, float, float);
    INFO("header: ", data.first.at(0), ',', data.first.at(1), ',', data.first.at(2), ',', data.first.at(3));
    vecOutput(data.second);
}
```

+ ___CSV_READ_IFS_ALL(ifs, splitor, itemType, ...)___

|param|describe|
|---|---|
|ifs|the input fstream|
|splitor|the splitor|
|itemType|the type of the item in the csv file|
|...|the types of the members, it's order is same as the declaration sequence of member variables.|
|return|std::vector<itemType> data|

```cpp
void test_CSV_READ_IFS_ALL()
{
    INFO("test the macro 'CSV_READ_IFS_ALL', file '../data/info.csv'");
    std::ifstream ifs("../data/info.csv");
    auto data = CSV_READ_IFS_ALL(ifs, ',', Info, int, std::string, float);
    vecOutput(data);
    ifs.close();
}
```

+ ___CSV_READ_IFS_ALL_H(ifs, splitor, itemType, ...)___

|param|describe|
|---|---|
|ifs|the input fstream|
|splitor|the splitor|
|itemType|the type of the item in the csv file|
|...|the types of the members, it's order is same as the declaration sequence of member variables.|
|return|std::pair(std::array<std::string, LabNum>, std::vector<itemType>) {header, data}|

```cpp
void test_CSV_READ_IFS_ALL_H()
{
    INFO("test the macro 'CSV_READ_IFS_ALL_H', file '../data/refpoint3f.csv'");
    std::ifstream ifs("../data/refpoint3f.csv");
    auto data = CSV_READ_IFS_ALL_H(ifs, ',', ns_geo::RefPoint3f, uint, float, float, float);
    INFO("header: ", data.first.at(0), ',', data.first.at(1), ',', data.first.at(2), ',', data.first.at(3));
    vecOutput(data.second);
    ifs.close();
}
```

+ ___CSV_READ_IFS_CER(ifs, splitor, itemNum, itemType, ...)___

|param|describe|
|---|---|
|ifs|the input fstream|
|splitor|the splitor|
|itemNum|the number of the items to read|
|itemType|the type of the item in the csv file|
|...|the types of the members, it's order is same as the declaration sequence of member variables.|
|return|std::vector<itemType> data|

```cpp
void test_CSV_READ_IFS_CER()
{
    INFO("test the macro 'CSV_READ_IFS_CER', file '../data/info.csv'");
    std::ifstream ifs("../data/info.csv");
    auto data = CSV_READ_IFS_CER(ifs, ',', 4, Info, int, std::string, float);
    vecOutput(data);
    ifs.close();
}
```

+ ___CSV_READ_IFS_CER_H(ifs, splitor, itemNum, itemType, ...)___

|param|describe|
|---|---|
|ifs|the input fstream|
|splitor|the splitor|
|itemNum|the number of the items to read|
|itemType|the type of the item in the csv file|
|...|the types of the members, it's order is same as the declaration sequence of member variables.|
|return|std::pair(std::array<std::string, LabNum>, std::vector<itemType>) {header, data}|

```cpp
void test_CSV_READ_IFS_CER_H()
{
    INFO("test the macro 'CSV_READ_IFS_CER_H', file '../data/refpoint3f.csv'");
    std::ifstream ifs("../data/refpoint3f.csv");
    auto data = CSV_READ_IFS_CER_H(ifs, ',', 4, ns_geo::RefPoint3f, uint, float, float, float);
    INFO("header: ", data.first.at(0), ',', data.first.at(1), ',', data.first.at(2), ',', data.first.at(3));
    vecOutput(data.second);
    ifs.close();
}
```

+ ___CSVWriter[OFS]___

```cpp
void test_CSVWriter_OFS()
{
    INFO("test the ns_csv::CSVWriter[OFS], file '../data/info.csv'");

    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

    std::ofstream ofs("../data/point3f.csv");
    ns_csv::CSVWriter writer(ofs);

    writer.writeItems(',', "x+z", "x+y", "y-z", "z-y");

    for (const auto &p : ps)
        writer.writeItems(',', p.x(), p.y(), p.z());

    ofs.close();
}
```

+ ___CSVWriter[FILE]___

```cpp
void test_CSVWriter_FILE()
{
    INFO("test the ns_csv::CSVWriter[FILE], file '../data/info.csv'");

    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    ns_csv::CSVWriter writer("../data/point3f.csv");

    writer.writeItems(',', "x+z", "x+y", "y-z", "z-y");

    for (const auto &p : ps)
        writer.writeItems(',', p.x(), p.y(), p.z());
}
```

+ ___CSV_HEADER(...)___

```cpp
#define CSV_HEADER(...) \
    ARRAY(__VA_ARGS__) { __VA_ARGS__ }
```

+ ___CSV_ELEM(methods)___

```cpp
#define CSV_ELEM(method) elem.method
```

+ ___CSV_WRITE_OFS(ofs, data, splitor, itemType, ...)___

|param|describe|
|---|---|
|ofs|the output fstream|
|data|the data vector|
|splitor|the splitor|
|...|the [methods | member name] to get members from a item|
|return|void|

```cpp
void test_CSV_WRITE_OFS()
{
    INFO("test the macro 'CSV_WRITE_OFS', file '../data/point3f.csv'");
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    std::ofstream ofs("../data/point3f.csv");
    CSV_WRITE_OFS(ofs, ps, ',',
                  CSV_ELEM(x()) * CSV_ELEM(z()),
                  CSV_ELEM(x()) + CSV_ELEM(y()),
                  CSV_ELEM(y()) - CSV_ELEM(z()),
                  CSV_ELEM(z()) * CSV_ELEM(y()));
    ofs.close();
}
```

+ ___CSV_WRITE_OFS_H(ofs, header, data, splitor, itemType, ...)___

|param|describe|
|---|---|
|ofs|the output fstream|
|header|the header labels|
|data|the data vector|
|splitor|the splitor|
|...|the [methods | member name] to get members from a item|
|return|void|

```cpp
void test_CSV_WRITE_OFS_H()
{
    INFO("test the macro 'CSV_WRITE_OFS_H', file '../data/point3f.csv'");
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    std::ofstream ofs("../data/point3f.csv");
    CSV_WRITE_OFS_H(ofs, CSV_HEADER("x+z", "x+y", "y-z", "z-y"), ps, ',',
                    CSV_ELEM(x()) * CSV_ELEM(z()),
                    CSV_ELEM(x()) + CSV_ELEM(y()),
                    CSV_ELEM(y()) - CSV_ELEM(z()),
                    CSV_ELEM(z()) * CSV_ELEM(y()));
    auto header = CSV_HEADER("x+z", "x+y", "y-z", "z-y");
    ofs.close();
}
```

+ ___CSV_WRITE_FILE(fileName, data, splitor, itemType, ...)___

|param|describe|
|---|---|
|fileName|the file name|
|data|the data vector|
|splitor|the splitor|
|...|the [methods | member name] to get members from a item|
|return|void|

```cpp
void test_CSV_WRITE_FILE()
{
    INFO("test the macro 'CSV_WRITE_FILE', file '../data/point3f.csv'");
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    CSV_WRITE_FILE("../data/point3f.csv", ps, ',', 
                   CSV_ELEM(x()) * CSV_ELEM(z()),
                   CSV_ELEM(x()) + CSV_ELEM(y()),
                   CSV_ELEM(y()) - CSV_ELEM(z()),
                   CSV_ELEM(z()) * CSV_ELEM(y()));
}
```

+ ___CSV_WRITE_FILE_H(fileName, header, data, splitor, itemType, ...)___

|param|describe|
|---|---|
|fileName|the file name|
|header|the header labels|
|data|the data vector|
|splitor|the splitor|
|...|the [methods | member name] to get members from a item|
|return|void|

```cpp
void test_CSV_WRITE_FILE_H()
{
    INFO("test the macro 'CSV_WRITE_FILE_H', file '../data/point3f.csv'");
    auto ps = ns_geo::PointSet3f::randomGenerator(10, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    CSV_WRITE_FILE_H("../data/point3f.csv", CSV_HEADER("x+z", "x+y", "y-z", "z-y"), ps, ','
                     CSV_ELEM(x()) * CSV_ELEM(z()),
                     CSV_ELEM(x()) + CSV_ELEM(y()),
                     CSV_ELEM(y()) - CSV_ELEM(z()),
                     CSV_ELEM(z()) * CSV_ELEM(y()));
}
```

## Files

[info.csv](./data/info.csv)   

[point3f.csv](./data/point3f.csv)

[refpoint3f.csv](./data/refpoint3f.csv)
