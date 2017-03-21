#include <iostream>
#include <iomanip>
#include <sstream>
#include "pthread.h"
#include "sched.h"
#include "semaphore.h"
#include "omp.h"
#if defined(_WIN32) || defined(WIN32) 
#include "windows.h"
#endif
#include <algorithm>
#include "CbcEventHandler.hpp"
#include "CoinPragma.hpp"
#include "CbcModel.hpp"
#include "CoinModel.hpp"
#include "OsiClpSolverInterface.hpp"
#include "OsiCbcSolverInterface.hpp"
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
#include "CbcSolver.hpp"


//=================================================================================================================
using namespace std;
int b;

class abort_exception: public exception
{
  virtual const char* what() const throw()
  {
    return "Abort exception happened";
  }
} a_e_1;

//==================================================================================================================	
/* Meaning of whereFrom:
   1 after initial solve by dualsimplex etc
   2 after preprocessing
   3 just before branchAndBound (so user can override)
   4 just after branchAndBound (before postprocessing)
   5 after postprocessing
*/
static int callBack(CbcModel * model, int whereFrom)
{
  int returnCode=0;
  switch (whereFrom) {
  case 1:
	if(b==1)
		returnCode=1;
	break;
  case 2:
    if(b==1)
		returnCode=1;
	break;
  case 3:
    if(b==1)
		returnCode=1;
	break;
    
  case 4:
    if(b==1)
		returnCode=1;
	break;
  case 5:
   if(b==1)
		returnCode=1;
	break;
  default:
    abort();
  }
  return returnCode;
}
#include "CbcEventHandler.hpp"
static int cancelAsap=0;
/*
  0 - not yet in Cbc
  1 - in Cbc with new signal handler
  2 - ending Cbc
*/
static int statusOfCbc=0;
#include "CoinSignal.hpp"
static CoinSighandler_t saveSignal = static_cast<CoinSighandler_t> (0);

extern "C" {
     static void
#if defined(_MSC_VER)
     __cdecl
#endif // _MSC_VER
     signal_handler(int /*whichSignal*/)
     {
       cancelAsap=3;
       return;
     }
}



class MyEventHandler3 : public CbcEventHandler {
  
public:
  /**@name Overrides */
  //@{
  virtual CbcAction event(CbcEvent whichEvent);
  //@}

  /**@name Constructors, destructor etc*/
  //@{
  /** Default constructor. */
  MyEventHandler3();
  /// Constructor with pointer to model (redundant as setEventHandler does)
  MyEventHandler3(CbcModel * model);
  /** Destructor */
  virtual ~MyEventHandler3();
  /** The copy constructor. */
  MyEventHandler3(const MyEventHandler3 & rhs);
  /// Assignment
  MyEventHandler3& operator=(const MyEventHandler3 & rhs);
  /// Clone
  virtual CbcEventHandler * clone() const ;
  //@}
   
    
protected:
  // data goes here
};
//-------------------------------------------------------------------
// Default Constructor 
//-------------------------------------------------------------------
MyEventHandler3::MyEventHandler3 () 
  : CbcEventHandler()
{
}

//-------------------------------------------------------------------
// Copy constructor 
//-------------------------------------------------------------------
MyEventHandler3::MyEventHandler3 (const MyEventHandler3 & rhs) 
: CbcEventHandler(rhs)
{  
}

// Constructor with pointer to model
MyEventHandler3::MyEventHandler3(CbcModel * model)
  : CbcEventHandler(model)
{
}

//-------------------------------------------------------------------
// Destructor 
//-------------------------------------------------------------------
MyEventHandler3::~MyEventHandler3 ()
{
}

//----------------------------------------------------------------
// Assignment operator 
//-------------------------------------------------------------------
MyEventHandler3 &
MyEventHandler3::operator=(const MyEventHandler3& rhs)
{
  if (this != &rhs) {
    CbcEventHandler::operator=(rhs);
  }
  return *this;
}
//-------------------------------------------------------------------
// Clone
//-------------------------------------------------------------------
CbcEventHandler * MyEventHandler3::clone() const
{
  return new MyEventHandler3(*this);
}

CbcEventHandler::CbcAction 
MyEventHandler3::event(CbcEvent whichEvent)
{
  if (b==1) {
      return stop; // say finished
    } else {
      return noAction; // carry on
	  
    }
  
}


class MyEventHandler4 : public ClpEventHandler {
  
public:
  /**@name Overrides */
  //@{
  virtual int event(Event whichEvent);
  //@}

  /**@name Constructors, destructor etc*/
  //@{
  /** Default constructor. */
  MyEventHandler4();
  /// Constructor with pointer to model (redundant as setEventHandler does)
  MyEventHandler4(ClpSimplex * model);
  /** Destructor */
  virtual ~MyEventHandler4();
  /** The copy constructor. */
  MyEventHandler4(const MyEventHandler4 & rhs);
  /// Assignment
  MyEventHandler4& operator=(const MyEventHandler4 & rhs);
  /// Clone
  virtual ClpEventHandler * clone() const ;
  //@}
   
    
protected:
  // data goes here
};
//-------------------------------------------------------------------
// Default Constructor 
//-------------------------------------------------------------------
MyEventHandler4::MyEventHandler4 () 
  : ClpEventHandler()
{
}

//-------------------------------------------------------------------
// Copy constructor 
//-------------------------------------------------------------------
MyEventHandler4::MyEventHandler4 (const MyEventHandler4 & rhs) 
: ClpEventHandler(rhs)
{  
}

// Constructor with pointer to model
MyEventHandler4::MyEventHandler4(ClpSimplex * model)
  : ClpEventHandler(model)
{
}

//-------------------------------------------------------------------
// Destructor 
//-------------------------------------------------------------------
MyEventHandler4::~MyEventHandler4 ()
{
}

//----------------------------------------------------------------
// Assignment operator 
//-------------------------------------------------------------------
MyEventHandler4 &
MyEventHandler4::operator=(const MyEventHandler4& rhs)
{
  if (this != &rhs) {
    ClpEventHandler::operator=(rhs);
  }
  return *this;
}
//-------------------------------------------------------------------
// Clone
//-------------------------------------------------------------------
ClpEventHandler * MyEventHandler4::clone() const
{
  return new MyEventHandler4(*this);
}

int
MyEventHandler4::event(Event whichEvent)
{
   //if ( (cancelAsap&1)!=0 ) {
	if ( b==1 ) {   
    //printf("Clp got cancel\n");
    return 5;
  } else {
    return -1;
  }
}


//=============================================================================================================
// CoinModel build objects
void addCol(CoinModel *build, double collb, double colub, double obj, const char *name, bool isInt){
	build->addCol(0,NULL,NULL,collb,colub,obj,name, isInt);}

void addRow(CoinModel *build, int numberInRow, int index [], double values [], double rowlb, double rowup, const char *name){
	
	build->addRow(numberInRow, (const int*) index, values, rowlb,rowup,name);
	
	}
	
	
// Add rows at once to OsiClpSolverInterface
void addRows(OsiClpSolverInterface *solver, CoinModel *build){solver->loadFromCoinModel(*build);}

//set Integer variables in OsiClpSolverInterface
void setInteger(OsiClpSolverInterface *solver, int i){solver->setInteger(i);}

// Assign OsiClpSolverInterface to CbcModel
void assignSolver(CbcModel *model, OsiClpSolverInterface *solver){
		OsiSolverInterface * solver1 = solver;
		model->assignSolver(solver1);
		delete[] solver1;
}

// Reading/Writing Lp/Mps with OsiClpSolverInterface
void readMps(OsiClpSolverInterface *solver, const char *name){solver->readMps(name,"");}
void readLp(OsiClpSolverInterface *solver, const char *name){
//	try{
	solver->setLogLevel(0);solver->readLp(name);
//	} catch(CoinError e){
//		e.print();
//	}
	}
void writeMps(OsiClpSolverInterface *solver, const char *name){solver->writeMps(name);}
void writeLp(OsiClpSolverInterface *solver, const char *name){solver->writeLp(name);}




// CbcModel functions
void branchAndBound(CbcModel * model){model->branchAndBound();}
void setLogLevel(CbcModel * model, int i){model->setLogLevel(i);}


//=========================================================================================================
//solvers
void solve(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0){
	CbcMain0(*model);
	model->setLogLevel(logLevel);
    const char * argv2[]={"driver3","-strong","5","-heuristicsOnOff","off","-presolve","off","-cutsOnOff","off","-primalS","-preprocess","off","-tune","100000000","-passc","1","-feas","off","-rins","off","-solve","-quit"};
    CbcMain1(22,argv2,*model);
}

void solve_1(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0){
// Set strategy - below is == CbcStrategyDefault()
	OsiSolverInterface * solver2= solver;
	CbcModel model1(*solver2);
	
	/*model->assignSolver(solver2);
	model->solver()->setIntParam(OsiNameDiscipline,1);
  CbcStrategyDefault strategy(true,5,5);
  model->setStrategy(strategy);
  // Do complete search
  model->setLogLevel(logLevel);
  model->branchAndBound();*/
  CbcStrategyDefault strategy;
  model1.setStrategy(strategy);
  model1.branchAndBound();
  model->gutsOfCopy(model1, 2);
  model->setProblemStatus(model1.status());
  model->setSecondaryStatus(model1.secondaryStatus());
  
  
}

