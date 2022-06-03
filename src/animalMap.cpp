#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <strstream>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <functional>
#include "animalMap.h"
#include "rutil.h"
#include <plog/Log.h>



using namespace std;

void animalMap::inputSolITB(char* fname1, string startYear, string endYear){


  ifstream solfile(fname1);
  if(!solfile){
    cout<< "Cannot open file "<<fname1<<endl;
    exit(1);
  }
  cout<<"\ninputSolITB(): Reading file "<<fname1<<endl;
  cout<<"*****************************************************************"<< endl;

  std::string sep(";");
  std::string subStr;
  Tokenizer colData;
  string inputStr, myId, birthDateYYYYMMDD, country;
  int numDescendants,numObs, rec=0, numCol, numFound=0, numSkipped=0, numSkipped1=0;
  double sol, acc, matSol, matAcc;
  while (getline(solfile,inputStr)) 	{
    // remove Mac carriage return from argument...
    size_t foundloc = inputStr.find('\r');
    if ( foundloc != string::npos ) {
      subStr = inputStr.substr(0,foundloc);
      inputStr = subStr;
    }
    colData.getTokens(inputStr,sep);
    if(rec==0){
      numCol = colData.size();
    }
    myId  = colData[0];
    birthDateYYYYMMDD = colData[1];
    numDescendants  = atoi(colData[2].c_str());
    numObs  = atoi(colData[3].c_str());
    sol  = atof(colData[4].c_str());
    acc = atof(colData[5].c_str());
    matSol  = atof(colData[6].c_str());
    matAcc = atof(colData[7].c_str());
    country = colData[8];
    rec++;
    if(country == "che") {
      animal *aPtr = new animal(myId, birthDateYYYYMMDD, numDescendants, numObs, -9999, -9999 , sol, acc, matSol, matAcc, -9999, -9999, false, false, CONSTANTS::STRING_NA, CONSTANTS::STRING_NA); //Sophie

      if(rec%100000==0){
        cout<<rec<<" records processed \r";
        cout.flush();
      }

      map<string,animal*>::iterator ait = this->find(aPtr->indITBStr);
      if(ait == this->end()){
          (*this)[aPtr->indITBStr] = aPtr;

        LOGD<<"aPtr->indITBStr "<<aPtr->indITBStr<<" , aPtr->birthYearStr "<<aPtr->birthYearStr<<" ,aPtr->birthMonthSt "<<aPtr->birthMonthStr<<" ,aPtr->birthDayStr "<<aPtr->birthDayStr
            <<" ,aPtr->numDescendantsITB "<<aPtr->numDescendantsITB<<" ,aPtr->numObsITB "<<aPtr->numObsITB<<" ,aPtr->solITB "<<aPtr->solITB<<" ,aPtr->solMatITB "<<aPtr->solMatITB
            <<" ,aPtr->accITB "<<aPtr->accITB<<" , aPtr->matAccITB "<<aPtr->matAccITB;

        }

      //Sophie: Basis festlegen
      if(aPtr->birthYearStr >= startYear && aPtr->birthYearStr <= endYear){
        if(aPtr->sexITBStr == "M"){
          aPtr->base = true;
          LOGD<<"aPtr->indITBStr "<<aPtr->indITBStr<<" is flagged as basis animal";
        }
      }

      }

    }

  cout<<"\nTotal number of interbeef animals: "<<rec<<endl;

};


