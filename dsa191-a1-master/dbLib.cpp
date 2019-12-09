/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

#include <time.h>
clock_t startload, endload;
double cpu_time_used;

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// TCity: OK
L1List<TCity> *LoadCities(){

    L1List<TCity>* citylist = new L1List<TCity>();
    L1Item<TCity> tcity;
    
    ifstream ifs("cities.csv");

    if (ifs.is_open())
    {
        
        string name = ""; 
        string temp = "";

        getline(ifs,name);

        while (getline(ifs,temp))
        {
            bool iserror = false;
            int idarr[14] = {0};
            int numcomma = 1;
            
            for (int i = 0; i < temp.length()-1; ++i)
            {
                if (temp[i+1] == ',' || temp[i-1] == ',')
                    idarr[numcomma++] = i;
            }

            try
            {
                tcity.data.id             = stoi(temp.substr(idarr[0], idarr[1]-idarr[0]+1)); 
                tcity.data.name           = temp.substr(idarr[2], idarr[3]-idarr[2]+1);     
                //tcity.data.coords         = temp.substr(idarr[4], idarr[5]-idarr[4]+1);
                //tcity.data.start_year     = stoi(temp.substr(idarr[6], idarr[7]-idarr[6]+1));
                //tcity.data.url_name       = temp.substr(idarr[8], idarr[9]-idarr[8]+1);
                //tcity.data.country        = temp.substr(idarr[10], idarr[11]-idarr[10]+1);
                //tcity.data.country_state  = temp.substr(idarr[12], idarr[13]-idarr[12]+1);

                citylist->push_back(tcity.data);
            }
            catch(const std::exception& e)
            {
                continue;
            }
            
        }
        ifs.close();

        return citylist;
    }
    else
    {
        throw "can't open cities.csv";
    }

}

// TLine: OK
L1List<TLine> *LoadLines(){

    L1List<TLine>* lineslist = new L1List<TLine>();
    L1Item<TLine> tline;
    
    ifstream ifs("lines.csv");

    if (ifs.is_open())
    {
        
        string name = ""; 
        string temp = "";

        getline(ifs,name);

        while (getline(ifs,temp))
        {
            bool iserror = false;
            int idarr[14] = {0};
            int numcomma = 1;
            
            for (int i = 0; i < temp.length()-1; ++i)
            {
                if (temp[i+1] == ',' || temp[i-1] == ',')
                    idarr[numcomma++] = i;
            }

            try
            {
                tline.data.id                  = stoi(temp.substr(idarr[0], idarr[1]-idarr[0]+1)); 
                tline.data.city_id             = stoi(temp.substr(idarr[2], idarr[3]-idarr[2]+1));  
                tline.data.name                = temp.substr(idarr[4], idarr[5]-idarr[4]+1);
                // tline.data.url_name            = stoi(temp.substr(idarr[6], idarr[7]-idarr[6]+1));
                // tline.data.color               = temp.substr(idarr[8], idarr[9]-idarr[8]+1);
                // tline.data.system_id           = stoi(temp.substr(idarr[10], idarr[11]-idarr[10]+1));
                // tline.data.transport_mode_id   = stoi(temp.substr(idarr[12], idarr[13]-idarr[12]+1));

                lineslist->push_back(tline.data);
            }
            catch(const std::exception& e)
            {
                continue;
            }
          
     
        }
        ifs.close();

        return lineslist;
    }
    else
    {
        throw "can't open lines.csv";
    }

}