double round(double a,int n){
	int temp = pow(10.,n);
	double temp1 = a*temp;
	double temp2 = temp1-floor(temp1);
	if (temp2 <= 0.5) 
		return floor(temp1)/temp; 
	else
		return ceil(temp1)/temp; 
	
}

void cutoff(CbcModel *model, int n){
	const CoinPackedMatrix *B = model->solver()->getMatrixByCol();
	int nnz = B->getNumElements();
	const double *el=B->getElements();
	double *el_new = new double[nnz];
	for (int i=0;i<nnz;i++){
		el_new[i]=round(el[i],11);
	}
	CoinPackedMatrix *A=new CoinPackedMatrix(true,B->getMinorDim(),B->getMajorDim(),nnz,el_new,B->getIndices(),B->getVectorStarts(), B->getVectorLengths());
	model->solver()->replaceMatrix(*A);
}

int solve_2(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0){


	solver->setHintParam(OsiDoDualInInitial,true,OsiHintTry);
	//solver->setHintParam(OsiDoScale,true,OsiHintTry);
	solver->setLogLevel(logLevel);
		
	//int n = solver->getNumCols();
	//cout << "-----------NumVars = " << n << " --------------\n"; 
	//std::string * Names = new std::string[n];
	 //double time = CoinCpuTime();
	 OsiClpSolverInterface temp = OsiClpSolverInterface(*solver);
	 
  OsiSolverInterface *solver2 = solver;
  CglPreProcess *process = new CglPreProcess;
  process->messageHandler()->setLogLevel(logLevel);
  solver2 = process->preProcess(*solver,false,2);
  //model.assignSolver(solver2);
  if(solver2)
	  cout << " ";
  else{
	  //model most probably infeasible but double check!
	  OsiSolverInterface *temp1= &temp;
	  CbcModel model1(*temp1);
	  
	  
	  
	  model1.branchAndBound();
	  
	  if (model1.isProvenInfeasible()){
		  //model->gutsOfCopy(model1, 2);
		  model->setProblemStatus(0);
			model->setSecondaryStatus(1);
			cout << " \nmodel infeasible\n";
			delete process;
			return 0;
	  } 
	  if (model1.isProvenOptimal()) {
		  *solver=OsiClpSolverInterface(temp);
		  const double * sol = model1.getColSolution();
		  double Obj = model1.getObjValue();
		  int nCols = model1.getNumCols();
		  model->setBestSolution(sol, nCols,Obj,true);
		  model->gutsOfCopy(model1, 2);
		  
		  
		  model->setProblemStatus(0);
			model->setSecondaryStatus(0);
		  delete process;
		  //cout << "=====================" <<model->isProvenInfeasible() << " =======" << model->isProvenOptimal() <<endl;
		  return 1;
	  }
	 }
  
  
    //solver2->initialSolve();
    //solver2->resolve();
  
    CbcModel model1(*solver2);
	//model1.solver()->setIntParam(CbcOsiParam::DUALBOUND,1000000);
	model1.solver()->setHintParam(OsiDoDualInInitial,true,OsiHintTry);
	//model1.solver()->setHintParam(OsiDoScale,true,OsiHintTry);
	model1.setLogLevel(logLevel);
	model1.messageHandler()->setLogLevel(logLevel);
	model1.solver()->messageHandler()->setLogLevel(logLevel);
	model1.setMaximumNodes(model->getMaximumNodes());
	model1.setThreadMode(model->getThreadMode());
	model1.setNumberThreads(model->getNumberThreads());
	model1.setIntegerTolerance(model->getIntegerTolerance());
  	//CbcMain0(model1);
	//model1.solver()->initialSolve();
	
	model1.initialSolve();
    
  
  //================================================================================================================
  /*
  CglProbing generator1;
  generator1.setUsingObjective(true);
  generator1.setMaxPass(1);
  generator1.setMaxPassRoot(5);
  // Number of unsatisfied variables to look at
  generator1.setMaxProbe(10);
  generator1.setMaxProbeRoot(1000);
  // How far to follow the consequences
  generator1.setMaxLook(50);
  generator1.setMaxLookRoot(500);
  // Only look at rows with fewer than this number of elements
  generator1.setMaxElements(200);
  generator1.setRowCuts(3);

  CglGomory generator2;
  // try larger limit
  generator2.setLimit(300);

  CglKnapsackCover generator3;

  CglRedSplit generator4;
  // try larger limit
  generator4.setLimit(200);

  CglClique generator5;
  generator5.setStarCliqueReport(false);
  generator5.setRowCliqueReport(false);

  CglMixedIntegerRounding2 mixedGen;
  CglFlowCover flowGen;
  
  CglGMI cut1;
  CglMixedIntegerRounding2 cut2;
  CglOddHole cut3;
  CglSimpleRounding cut4;
  CglResidualCapacity cut5;
  CglTwomir cut6;
  CglZeroHalf cut7;
  
  
  // Add in generators
  // Experiment with -1 and -99 etc
  model1.addCutGenerator(&generator1,-1,"Probing");
  model1.addCutGenerator(&generator2,-1,"Gomory");
  model1.addCutGenerator(&generator3,-1,"Knapsack");
  model1.addCutGenerator(&generator4,-1,"RedSplit");
  model1.addCutGenerator(&generator5,-1,"Clique");
  model1.addCutGenerator(&flowGen,-1,"FlowCover");
  model1.addCutGenerator(&mixedGen,-1,"MixedIntegerRounding");
  model1.addCutGenerator(&cut1,-1,"GMI");
  model1.addCutGenerator(&cut2,-1,"MixedIntegerRounding2");
  model1.addCutGenerator(&cut3,-1,"OddHole");
  model1.addCutGenerator(&cut4,-1,"SimpleRounding");
  model1.addCutGenerator(&cut5,-1,"ResidualCapacity");
  model1.addCutGenerator(&cut6,-1,"Twomir");
  model1.addCutGenerator(&cut7,-1,"ZeroHalf");
  
 */
  // Uncommenting this should switch off all CBC messages
  // model1.messagesPointer()->setDetailMessages(10,10000,NULL);
  // Allow rounding heuristic

  //CbcRounding heuristic1(model1);
  //CbcHeuristicLocal heuristic2(model1);
	
	//CbcHeuristicDiveLineSearch heuristic3(model1);
	//CbcHeuristicDivePseudoCost heuristic4(model1);
	//CbcHeuristicDiveVectorLength heuristic5(model1);
	//CbcHeuristicDW heuristic6(model1);
	
	//CbcHeuristicLocal heuristic8(model1);
	//CbcHeuristicPivotAndFix heuristic9(model1);
	//CbcHeuristicRENS heuristic10(model1);
	//CbcHeuristicVND heuristic11(model1);
	
    
  
 //model1.addHeuristic(&heuristic1);
  //model1.addHeuristic(&heuristic2);
	//model1.addHeuristic(&heuristic3);
	//model1.addHeuristic(&heuristic4);
	//model1.addHeuristic(&heuristic5);
	//model1.addHeuristic(&heuristic6);
	
	//model1.addHeuristic(&heuristic8);
	//model1.addHeuristic(&heuristic9);
	//model1.addHeuristic(&heuristic10);
	//model1.addHeuristic(&heuristic11);
  
  // Do initial solve to continuous
  //model1.initialSolve();

  // Could tune more
  double objValue = model1.solver()->getObjSense()*model1.solver()->getObjValue();
  double minimumDropA=CoinMin(1.0,fabs(objValue)*1.0e-3+1.0e-4);
  double minimumDrop= fabs(objValue)*1.0e-4+1.0e-4;
  //printf("min drop %g (A %g)\n",minimumDrop,minimumDropA);
  model1.setMinimumDrop(minimumDrop);

  
  
    model1.setMaximumCutPassesAtRoot(50); // use minimum drop
	model1.setMaximumCutPasses(1000);
  // Switch off strong branching if wanted
  // model1.setNumberStrong(0);
  // Do more strong branching if small
  
    
  model1.setNumberStrong(8);
  
  model1.setNumberBeforeTrust(5);

  model1.solver()->setIntParam(OsiMaxNumIterationHotStart,100);

 
 
    model1.messageHandler()->setLogLevel(logLevel);
    model1.solver()->messageHandler()->setLogLevel(logLevel);
  

  // Default strategy will leave cut generators as they exist already
  // so cutsOnlyAtRoot (1) ignored
  // numberStrong (2) is 5 (default)
  // numberBeforeTrust (3) is 5 (default is 0)
  // printLevel (4) defaults (0)
  //CbcStrategyDefault strategy(5);
  
  //  strategy.setupPreProcessing(2);
  //model1.setStrategy(strategy);
	model1.setLogLevel(logLevel);
  
  model1.findCliques(true,10,20);
 model1.setTypePresolve(2);
 //model1.setSpecialOptions(4);
 model1.setMoreSpecialOptions(16777216);
 model1.setMoreSpecialOptions(32768);
 model1.setMoreSpecialOptions(1024);
model1.setMoreSpecialOptions2(1);
model1.setMoreSpecialOptions2(128); 
//model1.setMoreSpecialOptions2(8192); 

 
  //================================================================================================================
  //CbcTreeLocal localTree(&model,model.solver()->getColSolution(),10,0,50,10000,2000);
  //model.passInTreeHandler(localTree);
  
  //CbcStrategyDefault strategy;
  //model1.setStrategy(strategy);
  model1.branchAndBound();
  
  
  OsiSolverInterface * solver3;
  
  process->postProcess(*model1.solver());
  
  solver3 = solver;
  
  model->gutsOfCopy(model1, 2);
  
  model->setProblemStatus(model1.status());
	model->setSecondaryStatus(model1.secondaryStatus());
  
  
  //CbcModel *temp = model;
  //temp = model;
  //model1.assignSolver(solver3);
  //model = model1.clone(true);
  //model = model1;
  
  
  //model1.gutsOfDestructor();
  
  
  
    
 if (model1.isProvenOptimal()){
	  model->setProblemStatus(0);
	  model->setSecondaryStatus(0);
	
  }
  
  if(model1.isProvenInfeasible()){
		 
		   model->setProblemStatus(0);
			model->setSecondaryStatus(1);
	  }
	  
  delete process;
  return 2;
}


