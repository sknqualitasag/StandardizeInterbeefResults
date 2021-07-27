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
            <<" ,aPtr->numDescendantsWWITB "<<aPtr->numDescendantsWWITB<<" ,aPtr->numObsWWITB "<<aPtr->numObsWWITB<<" ,aPtr->solWWITB "<<aPtr->solWWITB<<" ,aPtr->solMatWWITB "<<aPtr->solMatWWITB
            <<" ,aPtr->accWWITB "<<aPtr->accWWITB<<" , aPtr->matAccWWITB "<<aPtr->matAccWWITB;

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
            <<" ,aPtr->numDescendantsWWITB "<<aPtr->numDescendantsWWITB<<" ,aPtr->numObsWWITB "<<aPtr->numObsWWITB
            <<" , aPtr->numDaughterWWITB " <<aPtr->numDaughterWWITB<<" ,aPtr->numProgreniesWWIT  "<<aPtr->numProgreniesWWITB
            <<" ,aPtr->solWWITB "<<aPtr->solWWITB<<" ,aPtr->solMatWWITB "<<aPtr->solMatWWITB
            <<" ,aPtr->accWWITB "<<aPtr->accWWITB<<" , aPtr->matAccWWITB "<<aPtr->matAccWWITB
            <<" , aPtr->numProgreniesCHWWITB "<<aPtr->numProgreniesCHWWITB<<" ,aPtr->numHerdsCHWWITB "<<aPtr->numHerdsCHWWITB
            <<" ,aPtr->itbPubldWWIT "<<aPtr->itbPubldWWITB<<" , aPtr->itbPublmWWIT "<<aPtr->itbPublmWWITB;

      }else{
        ait->second->numDaughterWWITB = numDaughter;
        ait->second->numProgreniesWWITB = numProgrenies;
        ait->second->numProgreniesCHWWITB = numProgreniesCH;
        ait->second->numHerdsCHWWITB = numHerdsCH;
        ait->second->itbPubldWWITB = itbPubld;
        ait->second->itbPublmWWITB = itbPublm;
        ait->second->statusOfBullStr = statusOfBull;
        ait->second->nameStr = name;

        LOGD<<"ait->second->indITBStr "<<ait->second->indITBStr<<" is already in aMap therefore add some info"
            <<" , ait->second->numDaughterWWITB " <<ait->second->numDaughterWWITB<<" ,ait->second->numProgreniesWWIT  "<<ait->second->numProgreniesWWITB
            <<" , ait->second->numProgreniesCHWWITB "<<ait->second->numProgreniesCHWWITB<<" ,ait->second->numHerdsCHWWITB "<<ait->second->numHerdsCHWWITB
            <<" , ait->second->itbPubldWWIT "<<ait->second->itbPubldWWITB<<" , ait->second->itbPublmWWIT "<<ait->second->itbPublmWWITB;

      }
    }

  }

  cout<<"\nTotal number of interbeef animals in the publication file: "<<rec<<endl;

};


void animalMap::standardizeITB(double mean, double std, string outfileITB, string basisBreedYearAbreviation){

  cout<<"\nstandardizeITB(): Standardize interbeef ebvs "<<endl;
  cout<<"*****************************************************************"<< endl;

  double sumWWITB = 0, meanWWITB = 0, sumMatWWITB = 0, meanMatWWITB = 0, multiWWITB = 0, multiMatWWITB = 0, sdWWITB = 0, sdMatWWITB = 0, num = 0;
  int recd = 0, recm = 0;

  for(map<string, animal*>::iterator ait=this->begin(); ait != this->end(); ait++){
    animal* ptr = ait->second;

    if(ptr->base){
      LOGD<<"ptr->indITBStr "<<ptr->indITBStr<<" is in the base, ptr->birthYearStr "<<ptr->birthYearStr
          <<" ,ptr->solWWITB "<<ptr->solWWITB<<" ,ptr->solMatWWITB "<<ptr->solMatWWITB;

      sumWWITB += ptr->solWWITB;
      sumMatWWITB += ptr->solMatWWITB;
      multiWWITB += ptr->solWWITB * ptr->solWWITB;
      multiMatWWITB += ptr->solMatWWITB * ptr->solMatWWITB;
      num++;

      meanWWITB = sumWWITB/num;
      meanMatWWITB = sumMatWWITB/num;

      sdWWITB = sqrt((multiWWITB/num - (meanWWITB*meanWWITB))*(num/(num-1)));
      sdMatWWITB = sqrt((multiMatWWITB/num - (meanMatWWITB*meanMatWWITB))*(num/(num-1)));
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

    ptr->scaledSolWWITB = (((ptr->solWWITB - meanWWITB)/sdWWITB)*std)+mean;
    ptr->scaledSolMatWWITB = (((ptr->solMatWWITB - meanMatWWITB)/sdMatWWITB)*std)+mean;

    LOGD<<"ptr->indITBStr "<<ptr->indITBStr<<" is standardized for wwd "<<ptr->scaledSolWWITB<<" and for wwm "<<ptr->scaledSolMatWWITB;



    if(ptr->itbPubldWWITB){

      outFilestdfmtQualitas<<ptr->indITBStr<<" wwd "<<ptr->numDescendantsWWITB<<" "<<ptr->numHerdsCHWWITB<<" "<<setprecision(2)<<ptr->scaledSolWWITB<<" "<<setprecision(2)<<ptr->accWWITB<<" ITB "<<"I "<<"Y "<<basisBreedYearAbreviation<<" "<<ptr->statusOfBullStr<<" \""<<ptr->nameStr<<"\""<<endl;
      recd++;
      LOGD<<"ptr->indITBStr "<<ptr->indITBStr<<" is standardizedWWD and ready for publication.";

    }
    if(ptr->itbPublmWWITB){

      outFilestdfmtQualitas<<ptr->indITBStr<<" wwm "<<ptr->numDaughterWWITB<<" "<<ptr->numHerdsCHWWITB<<" "<<setprecision(2)<<ptr->scaledSolMatWWITB<<" "<<setprecision(2)<<ptr->accWWITB<<" ITB "<<"I "<<"Y "<<basisBreedYearAbreviation<<" "<<ptr->statusOfBullStr<<" \""<<ptr->nameStr<<"\""<<endl;
      recm++;
      LOGD<<"ptr->indITBStr "<<ptr->indITBStr<<" is standardizedWWM and ready for publication.";


    }


  }

  cout<<"\nmeanWWITB : "<<meanWWITB<<endl;
  cout<<"\nsdWWITB : "<<sdWWITB<<endl;
  cout<<"\nmeanMatWWITB : "<<meanMatWWITB<<endl;
  cout<<"\nsdMatWWITB : "<<sdMatWWITB<<endl;
  cout<<"\nnumber in basis : "<<num<<endl;

  cout<<"\nnumber of animals for the publication of interbeef weaning weight direct ebvs : "<<recd<<endl;
  cout<<"\nnumber of animals for the publication of interbeef weaning weight maternal ebvs : "<<recm<<endl;

}
