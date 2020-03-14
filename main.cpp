#include <iostream>
#include "file_reader.h"
#include "srt_file.h"
#include <string.h>
#include <stdlib.h>

using namespace std_file;
using namespace srt_file;
using namespace std;

int main(int argc, char** argv)
{
    if (argc == 4) {
        cout << argv[1] << " " << argv[2] << " " << argv[3] << endl;
        SRT_File* std_text_file = new SRT_File(argv[1]);
        if ((strcmp(argv[2],"-") == 0) || (strcmp(argv[2],"+") == 0)) {

            if (std_text_file->is_digit(argv[3])) {
                std_text_file->Read_File_Content();
                std_text_file->Parse_srt_content();
                if((strcmp(argv[2],"-") == 0))
                    std_text_file->changed_time(-1*stoi(argv[3]));
                else
                    std_text_file->changed_time(stoi(argv[3]));
                std_text_file->create_changed_file("changedfile.srt");
            }
            else {
                cout << "Delay parameter must be integer!" << endl;
            }
        }
        else {
            cout << "Sign parameter must be + or - !" << endl;
        }
    }
    else {
        cout << "Insert enough parameter!" << endl;
    }
    return 0;
}
