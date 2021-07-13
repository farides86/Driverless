#FORCESNLPsolver : A fast customized optimization solver.
#
#Copyright (C) 2013-2021 EMBOTECH AG [info@embotech.com]. All rights reserved.
#
#
#This program is distributed in the hope that it will be useful.
#EMBOTECH makes NO WARRANTIES with respect to the use of the software 
#without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
#PARTICULAR PURPOSE. 
#
#EMBOTECH shall not have any liability for any damage arising from the use
#of the software.
#
#This Agreement shall exclusively be governed by and interpreted in 
#accordance with the laws of Switzerland, excluding its principles
#of conflict of laws. The Courts of Zurich-City shall have exclusive 
#jurisdiction in case of any dispute.
#
#def __init__():
'''
a Python wrapper for a fast solver generated by FORCESPRO v4.3.1

   OUTPUT = FORCESNLPsolver_py.FORCESNLPsolver_solve(PARAMS) solves a multistage problem
   subject to the parameters supplied in the following dictionary:
       PARAMS['xinit'] - column vector of length 5
       PARAMS['x0'] - column vector of length 210
       PARAMS['all_parameters'] - column vector of length 60
       PARAMS['reinitialize'] - scalar

   OUTPUT returns the values of the last iteration of the solver where
       OUTPUT['x01'] - column vector of size 7
       OUTPUT['x02'] - column vector of size 7
       OUTPUT['x03'] - column vector of size 7
       OUTPUT['x04'] - column vector of size 7
       OUTPUT['x05'] - column vector of size 7
       OUTPUT['x06'] - column vector of size 7
       OUTPUT['x07'] - column vector of size 7
       OUTPUT['x08'] - column vector of size 7
       OUTPUT['x09'] - column vector of size 7
       OUTPUT['x10'] - column vector of size 7
       OUTPUT['x11'] - column vector of size 7
       OUTPUT['x12'] - column vector of size 7
       OUTPUT['x13'] - column vector of size 7
       OUTPUT['x14'] - column vector of size 7
       OUTPUT['x15'] - column vector of size 7
       OUTPUT['x16'] - column vector of size 7
       OUTPUT['x17'] - column vector of size 7
       OUTPUT['x18'] - column vector of size 7
       OUTPUT['x19'] - column vector of size 7
       OUTPUT['x20'] - column vector of size 7
       OUTPUT['x21'] - column vector of size 7
       OUTPUT['x22'] - column vector of size 7
       OUTPUT['x23'] - column vector of size 7
       OUTPUT['x24'] - column vector of size 7
       OUTPUT['x25'] - column vector of size 7
       OUTPUT['x26'] - column vector of size 7
       OUTPUT['x27'] - column vector of size 7
       OUTPUT['x28'] - column vector of size 7
       OUTPUT['x29'] - column vector of size 7
       OUTPUT['x30'] - column vector of size 7

   [OUTPUT, EXITFLAG] = FORCESNLPsolver_py.FORCESNLPsolver_solve(PARAMS) returns additionally
   the integer EXITFLAG indicating the state of the solution with 
       1 - Optimal solution has been found (subject to desired accuracy)
       2 - (only branch-and-bound) A feasible point has been identified for which the objective value is no more than codeoptions.mip.mipgap*100 per cent worse than the global optimum 
       0 - Timeout - maximum number of iterations reached
      -1 - (only branch-and-bound) Infeasible problem (problems solving the root relaxation to the desired accuracy)
      -2 - (only branch-and-bound) Out of memory - cannot fit branch and bound nodes into pre-allocated memory.
      -6 - NaN or INF occured during evaluation of functions and derivatives. Please check your initial guess.
      -7 - Method could not progress. Problem may be infeasible. Run FORCESdiagnostics on your problem to check for most common errors in the formulation.
     -10 - The convex solver could not proceed due to an internal error
    -100 - License error

   [OUTPUT, EXITFLAG, INFO] = FORCESNLPsolver_py.FORCESNLPsolver_solve(PARAMS) returns 
   additional information about the last iterate:
       INFO.it        - number of iterations that lead to this result
       INFO.it2opt    - number of convex solves
       INFO.res_eq    - max. equality constraint residual
       INFO.res_ineq  - max. inequality constraint residual
       INFO.pobj      - primal objective
       INFO.dobj      - dual objective
       INFO.dgap      - duality gap := pobj - dobj
       INFO.rdgap     - relative duality gap := |dgap / pobj|
       INFO.mu        - duality measure
       INFO.sigma     - centering parameter
       INFO.lsit_aff  - iterations of affine line search
       INFO.lsit_cc   - iterations of line search (combined direction)
       INFO.step_aff  - step size (affine direction)
       INFO.step_cc   - step size (centering direction)
       INFO.solvetime - Time needed for solve (wall clock time)

 See also COPYING

'''

