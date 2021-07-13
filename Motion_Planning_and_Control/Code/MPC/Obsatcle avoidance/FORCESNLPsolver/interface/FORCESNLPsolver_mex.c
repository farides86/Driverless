/*
FORCESNLPsolver : A fast customized optimization solver.

Copyright (C) 2013-2021 EMBOTECH AG [info@embotech.com]. All rights reserved.


This software is intended for simulation and testing purposes only. 
Use of this software for any commercial purpose is prohibited.

This program is distributed in the hope that it will be useful.
EMBOTECH makes NO WARRANTIES with respect to the use of the software 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE. 

EMBOTECH shall not have any liability for any damage arising from the use
of the software.

This Agreement shall exclusively be governed by and interpreted in 
accordance with the laws of Switzerland, excluding its principles
of conflict of laws. The Courts of Zurich-City shall have exclusive 
jurisdiction in case of any dispute.

*/

#include "mex.h"
#include "math.h"
#include "../include/FORCESNLPsolver.h"
#ifndef SOLVER_STDIO_H
#define SOLVER_STDIO_H
#include <stdio.h>
#endif

/* For compatibility with Microsoft Visual Studio 2015 */
#if _MSC_VER >= 1900
FILE _iob[3];
FILE * __cdecl __iob_func(void)
{
	_iob[0] = *stdin;
	_iob[1] = *stdout;
	_iob[2] = *stderr;
	return _iob;
}
#endif

/* copy functions */

void copyCArrayToM_double(double *src, double *dest, solver_int32_default dim) 
{
    solver_int32_default i;
    for( i = 0; i < dim; i++ ) 
    {
        *dest++ = (double)*src++;
    }
}

void copyMArrayToC_double(double *src, double *dest, solver_int32_default dim) 
{
    solver_int32_default i;
    for( i = 0; i < dim; i++ ) 
    {
        *dest++ = (double) (*src++) ;
    }
}

void copyMValueToC_double(double * src, double * dest)
{
	*dest = (double) *src;
}



extern void FORCESNLPsolver_casadi2forces(FORCESNLPsolver_float *x, FORCESNLPsolver_float *y, FORCESNLPsolver_float *l, FORCESNLPsolver_float *p, FORCESNLPsolver_float *f, FORCESNLPsolver_float *nabla_f, FORCESNLPsolver_float *c, FORCESNLPsolver_float *nabla_c, FORCESNLPsolver_float *h, FORCESNLPsolver_float *nabla_h, FORCESNLPsolver_float *hess, solver_int32_default stage, solver_int32_default iteration, solver_int32_default threadID);
FORCESNLPsolver_extfunc pt2function_FORCESNLPsolver = &FORCESNLPsolver_casadi2forces;


/* Some memory for mex-function */
static FORCESNLPsolver_params params;
static FORCESNLPsolver_output output;
static FORCESNLPsolver_info info;

