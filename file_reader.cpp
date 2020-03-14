#include "file_reader.h"

using namespace std;
using namespace std_file;


Std_Text_File::Std_Text_File(string Filename) {
	this->Filename = Filename;
}

Std_Text_File::~Std_Text_File() {

}

void Std_Text_File::Read_File_Content() {

	ifstream infile;
	string line;
	infile.open(this->Filename);
	this->size_of_file = infile.tellg();
	this->content_of_file = "";
	while (getline(infile, line)) {
		this->content_of_file.append(line);
		this->content_of_file.append("\n");
	}
	this->original_content = this->content_of_file;
	infile.close();

}
void Std_Text_File::Change_File_Content(string Changed_String) {
	this->changed_string = Changed_String;
	ofstream outfile;
	outfile.open(this->Filename);
	outfile << changed_string;
	outfile.close();
}
string Std_Text_File::Get_Original_Content() {
	return this->original_content;
}

void Std_Text_File::print_file_content() {
	cout << this->content_of_file << endl;
}