import ctypes
import os
import numpy as np
import numpy.ctypeslib as npct
import sys

#_lib = ctypes.CDLL(os.path.join(os.getcwd(),'FORCESNLPsolver/lib/FORCESNLPsolver.dll')) 
try:
    _lib = ctypes.CDLL(os.path.join(os.path.dirname(os.path.abspath(__file__)),'FORCESNLPsolver/lib/FORCESNLPsolver.dll'))
    csolver = getattr(_lib,'FORCESNLPsolver_solve')
except:
    _lib = ctypes.CDLL(os.path.join(os.path.dirname(os.path.abspath(__file__)),'FORCESNLPsolver/lib/libFORCESNLPsolver.dll'))
    csolver = getattr(_lib,'FORCESNLPsolver_solve')

class FORCESNLPsolver_params_ctypes(ctypes.Structure):
#    @classmethod
#    def from_param(self):
#        return self
    _fields_ = [('xinit', ctypes.c_double * 5),
('x0', ctypes.c_double * 210),
('all_parameters', ctypes.c_double * 60),
('reinitialize', ctypes.c_int),
]

FORCESNLPsolver_params = {'xinit' : np.array([]),
'x0' : np.array([]),
'all_parameters' : np.array([]),
'reinitialize' : np.array([]),
}
params = {'xinit' : np.array([]),
'x0' : np.array([]),
'all_parameters' : np.array([]),
'reinitialize' : np.array([]),
}
FORCESNLPsolver_params_types = {'xinit' : np.float64,
'x0' : np.float64,
'all_parameters' : np.float64,
'reinitialize' : np.int32,
}

class FORCESNLPsolver_outputs_ctypes(ctypes.Structure):
#    @classmethod
#    def from_param(self):
#        return self
    _fields_ = [('x01', ctypes.c_double * 7),
('x02', ctypes.c_double * 7),
('x03', ctypes.c_double * 7),
('x04', ctypes.c_double * 7),
('x05', ctypes.c_double * 7),
('x06', ctypes.c_double * 7),
('x07', ctypes.c_double * 7),
('x08', ctypes.c_double * 7),
('x09', ctypes.c_double * 7),
('x10', ctypes.c_double * 7),
('x11', ctypes.c_double * 7),
('x12', ctypes.c_double * 7),
('x13', ctypes.c_double * 7),
('x14', ctypes.c_double * 7),
('x15', ctypes.c_double * 7),
('x16', ctypes.c_double * 7),
('x17', ctypes.c_double * 7),
('x18', ctypes.c_double * 7),
('x19', ctypes.c_double * 7),
('x20', ctypes.c_double * 7),
('x21', ctypes.c_double * 7),
('x22', ctypes.c_double * 7),
('x23', ctypes.c_double * 7),
('x24', ctypes.c_double * 7),
('x25', ctypes.c_double * 7),
('x26', ctypes.c_double * 7),
('x27', ctypes.c_double * 7),
('x28', ctypes.c_double * 7),
('x29', ctypes.c_double * 7),
('x30', ctypes.c_double * 7),
]

FORCESNLPsolver_outputs = {'x01' : np.array([]),
'x02' : np.array([]),
'x03' : np.array([]),
'x04' : np.array([]),
'x05' : np.array([]),
'x06' : np.array([]),
'x07' : np.array([]),
'x08' : np.array([]),
'x09' : np.array([]),
'x10' : np.array([]),
'x11' : np.array([]),
'x12' : np.array([]),
'x13' : np.array([]),
'x14' : np.array([]),
'x15' : np.array([]),
'x16' : np.array([]),
'x17' : np.array([]),
'x18' : np.array([]),
'x19' : np.array([]),
'x20' : np.array([]),
'x21' : np.array([]),
'x22' : np.array([]),
'x23' : np.array([]),
'x24' : np.array([]),
'x25' : np.array([]),
'x26' : np.array([]),
'x27' : np.array([]),
'x28' : np.array([]),
'x29' : np.array([]),
'x30' : np.array([]),
}


