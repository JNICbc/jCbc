import src.jCbc;                             
import src.SWIGTYPE_p_CbcModel;
import src.SWIGTYPE_p_double;
import src.SWIGTYPE_p_int;
import src.SWIGTYPE_p_CoinModel;
import src.SWIGTYPE_p_OsiClpSolverInterface;


public class ex1 {
public static void main(String argv[]) {
System.loadLibrary("jCbc"); // load the dll library

//CoinModel for adding Rows and Columns faster 

SWIGTYPE_p_CoinModel modelObject = jCbc.new_jCoinModel(); 

//this is our LP solver!
SWIGTYPE_p_OsiClpSolverInterface solver = jCbc.new_jOsiClpSolverInterface(); 

// values for objective function (costs)
double objValue[] = {1.0, 2.0, 4.0}; 
// variable upper bounds
double upper[] = {1.0, 10.0, Double.MAX_VALUE}; 
// variable lower bounds
double lower[] = {0.0,-Double.MAX_VALUE, 2.0}; 


//define variables: 
jCbc.addCol(modelObject,lower[0],upper[0],objValue[0],"x1",true); 
jCbc.addCol(modelObject,lower[1],upper[1],objValue[1],"x2",false);
jCbc.addCol(modelObject,lower[2],upper[2],objValue[2],"x3",true);

// this defines a swig type integer array of length 3 
SWIGTYPE_p_int row1Index = jCbc.new_jarray_int(2);	
// set the values of this array
jCbc.jarray_int_setitem(row1Index,0,0);          
jCbc.jarray_int_setitem(row1Index,1,2);


SWIGTYPE_p_double row1Value = jCbc.new_jarray_double(2); 
jCbc.jarray_double_setitem(row1Value,0,1.0);        
jCbc.jarray_double_setitem(row1Value,1,3.0);

//add row to CoinModel
jCbc.addRow(modelObject,2, row1Index, row1Value, 1.0, Double.MAX_VALUE,"r1"); 

SWIGTYPE_p_int row2Index = jCbc.new_jarray_int(3);	 
jCbc.jarray_int_setitem(row2Index,0,0);          
jCbc.jarray_int_setitem(row2Index,1,1);
jCbc.jarray_int_setitem(row2Index,2,2);


SWIGTYPE_p_double row2Value = jCbc.new_jarray_double(3); 
jCbc.jarray_double_setitem(row2Value,0,-1.0);        
jCbc.jarray_double_setitem(row2Value,1,2.0);
jCbc.jarray_double_setitem(row2Value,2,-0.5);

jCbc.addRow(modelObject,3, row2Index, row2Value, -Double.MAX_VALUE, 3.0,"r2");

SWIGTYPE_p_int row3Index = jCbc.new_jarray_int(3);	 
jCbc.jarray_int_setitem(row3Index,0,0);          
jCbc.jarray_int_setitem(row3Index,1,1);
jCbc.jarray_int_setitem(row3Index,2,2);

SWIGTYPE_p_double row3Value = jCbc.new_jarray_double(3); 
jCbc.jarray_double_setitem(row3Value,0,1.0);        
jCbc.jarray_double_setitem(row3Value,1,-1.0);
jCbc.jarray_double_setitem(row3Value,2,2.0);

jCbc.addRow(modelObject,3,row3Index,row3Value,7/2.,7/2.,"r3");

//add all rows to OsiClpSolverInterface at once
jCbc.addRows(solver, modelObject);

// This defines a new empty CbcModel
SWIGTYPE_p_CbcModel Model = jCbc.new_jCbcModel();
// Assign the solver to CbcModel
jCbc.assignSolver(Model,solver); 


jCbc.setModelName(solver, "test");

jCbc.solve(Model,solver,0);

// get the solution
SWIGTYPE_p_double sol = jCbc.new_jarray_double(3); 
sol = jCbc.getColSolution(Model);

// print solution 
System.out.println("Solution:"); 

System.out.println("Objective_Value=" + jCbc.getObjValue(Model)); 
for (int j = 0; j < 3; j++){
	System.out.println(jCbc.getColName(solver,j)+"="
		+jCbc.jarray_double_getitem(sol,j));
}
//delete
jCbc.delete_jCoinModel(modelObject);
jCbc.delete_jCbcModel(Model);

}
}
