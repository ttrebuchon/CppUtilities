#include <CSV/CSV.h>

#include <Exception/NotImplemented.h>
#include <sstream>
#include <String/String.h>

namespace Util
{
namespace CSV
{

    CSV_Row* CSV_File::parseLine(std::string line)
    {
        //TODO
        throw NotImp();
    }


    CSV_File::CSV_File(std::string delimiter, std::string escapeSeq) : rows(), delimiter(delimiter), escapeSeq(escapeSeq)
    {
        
    }

    CSV_File::~CSV_File()
    {
        for (auto row : rows)
        {
            delete row;
        }
    }

    void CSV_File::openFile(std::string fileName)
    {
        for (auto row : rows)
        {
            delete row;
        }
        rows = std::vector<CSV_Row*>();

        std::ifstream file(fileName);

        std::string tmp;
        String fileStr = "";
        while (std::getline(file, tmp))
        {
            fileStr += tmp;
            if (!fileStr.endsWith(escapeSeq))
            {
                rows.push_back(parseLine(fileStr));
                fileStr = "";
            }
        }
        if (fileStr != "")
        {
            rows.push_back(parseLine(fileStr));
        }
    }

    void CSV_File::writeFile(std::string fileName) const
    {
        std::string str = this->asString();
        std::ofstream file(fileName);
        file << str << std::flush;
        file.close();
    }

    int CSV_File::length() const
    {
        return rows.size();
    }

    void CSV_File::length(const int newLength)
    {
        if (rows.size() > newLength)
        {
            for (int i = newLength; i < rows.size(); i++)
            {
                delete rows[i];
            }
            rows.resize(newLength);
        }
        else
        {
            while (rows.size() < newLength)
            {
                rows.push_back(new CSV_Row(this));
            }
        }
    }

    std::string CSV_File::asString() const
    {
        std::stringstream ss;
        for (auto row : rows)
        {
            ss << row->asString() << "\n";
        }
        return ss.str();
    }

    CSV_Row& CSV_File::operator[](const int row)
    {
        if (row >= rows.size())
        {
            this->length(row+1);
        }
        return *rows[row];
    }














    CSV_Row::CSV_Row(CSV_File* file) : cells(), file(file)
    {

    }

    std::string& CSV_Row::operator[](const int cell)
    {
        if (cell >= cells.size())
        {
            cells.resize(cell+1);
        }

        return cells[cell];
    }

    int CSV_Row::length() const
    {
        return cells.size();
    }

    void CSV_Row::length(const int newLength)
    {
        cells.resize(newLength);
    }

    std::string CSV_Row::asString() const
    {

        std::string delimiter = ",", escapeSeq = "\\";
        if (file != NULL)
        {
            delimiter = file->delimiter;
            escapeSeq = file->escapeSeq;
        }

        std::stringstream line;

        bool first = true;
        for (String cell : cells)
        {
            if (!first)
            {
                line << delimiter;
            }
            if (!(cell.contains(delimiter) || cell.contains("\n") || cell.contains(escapeSeq)))
            {
                line << cell;
            }
            else
            {
                cell = cell.replace(escapeSeq, escapeSeq + escapeSeq);
                cell = cell.replace("\n", escapeSeq + "\n");
                cell = cell.replace(delimiter, escapeSeq + delimiter);
                
                line << cell;
            }
            first = false;
        }

        return line.str();
    }


}
}