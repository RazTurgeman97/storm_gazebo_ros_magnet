/*
 * Copyright (c) 2016, Vanderbilt University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Addisu Z. Taddese
 */

#include <ignition/gazebo/System.hh>
#include <ignition/gazebo/Model.hh>
#include <ignition/gazebo/components/Pose.hh>
#include <ignition/plugin/Register.hh>
#include <ignition/math/Vector3.hh>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <memory>
#include <cmath>

namespace storm_gazebo_magnet
{
    class DipoleMagnet : public ignition::gazebo::System,
                         public ignition::gazebo::ISystemConfigure,
                         public ignition::gazebo::ISystemPreUpdate
    {
    private:
        ignition::gazebo::Entity modelEntity;
        ignition::math::Vector3d magneticForce;
        double magneticMomentWheel;   // Magnetic moment of the wheel (A·m²)
        double magneticMomentSurface; // Magnetic moment of the surface (A·m²)
        double distance;              // Distance between wheel and surface (m)
        double angle;                 // Angle between dipoles (rad)

    public:
        DipoleMagnet()
            : magneticForce(0, 0, 0),
              magneticMomentWheel(1.0),   // Default value
              magneticMomentSurface(5.0), // Default value
              distance(0.01),             // Default value (1 cm)
              angle(0.0)                  // Default: aligned dipoles
        {
        }

        void Configure(const ignition::gazebo::Entity &_entity,
                       const std::shared_ptr<const sdf::Element> &_sdf,
                       ignition::gazebo::EntityComponentManager &_ecm,
                       ignition::gazebo::EventManager & /*_eventMgr*/) override
        {
            this->modelEntity = _entity;

            // Parse SDF parameters
            if (_sdf->HasElement("magneticMomentWheel"))
            {
                this->magneticMomentWheel = _sdf->Get<double>("magneticMomentWheel");
            }
            if (_sdf->HasElement("magneticMomentSurface"))
            {
                this->magneticMomentSurface = _sdf->Get<double>("magneticMomentSurface");
            }
            if (_sdf->HasElement("distance"))
            {
                this->distance = _sdf->Get<double>("distance");
            }
            if (_sdf->HasElement("angle"))
            {
                this->angle = _sdf->Get<double>("angle");
            }
        }

        void PreUpdate(const ignition::gazebo::UpdateInfo &_info,
                       ignition::gazebo::EntityComponentManager &_ecm) override
        {
            if (_info.paused)
                return;

            // Calculate magnetic adhesion force
            this->CalculateMagneticAdhesionForce();

            // Apply the force to the model's link
            auto poseComp = _ecm.Component<ignition::gazebo::components::Pose>(this->modelEntity);
            if (poseComp)
            {
                // Retrieve the current pose
                auto pose = poseComp->Data();

                // Simulate force application (e.g., update Z position)
                pose.Pos().Z() += this->magneticForce.Z();
                _ecm.SetComponentData<ignition::gazebo::components::Pose>(this->modelEntity, pose);
            }
        }

        void CalculateMagneticAdhesionForce()
        {
            // Physical constants
            constexpr double mu0 = 4 * M_PI * 1e-7; // Permeability of free space

            // Magnetic force calculation
            double forceMagnitude = (3 * mu0 * this->magneticMomentWheel * this->magneticMomentSurface) /
                                     (4 * M_PI * std::pow(this->distance, 4)) *
                                     (2 * std::pow(std::cos(this->angle), 2) - 1);

            // Apply force in the Z direction to counteract gravity
            this->magneticForce = ignition::math::Vector3d(0, 0, std::abs(forceMagnitude));
        }
    };
} // namespace storm_gazebo_magnet

IGNITION_ADD_PLUGIN(storm_gazebo_magnet::DipoleMagnet,
                    ignition::gazebo::System,
                    ignition::gazebo::ISystemConfigure,
                    ignition::gazebo::ISystemPreUpdate)

IGNITION_ADD_PLUGIN_ALIAS(storm_gazebo_magnet::DipoleMagnet, "storm_gazebo_magnet::DipoleMagnet")
