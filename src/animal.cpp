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
#include <cstring>
#include "animal.h"
#include "rutil.h"



using namespace std;

animal::  animal(string myId, string birthDateYYYYMMDD, int numDescendants, int numObs, int numDaughter, int numProgrenies, double sol, double acc, double matSol, double matAcc, int numProgreniesCH, int numHerdsCH, double itbPubld, double itbPublm, string statusOfBull, string name){ //Sophie


  indITBStr = getVerifiedITBNr(myId);
  indITBBreedStr = verifyBreed(myId);
  sexITBStr = verifySex(myId);


  if(birthDateYYYYMMDD.size() == 8){
    birthYearStr = birthDateYYYYMMDD.substr(0,4).c_str();
    birthYearInt = atoi(birthYearStr.c_str());
    if(birthYearInt < 1950) {
      birthYearInt = -9999;
      birthYearStr = "-9999";
    }
    birthMonthStr = birthDateYYYYMMDD.substr(4,2).c_str();
    birthMonthInt=atoi(birthMonthStr.c_str());
    if(birthMonthInt<1 || birthMonthInt>12) {
      birthMonthInt = -9999;
      birthMonthStr = "-9999";
    }

    birthDayStr = birthDateYYYYMMDD.substr(6,2).c_str();
    birthDayInt=atoi(birthDayStr.c_str());
    if(birthDayInt<1 || birthDayInt>31) {
      birthDayInt = -9999;
      birthDayStr = "-9999";
    }
  }
  else {
    birthYearInt = -9999;
    birthYearStr = "-9999";
    birthMonthInt = -9999;
    birthMonthStr = "-9999";
    birthDayInt = -9999;
    birthDayStr = "-9999";
  }

  numDescendantsITB = numDescendants;
  numObsITB = numObs;
  numDaughterITB = numDaughter;
  numProgreniesITB = numProgrenies;
  solITB = sol;
  accITB = acc;
  solMatITB = matSol;
  matAccITB = matAcc;
  numProgreniesCHITB = numProgreniesCH;
  numHerdsCHITB = numHerdsCH;
  itbPubldITB = itbPubld;
  itbPublmITB = itbPublm;
  statusOfBullStr = statusOfBull;
  nameStr = name;


  scaledSolITB = -9999.0;
  scaledSolMatITB = -9999.0;
  base = false;
  meanDir = 0.0;
  meanMat = 0.0;






}


//' Verification function of ITB-Nr
string animal::getVerifiedITBNr(string id){
  if (id.size() != CONSTANTS::ITB_NR_LENGTH){
    return(CONSTANTS::STRING_NA);
  }
  return(id);
}


//' Verification function of breed
string animal::verifyBreed(string id){

  // check whether first three positions of id are letters
  string breedCode = id.substr(0,CONSTANTS::BREED_CODE_LENGTH);
  // breedCode should not be numeric
  if (strspn(breedCode.c_str(), CONSTANTS::LETTERS) != CONSTANTS::BREED_CODE_LENGTH){
    return(CONSTANTS::STRING_NA);
  }

  return(breedCode);

}


//' Verification function of sex
string animal::verifySex(string id){

  string sexCode = id.substr(6,CONSTANTS::SEX_CODE_LENGTH);
  if(sexCode == "F" || sexCode == "M") return(sexCode);

}