// TStation: OK
L1List<TStation> *LoadStation(){

    L1List<TStation>* stationlist = new L1List<TStation>();
    L1Item<TStation> tstation;
    
    ifstream ifs("stations.csv");

    if (ifs.is_open())
    {
        
        string name = ""; 
        string temp = "";

        getline(ifs,name);

        while (getline(ifs,temp))
        {

            

            bool iserror = false;
            int idarr[14] = {0};
            int numcomma = 1;

            for (int i = 0; i < temp.length()-1; ++i)
            {
                if (temp[i] == ',' && !iserror)
                {
                    idarr[numcomma++] = i;
                }
                if (temp[i] == '"')
                {
                    if (!iserror)
                        iserror = true;
                    else
                        iserror = false;
                    
                }
                
            }

            idarr[numcomma++] = temp.length()-1;

                tstation.data.id            = stoi(temp.substr(idarr[0], idarr[1])); 
                tstation.data.name          = temp.substr(idarr[1]+1, idarr[2]-idarr[1]-1);  
                tstation.data.geometry      = temp.substr(idarr[2]+1, idarr[3]-idarr[2]-1);
                tstation.data.buildstart    = (idarr[4] - idarr[3] == 1)?-1:stoi(temp.substr(idarr[3]+1, idarr[4]-idarr[3]-1));
                tstation.data.opening       = (idarr[5] - idarr[4] == 1)?-1:stoi(temp.substr(idarr[4]+1, idarr[5]-idarr[4]-1));
                tstation.data.closure       = (idarr[6] - idarr[5] == 1)?-1:stoi(temp.substr(idarr[5]+1, idarr[6]-idarr[6]-1));
                tstation.data.city_id       = stoi(temp.substr(idarr[6]+1));
                
                stationlist->push_back(tstation.data);

     
        }
        ifs.close();

        return stationlist;
    }
    else
    {
        throw "can't open stations.csv";
    }

}

// Station Line Node: Ok
L1List<TStationLine> *LoadStaLine(){

    L1List<TStationLine>* stalinelist = new L1List<TStationLine>();
    L1Item<TStationLine> staTLine;
    
    ifstream ifs("station_lines.csv");

    if (ifs.is_open())
    {
        
        string name = ""; 
        string temp = "";

        getline(ifs,name);

        while (getline(ifs,temp))
        {
            bool iserror = false;
            int idarr[14] = {0};
            int numcomma = 1;
            
            for (int i = 0; i < temp.length()-1; ++i)
            {
                if (temp[i+1] == ',' || temp[i-1] == ',' || temp[i+1] == '\n')
                    idarr[numcomma++] = i;
            }

            try
            {
                staTLine.data.id         = stoi(temp.substr(idarr[0], idarr[1]-idarr[0]+1)); 
                staTLine.data.station_id = stoi(temp.substr(idarr[2], idarr[3]-idarr[2]+1));  
                staTLine.data.line_id    = stoi(temp.substr(idarr[4], idarr[5]-idarr[4]+1));
                staTLine.data.city_id    = stoi(temp.substr(idarr[6], idarr[7]-idarr[6]+1));
                staTLine.data.created_at = temp.substr(idarr[8], idarr[9]-idarr[8]+1);
                staTLine.data.updated_at = temp.substr(idarr[10], idarr[11]-idarr[10]+1);

                stalinelist->push_back(staTLine.data);
            }
            catch(const std::exception& e)
            {
                continue;
            }
            
            
     
        }
        ifs.close();

        return stalinelist;
    }
    else
    {
        throw "can't open station_lines.csv";
    }

}

// System Node: OK
L1List<TSystem> *LoadSystem(){

    L1List<TSystem>* systemlist = new L1List<TSystem>();
    L1Item<TSystem> tsystem;
    
    ifstream ifs("systems.csv");

    if (ifs.is_open())
    {
        
        string name = ""; 
        string temp = "";

        getline(ifs,name);

        while (getline(ifs,temp))
        {
            bool iserror = false;
            int idarr[14] = {0};
            int numcomma = 1;

            for (int i = 0; i < temp.length()-1; ++i)
            {
                if (temp[i+1] == ',' || temp[i-1] == ',')
                    idarr[numcomma++] = i;
            }

            try
            {
                tsystem.data.id              = stoi(temp.substr(idarr[0], idarr[1]-idarr[0]+1)); 
                tsystem.data.city_id         = stoi(temp.substr(idarr[2], idarr[3]-idarr[2]+1));  
                tsystem.data.name            = temp.substr(idarr[4], idarr[5]-idarr[4]+1);
                
                systemlist->push_back(tsystem.data);
            }
            catch(const std::exception& e)
            {
                continue;
            }
            
            
     
        }
        ifs.close();

        return systemlist;
    }
    else
    {
        throw "can't open systems.csv";
    }

}