int solve_3(CbcModel *model, OsiClpSolverInterface *solver, int logLevel= 0,double presolve_tolerance=1e-07){

   model->setLogLevel(logLevel);
   solver->setLogLevel(logLevel);
   ClpSimplex *simplex = solver->getModelPtr();
  
  ClpPresolve pinfo;
  double time_2 = CoinCpuTime();
  ClpSimplex * simplex2 = pinfo.presolvedModel(*simplex,presolve_tolerance,true,5,false,false);	
  double time_3 = CoinCpuTime() - time_2;
  //cout << "Presolve= "<< time_3 << "\n";
  
  
  int status = 0;
  if(simplex2){
	  simplex2->setLogLevel(logLevel);
	  status = simplex2->status();
  }
 if(!simplex2 || status == 1 || status == 2){
	  model->setProblemStatus(0);
  model->setSecondaryStatus(1);
  cout << " \nmodel infeasible\n";
  return 1;
  }

 
   OsiClpSolverInterface solver2(simplex2);
   solver2.messageHandler()->setLogLevel(logLevel);


	 CbcModel model1(solver2);
	 model1.setLogLevel(logLevel);
	 model1.solver()->messageHandler()->setLogLevel(logLevel);
	model1.setMaximumNodes(model->getMaximumNodes());
	model1.setThreadMode(model->getThreadMode());
	model1.setNumberThreads(model->getNumberThreads());
	model1.setIntegerTolerance(model->getIntegerTolerance());

	 double time = CoinCpuTime();
	//model1.setLogLevel(logLevel);
	//CbcMain0(model1);
	model1.setLogLevel(logLevel);
    //const char * argv2[]={"driver3","-strong","0","-passC","1","-rins","off" ,"-feas","off","-tune","1000000","-solve","-quit"};
    //CbcMain1(13,argv2,model1);
	//CbcStrategyDefault strategy;
    //model1.setStrategy(strategy);
	model1.branchAndBound();
	double time1 = CoinCpuTime() - time;
	//cout << "Branch and bound time = "<< time1<< endl;
	
	
	OsiClpSolverInterface * clpSolver = dynamic_cast<OsiClpSolverInterface *> (model1.solver());
  assert (clpSolver);
  
  clpSolver->setLogLevel(logLevel);
  ClpSimplex * clp = clpSolver->getModelPtr();
  
  clp->setLogLevel(logLevel);
  *simplex2 = *clp;
  double time4 = CoinCpuTime();
  simplex2->checkSolution();
  
  pinfo.postsolve(true);
 //cout << "postsolve" <<  CoinCpuTime() - time4;
     

  const int * original = pinfo.originalColumns();
  double * lower2 = simplex2->columnLower();
  double * upper2 = simplex2->columnUpper();
  const char * info2 = simplex2->integerInformation();
  double * lower = simplex->columnLower();
  double * upper = simplex->columnUpper();
  int i;
  
  for (i=0;i<simplex2->numberColumns();i++) {
   // if (info2[i]) {
      int iSeq = original[i];
      upper[iSeq]=upper2[i];
      lower[iSeq]=lower2[i];
   //
   }
  
  //simplex->dual();
  model->gutsOfCopy(model1,2);
	model->setProblemStatus(model1.status());
		model->setSecondaryStatus(model1.secondaryStatus());
	
	  
	  if (model1.solver()->isProvenOptimal()){
		  model->setProblemStatus(0);
	  model->setSecondaryStatus(0);
	  }
	 else if(model1.isProvenInfeasible()){
		 
		   model->setProblemStatus(0);
			model->setSecondaryStatus(1);
	  }
	 delete simplex2;
	 
	 return 0;
			

}



//============================================================================================================================

// OsiClpSolverInterface functions
void initialSolve(OsiClpSolverInterface *solver){solver->initialSolve();}
void setLogLevel(OsiClpSolverInterface *solver, int i){solver->setLogLevel(i);}
int isInteger(OsiClpSolverInterface *solver, int i){return solver->isInteger(i); }
int isBinary(OsiClpSolverInterface *solver, int i){return solver->isBinary(i); }

// All these methods can also be done using OsiClpSolverInterface, with CbcModel it will probably take longer time.
const double * getSol(CbcModel *model){return model->solver()->getColSolution();}
int isInteger(CbcModel *model, int i){return model->isInteger(i); }

void addRows(CbcModel *model, CoinModel *build){
	OsiClpSolverInterface *solver1;
    solver1=new OsiClpSolverInterface;
    OsiSolverInterface * solver = solver1;
	solver->loadFromCoinModel(*build);
	model->assignSolver(solver);
	delete[] solver, solver1;
}

void readMps(CbcModel *model, const char *name){model->solver()->readMps(name,"");}
void readLp(CbcModel *model, const char *name){model->solver()->readLp(name);}
void writeMps(CbcModel *model, const char *name){model->solver()->writeMps(name);}
void writeLp(CbcModel *model, const char *name){model->solver()->writeLp(name);}
void setInteger(CbcModel *model, int i){model->solver()->setInteger(i);}

//Names
std::string getRowName(OsiClpSolverInterface *solver, int i){return solver->getRowName(i);}
std::string getColName(OsiClpSolverInterface *solver, int i){return solver->getColName(i);}
std::string getRowName(CbcModel *model, int i){return model->solver()->getRowName(i);}
std::string getColName(CbcModel *model, int i){return model->solver()->getColName(i);}
void setModelName(OsiClpSolverInterface *solver, std::string name){solver->setStrParam(OsiProbName,name);}
std::string  getModelName(OsiClpSolverInterface *solver){
	std::string temp;
	solver->getStrParam(OsiProbName,temp);
	return temp;
	}

//problem status
int status(CbcModel *model){return model->status();}//returns 0 if finished (which includes the case 
													//when the algorithm is finished because it has been proved infeasible), 
													//1 if stopped by user, and 2 if difficulties arose.
int isProvenOptimal(CbcModel *model){return model->isProvenOptimal();}
int isProvenInfeasible(CbcModel *model){return model->isProvenInfeasible();}
int secondaryStatus(CbcModel *model){return model->secondaryStatus();}
/*  cbc secondary status of problem
        -1 unset (status_ will also be -1)
	0 search completed with solution
	1 linear relaxation not feasible (or worse than cutoff)
	2 stopped on gap
	3 stopped on nodes
	4 stopped on time
	5 stopped on user event
	6 stopped on solutions
	7 linear relaxation unbounded*/

//problem stats
int getNumRows(OsiClpSolverInterface *solver){return solver->getNumRows();}
int getNumCols(OsiClpSolverInterface *solver){return solver->getNumCols();}
int getNumRows(CbcModel *model){return model->getNumRows();}
int getNumCols(CbcModel *model){return model->getNumCols();}

int  numberIntegers(CbcModel *model){return model->numberIntegers();}

//solution
const double * getColSolution(OsiClpSolverInterface *solver){return solver->getColSolution();}
const double * getRowPrice(OsiClpSolverInterface *solver){return solver->getRowPrice();}
const double * getRowActivity(OsiClpSolverInterface *solver){return solver->getRowActivity();}
const double * getReducedCost(OsiClpSolverInterface *solver){return solver->getReducedCost();}

const double * getColSolution(CbcModel *model){return model->bestSolution();}
const double * getRowPrice(CbcModel *model){return model->getRowPrice();}
const double * getRowActivity(CbcModel *model){return model->getRowActivity();}
const double * getReducedCost(CbcModel *model){return model->getReducedCost();}

const double getObjValue(CbcModel *model){return model->solver()->getObjValue();} 
const double getObjValue(OsiClpSolverInterface *solver){return solver->getObjValue();} 

