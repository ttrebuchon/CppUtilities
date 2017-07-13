#pragma once

#include <fstream>
#include <vector>
#include <QUtils/Exception/Exception.h>

namespace QUtils
{
namespace CSV
{

    UTIL_CUSTOM_EXCEPTION(InvalidCellContentException, "Invalid content in CSV cell");
    UTIL_CUSTOM_EXCEPTION(FileNotFoundException, "Could not open file");
    class CSV_Row;

    class CSV_File
    {
        private:

        std::vector<CSV_Row*> rows;

        CSV_Row* parseLine(std::string line);

        public:
        CSV_File();
        ~CSV_File();

        void openFile(std::string fileName);
        void writeFile(std::string fileName) const;

        int length() const;
        void length(const int newSize);

        std::string asString() const;

        CSV_Row& operator[](const int i);
        CSV_Row* removeAt(const int i);
        CSV_Row* insertAt(const int i);
        void placeAt(CSV_Row*, const int i);

        
        friend class CSV_Row;
    };

    class CSV_Row
    {
        private:
        std::vector<std::string> cells;

        CSV_Row();

        public:
        std::string& operator[](const int i);

        int length() const;
        void length(const int newLength);

        std::string asString() const;

        friend class CSV_File;
    };
}
}