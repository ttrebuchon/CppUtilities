#include "../Tests.h"
#include <CSV/CSV.h>

using Utils::CSV::CSV_File;

bool Testing::CSV_Test()
{
    CSV_File file;

    file[0][0] = ",Hello...\\\n";
    //dout << file[0][0] << std::endl;

    dout << "\"" << file.asString() << "\"" << std::endl;

    return true;
}