//time
double getCoinCpuTime(){return CoinCpuTime();}

//CoinPackedMatrix
void loadProblem(OsiClpSolverInterface *solver, CoinPackedMatrix *byRow, double  columnLower[], double columnUpper[], 
			double objective[], double rowLower[], double rowUpper[]){
				
				solver->loadProblem(*byRow,columnLower, columnUpper, objective,rowLower, rowUpper);	
				
			}

CoinPackedMatrix * createMatrix( int numberColumns, int numberRows, int numberElements ,
								double elementByRow[], int column[], int rowStart[]){
									
	CoinPackedMatrix * M = new CoinPackedMatrix(false, numberColumns, numberRows, 
											numberElements ,elementByRow, (const int*)column, (const int*)rowStart, NULL);
									return M;
								}

void setRowName(OsiClpSolverInterface *solver, int i , const char *name){
	solver->setRowName(i,name);
}


//tolerances
void setPrimalTolerance(CbcModel *model, double a){
	model->solver()->setDblParam(OsiPrimalTolerance, a);
}

void setDualTolerance(CbcModel *model, double a){
	model->solver()->setDblParam(OsiDualTolerance, a);
}

void setIntegerTolerance(CbcModel *model, double a){
	model->setIntegerTolerance(a);
}

void test(std::pair<std::string, int> a){
	cout << a.first << " + " << a.second;
}

void test1(std::vector<std::pair<std::string, int> > a){
	cout << a.at(0).first << " + " << a.at(1).second;
}

int solve_whs(CbcModel *model, OsiClpSolverInterface *solver, std::string names[], int values[],int intvars, int logLevel= 0,double presolve_tolerance=1e-07){
//	try{ 
	
	//std::vector< std::pair< std::string, double > > A;
	
   model->setLogLevel(logLevel);
   solver->setLogLevel(logLevel);
   ClpSimplex *simplex = solver->getModelPtr();
  
   
   int numCols = solver->getNumCols();
   ClpPresolve pinfo;
   ClpSimplex * simplex2 = pinfo.presolvedModel(*simplex,presolve_tolerance,true,5,false,false);	
  
   
  
  int status = 0;
  if(simplex2){
	  simplex2->initialSolve();
	  
	  
	  simplex2->setLogLevel(logLevel);
	  status = simplex2->status();
  }
  
  if(!simplex2 || status == 1 || status == 2){
	  model->setProblemStatus(0);
  model->setSecondaryStatus(1);
  cout << " \nmodel infeasible\n";
  return 1;
  }
  
  bool whs = false;
  const double * sol0 = NULL;
	
  ClpSimplex *simplex_cpy = new ClpSimplex(*simplex2);
  OsiClpSolverInterface solver1(simplex_cpy);
  double * obj = simplex2->objective();
  double obj_val = 0.0;
 
  	
  
//  int priority[solver1.getNumCols()];
//  for (int i=0;i<solver1.getNumIntegers();i++)
//		priority[i]=0;
  
if (intvars > 0){ 
	
	 const double * UB = solver1.getColUpper();
	 const double * LB = solver1.getColLower();
	 
	 for (int i=0;i<solver1.getNumCols();i++){
		 solver1.setObjCoeff(i,0);
			if (solver1.isInteger(i)){
				for (int k=0;k<intvars;k++){
					if (solver1.getColName(i) == names[k]){
						if (UB[i]>LB[i]){
						solver1.setColLower(i,values[k]);
						solver1.setColUpper(i,values[k]);
						
						//if (values[k]==1)
						//	priority[i]=-1;
						//else
						//	priority[i]=1;
					}
					}
				}
			}
	 }
	 
	// CbcModel model2(solver1);
	 //model2.setIntParam(CbcModel::CbcMaxNumSol,1);
	 solver1.setLogLevel(0);
	 solver1.messageHandler()->setLogLevel(0);
	 solver1.branchAndBound();
	 //CbcMain0(model2);
	//model2.setLogLevel(logLevel);
    //const char * argv2[]={"-heuristicsOnOff off","-presolve","off","-cutsOnOff","off","-primalS","-preprocess","off","-maxSo","1","-solve","-quit"};
    //CbcMain1(12,argv2,model2);
	 
	 
	 if(!solver1.isProvenPrimalInfeasible() && !solver1.isProvenDualInfeasible()){
		sol0 = solver1.getColSolution();
		
		int nCols = solver1.getNumCols();
		for (int i=0 ; i < nCols ; i++)
			obj_val = obj_val + sol0[i]*obj[i];
		
		whs = true;
		//CbcModel model_fake(solver1);
		 //A = model_fake.getMIPStart();
	 }
	 else {
	 cout << "\\warm start solution infeasible\\";
	 delete simplex_cpy;
			delete simplex2;
		 return 1;
	 }
	 
	} 
	
	//const double *a = simplex2->getObjCoefficients();
	//int b[simplex2->getNumCols()]; 
	//for (int i = 0;i<simplex2->getNumCols();i++)
	//b[i]=i;
	//simplex2->addRow(simplex2->getNumCols(),b,a,-COIN_DBL_MAX,solver1.getObjValue());
	
   OsiClpSolverInterface solver2(simplex2);
   solver2.messageHandler()->setLogLevel(logLevel);

	
	
	
	 CbcModel model1(solver2);
	 model1.setLogLevel(logLevel);
	 model1.solver()->messageHandler()->setLogLevel(logLevel);
	 model1.setLogLevel(logLevel);
	model1.setMaximumNodes(model->getMaximumNodes());
	model1.setThreadMode(model->getThreadMode());
	model1.setNumberThreads(model->getNumberThreads());
	model1.setIntegerTolerance(model->getIntegerTolerance());
     //model1.initialSolve();
	

/*
 for (int i=0;i<model1.solver()->getNumCols();i++){
		 
			if (model1.solver()->isInteger(i)){
				//cout << model1.solver()->getColName(i) << " = " << sol_tmp[i]<<endl;
			if (model1.solver()->getColName(i) =="int_hands" || model1.solver()->getColName(i) =="c_sac093intflow" ||model1.solver()->getColName(i) =="int_sac_below" ||model1.solver()->getColName(i) =="int_whs_stor_chg" ||model1.solver()->getColName(i) =="int_ibu_uwfe" )
							priority[i]=0;
			else if (model1.solver()->getColName(i) =="int_sweir"  || model1.solver()->getColName(i) =="int_fweir1"  || model1.solver()->getColName(i) =="int_fweir2"  || model1.solver()->getColName(i) =="int_tweir")		
				priority[i]=0;
			else 
				priority[i]=1;
				
			}
	 }
 
 */
	
	 	 
if(whs){  
	
	//cout << "whs : " << solver1.getObjValue() << "\n";
    model1.setHotstartSolution(sol0 /*, priority */);
	model1.setBestSolution(sol0,solver1.getNumCols(),obj_val);
	model1.setBestObjectiveValue(obj_val);
	//model1.setMIPStart(A);
	
}
	
	//model1.setSpecialOptions(4);
	//model1.setMoreSpecialOptions(1024);
	//model1.passInPriorities(priority, false);
	
	double time = CoinCpuTime();
	
	//CbcMain0(model1);
	model1.setLogLevel(logLevel);
    //const char * argv2[]={"-heuristicsOnOff off","-presolve","off","-cutsOnOff","off","-primalS","-preprocess","off","-tune","100000000","-passc","1","-feas","off","-rins","off","-solve","-quit"};
    //CbcMain1(18,argv2,model1);
	
	//stringstream convert; 
	//convert << logLevel;
	//string Result = convert.str();
	//string log = "-log " + Result;
	
	//callCbc(log+" -heuristicsOnOff off -presolve off -cutsOnOff off -primalS -preprocess off  -branch -quit",model1);

	//CbcMain0(model1);
	model1.setLogLevel(logLevel);
    //const char * argv2[]={"driver3","-preprocess","off","-passC","1","-rins","off" ,"-feas","off","-tune","1000000","-solve","-quit"};
    //CbcMain1(13,argv2,model1);
	//CbcStrategyDefault strategy;
    //model1.setStrategy(strategy);
 model1.findCliques(true,10,20);
 model1.setTypePresolve(2);
 model1.setMoreSpecialOptions(16777216);
 model1.setMoreSpecialOptions(32768);
 model1.setMoreSpecialOptions2(1);
 model1.setMoreSpecialOptions2(128); 
	model1.setMaximumCutPassesAtRoot(1); 
//	model1.setSpecialOptions(4);
	model1.branchAndBound();
	//cout << "model1 " << model1.getObjValue() << "\n";
	
	

	if (model1.solver()->isProvenPrimalInfeasible() == 1){
		cout << "\nModel Infeasible\n";
		model->setProblemStatus(0);
		model->setSecondaryStatus(1);
		delete simplex2;
		delete simplex_cpy;
		return 1;
		
	}
	
	double time1 = CoinCpuTime() - time;
	
	
  OsiClpSolverInterface * clpSolver = dynamic_cast<OsiClpSolverInterface *> (model1.solver());
  assert (clpSolver);
  
  clpSolver->setLogLevel(logLevel);
  ClpSimplex * clp = clpSolver->getModelPtr();
  
  clp->setLogLevel(logLevel);
  *simplex2 = *clp;
  simplex2->checkSolution();
  pinfo.postsolve(true);
 
     

  const int * original = pinfo.originalColumns();
  double * lower2 = simplex2->columnLower();
  double * upper2 = simplex2->columnUpper();
  const char * info2 = simplex2->integerInformation();
  double * lower = simplex->columnLower();
  double * upper = simplex->columnUpper();
  int i;
  
  for (i=0;i<simplex2->numberColumns();i++) {
    //if (info2[i]) {
      int iSeq = original[i];
      upper[iSeq]=upper2[i];
      lower[iSeq]=lower2[i];
	//}
   }
  //cout << "after postsolve " << model1.getObjValue() << "\n";
  
    //simplex->primal();
    //simplex2->checkSolution();
    model->gutsOfCopy(model1,2);
	model->setProblemStatus(model1.status());
	model->setSecondaryStatus(model1.secondaryStatus());
		
	
	  if (model1.isProvenOptimal()){
		  model->setProblemStatus(0);
		model->setSecondaryStatus(0);
	  }
	  else if(model1.isProvenInfeasible()){
		   model->setProblemStatus(0);
			model->setSecondaryStatus(1);
	  }
	   
	 
	 delete simplex2;
	 delete simplex_cpy;
			
	//} catch(CoinError e) {
    //e.print();
	//}
	
}


