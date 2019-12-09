/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering int HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms int Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

#pragma region Tcity Node
struct TCity {
    // The structure to store city information
    int     id;
	string  name;
	string  coords;
	int     start_year;
	string  url_name;
	string  country;
	string  country_state;
};

#pragma endregion

#pragma region TLine Node
struct TLine {
    // The structure to store line information
    int     id;
	int     city_id;
	string  name;
	string  url_name;
	string  color;
	int     system_id;
	int     transport_mode_id;
};

#pragma endregion

#pragma region Station_line Node
struct TStationLine {
    // The structure to store TStationLine information
    int		id;
	int 	station_id;
	int 	line_id;
	int 	city_id;
	string 	created_at;
	string 	updated_at;
};


#pragma endregion

#pragma region Station Node
struct TStation {
	int 	id;
	string 	name;
	string 	geometry;
	int 	buildstart;
	int 	opening;
	int 	closure;
	int 	city_id;
};



#pragma endregion

#pragma region System Node
struct TSystem {
	int 	id;
	int 	city_id;
	string 	name;


};

#pragma endregion

#pragma region Ttrack Node
struct TTrack {
    // The structure to store track information
    int     id;
	string  geometry;
	int     buildstart;
	int     opening;
	int     closure;
	int     length;
	int     city_id;
};



#pragma endregion

#pragma region Track_Lines
struct TTrackLine {
	int	 	id;
	int 	section_id;
	int 	line_id;
	string 	created_at;
	string 	updated_at;
	int 	city_id;

};




#pragma endregion




class TDataset {
    // This class can be a container that help you manage your tables
    public:
		L1List<TCity>        	*cityList;
		L1List<TLine>	    	*lineList;
		L1List<TStationLine>	*stalineList;
		L1List<TStation>		*stationList;
		L1List<TSystem>			*sysList;
		L1List<TTrack>			*trackList;
		L1List<TTrackLine>		*tralineList;
        
        TDataset(){
            this->cityList      = NULL;
            this->lineList      = NULL;
            this->stalineList   = NULL;
            this->stationList   = NULL;
            this->sysList       = NULL;
            this->trackList     = NULL;
            this->tralineList   = NULL;
        }
};

// Please add more or modify as needed

void LoadData(void* &);
void ReleaseData(void* &);

#endif //DSA191_A1_DBLIB_H