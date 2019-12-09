/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"
#include "dbLib.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

#pragma region Handle Data
// Remove station Id
void RMStationId(TStationLine& tstaline, bool remove)
{
    if (remove)
      tstaline.station_id = -1;  
}


#pragma endregion
#pragma region // find data
// find Cities Id
int findCityId(TCity&  city, string name)
{
    if (city.name == name )
        return city.id;
    return -1;
    
}

int findCityId(TStation&  tstation, string name)
{
    if (tstation.name == name )
        return tstation.id;
    return -1;
    
}
int findStaLineId(TStationLine&  tstaline, int _stationid)
{
    if (tstaline.station_id == _stationid )
        return tstaline.id;
    return -1;
    
}

int findCityId(TStationLine& tstaline, int _lineid )
{
    if (tstaline.line_id == _lineid)
        return tstaline.city_id;
    return -1;
}


// Find station ID in station Line list
int findStaIdOfCity(TStation&  tstation, int city_id)
{
    if (tstation.city_id == city_id )
        return tstation.id;
    return -1;
    
}

int findStationId(TStation& tstation, int stationid)
{
    if (tstation.id == stationid)
        return tstation.id;
    return -1;
}

bool StationIdRemove(TStation& tstation, int stationid){
    return tstation.id == stationid;
}
bool StaLineIdRemove(TStationLine& tstationline, int stationid){
    return tstationline.station_id == stationid;
}
bool RemoveStaLine(TStationLine& tstationline, int station_id, int line_id){
    return (tstationline.station_id == station_id) &&(tstationline.line_id == line_id);
}
// find closer station id
int findCloserId(TStation& tstation, int stationid)
{
    if (tstation.id == stationid)
        return tstation.closure;
    return -1;
}

// find Station line id
int findStaLineId(TStation& tstation, int stationid)
{
    if (tstation.id == stationid)
        return tstation.id;
    return -1;
}


#pragma endregion

#pragma region // Get Data


// get valide name line
string GetNameLine(TLine& tline, int id)
{
    if (tline.id == id)
        return tline.name;
    return "";
}

// Get Station Id
int GetStationID(TStation& tstation, int city_id)
{
    if (tstation.city_id == city_id)
        return tstation.id;
    return -1;
}
// Get Station Line Id
int GetStationLineID(TStationLine& tstaline, int lines_id)
{
    if (tstaline.line_id == lines_id)
        return tstaline.station_id;
    return -1;
}

// Get Line ID
int GetLineID(TLine& tline, int city_id)
{
    if (tline.city_id == city_id)
        return tline.id;
    return -1;
}

// get geometry 
string GetGeometry(TTrack& ttrack, int _trackid)
{
    if (ttrack.id == _trackid)
        return ttrack.geometry;
    return "";
}

string GetGeometry(TStation& tstation, int _stationid)
{
    if (tstation.id == _stationid)
        return tstation.geometry;
    return "";
}


// get update of line
string GetUpdate(TTrackLine& ttrackline, int _lineid)
{
    if (ttrackline.line_id == _lineid)
        return ttrackline.updated_at;
    return "";
}
// get creat at of line
string GetCreated(TTrackLine& ttrackline, int _lineid)
{
    if (ttrackline.line_id == _lineid)
        return ttrackline.created_at;
    return "";
}



#pragma endregion

#pragma region // Check Data

// check Station And Line is exist in this list
bool checkStaAndLineId(TStationLine& tstaline, int _stationid, int _lineid)
{
    return (tstaline.line_id == _lineid) && (tstaline.station_id == _stationid);
}

 // check valid Id city
bool IsValidID(TLine& tline, int id)
{
    
    return tline.city_id == id;
}


// Is valid Station Id
bool ValidStationID(TStation& tstation, int Id)
{
    return (tstation.city_id == Id);
}
// Is valid Line Id
bool ValidLineID(TLine& tline, int Id)
{
    return (tline.city_id == Id);
}
// Is valid Station Line Id
bool ValidStationLineID(TStationLine& tstationline, int line_id)
{
    return (tstationline.line_id == line_id);
}