int solve_whs2(CbcModel *model, OsiClpSolverInterface *solver, std::string names[], int values[],int intvars, int logLevel= 0,double presolve_tolerance=1e-07){
//	try{ 
	
	std::vector< std::pair< std::string, double > > A;
	solver->setHintParam(OsiDoDualInInitial,true,OsiHintTry);
	
	model->setLogLevel(logLevel);
   solver->setLogLevel(logLevel);
   
  OsiSolverInterface *solver0 = new OsiClpSolverInterface();
  CglPreProcess *process = new CglPreProcess;
  process->messageHandler()->setLogLevel(logLevel);
  solver0 = process->preProcess(*solver,false,2);
  
  solver0->writeLp("solver0");
  
  OsiSolverInterface *solver1 = new OsiClpSolverInterface();
  solver1=solver0->clone();
  
  OsiSolverInterface *solver2 = new OsiClpSolverInterface();
  solver2=solver0->clone();
  
  int numCols = solver->getNumCols();
  bool whs = false;
  const double * sol0 = NULL;
  
	
  solver1->messageHandler()->setLogLevel(logLevel);
  
 // int priority[solver1->getNumCols()];
 // for (int i=0;i<solver1->getNumIntegers();i++)
//		priority[i]=0;
  
  CoinWarmStart * B = NULL;
  
if (intvars > 0){ 

	 const double * UB = solver1->getColUpper();
	 const double * LB = solver1->getColLower();
	 
	 for (int i=0;i<solver1->getNumCols();i++){
		 //solver1->setObjCoeff(i,0);
			if (solver1->isInteger(i)){
				for (int k=0;k<intvars;k++){
					if (solver1->getColName(i) == names[k]){
						if (UB[i]>LB[i]){
						solver1->setColLower(i,values[k]);
						solver1->setColUpper(i,values[k]);
						
						//if (values[k]==1)
						//	priority[i]=-1;
						//else
						//	priority[i]=1;
					}
					}
				}
			}
	 }
	 
	 solver1->initialSolve();
	  B=solver1->getWarmStart();
	 
	 //solver1->writeLp("fixed");
	 
	 
	 if(!solver1->isProvenPrimalInfeasible() && !solver1->isProvenDualInfeasible()){
		sol0 = solver1->getColSolution();
		whs = true;
		CbcModel model_fake(*solver1);
		 A = model_fake.getMIPStart();
	 }
	 else {
	 cout << "\\warm start solution infeasible\\";
		 return 1;
	 }
	 
	} 
	
	//const double *a = simplex2->getObjCoefficients();
	//int b[simplex2->getNumCols()]; 
	//for (int i = 0;i<simplex2->getNumCols();i++)
	//b[i]=i;
	//simplex2->addRow(simplex2->getNumCols(),b,a,-COIN_DBL_MAX,solver1.getObjValue());
	
	solver2->messageHandler()->setLogLevel(logLevel);
	
	
	
	
	 CbcModel model1(*solver2);
	 model1.setLogLevel(logLevel);
	 model1.solver()->messageHandler()->setLogLevel(logLevel);
	 model1.setLogLevel(logLevel);
	
     //model1.initialSolve();
	
	/*
 for (int i=0;i<model1.solver()->getNumCols();i++){
		 
			if (model1.solver()->isInteger(i)){
				//cout << model1.solver()->getColName(i) << " = " << sol_tmp[i]<<endl;
			if (model1.solver()->getColName(i) =="int_hands" || model1.solver()->getColName(i) =="c_sac093intflow" ||model1.solver()->getColName(i) =="int_sac_below" ||model1.solver()->getColName(i) =="int_whs_stor_chg" ||model1.solver()->getColName(i) =="int_ibu_uwfe" )
							priority[i]=0;
			else if (model1.solver()->getColName(i) =="int_sweir"  || model1.solver()->getColName(i) =="int_fweir1"  || model1.solver()->getColName(i) =="int_fweir2"  || model1.solver()->getColName(i) =="int_tweir")		
				priority[i]=0;
			else 
				priority[i]=1;
				
			}
	 }
 
 */
	
	if(whs){  
	
	//model1.solver()->setWarmStart(B);
    model1.setHotstartSolution(sol0 /*, priority*/);
	model1.setBestSolution(sol0,solver1->getNumCols(),solver1->getObjValue());
	model1.setBestObjectiveValue(solver1->getObjValue());
	model1.setMIPStart(A);
	
}
	
	double time = CoinCpuTime();
	
	model1.solver()->setHintParam(OsiDoDualInInitial,true,OsiHintTry	);
	model1.setLogLevel(logLevel);
	model1.messageHandler()->setLogLevel(logLevel);
	model1.solver()->messageHandler()->setLogLevel(logLevel);
	//model1.initialSolve();
    
  // Could tune more
  double objValue = model1.solver()->getObjSense()*model1.solver()->getObjValue();
  double minimumDropA=CoinMin(1.0,fabs(objValue)*1.0e-3+1.0e-4);
  double minimumDrop= fabs(objValue)*1.0e-4+1.0e-4;
	model1.setMinimumDrop(minimumDrop);
    model1.setMaximumCutPassesAtRoot(50); // use minimum drop
	model1.setMaximumCutPasses(1000);
	model1.setNumberStrong(8);
	model1.setNumberBeforeTrust(5);
	model1.solver()->setIntParam(OsiMaxNumIterationHotStart,100);
    model1.messageHandler()->setLogLevel(logLevel);
    model1.solver()->messageHandler()->setLogLevel(logLevel);
	model1.setLogLevel(logLevel);
	model1.findCliques(true,10,20);
	model1.setTypePresolve(2);
	model1.setSpecialOptions(4);
	model1.setMoreSpecialOptions(16777216);
	model1.setMoreSpecialOptions(32768);
	model1.setMoreSpecialOptions(1024);
	model1.setMoreSpecialOptions2(1);
	model1.setMoreSpecialOptions2(128); 

  
  
  callCbc("-log 3 -heuristics off -solve -quit",model1);

 	if(model1.isInitialSolveProvenPrimalInfeasible()>2){
		cout << "\nStopped due to numerical instabilities.\n";
		model->setProblemStatus(0);
		model->setSecondaryStatus(1);
		delete solver1;
		delete solver2;
		return 1;
	}
	

	if (model1.solver()->isProvenPrimalInfeasible() == 1){
		cout << "\nModel Infeasible\n";
		model->setProblemStatus(0);
		model->setSecondaryStatus(1);
		delete solver1;
		delete solver2;
		return 1;
		
	}
	
	double time1 = CoinCpuTime() - time;
	
  OsiSolverInterface * solver3;
  
  process->postProcess(*model1.solver());
  
  solver3 = solver;
  
  model->gutsOfCopy(model1, 2);
  
  model->setProblemStatus(model1.status());
	model->setSecondaryStatus(model1.secondaryStatus());

    
 if (model1.isProvenOptimal()){
	  model->setProblemStatus(0);
	  model->setSecondaryStatus(0);
	
  }
  
  if(model1.isProvenInfeasible()){
		 
		   model->setProblemStatus(0);
			model->setSecondaryStatus(1);
	  }
	  
  return 0;
}