void animalMap::inputPubInfoITB(char* fname1){

  ifstream solfile(fname1);
  if(!solfile){
    cout<< "Cannot open file "<<fname1<<endl;
    exit(1);
  }

  cout<<"\ninputPubInfoITB(): Reading file "<<fname1<<endl;
  cout<<"*****************************************************************"<< endl;

  std::string sep(";");
  std::string subStr;
  Tokenizer colData;
  string inputStr, myId, birthDateYYYYMMDD, country, name, statusOfBull;
  bool itbPubld, itbPublm;
  int numDescendants,numObs, rec=0, numCol, numFound=0, numSkipped=0, numSkipped1=0, numPubl=0;
  int numDaughter, numProgrenies, numProgreniesCH, numHerdsCH;
  double sol, acc, matSol, matAcc;
  while (getline(solfile,inputStr)) 	{
    // remove Mac carriage return from argument...
    size_t foundloc = inputStr.find('\r');
    if ( foundloc != string::npos ) {
      subStr = inputStr.substr(0,foundloc);
      inputStr = subStr;
    }
    colData.getTokens(inputStr,sep);
    if(rec==0){
      numCol = colData.size();
    }
    myId  = colData[0];
    string myIdCode= myId.substr(0,1);
    if(myIdCode == " "){
      myId = myId.substr(1,myId.size());
    }
    birthDateYYYYMMDD = colData[1];
    numDescendants  = atoi(colData[2].c_str());
    numObs  = atoi(colData[3].c_str());
    numDaughter = atoi(colData[4].c_str());
    numProgrenies = atoi(colData[5].c_str());
    sol  = atof(colData[6].c_str());
    acc = atof(colData[7].c_str());
    matSol  = atof(colData[8].c_str());
    matAcc = atof(colData[9].c_str());
    country = colData[10];
    numProgreniesCH = atoi(colData[11].c_str());
    numHerdsCH= atoi(colData[12].c_str());
    itbPubld = stod(colData[13].c_str());
    itbPublm = stod(colData[15].c_str());
    statusOfBull = colData[16];
    name = colData[17];

    rec++;
    if(country == "che") {

      if(rec%100000==0){
        cout<<rec<<" records processed \r";
        cout.flush();
      }

      map<string,animal*>::iterator ait = this->find(myId);
      if(ait == this->end()){
        animal *aPtr = new animal(myId, birthDateYYYYMMDD, numDescendants, numObs, numDaughter, numProgrenies, sol, acc, matSol, matAcc, numProgreniesCH, numHerdsCH, itbPubld, itbPublm, statusOfBull, name); //Sophie
        (*this)[aPtr->indITBStr] = aPtr;

        LOGD<<"aPtr->indITBStr "<<aPtr->indITBStr<<" , aPtr->birthYearStr "<<aPtr->birthYearStr<<" ,aPtr->birthMonthSt "<<aPtr->birthMonthStr<<" ,aPtr->birthDayStr "<<aPtr->birthDayStr
            <<" ,aPtr->numDescendantsITB "<<aPtr->numDescendantsITB<<" ,aPtr->numObsITB "<<aPtr->numObsITB
            <<" , aPtr->numDaughterITB " <<aPtr->numDaughterITB<<" ,aPtr->numProgreniesIT  "<<aPtr->numProgreniesITB
            <<" ,aPtr->solITB "<<aPtr->solITB<<" ,aPtr->solMatITB "<<aPtr->solMatITB
            <<" ,aPtr->accITB "<<aPtr->accITB<<" , aPtr->matAccITB "<<aPtr->matAccITB
            <<" , aPtr->numProgreniesCHITB "<<aPtr->numProgreniesCHITB<<" ,aPtr->numHerdsCHITB "<<aPtr->numHerdsCHITB
            <<" ,aPtr->itbPubldITB "<<aPtr->itbPubldITB<<" , aPtr->itbPublmIT "<<aPtr->itbPublmITB;

      }else{
        ait->second->numDaughterITB = numDaughter;
        ait->second->numProgreniesITB = numProgrenies;
        ait->second->numProgreniesCHITB = numProgreniesCH;
        ait->second->numHerdsCHITB = numHerdsCH;
        ait->second->itbPubldITB = itbPubld;
        ait->second->itbPublmITB = itbPublm;
        ait->second->statusOfBullStr = statusOfBull;
        ait->second->nameStr = name;

        LOGD<<"ait->second->indITBStr "<<ait->second->indITBStr<<" is already in aMap therefore add some info"
            <<" , ait->second->numDaughterITB " <<ait->second->numDaughterITB<<" ,ait->second->numProgreniesIT  "<<ait->second->numProgreniesITB
            <<" , ait->second->numProgreniesCHITB "<<ait->second->numProgreniesCHITB<<" ,ait->second->numHerdsCHITB "<<ait->second->numHerdsCHITB
            <<" , ait->second->itbPubldIT "<<ait->second->itbPubldITB<<" , ait->second->itbPublmIT "<<ait->second->itbPublmITB;

      }
    }

  }

  cout<<"\nTotal number of interbeef animals in the publication file: "<<rec<<endl;

};