/* THE mex-function */
void mexFunction( solver_int32_default nlhs, mxArray *plhs[], solver_int32_default nrhs, const mxArray *prhs[] )  
{
	/* file pointer for printing */
	FILE *fp = NULL;

	/* define variables */	
	mxArray *par;
	mxArray *outvar;
	const mxArray *PARAMS = prhs[0];
	double *pvalue;
	solver_int32_default i;
	solver_int32_default exitflag;
	const solver_int8_default *fname;
	const solver_int8_default *outputnames[50] = {"x01","x02","x03","x04","x05","x06","x07","x08","x09","x10","x11","x12","x13","x14","x15","x16","x17","x18","x19","x20","x21","x22","x23","x24","x25","x26","x27","x28","x29","x30","x31","x32","x33","x34","x35","x36","x37","x38","x39","x40","x41","x42","x43","x44","x45","x46","x47","x48","x49","x50"};
	const solver_int8_default *infofields[10] = { "it", "it2opt", "res_eq", "res_ineq",  "rsnorm",  "rcompnorm",  "pobj",  "mu",  "solvetime",  "fevalstime"};
	
	/* Check for proper number of arguments */
    if (nrhs != 1) 
	{
        mexErrMsgTxt("This function requires exactly 1 input: PARAMS struct.\nType 'help FORCESNLPsolver_mex' for details.");
    }    
	if (nlhs > 3) 
	{
        mexErrMsgTxt("This function returns at most 3 outputs.\nType 'help FORCESNLPsolver_mex' for details.");
    }

	/* Check whether params is actually a structure */
	if( !mxIsStruct(PARAMS) ) 
	{
		mexErrMsgTxt("PARAMS must be a structure.");
	}

	/* copy parameters into the right location */
	par = mxGetField(PARAMS, 0, "x0");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.x0 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.x0 must be a double.");
    }
    if( mxGetM(par) != 350 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.x0 must be of size [350 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.x0,350);

	}
	par = mxGetField(PARAMS, 0, "xinit");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.xinit not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.xinit must be a double.");
    }
    if( mxGetM(par) != 5 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.xinit must be of size [5 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.xinit,5);

	}
	par = mxGetField(PARAMS, 0, "all_parameters");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.all_parameters not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.all_parameters must be a double.");
    }
    if( mxGetM(par) != 100 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.all_parameters must be of size [100 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.all_parameters,100);

	}


	#if SET_PRINTLEVEL_FORCESNLPsolver > 0
		/* Prepare file for printfs */
        fp = fopen("stdout_temp","w+");
		if( fp == NULL ) 
		{
			mexErrMsgTxt("freopen of stdout did not work.");
		}
		rewind(fp);
	#endif

	/* call solver */
	exitflag = FORCESNLPsolver_solve(&params, &output, &info, fp, pt2function_FORCESNLPsolver);
	
	#if SET_PRINTLEVEL_FORCESNLPsolver > 0
		/* Read contents of printfs printed to file */
		rewind(fp);
		while( (i = fgetc(fp)) != EOF ) 
		{
			mexPrintf("%c",i);
		}
		fclose(fp);
	#endif

	/* copy output to matlab arrays */
	plhs[0] = mxCreateStructMatrix(1, 1, 50, outputnames);
		outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x01, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x01", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x02, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x02", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x03, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x03", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x04, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x04", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x05, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x05", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x06, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x06", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x07, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x07", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x08, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x08", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x09, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x09", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x10, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x10", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x11, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x11", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x12, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x12", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x13, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x13", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x14, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x14", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x15, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x15", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x16, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x16", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x17, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x17", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x18, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x18", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x19, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x19", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x20, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x20", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x21, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x21", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x22, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x22", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x23, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x23", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x24, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x24", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x25, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x25", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x26, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x26", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x27, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x27", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x28, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x28", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x29, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x29", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x30, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x30", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x31, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x31", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x32, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x32", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x33, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x33", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x34, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x34", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x35, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x35", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x36, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x36", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x37, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x37", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x38, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x38", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x39, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x39", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x40, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x40", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x41, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x41", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x42, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x42", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x43, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x43", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x44, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x44", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x45, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x45", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x46, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x46", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x47, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x47", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x48, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x48", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x49, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x49", outvar);

	outvar = mxCreateDoubleMatrix(7, 1, mxREAL);
	copyCArrayToM_double( output.x50, mxGetPr(outvar), 7);
	mxSetField(plhs[0], 0, "x50", outvar);

	/* copy exitflag */
	if( nlhs > 1 )
	{
	plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
	*mxGetPr(plhs[1]) = (double)exitflag;
	}

	/* copy info struct */
	if( nlhs > 2 )
	{
	        plhs[2] = mxCreateStructMatrix(1, 1, 10, infofields);
         
		
		/* iterations */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = (double)info.it;
		mxSetField(plhs[2], 0, "it", outvar);

		/* iterations to optimality (branch and bound) */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = (double)info.it2opt;
		mxSetField(plhs[2], 0, "it2opt", outvar);
		
		/* res_eq */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.res_eq;
		mxSetField(plhs[2], 0, "res_eq", outvar);

		/* res_ineq */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.res_ineq;
		mxSetField(plhs[2], 0, "res_ineq", outvar);

		/* rsnorm */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.rsnorm;
		mxSetField(plhs[2], 0, "rsnorm", outvar);

		/* rcompnorm */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.rcompnorm;
		mxSetField(plhs[2], 0, "rcompnorm", outvar);
		
		/* pobj */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.pobj;
		mxSetField(plhs[2], 0, "pobj", outvar);

		/* mu */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.mu;
		mxSetField(plhs[2], 0, "mu", outvar);

		/* solver time */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.solvetime;
		mxSetField(plhs[2], 0, "solvetime", outvar);

		/* solver time */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.fevalstime;
		mxSetField(plhs[2], 0, "fevalstime", outvar);
	}
}