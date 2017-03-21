%module jCbc
%{
#include <iostream>
#include <iomanip>
#include "omp.h"
#if defined(_WIN32) || defined(WIN32) 
#include "windows.h"
#endif
#include <algorithm>
#include "pthread.h"
#include "sched.h"
#include "semaphore.h"
#include "CbcEventHandler.hpp"
#include "CoinPragma.hpp"
#include "CoinPragma.hpp"
#include "CbcModel.hpp"
#include "CoinModel.hpp"
#include "OsiClpSolverInterface.hpp"
#include "OsiSolverInterface.hpp"
#include "CbcStrategy.hpp"
#include "CglPreProcess.hpp"
#include "CoinTime.hpp"
#include "CbcHeuristicDiveCoefficient.hpp"
#include "CbcHeuristicDiveFractional.hpp"
#include "CbcHeuristicDiveGuided.hpp"
#include "CbcHeuristicDiveVectorLength.hpp"
#include "CbcHeuristicDivePseudoCost.hpp"
#include "CbcHeuristicDiveLineSearch.hpp"
#include "CbcHeuristic.hpp"
#include "CoinError.hpp"
#include "OsiCuts.hpp"
#include "CglCutGenerator.hpp"
#include "CglGomory.hpp"
#include "CglProbing.hpp"
#include "CglKnapsackCover.hpp"
#include "CglOddHole.hpp"
#include "CglMixedIntegerRounding.hpp"
#include "CglTwomir.hpp"
#include "ClpSimplex.hpp"
#include "ClpPresolve.hpp"
#include "CoinHelperFunctions.hpp"
#include "CoinBuild.hpp"
#include "CbcBranchDynamic.hpp"
#include "CbcBranchDecision.hpp"
#include "CbcBranchDefaultDecision.hpp"
#include "CbcCutGenerator.hpp"
#include "CbcHeuristicLocal.hpp"
#include "CglRedSplit.hpp"
#include "CglClique.hpp"
#include "CglFlowCover.hpp"
#include "CglMixedIntegerRounding2.hpp"
#include "CglSimpleRounding.hpp"
#include "CbcHeuristicDINS.hpp"
#include "CbcHeuristicDive.hpp"
#include "CbcHeuristicDiveLineSearch.hpp"
#include "CbcHeuristicDivePseudoCost.hpp"
#include "CbcHeuristicDW.hpp"
#include "CbcHeuristicGreedy.hpp"
#include "CbcHeuristicPivotAndFix.hpp"
#include "CbcHeuristicRandRound.hpp"
#include "CbcHeuristicRENS.hpp"
#include "CbcHeuristicVND.hpp"
#include "CglGMI.hpp"
#include "CglRedSplit2.hpp"
#include "CglResidualCapacity.hpp"
#include "CglZeroHalf.hpp"
#include "CbcTreeLocal.hpp"
#include "CbcCompare.hpp"
#include "CbcBranchActual.hpp"
#include "ClpSolve.hpp"
#include "CoinWarmStart.hpp"
#include "CbcHeuristicFPump.hpp"
#include "CbcHeuristicRINS.hpp"




/* Put header files here or function declarations like below */
extern void addCol(CoinModel *build, double collb, double colub, double obj,const char *name, bool isInt);
extern void addRows(CbcModel *model, CoinModel *build);
extern void addRow(CoinModel *build, int numberInRow, int index [], double values [], double rowlb, double rowup, const char *name);
extern void branchAndBound(CbcModel * model);
extern void readMps(CbcModel *model, const char *name);
extern void readLp(CbcModel *model, const char *name);
extern void writeMps(CbcModel *model, const char *name);
extern void writeLp(CbcModel *model, const char *name);
extern const double * getSol(CbcModel *model);
extern void setInteger(CbcModel *model, int i);
extern void addRows(OsiClpSolverInterface *solver, CoinModel *build);
extern void assignSolver(CbcModel *model, OsiClpSolverInterface *solver);
extern void readMps(OsiClpSolverInterface *solver, const char *name);
extern void readLp(OsiClpSolverInterface *solver, const char *name);
extern void setInteger(OsiClpSolverInterface *solver, int i);
extern void initialSolve(OsiClpSolverInterface *solver);
extern void setLogLevel(OsiClpSolverInterface *solver, int i);
extern void setLogLevel(CbcModel * model, int i);
extern void solve(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0);
extern void solve_1(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0);
extern int solve_2(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0);
extern int solve_3(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0,double presolve_tolerance=1e-07);
extern void writeMps(OsiClpSolverInterface *solver, const char *name);
extern void writeLp(OsiClpSolverInterface *solver, const char *name);
extern int isInteger(OsiClpSolverInterface *solver, int i);
extern int isInteger(CbcModel * model, int i);
extern std::string getRowName(OsiClpSolverInterface *solver, int i);
extern std::string getColName(OsiClpSolverInterface *solver, int i);
extern std::string getRowName(CbcModel *model, int i);
extern std::string getColName(CbcModel *model, int i);
extern int getNumRows(OsiClpSolverInterface *solver);
extern int getNumCols(OsiClpSolverInterface *solver);
extern int getNumRows(CbcModel *model);
extern int getNumCols(CbcModel *model);
extern const double * getColSolution(OsiClpSolverInterface *solver);
extern const double * getRowPrice(OsiClpSolverInterface *solver);
extern const double * getRowActivity(OsiClpSolverInterface *solver);
extern const double * getReducedCost(OsiClpSolverInterface *solver);
extern const double * getColSolution(CbcModel *model);
extern const double * getRowPrice(CbcModel *model);
extern const double * getRowActivity(CbcModel *model);
extern const double * getReducedCost(CbcModel *model);
extern int  numberIntegers(CbcModel *model);
extern const double getObjValue(CbcModel *model);
extern int status(CbcModel *model);
extern int isProvenOptimal(CbcModel *model);
extern int isProvenInfeasible(CbcModel *model);
extern void setModelName(OsiClpSolverInterface *solver, std::string name);
extern std::string getModelName(OsiClpSolverInterface *solver);
extern int isBinary(OsiClpSolverInterface *solver, int i);
extern int secondaryStatus(CbcModel *model);
extern double getCoinCpuTime();
extern const double getObjValue(OsiClpSolverInterface *solver);
extern void setRowName(OsiClpSolverInterface *solver, int i , const char *name);
extern void setPrimalTolerance(CbcModel *model, double a);
extern void setDualTolerance(CbcModel *model, double a);
extern void setIntegerTolerance(CbcModel *model, double a);
extern int solve_whs(CbcModel *model, OsiClpSolverInterface *solver, std::string names[], int values[],int intvars,  int logLevel= 0,double presolve_tolerance=1e-07);
extern int getNumIntegers(OsiClpSolverInterface *solver);
extern void writeLp1(CbcModel *model, const char *name, double epsilon=1e-5, int decimals=5 );
extern void writeMps1(CbcModel *model, const char *name, int 	formatType = 0, int numberAcross = 2,double objSense = 0.0);
extern void callCbc(std::string a,CbcModel *model);
extern void setMaximumNodes(CbcModel *model, int value);
extern void setNumberThreads(CbcModel * model,int a);
extern void setThreadMode(CbcModel * model,int a);
extern void par_solve(CbcModel *model, OsiClpSolverInterface *solver, std::string s, std::string names[] = NULL, int values[]= NULL,int intvars= 0,std::string names1[]= NULL, int values1[]= NULL,int intvars1= 0,std::string names2[]= NULL, int values2[]= NULL,int intvars2= 0);
extern void cutoff(CbcModel *model, int n);
extern int solve_unified(CbcModel *model, OsiClpSolverInterface *solver, std::string names[] = NULL, int values[] = NULL, int intvars = 0, int logLevel= 0 );
extern double getMinRHS(OsiClpSolverInterface *solver);
extern double getMinCoeff(OsiClpSolverInterface *solver);
extern double getMaxCoeff(OsiClpSolverInterface *solver);

%}