#pragma endregion



#pragma region Two ParamHandle 
void TwoParamHandle(void* pData, void* &pOutput, int &N, string firstpara, string secondpara)
{
    // handle for request with two param
    string _firstpara[] = {"CL","LSC","LLC","LSL","FC","FS","IS", "RS"};
    int firstparamID = -1;
    for (int i = 0; i < 8; ++i)
        if (firstpara == _firstpara[i])
        {
            firstparamID = i;
            break;
        }

    
    
    switch(firstparamID){
                case 0:
                {
                    N = 1;
                    pOutput = new int [N];

                    int     IDcity      = -1;
                    TCity   tCity;
                    char*   _pNameCity  = new char [secondpara.length()+1];
                    string  _NameCity   = secondpara;
                    

                    strcpy(_pNameCity, secondpara.c_str());

                    // get ID of Cities in citylist
                    
                    int(*pfindCitiesId)(TCity& , string) = findCityId; // con tro ham
                    IDcity = ((TDataset*)pData)->cityList->traverse(pfindCitiesId, _pNameCity);

                    // get num line of cityname 
                    int NumLines = 0;

                    if (IDcity == -1)
                        NumLines = -1;
                    else
                    {
                        bool(*pIsvalidId)(TLine&, int) = IsValidID;
                        NumLines = ((TDataset*)pData)->lineList->traverse(pIsvalidId, IDcity);
                    }


                    // return value of numlines
                    
                    *((int*)pOutput) = NumLines;
                }
                    break;
                case 1:
                {
                   
                    int     IDcity      = -1;
                    TCity   tCity;
                    char*   _pNameCity  = new char [secondpara.length()+1];
                    string  _NameCity   = secondpara;
                    
                    strcpy(_pNameCity, secondpara.c_str());

                    // get ID of Cities in citylist
                    int(*pfindCitiesId)(TCity& , string) = findCityId; // con tro ham
                    IDcity = ((TDataset*)pData)->cityList->traverse(pfindCitiesId, _pNameCity);

                    // count num Station ID
                    int NumstationID = 0;
                    bool(*pValidStationID)(TStation&, int) = ValidStationID;
                    
                    NumstationID = ((TDataset*)pData)->stationList->traverse(pValidStationID,IDcity);

                    N       = NumstationID;
                    
                    if (N == 0)
                    {
                        N = 0;
                        pOutput = nullptr;
                    }
                    else
                    {
                        int(*pGetStationId)(TStation&, int) = GetStationID;
                        ((TDataset*)pData)->stationList->traverse(pGetStationId,IDcity,pOutput,N);
                   
                    }
                }
                    break;
                case 2:
                {
                    int     IDcity      = -1;
                    TCity   tCity;
                    char*   _pNameCity  = new char [secondpara.length()+1];
                    string  _NameCity   = secondpara;
                    
                    strcpy(_pNameCity, secondpara.c_str());

                    // get ID of Cities in citylist
                    int(*pfindCitiesId)(TCity& , string) = findCityId; // con tro ham
                    IDcity = ((TDataset*)pData)->cityList->traverse(pfindCitiesId, _pNameCity);

                    // count num Line ID
                    int NumLineID = 0;
                    bool(*pValidLineID)(TLine&, int) = ValidLineID;
                    
                    NumLineID = ((TDataset*)pData)->lineList->traverse(pValidLineID,IDcity);

                    N       = NumLineID;
                    
                    if (N == 0)
                    {
                        pOutput = nullptr;
                    }
                    else
                    {
                        int(*pGetLineId)(TLine&, int) = GetLineID;
                        ((TDataset*)pData)->lineList->traverse(pGetLineId,IDcity,pOutput,N);
                   
                    }

                    
                }
                    break;
                case 3:
                {
                    int  _linecityid = 0;
                    try
                    {
                        _linecityid   = stoi(secondpara);
                    }
                    catch(const std::exception& e)
                    {
                        pOutput = nullptr;
                        N = 0;
                        return;
                    }
                    
            
                    // count num Station ID
                    int NumstalineID = 0;

                    bool(*pValidStationLineID)(TStationLine&, int) = ValidStationLineID;
                    
                    
                    NumstalineID = ((TDataset*)pData)->stalineList->traverse(pValidStationLineID,_linecityid);
                    

                    N = NumstalineID;
                    
                    
                    if (N == 0)
                    {
                        N = 0;
                        pOutput = nullptr;
                    }
                    else
                    {
                        int(*pGetStationLineId)(TStationLine&, int) = GetStationLineID;
                        ((TDataset*)pData)->stalineList->traverse(pGetStationLineId,_linecityid,pOutput,N);
                   
                    }

                }
                    break;
                case 4:
                {
                    N = 1;
                    pOutput = new int [N];

                    int     IDcity      = -1;
                    TCity   tCity;
                    char*   _pNameCity  = new char [secondpara.length()+1];
                    string  _NameCity   = secondpara;
                    

                    strcpy(_pNameCity, secondpara.c_str());

                    // get ID of Cities in citylist
                    
                    int(*pfindCitiesId)(TCity& , string) = findCityId; // con tro ham
                    IDcity = ((TDataset*)pData)->cityList->traverse(pfindCitiesId, _pNameCity);

                    *((int*)pOutput) = IDcity;
                }
                    break;
                case 5:
                {
                    N = 1;
                    pOutput = new int [N];

                    char*   _pNameStation  = new char [secondpara.length()+1];
                    string  _NameStation   = secondpara;
                    
                    strcpy(_pNameStation, secondpara.c_str());

                   // Get Station Id
                    int StationID = -1;

                    int(*pfindCitiesId)(TStation& , string) = findCityId; // con tro ham
                    StationID = ((TDataset*)pData)->stationList->traverse(pfindCitiesId, _pNameStation);


                    if (StationID == -1)
                    {
                        *((int*)pOutput) = -1;
                    }
                    else
                    {
                        *((int*)pOutput) = StationID;
                    }
                    

                    

                }
                    break;
                case 6:
                {
                    string csv_descrip = secondpara;
                    L1Item<TStation> tstation;

                    int size        = ((TDataset*)pData)->stationList->getSize();
                    int max_id      = ((TDataset*)pData)->stationList->at(size-1).id;
                    bool iserror    = false;
                    int idarr[14]   = {0};
                    int numcomma    = 1;


                    // TStation EndNode = ((TDataset*)pData)->stationList->EndNode();
                    // int maxid = EndNode.id;

                    // find index of each elements
                    for (int i = 0; i < csv_descrip.length()-1; ++i)
                    {
                        if (csv_descrip[i] == ',' && !iserror)
                        {
                            idarr[numcomma++] = i;
                        }
                        if (csv_descrip[i] == '"')
                        {
                            if (!iserror)
                                iserror = true;
                            else
                                iserror = false;
                            
                        }
                    }

                    // load each elements
                    int newId, newBuildstart,newOpening,newClosure;
                    string newName, newGeometry;
                    try{
                        newId            = ++max_id;
                        newName          = csv_descrip.substr(idarr[0], idarr[1]);
                        newGeometry      = csv_descrip.substr(idarr[0], idarr[1]);
                        newBuildstart    = (idarr[3] - idarr[2] == 1)?-1:stoi(csv_descrip.substr(idarr[2]+1, idarr[3]-idarr[2]-1));
                        newOpening       = (idarr[4] - idarr[3] == 1)?-1:stoi(csv_descrip.substr(idarr[3]+1, idarr[4]-idarr[3]-1));
                        newClosure       = (idarr[5] - idarr[4] == 1)?-1:stoi(csv_descrip.substr(idarr[4]+1, idarr[5]-idarr[4]-1));
                    }
                    catch(const std::exception& e)
                    {
                        pOutput = nullptr;
                        N = 0;
                        return;
                    }
                    // load to list
                    tstation.data.id            =       newId;  
                    tstation.data.name          =       newName;
                    tstation.data.geometry      =       newGeometry;
                    tstation.data.buildstart    =       newBuildstart;
                    tstation.data.opening       =       newOpening;
                    tstation.data.closure       =       newClosure;
                        
                    ((TDataset*)pData)->stationList->push_back(tstation.data);
                    
                    // get size to check
                    size = ((TDataset*)pData)->stationList->getSize();
                    if (max_id  != ((TDataset*)pData)->stationList->at(size-1).id)
                    {
                        N       = 0;
                        pOutput = nullptr;
                    }
                    else
                    {
                        N       = 1;
                        pOutput = new int [N];
                        *((int*)pOutput) = max_id;   
                    } 
                }
                    break;
                case 7:
                {
                    N               = 1;
                    pOutput         = new int [N];
                    int station_id  = -1;

                    try
                    {
                        station_id = stoi(secondpara);
                    }
                    catch(const std::exception& e)
                    {
                        pOutput = nullptr;
                        N = 0;
                        return;
                    }

                    bool (*pStationIdRemove)(TStation&, int) = StationIdRemove;
                    int pos = 0;
                    bool isremoved = false;

                    if(((TDataset*)pData)->stationList->traverse(pStationIdRemove,station_id, pos)){
                        int rmPos = ((TDataset*)pData)->stationList->remove(pos);
                        if (rmPos != -1)
                        {
                            isremoved = true;
                            bool (*pStaLineIdRemove)(TStationLine&, int) = StaLineIdRemove;
                            if(((TDataset*)pData)->stalineList->traverse(StaLineIdRemove, station_id, pos)){
                              ((TDataset*)pData)->stalineList->remove(pos);  
                            }
                        }
                    }
                    if (!isremoved)
                        *((int*)pOutput) = -1;
                    else
                    {
                        *((int*)pOutput) = 0;
                    }
                    

                     

                }
                    break;
                default:
                {
                    N = 1;
                    pOutput = new int[N];
                    *((int*)pOutput) = -1;
                }
                    break;
    }
}
#pragma endregion