int solve_4(CbcModel *model, OsiClpSolverInterface *solver, int logLevel){
	
		
	solver->setHintParam(OsiDoDualInInitial,true,OsiHintTry);
	solver->setLogLevel(logLevel);
	OsiClpSolverInterface *temp = new OsiClpSolverInterface(*solver);
	 
  OsiSolverInterface *solver2 = solver;
  CglPreProcess *process = new CglPreProcess;
  process->messageHandler()->setLogLevel(logLevel);
  solver2 = process->preProcess(*solver,false,2);
  //model.assignSolver(solver2);
  if(solver2)
	  cout << " ";
  else{
	  //model most probably infeasible but double check!
	  
	  OsiSolverInterface *temp1= temp;
	  CbcModel model1(*temp1);
	  model1.branchAndBound();
	  
	  if (model1.isProvenInfeasible()){
		  //model->gutsOfCopy(model1, 2);
		  model->setProblemStatus(0);
			model->setSecondaryStatus(1);
			cout << " \nmodel infeasible\n";
			delete process,solver2 ,model1;
			return 0;
	  } 
	  if (model1.isProvenOptimal()) {
		  *solver=OsiClpSolverInterface(*temp);
		  const double * sol = model1.getColSolution();
		  double Obj = model1.getObjValue();
		  int nCols = model1.getNumCols();
		  model->setBestSolution(sol, nCols,Obj,true);
		  model->gutsOfCopy(model1, 2);
		  
		  
		  model->setProblemStatus(0);
			model->setSecondaryStatus(0);
		  delete process,solver2, model1, sol;
		  //cout << "=====================" <<model->isProvenInfeasible() << " =======" << model->isProvenOptimal() <<endl;
		  return 1;
	  }
	 }
 
  
    CbcModel model1(*solver2);
	model1.setLogLevel(logLevel);
	model1.messageHandler()->setLogLevel(logLevel);
	model1.solver()->messageHandler()->setLogLevel(logLevel);
  	
	model1.initialSolve();
    
  
 
 model1.setTypePresolve(2);
 model1.setSpecialOptions(4);
 model1.setMoreSpecialOptions(16777216);
 model1.setMoreSpecialOptions(32768);
 model1.setMoreSpecialOptions(1024);
model1.setMoreSpecialOptions2(1);
model1.setMoreSpecialOptions2(128); 
  
  
  CbcMain0(model1);
	model->setLogLevel(logLevel);
    const char * argv2[]={"driver3","-strong","5","-trust","0","-heuristicsOnOff","off","-presolve","off","-cutsOnOff","off","-primalS","-preprocess","off","-tune","100000000","-passc","1","-feas","off","-rins","off","-solve","-quit"};
    CbcMain1(24,argv2,model1);
  
  OsiSolverInterface * solver3;
  
  process->postProcess(*model1.solver());
  
  solver3 = solver;
  
  
  model->setProblemStatus(model1.status());
model->setSecondaryStatus(model1.secondaryStatus());
  
  model->gutsOfCopy(model1, 2);
 
  
  
  
   /* 
  if (model1.solver()->isProvenOptimal()){
	  model->setProblemStatus(0);
	  model->setSecondaryStatus(0);
  }
   if(!model1.isProvenInfeasible()){
		   model->setProblemStatus(0);
			model->setSecondaryStatus(1);
	  }*/
  delete process, solver3, solver2, model1;
  return 2;
	
	
	
}

int getNumIntegers(OsiClpSolverInterface *solver){
	return solver->getNumIntegers();
}

CoinWarmStart * getWarmStart(CbcModel *model){
	return model->solver()->getWarmStart();
}

void writeMps1(CbcModel *model, const char *name, int 	formatType = 0, int numberAcross = 2,double objSense = 0.0){
	model->solver()->writeMpsNative(name,NULL,NULL,formatType,numberAcross,objSense,0);
}

void writeLp1(CbcModel *model, const char *name, double epsilon=1e-5, int decimals=5 ){
	model->solver()->writeLp(name,"lp",epsilon,10, decimals, 0.0, true);
	}


void callCbc(std::string a,CbcModel *model){
	callCbc(a,*model);
}


void setMaximumNodes(CbcModel *model, int value){
	model->setMaximumNodes(value);
}

void setNumberThreads(CbcModel * model,int a){
	model->setNumberThreads(a);
}

void setThreadMode(CbcModel * model,int a){
	model->setThreadMode(a);
}


/*
void par_solve(CbcModel *model, OsiClpSolverInterface *solver, double tol_solve_3, std::string names[], int values[],int intvars, double presolve_tolerance) {
	//cout << "------------" << omp_get_num_procs() << "-------";
	solver->setLogLevel(0);

b=0;
int a1=0,a2=0,a3=0;
	 OsiClpSolverInterface *solver1 = new OsiClpSolverInterface(*solver);
	 OsiClpSolverInterface *solver2 = new OsiClpSolverInterface(*solver);
	 OsiClpSolverInterface *solver3 = new OsiClpSolverInterface(*solver);
	 solver1->setLogLevel(0);
	 solver2->setLogLevel(0);
	 solver3->setLogLevel(0);
	 CbcModel *model1 = new CbcModel(*solver1);
	 CbcModel *model2 = new CbcModel(*solver2);
	 CbcModel *model3 = new CbcModel(*solver3);
	 model1->setLogLevel(0);
	 model2->setLogLevel(0);
	 model3->setLogLevel(0);
	 MyEventHandler3 eventHandler;
//cout << omp_get_max_threads(); 

omp_set_num_threads(4);
#pragma omp parallel 
{
	
	//cout << " ====== " << omp_get_max_threads(); 
	
    if (omp_get_thread_num() == 0 ){
	 model1->passInEventHandler(&eventHandler);
	 cout << "\nhello1\n";
     solve_2(model1,solver1);
	 
	 if (model1->status()==0){
		 b=1;
		 a1=1;
		 
	 }
	
    }else if (omp_get_thread_num() == 1){
	 cout << "\nhello2\n";
	 model2->passInEventHandler(&eventHandler);
	 solve_3(model2,solver2,0,tol_solve_3);
	 if (model2->status()==0)
		 b=1;
		a2=1;	
    }else if (omp_get_thread_num() == 2){
	 cout << "\nhello3\n";
	 model3->passInEventHandler(&eventHandler);
	 solve_whs(model3,solver3,names,values,intvars,presolve_tolerance);
	 if (model3->status()==0)
		 b=1;
		a3=1;
    }
}
//cout << "\n"<<a1<<a2<<a3<<"\n";
if (a3==1){
	*solver=*solver1;
	delete solver1;
	delete solver2;
	delete solver3;
	delete model1;
	delete model2;
	delete model3;
	cout << "solve_whs finished earlier\n";
	return;
}else if (a1==1){
	*solver=*solver1;
	model->gutsOfCopy(*model1, 2);
	delete solver1;
	delete solver2;
	delete solver3;
	delete model1;
	delete model2;
	delete model3;
	cout << "solve_2 finished earlier\n";
	return;
}else if (a2==1){
	*solver=*solver2;
	model->gutsOfCopy(*model2, 2);
	delete solver1;
	delete solver2;
	delete solver3;
	delete model1;
	delete model2;
	delete model3;
	cout << "solve_3 finished earlier\n";
	return;
}}
*/



