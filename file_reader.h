#pragma once
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#ifndef FILE_READER_H // include guard
#define FILE_READER_H



namespace std_file {

	class Std_Text_File
	{
	public:
		Std_Text_File(string Filename);
		~Std_Text_File();
		void Read_File_Content();
		void Change_File_Content(string);
		string Get_Original_Content();
		void print_file_content();
	protected:
		string Filename;
		streampos size_of_file;
		string content_of_file;
		string original_content;
		string changed_string;
	};

}

#endif FILE_READER_H