/*
 * Copyright (c) 2014-2015, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Jeongseok Lee <jslee02@gmail.com>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_CONSTRAINT_CONTACTCONSTRAINT_H_
#define DART_CONSTRAINT_CONTACTCONSTRAINT_H_

#include "dart/constraint/ConstraintBase.h"

#include "dart/math/MathTypes.h"
#include "dart/collision/CollisionDetector.h"

namespace dart {

namespace dynamics {
class BodyNode;
class Skeleton;
}  // namespace dynamics

namespace constraint {

/// ContactConstraint represents a contact constraint between two bodies
class ContactConstraint : public ConstraintBase
{
public:
  /// Constructor
  ContactConstraint(collision::Contact& _contact, double _timeStep);

  /// Empty Constructor
  ContactConstraint():ConstraintBase() {};

  /// Destructor
  virtual ~ContactConstraint();

  //----------------------------------------------------------------------------
  // Property settings
  //----------------------------------------------------------------------------

  /// Set global error reduction parameter
  static void setErrorAllowance(double _allowance);

  /// Get global error reduction parameter
  static double getErrorAllowance();

  /// Set global error reduction parameter
  static void setErrorReductionParameter(double _erp);

  /// Get global error reduction parameter
  static double getErrorReductionParameter();

  /// Set global error reduction parameter
  static void setMaxErrorReductionVelocity(double _erv);

  /// Get global error reduction parameter
  static double getMaxErrorReductionVelocity();

  /// Set global constraint force mixing parameter
  static void setConstraintForceMixing(double _cfm);

  /// Get global constraint force mixing parameter
  static double getConstraintForceMixing();

  /// Set first frictional direction
  void setFrictionDirection(const Eigen::Vector3d& _dir);

  /// Get first frictional direction
  const Eigen::Vector3d& getFrictionDirection1() const;

  //----------------------------------------------------------------------------
  // Friendship
  //----------------------------------------------------------------------------

  friend class ConstraintSolver;
  friend class ConstrainedGroup;

public:
  //----------------------------------------------------------------------------
  // Constraint virtual functions
  //----------------------------------------------------------------------------

  // Here applyImpulse is necessary, getInformation, getVelocityChange, applyUnitImpulse
  // are not since there are only used for gathering information for ODE LCP solver
    
  // Documentation inherited
  virtual void update();

  // Documentation inherited
  virtual void getInformation(ConstraintInfo* _info);

  // Documentation inherited
  virtual void applyUnitImpulse(size_t _idx);

  // Documentation inherited
  virtual void getVelocityChange(double* _vel, bool _withCfm);

  // Documentation inherited
  virtual void excite();

  // Documentation inherited
  virtual void unexcite();

  // Documentation inherited
  virtual void applyImpulse(double* _lambda);

  // Documentation inherited
  virtual dynamics::SkeletonPtr getRootSkeleton() const;

  // Documentation inherited
  virtual void uniteSkeletons();

  // Documentation inherited
  virtual bool isActive() const;

// private:
  /// Get change in relative velocity at contact point due to external impulse
  /// \param[out] _relVel Change in relative velocity at contact point of the
  ///                     two colliding bodies
  virtual void getRelVelocity(double* _relVel);

  ///
  void updateFirstFrictionalDirection();

  ///
  Eigen::MatrixXd getTangentBasisMatrixODE(const Eigen::Vector3d& _n);

public:
  /// Time step
  double mTimeStep;

  /// Fircst body node
  dynamics::BodyNode* mBodyNode1;

  /// Second body node
  dynamics::BodyNode* mBodyNode2;

  /// Contacts between mBodyNode1 and mBodyNode2
  std::vector<collision::Contact*> mContacts;

  /// First frictional direction
  Eigen::Vector3d mFirstFrictionalDirection;

  /// Coefficient of Friction
  double mFrictionCoeff;

  /// Coefficient of restitution
  double mRestitutionCoeff;

  /// Local body jacobians for mBodyNode1
  Eigen::aligned_vector<Eigen::Vector6d> mJacobians1;

  /// Local body jacobians for mBodyNode2
  Eigen::aligned_vector<Eigen::Vector6d> mJacobians2;

  ///
  bool mIsFrictionOn;

  /// Index of applied impulse
  size_t mAppliedImpulseIndex;

  ///
  bool mIsBounceOn;

  ///
  bool mActive;

  /// Global constraint error allowance
  static double mErrorAllowance;

  /// Global constraint error redection parameter in the range of [0, 1]. The
  /// default is 0.01.
  static double mErrorReductionParameter;

  /// Maximum error reduction velocity
  static double mMaxErrorReductionVelocity;

  /// Global constraint force mixing parameter in the range of [1e-9, 1]. The
  /// default is 1e-5
  /// \sa http://www.ode.org/ode-latest-userguide.html#sec_3_8_0
  static double mConstraintForceMixing;

public:
  // To get byte-aligned Eigen vectors
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

} // namespace constraint
} // namespace dart

#endif  // DART_CONSTRAINT_CONTACTCONSTRAINT_H_

