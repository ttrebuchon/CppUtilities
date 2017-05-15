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
        CSV_Row* row = new CSV_Row();

        String cell = "";
        int index = 0;
        String _line = line;
        auto parseCell = [](String str) {
            String S = str.substr(1, str.length()-2);
            S = S.replace("\"\"", "\"");
            return S;
        };

        while (_line.length() > 0)
        {
            if (_line[0] != '"')
            {
                int commaIndex = _line.find(",");
                if (commaIndex != std::string::npos)
                {
                    cell = _line.substr(0, commaIndex);
                }
                else
                {
                    cell = _line;
                }
                
                (*row)[index] = cell;
                index++;
                if (commaIndex != std::string::npos)
                {
                    _line = _line.substr(commaIndex+1);
                }
                else
                {
                    _line = "";
                }
                
            }
            else
            {
                for (int i = 1; i < _line.length(); i++)
                {
                    if (_line[i] == '"')
                    {
                        if (_line.length() - 2 == i)
                        {
                            cell = _line;
                            (*row)[index] = parseCell(cell);
                            index++;
                            _line = "";
                            break;
                        }
                        else
                        {
                            if (_line[i+1] != '\"')
                            {
                                cell = _line.substr(0, i+1);
                                (*row)[index] = parseCell(cell);
                                index++;
                                if (i+2 < _line.length())
                                {
                                     _line = _line.substr(i+2);
                                }
                                else
                                {
                                     _line = _line.substr(i+1);
                                }
                               
                                break;
                            }
                        }
                    }

                }
            }
        }

        return row;
    }


    CSV_File::CSV_File() : rows()
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

        std::ifstream file(fileName, std::ifstream::in);
        std::string tmp;
        while (std::getline(file, tmp))
        {
            rows.push_back(parseLine(tmp));
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
                rows.push_back(new CSV_Row());
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














    CSV_Row::CSV_Row() : cells()
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
        std::stringstream line;

        bool first = true;
        for (String cell : cells)
        {
            if (cell.contains("\n"))
            {
                throw InvalidCellContentException();
            }
            if (!first)
            {
                line << ",";
            }
            if (!(cell.contains(",") || cell.contains("\"")))
            {
                line << cell;
            }
            else
            {
                cell = cell.replace("\"", "\"\"");
                cell = String("\"") + cell + "\"";
                line << cell;
            }
            first = false;
        }

        return line.str();
    }


}
}