#include "../Tests.h"
#include <CSV/CSV.h>
#include <map>

using Utils::CSV::CSV_File;

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

    std::vector<std::vector<std::string>> correctVals = { {"a", "b", "b", "1", "2" }, {"3", "4", "5", "", "6" }, {"", "", "", "", "", "", "", ""}, {"7", "8", "\"\"", "", ",8,", "9"} };


    file.openFile("Test_Files/CSV_Test.csv");
    for (int i = 0; i < file.length(); i++)
    {
        for (int j = 0; j < file[i].length(); j++)
        {
            assert_ex(file[i][j] == correctVals[i][j]);
        }
        dout << std::endl;
    }


    return true;
}