%include cpointer.i
%include "typemaps.i"
#include <utility>
#include <string>
%include carrays.i
%include <std_pair.i>
%include <std_vector.i>
%include <std_string.i>

%array_functions( double, jarray_double);
%array_functions( int, jarray_int);
%array_functions(std::string, jarray_string);
%pointer_functions(CbcModel, jCbcModel);
%pointer_functions(CoinModel, jCoinModel);
%pointer_functions(OsiClpSolverInterface, jOsiClpSolverInterface);
%pointer_functions(CoinPackedMatrix, jCoinPackedMatrix);


extern void addCol(CoinModel *build, double collb, double colub, double obj,const char *name, bool isInt);
extern void addRows(CbcModel *model, CoinModel *build);
extern void addRow(CoinModel *build, int numberInRow, int index[], double values [], double rowlb, double rowup, const char *name);
extern void branchAndBound(CbcModel * model);
extern void readMps(CbcModel *model, const char *name);
extern void readLp(CbcModel *model, const char *name);
extern void writeMps(CbcModel *model, const char *name);
extern void writeLp(CbcModel *model, const char *name);
extern const double * getSol(CbcModel *model);
extern void setInteger(CbcModel *model, int i);
extern void addRows(OsiClpSolverInterface *solver, CoinModel *build);
extern void assignSolver(CbcModel *model, OsiClpSolverInterface *solver);
extern void readMps(OsiClpSolverInterface *solver, const char *name);
extern void readLp(OsiClpSolverInterface *solver, const char *name);
extern void setInteger(OsiClpSolverInterface *solver, int i);
extern void initialSolve(OsiClpSolverInterface *solver);
extern void setLogLevel(OsiClpSolverInterface *solver, int i);
extern void setLogLevel(CbcModel * model, int i);
extern void writeMps(OsiClpSolverInterface *solver, const char *name);
extern void writeLp(OsiClpSolverInterface *solver, const char *name);
extern void solve(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0);
extern void solve_1(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0);
extern int solve_2(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0);
extern int solve_3(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0,double presolve_tolerance=1e-07);
extern int isInteger(OsiClpSolverInterface *solver, int i);
extern int isInteger(CbcModel * model, int i);
extern std::string getRowName(OsiClpSolverInterface *solver, int i);
extern std::string getColName(OsiClpSolverInterface *solver, int i);
extern std::string getRowName(CbcModel *model, int i);
extern std::string getColName(CbcModel *model, int i);
extern int getNumRows(OsiClpSolverInterface *solver);
extern int getNumCols(OsiClpSolverInterface *solver);
extern int getNumRows(CbcModel *model);
extern int getNumCols(CbcModel *model);
extern const double * getColSolution(OsiClpSolverInterface *solver);
extern const double * getRowPrice(OsiClpSolverInterface *solver);
extern const double * getRowActivity(OsiClpSolverInterface *solver);
extern const double * getReducedCost(OsiClpSolverInterface *solver);
extern const double * getColSolution(CbcModel *model);
extern const double * getRowPrice(CbcModel *model);
extern const double * getRowActivity(CbcModel *model);
extern const double * getReducedCost(CbcModel *model);
extern int  numberIntegers(CbcModel *model);
extern const double getObjValue(CbcModel *model);
extern int status(CbcModel *model);
extern int isProvenOptimal(CbcModel *model);
extern int isProvenInfeasible(CbcModel *model);
extern void setModelName(OsiClpSolverInterface *solver, std::string name);
extern std::string getModelName(OsiClpSolverInterface *solver);
extern int isBinary(OsiClpSolverInterface *solver, int i);
extern int secondaryStatus(CbcModel *model);
extern double getCoinCpuTime();
extern const double getObjValue(OsiClpSolverInterface *solver);
extern void setRowName(OsiClpSolverInterface *solver, int i , const char *name);
extern void setPrimalTolerance(CbcModel *model, double a);
extern void setDualTolerance(CbcModel *model, double a);
extern void setIntegerTolerance(CbcModel *model, double a);
extern int solve_whs(CbcModel *model, OsiClpSolverInterface *solver, std::string names[], int values[],int intvars, int logLevel= 0,double presolve_tolerance=1e-07);
extern int getNumIntegers(OsiClpSolverInterface *solver);
extern void writeLp1(CbcModel *model, const char *name, double epsilon=1e-5, int decimals=5 );
extern void writeMps1(CbcModel *model, const char *name, int 	formatType = 0, int numberAcross = 2,double objSense = 0.0);
extern void callCbc(std::string a,CbcModel *model);
extern void setMaximumNodes(CbcModel *model, int value);
extern void setNumberThreads(CbcModel * model,int a);
extern void setThreadMode(CbcModel * model,int a);
extern void par_solve(CbcModel *model, OsiClpSolverInterface *solver, std::string s, std::string names[] = NULL, int values[]= NULL,int intvars= 0,std::string names1[]= NULL, int values1[]= NULL,int intvars1= 0,std::string names2[]= NULL, int values2[]= NULL,int intvars2= 0);
extern void cutoff(CbcModel *model, int n);
extern int solve_unified(CbcModel *model, OsiClpSolverInterface *solver, std::string names[] = NULL, int values[] = NULL, int intvars = 0, int logLevel= 0 );
extern double getMinRHS(OsiClpSolverInterface *solver);
extern double getMinCoeff(OsiClpSolverInterface *solver);
extern double getMaxCoeff(OsiClpSolverInterface *solver);


