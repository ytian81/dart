/*
 * Copyright (c) 2013-2015, Georgia Tech Research Corporation
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
 *   * This code incorporates portions of Open Dynamics Engine
 *     (Copyright (c) 2001-2004, Russell L. Smith. All rights
 *     reserved.) and portions of FCL (Copyright (c) 2011, Willow
 *     Garage, Inc. All rights reserved.), which were released under
 *     the same BSD license as below
 *
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

#ifndef DART_SIMULATION_WORLD_H_
#define DART_SIMULATION_WORLD_H_

#include <string>
#include <vector>
#include <set>

#include <Eigen/Dense>

#include "dart/common/Timer.h"
#include "dart/common/NameManager.h"
#include "dart/common/Subject.h"
#include "dart/simulation/Recording.h"
#include "dart/dynamics/SimpleFrame.h"
#include "dart/dynamics/Skeleton.h"

namespace dart {

namespace integration {
class Integrator;
}  // namespace integration

namespace dynamics {
class Skeleton;
}  // namespace dynamics

namespace constraint {
class ConstraintSolver;
}  // namespace constraint

namespace simulation {

/// class World
class World : public virtual common::Subject
{
public:

  using NameChangedSignal
      = common::Signal<void(const std::string& _oldName,
                            const std::string& _newName)>;

  //--------------------------------------------------------------------------
  // Constructor and Destructor
  //--------------------------------------------------------------------------

  /// Constructor
  World(const std::string& _name = "world");

  /// Destructor
  virtual ~World();

  /// Create a clone of this World. All Skeletons and SimpleFrames that are held
  /// by this World will be copied over.
  ///
  /// Note that the states of the Skeletons will not be transferred over to this
  /// clone [TODO: copy the states as well]
  std::shared_ptr<World> clone() const;

  //--------------------------------------------------------------------------
  // Properties
  //--------------------------------------------------------------------------

  /// Set the name of this World
  const std::string& setName(const std::string& _newName);

  /// Get the name of this World
  const std::string& getName() const;

  /// Set gravity
  void setGravity(const Eigen::Vector3d& _gravity);

  /// Get gravity
  const Eigen::Vector3d& getGravity() const;

  /// Set time step
  void setTimeStep(double _timeStep);

  /// Get time step
  double getTimeStep() const;

  //--------------------------------------------------------------------------
  // Structural Properties
  //--------------------------------------------------------------------------

  /// Get the indexed skeleton
  dynamics::SkeletonPtr getSkeleton(size_t _index) const;

  /// Find a Skeleton by name
  /// \param[in] The name of the Skeleton you are looking for.
  /// \return If the skeleton does not exist then return nullptr.
  dynamics::SkeletonPtr getSkeleton(const std::string& _name) const;

  /// Get the number of skeletons
  size_t getNumSkeletons() const;

  /// Add a skeleton to this world
  std::string addSkeleton(dynamics::SkeletonPtr _skeleton);

  /// Remove a skeleton from this world
  void removeSkeleton(dynamics::SkeletonPtr _skeleton);

  /// Remove all the skeletons in this world, and return a set of shared
  /// pointers to them, in case you want to recycle them
  std::set<dynamics::SkeletonPtr> removeAllSkeletons();

  /// Get the dof index for the indexed skeleton
  int getIndex(int _index) const;

  /// Get the indexed Entity
  dynamics::SimpleFramePtr getSimpleFrame(size_t _index) const;

  /// Find an Entity by name
  dynamics::SimpleFramePtr getSimpleFrame(const std::string& _name) const;

  /// Get the number of Entities
  size_t getNumSimpleFrames() const;

  /// Add an Entity to this world
  std::string addSimpleFrame(dynamics::SimpleFramePtr _frame);

  /// Remove a SimpleFrame from this world
  void removeSimpleFrame(dynamics::SimpleFramePtr _frame);

  /// Remove all SimpleFrames in this world, and return a set of shared
  /// pointers to them, in case you want to recycle them
  std::set<dynamics::SimpleFramePtr> removeAllSimpleFrames();

  //--------------------------------------------------------------------------
  // Kinematics
  //--------------------------------------------------------------------------

  /// Return whether there is any collision between bodies
  bool checkCollision(bool _checkAllCollisions = false);

  //--------------------------------------------------------------------------
  // Simulation
  //--------------------------------------------------------------------------

  /// Reset the time, frame counter and recorded histories
  void reset();

  /// Calculate the dynamics and integrate the world for one step
  /// \param[in} _resetCommand True if you want to reset to zero the joint
  /// command after simulation step.
  void step(bool _resetCommand = true);

  /// Set current time
  void setTime(double _time);

  /// Get current time
  double getTime() const;

  /// Get the number of simulated frames
  ///
  /// TODO(MXG): I think the name of this function is much too similar to
  /// getSimpleFrame()
  int getSimFrames() const;

  //--------------------------------------------------------------------------
  // Constraint
  //--------------------------------------------------------------------------

  /// Get the constraint solver
  constraint::ConstraintSolver* getConstraintSolver() const;

  /// Set the constraint solver
  void setConstraintSolver(constraint::ConstraintSolver* _constraintSolver);

  /// Bake simulated current state and store it into mRecording
  void bake();

  /// Get recording
  Recording* getRecording();

protected:

  /// Register when a Skeleton's name is changed
  void handleSkeletonNameChange(dynamics::ConstMetaSkeletonPtr _skeleton);

  /// Register when a SimpleFrame's name is changed
  void handleSimpleFrameNameChange(const dynamics::Entity* _entity);

  /// Name of this World
  std::string mName;

  /// Skeletons in this world
  std::vector<dynamics::SkeletonPtr> mSkeletons;

  std::map<dynamics::ConstMetaSkeletonPtr,
           dynamics::SkeletonPtr> mMapForSkeletons;

  /// Connections for noticing changes in Skeleton names
  /// TODO(MXG): Consider putting this functionality into NameManager
  std::vector<common::Connection> mNameConnectionsForSkeletons;

  /// NameManager for keeping track of Skeletons
  dart::common::NameManager<dynamics::SkeletonPtr> mNameMgrForSkeletons;

  /// Entities in this world
  std::vector<dynamics::SimpleFramePtr> mSimpleFrames;

  /// Connections for noticing changes in Frame names
  /// TODO(MXG): Consider putting this functionality into NameManager
  std::vector<common::Connection> mNameConnectionsForSimpleFrames;

  /// Map from raw SimpleFrame pointers to their shared_ptrs
  std::map<const dynamics::SimpleFrame*, dynamics::SimpleFramePtr> mSimpleFrameToShared;

  /// NameManager for keeping track of Entities
  dart::common::NameManager<dynamics::SimpleFramePtr> mNameMgrForSimpleFrames;

  /// The first indeices of each skeleton's dof in mDofs
  ///
  /// For example, if this world has three skeletons and their dof are
  /// 6, 1 and 2 then the mIndices goes like this: [0 6 7].
  std::vector<int> mIndices;

  /// Gravity
  Eigen::Vector3d mGravity;

  /// Simulation time step
  double mTimeStep;

  /// Current simulation time
  double mTime;

  /// Current simulation frame number
  int mFrame;

  /// Constraint solver
  constraint::ConstraintSolver* mConstraintSolver;

  ///
  Recording* mRecording;

  //--------------------------------------------------------------------------
  // Signals
  //--------------------------------------------------------------------------
  NameChangedSignal mNameChangedSignal;

public:
  //--------------------------------------------------------------------------
  // Slot registers
  //--------------------------------------------------------------------------
  common::SlotRegister<NameChangedSignal> onNameChanged;

};

typedef std::shared_ptr<World> WorldPtr;

}  // namespace simulation
}  // namespace dart

#endif  // DART_SIMULATION_WORLD_H_
