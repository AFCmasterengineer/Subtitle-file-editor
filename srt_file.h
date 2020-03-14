#pragma once
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include "file_reader.h"

using namespace std;
using namespace std_file;

#ifndef SRT_FILE_H // include guard
#define SRT_FILE_H



namespace srt_file {

	class SRT_File: public Std_Text_File
	{
	public:
		typedef struct srt_content
		{
			string order;
			string timecode;
			string content;

		};
		SRT_File(string Filename);
		~SRT_File();
		void Parse_srt_content();
		bool is_digit(string line);
		void changed_time(int delay);
		void create_changed_file(string Filename);
		void parse_string_two_part(string str, string delim, string* array);

	private:

		int line_counter;
		srt_content srt_parsed_content[3000];
	};

}

#endif SRT_FILE_H
