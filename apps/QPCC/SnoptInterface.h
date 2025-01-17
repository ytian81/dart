/*
  RTQL8, Copyright (c) 2011 Georgia Tech Graphics Lab
  All rights reserved.

  Author	Zoran Popovic
  Date		06/19/2011
*/

#ifndef QPCC_SNOPT_INTERFACE_H
#define QPCC_SNOPT_INTERFACE_H

#include <vector>
#include <Eigen/Dense>
#include "OptimizerArrayTypes.h"

#ifndef	ZERO
#define	ZERO 1.0e-30
#endif  // ifndef ZERO

namespace qpcc {

class SnoptInterface {
public:
    enum Return { Solution, UserStop, Error, Stop, Infeasible};
    enum UpdateType { Obj = 1, Constr = 2 };
    enum SlackType { NoSlack = 0, Vslack = 1, Wslack = 2 };
    enum AbnormalType { NONE = 0, INFEASIBLE = 1, HESSIAN_UPDATE = 2, HESSIAN_RESET = 3 };
    
    struct Slack {
        int constr_idx;
        SlackType type;
        double val;
    };
    
    typedef int (*updateFunc) (long mask, int compute_gradients, double *coef_values, void *update_data);
    
    SnoptInterface(int constr_total, int coef_total,
                   int nonlin_constr_total, int nonlin_obj_coef, int nonlin_jac_coef,
                   int *constr_eqns, int has_objective, VVD J, VVB JMap, std::vector<double> *constraints,
                   double *objective, std::vector<double> *gradient,	updateFunc update_f, void *update_d);
    
    SnoptInterface(int has_objective, VVD J, VVB JMap, std::vector<double> *constraints, double *objective,
                   std::vector<double> *gradient, updateFunc update_f, void *update_d);
    ~SnoptInterface();
    
    Return solve(double *x, double *lo_bounds, double *hi_bounds, long int unit = 4);
    
    void clear(long mask, int compute_derivs);
    
    void resizeJacobian(int coef_total, int nonlin_coef_total, int constr_total, int nonlin_constr_total);
    void resizeCoef();
    
    int mNumConstr;
    int mNumCoef;
    int mNumNonlinConstr;
    int mNumNonlinObjCoef;
    int mNumNonlinJacCoef;
    
    double *mSolverX;
    double *mProblemX;
    double *mBoundsLo;
    double *mBoundsHi;
    int *mConstrEqns;
    
    int mHasObjective;
    
    static SnoptInterface *mRef;
    
    double *mObj;
    std::vector<double> *mdObjdCoef;
    
    std::vector<double> *mConstr;
    VVD mdConstrdCoef;
    
    Eigen::VectorXd mConstrScale;
    Eigen::VectorXd mCoefScale;
    
    VVB mCoefMap;
    double mReturnedObj;
    
    int mOutput;
    int mSum;
    bool mCheckTerm;
    bool mTermination;
    AbnormalType mAbnormal;
    int mBreak;
    
    void updateSolverX();
    void update(long mask, int compute_derivs, double *x);
    static void checkTermination(int *iAbort, double *xs);
    
    
protected:
    SnoptInterface::updateFunc mUpdateFunc;
    void *mUpdateData;
    
    void scaleValues(long update_type, int compute_derivs);
    
private:
    static void snoptObj(long int *mode, long int *nn_obj, double *x,
                         double *f_obj, double *g_obj, long int *nstate,
                         char *cu, long int *lencu, long int *iu, long int *leniu,
                         double *ru, long int *lenru);
    static void snoptJac(long int *mode, long int *nn_con, long int *nn_jac, long int *ne_jac,
                         double *x, double *f_con, double *g_con, long int *nstate,
                         char *cu, long int *lencu, long int *iu, long int *leniu,
                         double *ru, long int *lenru);
    void fillUpSnoptFormat(VVD jacobian, double **a, long int **ha, long int **ka);
    int sparseCount(int col);
    
};
}

#endif // #ifndef DART_OPTIMIZER_SNOPT_SNOPT_INTERFACE_H

