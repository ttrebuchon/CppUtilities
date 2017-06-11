#include "../Tests.h"
#include <CSV/CSV.h>
#include <map>

using Utils::CSV::CSV_File;

void print_csv(std::string);

bool Testing::CSV_Test()
{
    CSV_File file;

    file[0][0] = ",Hello...";

    std::string fileStr = file.asString();
    dout << "\"" << fileStr << "\"" << std::endl;
    std::string correctStr = "\",Hello...\"\n";
    assert_ex(fileStr == correctStr);



    file[0][0] = ",Hello...\"";

    fileStr = file.asString();
    dout << "\"" << fileStr << "\"" << std::endl;
    correctStr = "\",Hello...\"\"\"\n";
    assert_ex(fileStr == correctStr);

    std::vector<std::vector<std::string>> correctVals = { {"a", "b", "b", "1", "2" }, {"3", "4", "5", "", "6" }, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, {"7", "8", "\"\"\"", "", ",8,", "9"}, {"", "", "", "", "", "", "", ""} };

    file.openFile("Test_Files/CSV_Test.csv");
    for (int i = 0; i < file.length(); i++)
    {
        for (int j = 0; j < file[i].length(); j++)
        {
        	//dout << "[" << file[i][j] << "] vs. [" << correctVals[i][j] << "]" << std::endl;
            assert_ex(file[i][j] == correctVals[i][j]);
        }
        dout << std::endl;
    }
    
    CSV_File anorexia_data;
    anorexia_data.openFile("Test_Files/Sample-Data-Anorexia-Treatment.csv");
    for (int i = 0; i < anorexia_data.length(); i++)
    {
        for (int j = 0; j < anorexia_data[i].length(); j++)
        {
            dout << anorexia_data[i][j] << ", ";
        }
        dout << "\n" << std::endl;
    }
    
    dout << "\n\n" << std::endl;
    
    /*CSV_File repet_data;
    repet_data.openFile("Test_Files/Repetition-Periods-for-Elementary-Cellular-Automata.csv");
    
    for (int i = 0; i < repet_data.length(); i++)
    {
        for (int j = 0; j < repet_data[i].length(); j++)
        {
            dout << repet_data[i][j] << ",\n\n";
        }
        dout << "\n" << std::endl;
    }*/
    
    print_csv("Test_Files/Arecibo-Telescope-1974-Transmitted-Message.csv");
    dout << "\n\n\n";
    print_csv("Test_Files/Persistent-Structures-in-the-Code-20-Cellular-Automaton_1.csv");
    
    print_csv("Test_Files/Three-Color-Cellular-Automaton-Rules-that-Double-Their-Input.csv");
    
    //print_csv("Test_Files/Orbits-of-a-Planet-in-a-Binary-Star-System.csv");


    return true;
}

void print_csv(std::string path)
{
	CSV_File file;
	file.openFile(path);
	dout << path << ": " << std::endl;
	for (int i = 0; i < file.length(); i++)
    {
        for (int j = 0; j < file[i].length(); j++)
        {
            dout << file[i][j] << ", ";
        }
        dout << "\n" << std::endl;
    }
}