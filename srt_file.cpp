
#include "srt_file.h"
#include <sstream>

#include <string.h>
#include <stdio.h>

using namespace std;
using namespace std_file;
using namespace srt_file;


SRT_File::SRT_File(string Filename) :Std_Text_File(Filename) {
	this->Filename = Filename;
}

SRT_File::~SRT_File() {
}

void  SRT_File::Parse_srt_content() {
	string temp = this->content_of_file;
	stringstream temp_stream(temp);
	string line;
	bool pre_line_is_digit = false;
	this->line_counter=0;
	bool pre_line_content = false;
	while (getline(temp_stream, line)) {
		if (is_digit(line)) {

			if (pre_line_content) {
				//cout << srt_parsed_content[this->line_counter].order << endl;
				//cout << srt_parsed_content[this->line_counter].timecode << endl;
				//cout << srt_parsed_content[this->line_counter].content << endl;
				pre_line_content = false;
				this->line_counter++;
			}

			pre_line_is_digit = true;
			srt_parsed_content[this->line_counter].order = line;
		}
		else {
			if (pre_line_is_digit) {
				srt_parsed_content[this->line_counter].timecode = line;
				pre_line_is_digit = false;
			}
			else{
				srt_parsed_content[this->line_counter].content.append(line);
				srt_parsed_content[this->line_counter].content.append("\n");
				pre_line_content = true;
			}
		}

	}
}

bool SRT_File::is_digit(string line) {

	for (char c : line) {
		if ((atoi(&c) == 0) && (c != (char)0x30))
			return false;
	}
	return true;
}

void SRT_File::changed_time(int delay) {


	int srt_array_length = this->line_counter;

	cout << "Element number in Array -> " << srt_array_length << endl;



	for (int i = 0; i < srt_array_length; i++) {

		//string changed_string;
		string parts[2];
		parse_string_two_part(srt_parsed_content[i].timecode, " --> ", parts);
		string parts_f[3];
		string parts_f_[2];
		parse_string_two_part(parts[0], ":", parts_f);
		parse_string_two_part(parts_f[2], ",", parts_f_);
		string parts_s[3];
		string parts_s_[2];
		parse_string_two_part(parts[1], ":", parts_s);
		parse_string_two_part(parts_s[2], ",", parts_s_);
		int start_time_millisec = stoi(parts_f_[1]) + stoi(parts_f_[0])*1000  + stoi(parts_f[0]) * 1000 * 60 + stoi(parts_f[1]) * 1000 * 3600;
		int finish_time_millisec = stoi(parts_s_[1]) + stoi(parts_s_[0])*1000 + stoi(parts_s[0]) * 1000 * 60 + stoi(parts_s[1]) * 1000 * 3600;
		start_time_millisec += delay;
		int start_hour =     (start_time_millisec / 60000) % 60;
		int start_minute =   (start_time_millisec / 1000) / 3600;
		int start_second =   (start_time_millisec / 1000) % (60);
		int start_millisec = start_time_millisec % 1000;
		finish_time_millisec += delay;
		int stop_hour = (finish_time_millisec / 60000) % 60;
		int stop_minute =(finish_time_millisec / 1000) / 3600;
		int stop_second = (finish_time_millisec / 1000) % (60);
		int stop_millisec = finish_time_millisec % 1000;;
		char start_time[100];
		sprintf(start_time,"%02d:%02d:%02d,%03d",start_hour,start_minute,start_second,start_millisec);
		char stop_time[100];
		sprintf(stop_time, "%02d:%02d:%02d,%03d", stop_hour, stop_minute, stop_second, stop_millisec);
		char final_string[200];
		sprintf(final_string, "%s --> %s", start_time, stop_time);
        srt_parsed_content[i].timecode = (string)final_string;
	}

}

void SRT_File::create_changed_file(string Filename) {

	ofstream outline;
	outline.open(Filename);
	int srt_array_length = this->line_counter;



	for (int i = 0; i < srt_array_length; i++) {

		outline << srt_parsed_content[i].order << endl;
		outline << srt_parsed_content[i].timecode << endl;
		outline << srt_parsed_content[i].content << endl;

	}

	outline.close();
	cout<<"new subtitle created!"<<endl;
}

void SRT_File::parse_string_two_part(string str, string delim, string *array) {

	//string data = "12:45:35,256 --> 13:46:36,789";
	//char* next;
	char* temp;
	temp = strtok(&str[0], &delim[0]);

	int counter = 0;
	while (temp != NULL) {
		//cout << temp << endl;
		*(&array[0] + counter) = temp;
		temp = strtok(NULL, &delim[0]);
		counter++;
	}

}