void animalMap::standardizeITB(double mean, double std, string outfileITB, string basisBreedYearAbreviation){

  cout<<"\nstandardizeITB(): Standardize interbeef ebvs "<<endl;
  cout<<"*****************************************************************"<< endl;

  double sumITB = 0, meanITB = 0, sumMatITB = 0, meanMatITB = 0, multiITB = 0, multiMatITB = 0, sdITB = 0, sdMatITB = 0, num = 0;
  int recd = 0, recm = 0;

  for(map<string, animal*>::iterator ait=this->begin(); ait != this->end(); ait++){
    animal* ptr = ait->second;

    if(ptr->base){
      LOGD<<"ptr->indITBStr "<<ptr->indITBStr<<" is in the base, ptr->birthYearStr "<<ptr->birthYearStr
          <<" ,ptr->solITB "<<ptr->solITB<<" ,ptr->solMatITB "<<ptr->solMatITB;

      sumITB += ptr->solITB;
      sumMatITB += ptr->solMatITB;
      multiITB += ptr->solITB * ptr->solITB;
      multiMatITB += ptr->solMatITB * ptr->solMatITB;
      num++;

      meanITB = sumITB/num;
      meanMatITB = sumMatITB/num;

      sdITB = sqrt((multiITB/num - (meanITB*meanITB))*(num/(num-1)));
      sdMatITB = sqrt((multiMatITB/num - (meanMatITB*meanMatITB))*(num/(num-1)));
    }
  }


  ofstream outFilestdfmtQualitas((outfileITB).c_str());
  if(!outFilestdfmtQualitas){
    cout<< "standardizeITB(): Cannot open file "<<outfileITB<<endl;
    exit(1);
  }
  //Not scientific notation: https://stackoverflow.com/questions/2335657/prevent-scientific-notation-in-ostream-when-using-with-double
  outFilestdfmtQualitas.setf(ios_base::fixed);
  outFilestdfmtQualitas<<"idaITB trait nDau nHerd estimate rel type label pubCode base statusOfBull name"<<endl;

  for(map<string, animal*>::iterator ait=this->begin(); ait != this->end(); ait++){
    animal* ptr = ait->second;

    ptr->scaledSolITB = (((ptr->solITB - meanITB)/sdITB)*std)+mean;
    ptr->scaledSolMatITB = (((ptr->solMatITB - meanMatITB)/sdMatITB)*std)+mean;

    LOGD<<"ptr->indITBStr "<<ptr->indITBStr<<" is standardized for interbeef-d-trait "<<ptr->scaledSolITB<<" and for interbeef-m-trait "<<ptr->scaledSolMatITB;



    if(ptr->itbPubldITB){

      outFilestdfmtQualitas<<ptr->indITBStr<<" dir "<<ptr->numDescendantsITB<<" "<<ptr->numHerdsCHITB<<" "<<setprecision(2)<<ptr->scaledSolITB<<" "<<setprecision(2)<<ptr->accITB<<" ITB "<<"I "<<"Y "<<basisBreedYearAbreviation<<" "<<ptr->statusOfBullStr<<" \""<<ptr->nameStr<<"\""<<endl;
      recd++;
      LOGD<<"ptr->indITBStr "<<ptr->indITBStr<<" is standardized direct interbeef trait and ready for publication.";

    }
    if(ptr->itbPublmITB){

      outFilestdfmtQualitas<<ptr->indITBStr<<" mat "<<ptr->numDaughterITB<<" "<<ptr->numHerdsCHITB<<" "<<setprecision(2)<<ptr->scaledSolMatITB<<" "<<setprecision(2)<<ptr->accITB<<" ITB "<<"I "<<"Y "<<basisBreedYearAbreviation<<" "<<ptr->statusOfBullStr<<" \""<<ptr->nameStr<<"\""<<endl;
      recm++;
      LOGD<<"ptr->indITBStr "<<ptr->indITBStr<<" is standardized maternal interbeef trait and ready for publication.";


    }


  }

  cout<<"\nmeanITB : "<<meanITB<<endl;
  cout<<"\nsdITB : "<<sdITB<<endl;
  cout<<"\nmeanMatITB : "<<meanMatITB<<endl;
  cout<<"\nsdMatITB : "<<sdMatITB<<endl;
  cout<<"\nnumber in basis : "<<num<<endl;

  cout<<"\nnumber of animals for the publication of interbeef direct trait ebvs : "<<recd<<endl;
  cout<<"\nnumber of animals for the publication of interbeef maternal trait ebvs : "<<recm<<endl;

}
