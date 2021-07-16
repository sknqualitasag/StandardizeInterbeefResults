#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <Rcpp.h>
#include <plog/Log.h>
#include "parmMap.h"
#include "constants.h"
#include "animalMap.h"
#include "rutil.h"

using namespace Rcpp;


enum{
  SecondLog = 1,
};


// [[Rcpp::export]]
int StandardizeInterbeefResults_main(std::string paramFileName) {

  //Time tracking
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  time_t start_time = std::chrono::system_clock::to_time_t(start);



  std::cout<<"-----------------------------------------------------------------"<< std::endl;
  std::cout << "START StandardizeInterbeefResults_main() at " << std::ctime(&start_time) << std::endl;
  std::cout<<"-----------------------------------------------------------------"<< std::endl;


  ParmMap parmMap;
  parmMap.fileName = paramFileName;
  parmMap.inputParms();

  animalMap aMap;

  char *solFileITB						            = parmMap.getCharPtr("fileSolITB");
  char *pubFileITB						            = parmMap.getCharPtr("filePubInfoITB");
  std::string outfileITB						      = parmMap.getString("fileStandardizedSolutionsITB");
  std::string startYear                   = parmMap.getString("startYearBaseYYYY");
  std::string endYear                     = parmMap.getString("endYearBaseYYYY");
  std::string basisBreedYearAbreviation        = parmMap.getString("basisBreedYearAbreviation");

  double mean = CONSTANTS::MEAN_ITB_EBV; //Sophie: schauen ob ein anderen Typ nicht geschickter waere
  double std = CONSTANTS::SD_ITB_EBV;    //Sophie: schauen ob ein anderen Typ nicht geschickter waere

  //Sophie: Falls Fehler auftretten oder als Hilfe für die Entwicklung
  //plog::init(plog::debug, "DEBUG_InterbeefWeaning.txt"); //Sophie

  aMap.inputSolITB(solFileITB, startYear, endYear);
  aMap.inputPubInfoITB(pubFileITB);
  aMap.standardizeITB(mean,std,outfileITB,basisBreedYearAbreviation);




  //Time tracking
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  std::cout<<"\n-----------------------------------------------------------------"<< std::endl;
  std::cout << "END StandardizeInterbeefResults_main() at " << std::ctime(&end_time)
  << "elapsed time: " << elapsed_seconds.count() << " s"<<std::endl;
  std::cout<<"-----------------------------------------------------------------"<< std::endl;


  return 0;
}

//With RConsole ausführen
/*** R
StandardizeInterbeefResults_main()
*/
