import src.jCbc;                            
import src.SWIGTYPE_p_CbcModel;
import src.SWIGTYPE_p_double;
import src.SWIGTYPE_p_int;
import src.SWIGTYPE_p_CoinModel;
import src.SWIGTYPE_p_OsiClpSolverInterface;


public class ex2 {
public static void main(String argv[]) {
System.loadLibrary("jCbc"); 

SWIGTYPE_p_OsiClpSolverInterface solver = jCbc.new_jOsiClpSolverInterface(); 
SWIGTYPE_p_CbcModel Model = jCbc.new_jCbcModel();

jCbc.assignSolver(Model,solver); 

jCbc.readLp(solver,"model.lp");

jCbc.solve(Model,solver);

int nCols=jCbc.getNumCols(Model);
SWIGTYPE_p_double sol = jCbc.new_jarray_double(nCols); 
sol = jCbc.getColSolution(solver); 

System.out.println("Solution:"); 

System.out.println("Objective_Value=" + jCbc.getObjValue(Model)); 

for (int j = 0; j < nCols; j++){
if ( jCbc.isInteger(Model,j)==1) 
System.out.println("x["+j+"]="
+jCbc.jarray_double_getitem(sol,j)); 
}

jCbc.delete_jCbcModel(Model);
}}