// Track Node: OK
L1List<TTrack> *LoadTrack(){

    L1List<TTrack>* tracklist = new L1List<TTrack>();
    L1Item<TTrack> ttrack;
    
    ifstream ifs("tracks.csv");

    if (ifs.is_open())
    {
       
       string name = ""; 
        string temp = "";

        getline(ifs,name);

        while (getline(ifs,temp))
        {

            

            bool iserror = false;
            int idarr[14] = {0};
            int numcomma = 1;

            for (int i = 0; i < temp.length()-1; ++i)
            {
                if (temp[i] == ',' && !iserror)
                {
                    idarr[numcomma++] = i;
                }
                if (temp[i] == '"')
                {
                    if (!iserror)
                        iserror = true;
                    else
                        iserror = false;
                    
                }
                
            }

            idarr[numcomma++] = temp.length()-1;

                ttrack.data.id              = stoi(temp.substr(idarr[0], idarr[1])); 
                ttrack.data.geometry        = temp.substr(idarr[1]+1, idarr[2]-idarr[1]-1);  
                ttrack.data.buildstart      = (idarr[3] - idarr[2] == 1)?-1:stoi(temp.substr(idarr[2]+1, idarr[3]-idarr[2]-1));
                ttrack.data.opening         = (idarr[4] - idarr[3] == 1)?-1:stoi(temp.substr(idarr[3]+1, idarr[4]-idarr[3]-1));
                ttrack.data.closure         = (idarr[5] - idarr[4] == 1)?-1:stoi(temp.substr(idarr[4]+1, idarr[5]-idarr[4]-1));
                ttrack.data.length          = (idarr[6] - idarr[5] == 1)?-1:stoi(temp.substr(idarr[5]+1, idarr[6]-idarr[6]-1));
                ttrack.data.city_id         = stoi(temp.substr(idarr[6]+1));
                
                tracklist->push_back(ttrack.data);

     
        }
        ifs.close();



        return tracklist;
    }
    else
    {
        throw "can't open tracks.csv";
    }

}

// Track TLine:OK
L1List<TTrackLine> *LoadTrackLines(){

    L1List<TTrackLine>* tralinelist = new L1List<TTrackLine>();
    L1Item<TTrackLine> traTLine;
    
    ifstream ifs("track_lines.csv");

    if (ifs.is_open())
    {
        
        string name = ""; 
        string temp = "";

        getline(ifs,name);

        while (getline(ifs,temp))
        {
            bool iserror = false;
            int idarr[14] = {0};
            int numcomma = 1;

            for (int i = 0; i < temp.length()-1; ++i)
            {
                if (temp[i+1] == ',' || temp[i-1] == ',')
                    idarr[numcomma++] = i;
            }

            try
            {
                traTLine.data.id              = stoi(temp.substr(idarr[0], idarr[1]-idarr[0]+1)); 
                traTLine.data.section_id      = stoi(temp.substr(idarr[2], idarr[3]-idarr[2]+1));  
                traTLine.data.line_id         = stoi(temp.substr(idarr[4], idarr[5]-idarr[4]+1));
                traTLine.data.created_at      = temp.substr(idarr[6], idarr[7]-idarr[6]+1);
                traTLine.data.updated_at      = temp.substr(idarr[8], idarr[9]-idarr[8]+1);
                traTLine.data.city_id         = stoi(temp.substr(idarr[10], idarr[11]-idarr[10]+1));
                
                tralinelist->push_back(traTLine.data);
            }
            catch(const std::exception& e)
            {
                continue;
            }
            
            
     
        }
        ifs.close();

        return tralinelist;
    }
    else
    {
        throw "can't open track_lines.csv";
    }

}

void LoadData(void* &pData){

    startload = clock();
    TDataset* tdataset = new TDataset();
    
    tdataset->cityList = LoadCities();
    tdataset->lineList = LoadLines();
    tdataset->stationList = LoadStation();
    tdataset->stalineList = LoadStaLine();
    tdataset->sysList = LoadSystem();
    tdataset->trackList = LoadTrack();
    tdataset->tralineList = LoadTrackLines();

   

    pData = tdataset;
    endload = clock();
    cpu_time_used = (double (endload - startload)) / CLOCKS_PER_SEC;
    clog << "time to load file: " << cpu_time_used << '\n';
    return;
}

void ReleaseData(void* &pData)
{
    
}
