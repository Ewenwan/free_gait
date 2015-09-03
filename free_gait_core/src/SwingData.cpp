/*
 * SwingData.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#include "free_gait_core/SwingData.hpp"
#include "free_gait_core/SwingProfile.hpp"
#include "free_gait_core/SwingFootTrajectory.hpp"
#include "free_gait_core/SwingJointTrajectory.hpp"

namespace free_gait {

SwingData::SwingData() :
    noTouchdown_(false)
{
}

SwingData::SwingData(const SwingData& other) :
    name_(other.name_),
    surfaceNormal_(other.surfaceNormal_),
    surfaceNormalFrameId_(other.surfaceNormalFrameId_),
    trajectory_(other.trajectory_->clone()),
    noTouchdown_(other.noTouchdown_)
{

}

SwingData::~SwingData()
{
}

const std::string& SwingData::getName() const
{
  return name_;
}

void SwingData::setName(const std::string& name)
{
  name_ = name;
}


const std::string& SwingData::getSurfaceNormalFrameId() const
{
  return surfaceNormalFrameId_;
}

void SwingData::setSurfaceNormalFrameId(const std::string& frameId)
{
  surfaceNormalFrameId_ = frameId;
}

const Vector& SwingData::getSurfaceNormal() const
{
  return surfaceNormal_;
}

void SwingData::setSurfaceNormal(const Vector& surfaceNormal)
{
  surfaceNormal_ = surfaceNormal;
}

const SwingTrajectoryBase& SwingData::getTrajectory() const
{
  return *trajectory_;
}

std::shared_ptr<SwingTrajectoryBase> SwingData::getTrajectory()
{
  return trajectory_;
}

void SwingData::setTrajectory(const SwingTrajectoryBase& trajectory)
{
  trajectory_ = trajectory.clone();
}

std::ostream& operator<<(std::ostream& out, const SwingData& swingData)
{
  out << "Name: " << swingData.name_ << std::endl;
  out << "Surface normal: " << swingData.surfaceNormal_ << std::endl;
  out << "Surface frame: " << swingData.surfaceNormalFrameId_ << std::endl;
  out << "No touchdown: " << swingData.noTouchdown_ << std::endl;

  switch (swingData.trajectory_->getType()) {
    case SwingTrajectoryType::Profile: {
      const auto& trajectory = std::static_pointer_cast<SwingProfile>(swingData.trajectory_);
      out << *trajectory << std::endl;
      break; }
    case SwingTrajectoryType::FootTrajectory: {
      const auto& trajectory = std::static_pointer_cast<SwingFootTrajectory>(swingData.trajectory_);
      out << *trajectory << std::endl;
      break; }
    case SwingTrajectoryType::JointTrajectory: {
      const auto& trajectory = std::static_pointer_cast<SwingJointTrajectory>(swingData.trajectory_);
      out << *trajectory << std::endl;
      break; }
  }

  return out;
}

bool SwingData::isNoTouchdown() const
{
  return noTouchdown_;
}

void SwingData::setNoTouchdown(bool noTouchdown)
{
  noTouchdown_ = noTouchdown;
}

} /* namespace */

