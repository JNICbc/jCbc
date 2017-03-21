import src.jCbc;
import src.SWIGTYPE_p_CbcModel;
import src.SWIGTYPE_p_CoinModel;
import src.SWIGTYPE_p_OsiClpSolverInterface;
import src.SWIGTYPE_p_double;
import src.SWIGTYPE_p_int;
import src.SWIGTYPE_p_std__string;

public class ex4 {
public static void main(String argv[]) {
System.loadLibrary("jCbc");

SWIGTYPE_p_OsiClpSolverInterface solver = jCbc.new_jOsiClpSolverInterface(); 
jCbc.readLp(solver,"model.lp");
SWIGTYPE_p_CbcModel Model = jCbc.new_jCbcModel();
jCbc.assignSolver(Model,solver); 

jCbc.solve_2(Model,solver,0);

int numIntVars = jCbc.getNumIntegers(solver);
SWIGTYPE_p_std__string names = jCbc.new_jarray_string(numIntVars); 
SWIGTYPE_p_int values = jCbc.new_jarray_int(numIntVars); 
SWIGTYPE_p_double sol= jCbc.getColSolution(solver);

int k=0;
for (int j = 0; j < jCbc.getNumCols(solver); j++){
if (jCbc.isInteger(solver,j)==1){
jCbc.jarray_string_setitem(names,k,jCbc.getColName(solver,j));
jCbc.jarray_int_setitem(values,k,(int)jCbc.jarray_double_getitem(sol,j));
k++;
}} 

jCbc.delete_jCbcModel(Model);


SWIGTYPE_p_OsiClpSolverInterface solver0 = jCbc.new_jOsiClpSolverInterface(); 
jCbc.readLp(solver0,"model1.lp");

SWIGTYPE_p_CbcModel Model0 = jCbc.new_jCbcModel();
jCbc.assignSolver(Model0,solver0);

jCbc.par_solve(Model0,solver0,"4 solve_2 solve_3 solve_whs callCbc -solve",names,values,k);

System.out.println("ObjVal = " + jCbc.getObjValue(Model0)); 
jCbc.delete_jCbcModel(Model0);

}}
