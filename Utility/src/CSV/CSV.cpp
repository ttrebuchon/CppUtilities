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
        
        auto parseQuoted = [] (String& str) -> String {
        	int i = 0;
        	String quote = "";
        	str = str.substr(1);
        	if (str[0] == '"')
        	{
        		str = str.substr(1);
        		return "\"";
        	}
        	while (str.length() - i > 0)
        	{
        		if (str[i] != '"')
        		{
        			quote += str[i];
        			i++;
        		}
        		else
        		{
        			str = str.substr(i);
        			i = 0;
        			if (str.length() == 1)
        			{
        				str = str.substr(1);
        				break;
        			}
        			else
        			{
        				if (str[1] == '"')
        				{
        					quote += '"';
        					str = str.substr(2);
        				}
        				else
        				{
        					str = str.substr(1);
        					break;
        				}
        			}
        		}
        	}
        	str = str.substr(i);
        	i = 0;
        	return quote;
        };
        int i = 0;
        while (_line.length() - i > 0)
        {
        	if (_line[i] != ',' && _line[i] != '"')
        	{
        		cell += _line[i];
        		//_line = _line.substr(1);
        		i++;
        	}
        	else if (_line[i] == ',')
        	{
        		_line = _line.substr(i);
        		i = 0;
        		(*row)[index++] = cell;
        		cell = "";
        		_line = _line.substr(1);
        	}
        	else
        	{
        		_line = _line.substr(i);
        		i = 0;
        		cell += parseQuoted(_line);
        	}
        }
        _line = _line.substr(i);
        i = 0;
        
        if (cell != "")
        {
        	(*row)[index] = cell;
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
        if (file.fail())
        {
        	throw FileNotFoundException();
        }
        String tmp;
        while (std::getline(file, tmp))
        {
            if (tmp.contains("\r"))
            {
                tmp = tmp.replace("\r", "");
            }
            if (tmp.contains("\n"))
            {
                tmp = tmp.replace("\n", "");
            }
            rows.push_back(parseLine(tmp));
        }
        file.close();
    }

    void CSV_File::writeFile(std::string fileName) const
    {
        std::string str = this->asString();
        std::ofstream file(fileName);
        if (file.fail())
        {
        	throw FileNotFoundException();
        }
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