void par_solve(CbcModel *model, OsiClpSolverInterface *solver, std::string s, std::string names[] = NULL, int values[]= NULL,int intvars= 0,std::string names1[]= NULL, int values1[]= NULL,int intvars1= 0,std::string names2[]= NULL, int values2[]= NULL,int intvars2= 0) {


try{
	
double time1 = CoinCpuTime();
//break up the string input
std::stringstream ss(s);
std::istream_iterator<std::string> begin(ss);
std::istream_iterator<std::string> end;
std::vector<std::string> argv(begin, end);
//size of the string
int argc = argv.size();


//define event handlers to stop solvers once a solution has been found
MyEventHandler3 eventHandler;
MyEventHandler4 clpEventHandler;

//solvers 
enum function { 
	Solve_2,
	Solve_3,
	Solve_whs,
	CallCbc,
};

//cout << "argc = " << argc << endl; 
//   for(int i = 0; i < argc; i++) 
//      cout << "argv[" << i << "] = " << argv[i] << endl; 
  
//how any solvers (threads)
int n=atoi(argv[0].c_str());

//global variable indicates that a solution has been found in one of the solvers	
b=0;

//a[i] will become 1 if solver 1 finishes earlier
int *a = new int[n];
fill_n(a, n, 0); 
	
	
function *f=new function[n];
int *fp = new int[n];
fill_n(fp, n, 0); 
int * c1 = new int[n]; // c1[i] is the position of solver name in the string
int * c2 = new int[n]; // c2[i] is the number of tuning inputs for solver i
int j=0;
int whs=0; //number of solve_whs solvers to be used

//analyse the string and extract info 
for(int i = 1; i < argc; i++){
	if (argv[i]=="solve_2" || argv[i]=="solve_3" || argv[i]=="solve_whs" || argv[i]=="callCbc"){
		c1[j]=i;
		
		if (argv[i]== "solve_2")
			f[j]=Solve_2;
		if (argv[i]=="solve_3")
			f[j]=Solve_3;
		if (argv[i]=="solve_whs"){
			f[j]=Solve_whs;
			whs++;
			fp[j]=whs;
		}
		if (argv[i]=="callCbc")
			f[j]=CallCbc;
		j++;
	}
}

for(int i = 0; i < n-1; i++){
	c2[i]=c1[i+1]-c1[i]-1;
}
c2[n-1]=argc-c1[n-1]-1;

//for(int i = 0; i < n; i++)
//	cout << fp[i] << " -- " ;
//cout << "\n";

//define solvers
OsiClpSolverInterface **solvers = new OsiClpSolverInterface*[n];
for(int i = 0; i < n; i++)
	solvers[i] = new OsiClpSolverInterface(*solver);

//pass event handler, set log level for solvers
for(int i = 0; i < n; i++){
	solvers[i]->setLogLevel(0);
	solvers[i]->getModelPtr()->passInEventHandler(&clpEventHandler);
	// Tell solver to return fast if presolve or initial solve infeasible
	solvers[i]->getModelPtr()->setMoreSpecialOptions(3);

}
 
//define models, assign solvers, pass event handler, set log level	 
CbcModel **models = new CbcModel*[n];
for(int i = 0; i < n; i++)
	models[i] = new CbcModel(*solvers[i]);
 for(int i = 0; i < n; i++){
	models[i]->setLogLevel(0);
	models[i]->passInEventHandler(&eventHandler);
 }
double time2 = CoinCpuTime();

//cout << "Time to copy and construct solvers = " << time2-time1 << "\n";
	
int temp = whs*3; // there are whs solve_whs solvers. so 3*whs inputs (names, values, intvars)


//core
	#pragma omp parallel for
    for(int i=0; i<n; ++i){
		//cout << "\nThread " << i<< " started ... \n";
		if (f[i]==Solve_2){
			for (int j=1;j<=c2[i];j=j+2){
				if (argv[c1[i]+j]=="pt"){
					models[i]->solver()->setDblParam(OsiPrimalTolerance,atof(argv[c1[i]+j+1].c_str()));	
					//cout << "\ndoing solve_2 with pt " ;
				}
				if(argv[c1[i]+j]=="it"){
					models[i]->setIntegerTolerance(atof(argv[c1[i]+j+1].c_str()));	
					//cout << "\ndoing solve_2 with it " ;
				}
				if (argv[c1[i]+j]=="pst")
					cout << "\n pst is invalid for solve_2\n";
			}
		    solve_2(models[i],solvers[i],1);
			if (models[i]->status()==0&&models[i]->secondaryStatus()==0){
				 b=1;
				 a[i]=1;
				 #pragma omp flush(b)
				 
				 
				 for (int p=0;p<n && p!=i;p++)
					models[p]->sayEventHappened();
		 
			}
		}else if (f[i]==Solve_3){
			double presolve_tol3 = 1e-7; // default presolve_tol for solve_3 solvers
			for (int j=1;j<=c2[i];j=j+2){
				if (argv[c1[i]+j]=="pt"){
					models[i]->solver()->setDblParam(OsiPrimalTolerance,atof(argv[c1[i]+j+1].c_str()));	
					//cout << "\ndoing solve_3 with pt " ;
				}
				if(argv[c1[i]+j]=="it"){
					models[i]->setIntegerTolerance(atof(argv[c1[i]+j+1].c_str()));	
					//cout << "\ndoing solve_3 with it " ;
				}
				if (argv[c1[i]+j]=="pst")
					 presolve_tol3=atof(argv[c1[i]+j+1].c_str());
			}
			//cout << "\ndoing solve_3\n";
		    solve_3(models[i],solvers[i],1,presolve_tol3);
			//cout << "presolve_tol = " << presolve_tol3 << "\n";

			if (models[i]->status()==0&&models[i]->secondaryStatus()==0){
				 b=1;
				 a[i]=1;
				 #pragma omp flush(b)
				 for (int p=0;p<n && p!=i;p++)
					models[p]->sayEventHappened();
				
		 
			}
		}else if (f[i]==Solve_whs && fp[i]==1){
			double presolve_tol = 1e-7; // default presolve_tol for solve_whs solvers 
			for (int j=1;j<=c2[i];j=j+2){
				if (argv[c1[i]+j]=="pt"){
					models[i]->solver()->setDblParam(OsiPrimalTolerance,atof(argv[c1[i]+j+1].c_str()));	
					//cout << "\ndoing solve_whs with pt " ;
				}
				if(argv[c1[i]+j]=="it"){
					models[i]->setIntegerTolerance(atof(argv[c1[i]+j+1].c_str()));	
					//cout << "\ndoing solve_whs with it " ;
				}
				if (argv[c1[i]+j]=="pst")
					presolve_tol = atof(argv[c1[i]+j+1].c_str());
			}
			
			//cout << "\ndoing solve_whs\n";
			
			solve_whs(models[i],solvers[i],names,values,intvars,0,presolve_tol);
			//cout << "k= " << intvars << "\n";
			//cout << "pst " << presolve_tol << "\n";
			
			if (models[i]->status()==0&&models[i]->secondaryStatus()==0){
				 b=1;
				 a[i]=1;
				 #pragma omp flush(b)
				 for (int p=0;p<n && p!=i;p++)
					models[p]->sayEventHappened();
				 
		 
			}
		}else if (f[i]==Solve_whs && fp[i]==2){
		double presolve_tol = 1e-7; // default presolve_tol for solve_whs solvers 
		for (int j=1;j<=c2[i];j=j+2){
			if (argv[c1[i]+j]=="pt"){
				models[i]->solver()->setDblParam(OsiPrimalTolerance,atof(argv[c1[i]+j+1].c_str()));	
				//cout << "\ndoing solve_whs with pt " ;
			}
			if(argv[c1[i]+j]=="it"){
				models[i]->setIntegerTolerance(atof(argv[c1[i]+j+1].c_str()));	
				//cout << "\ndoing solve_whs with it " ;
			}
			if (argv[c1[i]+j]=="pst")
				presolve_tol = atof(argv[c1[i]+j+1].c_str());
		}
		
		//cout << "\ndoing solve_whs\n";
		
		solve_whs(models[i],solvers[i],names1,values1,intvars1,0,presolve_tol);
		//cout << "k= " << intvars1 << "\n";
		//cout << "pst " << presolve_tol << "\n";
		
		if (models[i]->status()==0&&models[i]->secondaryStatus()==0){
			 b=1;
			 a[i]=1;
			 #pragma omp flush(b)
			 for (int p=0;p<n && p!=i;p++)
					models[p]->sayEventHappened();
			 
	 
		}
		}else if (f[i]==Solve_whs && fp[i]==3){
			double presolve_tol = 1e-7; // default presolve_tol for solve_whs solvers 
			for (int j=1;j<=c2[i];j=j+2){
				if (argv[c1[i]+j]=="pt"){
					models[i]->solver()->setDblParam(OsiPrimalTolerance,atof(argv[c1[i]+j+1].c_str()));	
					//cout << "\ndoing solve_whs with pt " ;
				}
				if(argv[c1[i]+j]=="it"){
					models[i]->setIntegerTolerance(atof(argv[c1[i]+j+1].c_str()));	
					//cout << "\ndoing solve_whs with it " ;
				}
				if (argv[c1[i]+j]=="pst")
					presolve_tol = atof(argv[c1[i]+j+1].c_str());
			}
			
			//cout << "\ndoing solve_whs\n";
			
			solve_whs(models[i],solvers[i],names2,values2,intvars2,0,presolve_tol);
			//cout << "k= " << intvars2 << "\n";
			//cout << "pst " << presolve_tol << "\n";
			
			if (models[i]->status()==0&&models[i]->secondaryStatus()==0){
				 b=1;
				 a[i]=1;
				 #pragma omp flush(b)
				 for (int p=0;p<n && p!=i;p++)
					models[p]->sayEventHappened();
				 
		 
			}
		}else if (f[i]==CallCbc){
			//const char * argv2[2+c2[i]];
			//argv2[0]="-driver";
			string A;
			for (int k=1;k<=c2[i];k++){
				A=A+" "+argv[c1[i]+k];
				//argv2[k]=argv[c1[i]+k].c_str();
			}
			//cout << A<<"\n";
			callCbc(A,*models[i]);
		    //const char * argv2[]={"-driver3",A.c_str(),"-solve","-quit"};
			//argv2[2+c2[i]-2]="-solve";
			//argv2[3+c2[i]-1]="-quit";
			
			//CbcMain0(*models[i]);
			//CbcMain1(2+c2[i],argv2,*models[i],callBack);
			//cout << "Status: " << models[i]->status() << " == " << models[i]->secondaryStatus() << "\n";	
			if (models[i]->status()==0&&models[i]->secondaryStatus()==0){
				 b=1; 
				 a[i]=1;
				 #pragma omp flush(b)
				 for (int p=0;p<n && p!=i;p++)
					models[p]->sayEventHappened();
				
			}
		}	
	}

	//for (int k=0;k<n;k++)
	//	cout << a[k] << " -- ";
	//cout << "\n";
	
	for (int k=0;k<n;k++){
		if (a[k]==1){
			if (f[k]==2&&fp[k]==1){
				cout << "\n"<<"solve_whs 1 finished earlier!"<<"\n";
				*solver=*solvers[k];
				model->gutsOfCopy(*models[k], 2);
				model->setProblemStatus(0);
				model->setSecondaryStatus(0);
				break;
				}
			else if (f[k]==2&&fp[k]==2){
				cout << "\n"<<"Second solve_whs 2 finished earlier!"<<"\n";
				*solver=*solvers[k];
				model->gutsOfCopy(*models[k], 2);
				model->setProblemStatus(0);
				model->setSecondaryStatus(0);
				break;
				}
			else if (f[k]==2&&fp[k]==3){
				cout << "\n"<<"Third solve_whs 3 finished earlier!"<<"\n";
				*solver=*solvers[k];
				model->gutsOfCopy(*models[k], 2);
				model->setProblemStatus(0);
				model->setSecondaryStatus(0);
				break;
				}
			else if (f[k]==0){
				cout << "\n"<<"solve_2 finished earlier!"<<"\n";
				*solver=*solvers[k];
				model->gutsOfCopy(*models[k], 2);
				model->setProblemStatus(0);
				model->setSecondaryStatus(0);
				break;
				}
			else if (f[k]==1){
				cout << "\n"<<"solve_3 finished earlier!"<<"\n";
				*solver=*solvers[k];
				model->gutsOfCopy(*models[k], 2);
				model->setProblemStatus(0);
				model->setSecondaryStatus(0);
				break;
				}
			else if (f[k]==3){
				cout << "\n"<<"callCbc finished earlier!"<<"\n";
				*solver=*solvers[k];
				model->gutsOfCopy(*models[k], 2);
				model->setProblemStatus(0);
				model->setSecondaryStatus(0);
				break;
				}
}}
	//if (b==1)
	//		throw a_e_1;
for (int i=0;i<n;i++)
	delete solvers[i];
for (int i=0;i<n;i++)
	delete models[i];
delete a,c1,c2;
if (whs>0)
	delete f,fp;
delete[] models;
delete[] solvers;
}catch (exception& e)
  {
    cout << e.what() << '\n';
  }

}