#pragma region Three Param Handle
void ThreeParamHandle(void* pData, void* &pOutput, int &N, string firstpara, string secondpara, string thirdpara)
{
     // handle for request with three param
    string _firstpara[] = {"SLP", "US", "RSL"};
    int firstparamID = -1;
    for (int i = 0; i < 3; ++i)
        if (firstpara == _firstpara[i])
        {
            firstparamID = i;
            break;
        }
   
    switch (firstparamID)
    {
        case 0:{
            N       = 1;
            pOutput = new int[N];
            int TrackId  = 0;
            int StationId = 0;

            try
            {
                StationId   = stoi(secondpara);
                TrackId     = stoi(thirdpara);
            }
            catch(const std::exception& e)
            {
                pOutput = nullptr;
                N = 0;
                return;
            }
            


            
            // get geometry
            string Geometry = "";
            string(*pGetgeometry)(TTrack&, int) = GetGeometry;
            Geometry = ((TDataset*)pData)->trackList->traverse(pGetgeometry,TrackId);

            // get postion
            int posArr[1000] = {0};
            int numposArr   = 1;

            for (int i = 0; i < Geometry.length(); ++i )
            {
                if (Geometry[i] == '(' || Geometry[i] == ',' || Geometry[i] == ')')
                    posArr[numposArr++] = i;
                    
            }

            // Get point
            string point = "";
            string temp = "";
            string (*pGetpoint)(TStation&, int) = GetGeometry;
            temp = ((TDataset*)pData)->stationList->traverse(pGetpoint,StationId);
            int    pointArr[2] = {0};

                // get index of '(' and ')'
            for (int i = 0; i < temp.length(); ++i)
            {
                if (temp[i] == '(' )
                    pointArr[0] = i;
                if (temp[i] == ')')
                    pointArr[1] = i;
            }

                // get point
            point = temp.substr(pointArr[0]+1, pointArr[1]-pointArr[0]-1);


            // Find index station
            int indexStation = -1;

            for (int i = 1; i < numposArr-1; ++i)
            {

                if (point == Geometry.substr(posArr[i]+1, posArr[i+1]-posArr[i]-1))
                {
                    indexStation = i-1;
                    break;
                }
                   
            }

                *((int*)pOutput) = indexStation;
        }
        break;
        case 1:{
                    N               = 1;
                    pOutput         = new int [N];
                    *((int*)pOutput) = -1;
                    int station_id;
                    try
                    {
                        station_id  = stoi(secondpara);
                    }
                    catch(const std::exception& e)
                    {
                        pOutput = nullptr;
                        N = 0;
                        return;
                    }
                    
                    
                    string  csv_descrip  = thirdpara;
                    bool iserror        = false;
                    int idarr[14]       = {0};
                    int numcomma        = 1;

                    bool (*pStationIdRemove)(TStation&, int) = StationIdRemove;
                    int pos = 0;

                    if(((TDataset*)pData)->stationList->traverse(pStationIdRemove,station_id, pos))
                    {
                        int rmPos = ((TDataset*)pData)->stationList->remove(pos);
                        if (rmPos != -1)
                        {   
                            for (int i = 0; i < csv_descrip.length()-1; ++i)
                            {
                                if (csv_descrip[i] == ',' && !iserror)
                                {
                                    idarr[numcomma++] = i;
                                }
                                if (csv_descrip[i] == '"')
                                {
                                    if (!iserror)
                                        iserror = true;
                                    else
                                        iserror = false;
                                    
                                }
                                
                            }

                            int id,buildstart,opening,closure;
                            string name, geometry;
                            try{
                                id                  = station_id;
                                name                = csv_descrip.substr(idarr[0], idarr[1]-idarr[0]);
                                geometry            = csv_descrip.substr(idarr[1]+1, idarr[2]-idarr[1]-1);
                                buildstart          = (idarr[3] - idarr[2] == 1)?-1:stoi(csv_descrip.substr(idarr[2]+1, idarr[3]-idarr[2]-1));
                                opening             = (idarr[4] - idarr[3] == 1)?-1:stoi(csv_descrip.substr(idarr[3]+1, idarr[4]-idarr[3]-1));
                                closure             = (idarr[5] - idarr[4] == 1)?-1:stoi(csv_descrip.substr(idarr[4]+1, idarr[5]-idarr[4]-1));
                            }
                            catch(const std::exception& e)
                            {
                                pOutput = nullptr;
                                N = 0;
                                return;
                            }
                            TStation tstation;

                            tstation.id            = id;
                            tstation.geometry      = geometry;
                            tstation.name          = name;
                            tstation.buildstart    = buildstart;
                            tstation.opening       = opening;
                            tstation.closure       = closure;

                            ((TDataset*)(pData))->stationList->insert(pos, tstation);

                            *((int*)pOutput) = 0;
                        } 

                    }
                    else
                    {
                        *((int*)pOutput) = -1;
                    }
     
        }
        break;
        case 2:{
            N       = 1;
            pOutput = new int[N];
            int pos         = 0;
            int station_id, LineId;
            try
            {
                station_id   = stoi(secondpara);
                LineId      = stoi(thirdpara);

            }
            catch(const std::exception& e)
            {
                pOutput = nullptr;
                N = 0;
                return;
            }
            

            
            *((int*)pOutput) = -1;
                // count num Station ID
            bool (*pRemoveStaLine)(TStationLine&, int, int) = RemoveStaLine;
            if(((TDataset*)pData)->stalineList->traverse(pRemoveStaLine, station_id, LineId,pos)){
                if(!((TDataset*)pData)->stalineList->remove(pos))
                    *((int*)pOutput) = 0;  
            }
                
            
        }
        break;
        
        default:
            break;
    }

}