class FORCESNLPsolver_info(ctypes.Structure):
#    @classmethod
#    def from_param(self):
#        return self
    _fields_ = [("it", ctypes.c_int),
 ("res_eq", ctypes.c_double),
 ("rsnorm", ctypes.c_double),
 ("pobj", ctypes.c_double),
 ("solvetime", ctypes.c_double),
 ("fevalstime", ctypes.c_double),
 ("QPtime", ctypes.c_double)]

class FILE(ctypes.Structure):
        pass
if sys.version_info.major == 2:
    PyFile_AsFile = ctypes.pythonapi.PyFile_AsFile # problem here with python 3 http://stackoverflow.com/questions/16130268/python-3-replacement-for-pyfile-asfile
    PyFile_AsFile.argtypes = [ctypes.py_object]
    PyFile_AsFile.restype = ctypes.POINTER(FILE)

# determine data types for solver function prototype 
csolver.argtypes = ( ctypes.POINTER(FORCESNLPsolver_params_ctypes), ctypes.POINTER(FORCESNLPsolver_outputs_ctypes), ctypes.POINTER(FORCESNLPsolver_info), ctypes.POINTER(FILE))
csolver.restype = ctypes.c_int

def FORCESNLPsolver_solve(params_arg):
    '''
a Python wrapper for a fast solver generated by FORCESPRO v4.3.1

   OUTPUT = FORCESNLPsolver_py.FORCESNLPsolver_solve(PARAMS) solves a multistage problem
   subject to the parameters supplied in the following dictionary:
       PARAMS['xinit'] - column vector of length 5
       PARAMS['x0'] - column vector of length 210
       PARAMS['all_parameters'] - column vector of length 60
       PARAMS['reinitialize'] - scalar

   OUTPUT returns the values of the last iteration of the solver where
       OUTPUT['x01'] - column vector of size 7
       OUTPUT['x02'] - column vector of size 7
       OUTPUT['x03'] - column vector of size 7
       OUTPUT['x04'] - column vector of size 7
       OUTPUT['x05'] - column vector of size 7
       OUTPUT['x06'] - column vector of size 7
       OUTPUT['x07'] - column vector of size 7
       OUTPUT['x08'] - column vector of size 7
       OUTPUT['x09'] - column vector of size 7
       OUTPUT['x10'] - column vector of size 7
       OUTPUT['x11'] - column vector of size 7
       OUTPUT['x12'] - column vector of size 7
       OUTPUT['x13'] - column vector of size 7
       OUTPUT['x14'] - column vector of size 7
       OUTPUT['x15'] - column vector of size 7
       OUTPUT['x16'] - column vector of size 7
       OUTPUT['x17'] - column vector of size 7
       OUTPUT['x18'] - column vector of size 7
       OUTPUT['x19'] - column vector of size 7
       OUTPUT['x20'] - column vector of size 7
       OUTPUT['x21'] - column vector of size 7
       OUTPUT['x22'] - column vector of size 7
       OUTPUT['x23'] - column vector of size 7
       OUTPUT['x24'] - column vector of size 7
       OUTPUT['x25'] - column vector of size 7
       OUTPUT['x26'] - column vector of size 7
       OUTPUT['x27'] - column vector of size 7
       OUTPUT['x28'] - column vector of size 7
       OUTPUT['x29'] - column vector of size 7
       OUTPUT['x30'] - column vector of size 7

   [OUTPUT, EXITFLAG] = FORCESNLPsolver_py.FORCESNLPsolver_solve(PARAMS) returns additionally
   the integer EXITFLAG indicating the state of the solution with 
       1 - Optimal solution has been found (subject to desired accuracy)
       2 - (only branch-and-bound) A feasible point has been identified for which the objective value is no more than codeoptions.mip.mipgap*100 per cent worse than the global optimum 
       0 - Timeout - maximum number of iterations reached
      -1 - (only branch-and-bound) Infeasible problem (problems solving the root relaxation to the desired accuracy)
      -2 - (only branch-and-bound) Out of memory - cannot fit branch and bound nodes into pre-allocated memory.
      -6 - NaN or INF occured during evaluation of functions and derivatives. Please check your initial guess.
      -7 - Method could not progress. Problem may be infeasible. Run FORCESdiagnostics on your problem to check for most common errors in the formulation.
     -10 - The convex solver could not proceed due to an internal error
    -100 - License error

   [OUTPUT, EXITFLAG, INFO] = FORCESNLPsolver_py.FORCESNLPsolver_solve(PARAMS) returns 
   additional information about the last iterate:
       INFO.it        - number of iterations that lead to this result
       INFO.it2opt    - number of convex solves
       INFO.res_eq    - max. equality constraint residual
       INFO.res_ineq  - max. inequality constraint residual
       INFO.pobj      - primal objective
       INFO.dobj      - dual objective
       INFO.dgap      - duality gap := pobj - dobj
       INFO.rdgap     - relative duality gap := |dgap / pobj|
       INFO.mu        - duality measure
       INFO.sigma     - centering parameter
       INFO.lsit_aff  - iterations of affine line search
       INFO.lsit_cc   - iterations of line search (combined direction)
       INFO.step_aff  - step size (affine direction)
       INFO.step_cc   - step size (centering direction)
       INFO.solvetime - Time needed for solve (wall clock time)

 See also COPYING

    '''
    global _lib

    # convert parameters
    params_py = FORCESNLPsolver_params_ctypes()
    for par in params_arg:
        try:
            #setattr(params_py, par, npct.as_ctypes(np.reshape(params_arg[par],np.size(params_arg[par]),order='A')))
            if isinstance(getattr(params_py, par), ctypes.Array):
                params_arg[par] = np.require(params_arg[par], dtype=FORCESNLPsolver_params_types[par], requirements='F')
                setattr(params_py, par, npct.as_ctypes(np.reshape(params_arg[par],np.size(params_arg[par]),order='F')))
            else:
                setattr(params_py, par, params_arg[par])
        except:
            raise ValueError('Parameter ' + par + ' does not have the appropriate dimensions or data type. Please use numpy arrays for parameters.')
    
    outputs_py = FORCESNLPsolver_outputs_ctypes()
    info_py = FORCESNLPsolver_info()
    if sys.version_info.major == 2:
        if sys.platform.startswith('win'):
            fp = None # if set to none, the solver prints to stdout by default - necessary because we have an access violation otherwise under windows
        else:
            #fp = open('stdout_temp.txt','w')
            fp = sys.stdout
        try:
            PyFile_AsFile.restype = ctypes.POINTER(FILE)
            exitflag = _lib.FORCESNLPsolver_solve( ctypes.byref(params_py), ctypes.byref(outputs_py), ctypes.byref(info_py), PyFile_AsFile(fp)  )
            #fp = open('stdout_temp.txt','r')
            #print (fp.read())
            #fp.close()
        except:
            #print 'Problem with solver'
            raise
    elif sys.version_info.major == 3:
        if sys.platform.startswith('win'):
            libc = ctypes.cdll.msvcrt
        elif sys.platform.startswith('darwin'):
            libc = ctypes.CDLL('libc.dylib')
        else:
            libc = ctypes.CDLL('libc.so.6')       # Open libc
        cfopen = getattr(libc,'fopen')        # Get its fopen
        cfopen.restype = ctypes.POINTER(FILE) # Yes, fopen gives a file pointer
        cfopen.argtypes = [ctypes.c_char_p, ctypes.c_char_p] # Yes, fopen gives a file pointer 
        fp = cfopen('stdout_temp.txt'.encode('utf-8'),'w'.encode('utf-8'))    # Use that fopen 

        try:
            if sys.platform.startswith('win'):
                exitflag = _lib.FORCESNLPsolver_solve( ctypes.byref(params_py), ctypes.byref(outputs_py), ctypes.byref(info_py), None )
            else:
                exitflag = _lib.FORCESNLPsolver_solve( ctypes.byref(params_py), ctypes.byref(outputs_py), ctypes.byref(info_py), fp )
            libc.fclose(fp)
            fptemp = open('stdout_temp.txt','r')
            print (fptemp.read())
            fptemp.close()            
        except:
            #print 'Problem with solver'
            raise

    # convert outputs
    for out in FORCESNLPsolver_outputs:
        FORCESNLPsolver_outputs[out] = npct.as_array(getattr(outputs_py,out))

    return FORCESNLPsolver_outputs,int(exitflag),info_py

solve = FORCESNLPsolver_solve