int solve_unified(CbcModel *model, OsiClpSolverInterface *solver, std::string names[] = NULL, int values[] = NULL, int intvars = 0, int logLevel= 0 ){
	
	OsiClpSolverInterface *solver1 = new OsiClpSolverInterface(*solver);
	CbcModel * model1 = new CbcModel(*solver1);
	model1->setIntegerTolerance(1e-9);
	model1->solver()->setDblParam(OsiPrimalTolerance,1e-9);
	solver1->setDblParam(OsiPrimalTolerance,1e-9);
	int f=0;
	if (intvars == 0){
		
		delete model1;
		goto try_solve_2;
	}
	else{
		f = solve_whs(model1,solver1,names,values,intvars,logLevel);
		if (model1->status()==0 && model1->secondaryStatus() == 1){
			//cout <<  model1.isProvenInfeasible() << "  " <<  model1.isProvenOptimal() << "\n";
			cout << "whs inf, now trying solve_2\n";
			
			delete model1;
			goto try_solve_2;
		}
		else if (f == 3){
			cout << "\nprovided solution for whs inf, now trying solve_2\n";
			
			delete model1;
			goto try_solve_2;
		}
		else{
			*solver=*solver1;
			model->gutsOfCopy(*model1, 2);
			model->setProblemStatus(0);
			model->setSecondaryStatus(0);
			
			delete model1;
			return 6;
		}
	}
		
try_solve_2:
	
	OsiClpSolverInterface *solver2 = new OsiClpSolverInterface(*solver);
	CbcModel * model2 = new CbcModel(*solver2);
	model2->setIntegerTolerance(1e-9);
	model2->solver()->setDblParam(OsiPrimalTolerance,1e-8);
	solver2->setDblParam(OsiPrimalTolerance,1e-8);
	
	solve_2(model2,solver2,logLevel);
	if (model2->status()==0 && model2->secondaryStatus() == 1){
		//cout <<  model2.isProvenInfeasible() << "  " <<  model2.isProvenOptimal() << "\n";
			cout << "solve_2 inf, now trying solve_2 with tol 1e-4\n";
			
			delete model2;
			goto try_solve_2_tol;
			
	}else{
			*solver=*solver2;
			model->gutsOfCopy(*model2,2);
			model->setProblemStatus(0);
			model->setSecondaryStatus(0);
			
			delete model2;
			return 5;
	}
try_solve_2_tol:

	OsiClpSolverInterface *solver3 = new OsiClpSolverInterface(*solver);
	CbcModel * model3  = new CbcModel(*solver3);
	assignSolver(model3,solver3);
	model3->setIntegerTolerance(1e-9);
	
	model3->solver()->setDblParam(OsiPrimalTolerance,1e-4);
	solver3->setDblParam(OsiPrimalTolerance,1e-4);
	solve_2(model3,solver3,logLevel);
	
	if (model3->status()==0 && model3->secondaryStatus() == 1){
		cout << "Model infeasible!\n";
		//cout <<  model3.isProvenInfeasible() << "  " <<  model3.isProvenOptimal() << "\n";
		
		delete model3;
		return 1;
		}
		else{
			cout << "Optimal Solution found!\n";
			*solver=*solver3;
			model->gutsOfCopy(*model3, 2);
			//cout << model->getObjValue() << "   " << solver->getObjValue();
			model->setProblemStatus(0);
			model->setSecondaryStatus(0);
			
			delete model3;
			return 4;
		}

}

double getMinRHS(OsiClpSolverInterface *solver)
{
  double minimumNegative = -COIN_DBL_MAX;
  double maximumNegative = 0.0;
  double minimumPositive = COIN_DBL_MAX;
  double maximumPositive = 0.0;

  const double * RHS = solver->getRightHandSide();
  int numberRows = solver->getNumRows();
  int i;
  for (i = 0; i < numberRows; i++) {
      double value = RHS[i];
      if (value > 0.0) {
	minimumPositive = CoinMin(minimumPositive, value);
	maximumPositive = CoinMax(maximumPositive, value);
      } else if (value < 0.0) {
	minimumNegative = CoinMax(minimumNegative, value);
	maximumNegative = CoinMin(maximumNegative, value);
      }
    }
	return std::min(fabs(minimumNegative),fabs(minimumPositive));
  }
 

double getMinCoeff(OsiClpSolverInterface *solver) 
{
  double minimumNegative = -COIN_DBL_MAX;
  double maximumNegative = 0.0;
  double minimumPositive = COIN_DBL_MAX;
  double maximumPositive = 0.0;
  // get matrix data pointers
  const double * elementByColumn = solver->getMatrixByCol()->getElements();
  const CoinBigIndex * columnStart = solver->getMatrixByCol()->getVectorStarts();
  const int * columnLength = solver->getMatrixByCol()->getVectorLengths();
  const int * row = solver->getMatrixByCol()->getIndices();
  int numberColumns = solver->getNumCols();
  int numberRows = solver->getNumRows();
  int numberElements = solver->getMatrixByCol()->getNumElements();
  int i;
  for (i = 0; i < numberColumns; i++) {
    CoinBigIndex j;
    for (j = columnStart[i]; j < columnStart[i] + columnLength[i]; j++) {
      double value = elementByColumn[j];
      if (value > 0.0) {
	minimumPositive = CoinMin(minimumPositive, value);
	maximumPositive = CoinMax(maximumPositive, value);
      } else if (value < 0.0) {
	minimumNegative = CoinMax(minimumNegative, value);
	maximumNegative = CoinMin(maximumNegative, value);
      }
    }
  }
  return std::min(fabs(minimumNegative),fabs(minimumPositive));
  
}

double getMaxCoeff(OsiClpSolverInterface *solver) 
{
  double minimumNegative = -COIN_DBL_MAX;
  double maximumNegative = 0.0;
  double minimumPositive = COIN_DBL_MAX;
  double maximumPositive = 0.0;
  // get matrix data pointers
  const double * elementByColumn = solver->getMatrixByCol()->getElements();
  const CoinBigIndex * columnStart = solver->getMatrixByCol()->getVectorStarts();
  const int * columnLength = solver->getMatrixByCol()->getVectorLengths();
  const int * row = solver->getMatrixByCol()->getIndices();
  int numberColumns = solver->getNumCols();
  int numberRows = solver->getNumRows();
  int numberElements = solver->getMatrixByCol()->getNumElements();
  int i;
  for (i = 0; i < numberColumns; i++) {
    CoinBigIndex j;
    for (j = columnStart[i]; j < columnStart[i] + columnLength[i]; j++) {
      double value = elementByColumn[j];
      if (value > 0.0) {
	minimumPositive = CoinMin(minimumPositive, value);
	maximumPositive = CoinMax(maximumPositive, value);
      } else if (value < 0.0) {
	minimumNegative = CoinMax(minimumNegative, value);
	maximumNegative = CoinMin(maximumNegative, value);
      }
    }
  }
  return std::max(fabs(maximumNegative),fabs(maximumPositive));
  
}