#pragma endregion

#pragma region Four Param Handle
void FourParamHandle(void* pData, void* &pOutput, int &N, string firstpara, string secondpara, string thirdpara, string fourthpara)
{
    N                       = 1;
    pOutput                 = new int[N];
    *((int*)pOutput)        = -1;
    int station_id, line_id, pos;
    try{
        station_id          = stoi(secondpara); 
        line_id             = stoi(thirdpara);
        pos                 = stoi(fourthpara);
    }
    catch(const std::exception& e)
    {
        pOutput = nullptr;
        N = 0;
        return;
    }
    int index = 0;

    // count num Station ID
    bool(*pValidStationLineID)(TStationLine&, int) = ValidStationLineID;
    if(((TDataset*)pData)->stalineList->traverse(pValidStationLineID,line_id,pos,index)){
        TStationLine newStationLine;
        newStationLine.station_id = station_id;
        newStationLine.line_id = line_id;
        ((TDataset*)pData)->stalineList->insert(index, newStationLine);
        *((int*)pOutput) = 0;

    }
    

    

}

#pragma endregion
void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number

    // implement the Request

    
    pOutput = NULL;
    N       = 0;

    string  request(pRequest);
    int     numpara     = -1;
    string  _firstpara  = ""; // first param
    int     spaceArr[50] = {0};
    int     numspace    = 1;

    
    // get id of space
    for (int i = 0; i < request.length(); ++i)
    {
        if (request[i] == ' ')
        {
            spaceArr[numspace++] = i;
            
        }
    }

    _firstpara = request.substr(0, spaceArr[1]);

    
    // determine the number of paramer of invalid request

    if (_firstpara == "CL" || _firstpara == "LSC" || _firstpara == "LLC" || _firstpara == "LSL" ||
         _firstpara == "FC"    || _firstpara == "FS" || _firstpara == "IS" || _firstpara == "RS")
        numpara = 2;
    if ( _firstpara == "SLP"  || _firstpara == "US" || _firstpara == "RSL")
        numpara = 3;
    if (_firstpara == "ISL" )
        numpara = 4;

        // When CL is only one parameter
    if (_firstpara == "")
    {
        _firstpara = request;
        numpara = 1;
    }


    switch (numpara)
    {
        case 1: // 1 param
        {
            if (_firstpara == "CL")
            {
                N = 1;
                pOutput = new int[N];
                *((int*)pOutput) = ((TDataset*)pData)->lineList->getSize();
            }
        }
            break;
        case 2: // 2 param
        {
           
            string _secondpara = request.substr(spaceArr[1]+1);
            TwoParamHandle(pData, pOutput, N, _firstpara, _secondpara);
            
            
        }
            break;
        case 3: // 3 param
        {
           
            string _secondpara = request.substr(spaceArr[1] + 1,spaceArr[2]-spaceArr[1]-1);
            string _thirdpara =  request.substr(spaceArr[2]+1);
            ThreeParamHandle(pData, pOutput, N, _firstpara, _secondpara, _thirdpara);
        }
            break;
        case 4: // 4 param
        {
            string _secondpara      = request.substr(spaceArr[1] + 1,spaceArr[2]-spaceArr[1]-1);
            string _thirdpara   =  request.substr(spaceArr[2]+1, spaceArr[3]-spaceArr[2]-1);
            string _fourthpara    = request.substr(spaceArr[3]+1);

           

            FourParamHandle(pData, pOutput, N, _firstpara, _secondpara, _thirdpara, _fourthpara);
        }
            break;
        default:
            break;
    }


}

