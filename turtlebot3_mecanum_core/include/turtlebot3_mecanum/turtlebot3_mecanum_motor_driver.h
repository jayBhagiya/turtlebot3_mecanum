/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
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
*******************************************************************************/

/* Authors: Yoonseok Pyo, Leon Jung, Darby Lim, HanCheol Cho */

#ifndef TURTLEBOT3_MECANUM_MOTOR_DRIVER_H_
#define TURTLEBOT3_MECANUM_MOTOR_DRIVER_H_

#include <ros.h>

#include "variant.h"
#include <DynamixelSDK.h>

// Control table address (Dynamixel X-series)
#define ADDR_X_TORQUE_ENABLE            64
#define ADDR_X_GOAL_VELOCITY            104
#define ADDR_X_PROFILE_ACCELERATION     108
#define ADDR_X_PROFILE_VELOCITY         112
#define ADDR_X_GOAL_POSITION            116
#define ADDR_X_REALTIME_TICK            120
#define ADDR_X_PRESENT_VELOCITY         128
#define ADDR_X_PRESENT_POSITION         132

// Limit values (XM430-W210-T and XM430-W350-T)
#define BURGER_DXL_LIMIT_MAX_VELOCITY            265     // MAX RPM is 61 when XL is powered 12.0V
#define WAFFLE_DXL_LIMIT_MAX_VELOCITY            330     // MAX RPM is 77 when XM is powered 12.0V
#define MECANUM_DXL_LIMIT_MAX_VELOCITY           265     // MAX RPM is 61 when XL is powered 12.0V

// Data Byte Length
#define LEN_X_TORQUE_ENABLE             1
#define LEN_X_GOAL_VELOCITY             4
#define LEN_X_GOAL_POSITION             4
#define LEN_X_REALTIME_TICK             2
#define LEN_X_PRESENT_VELOCITY          4
#define LEN_X_PRESENT_POSITION          4

#define PROTOCOL_VERSION                2.0     // Dynamixel protocol version 2.0

/**/
// CHANGED ADDED IDs of the four motors
// #define DXL_LEFT_ID                     1       // ID of left motor
// #define DXL_RIGHT_ID                    2       // ID of right motor

#define DXL_LEFT_FRONT_ID               1       // ID of left front motor
#define DXL_RIGHT_FRONT_ID              2       // ID of right front motor
#define DXL_LEFT_REAR_ID                3       // ID of left rear motor
#define DXL_RIGHT_REAR_ID               4       // ID of right rear motor
/**/

#define BAUDRATE                        1000000 // baurd rate of Dynamixel
#define DEVICENAME                      ""      // no need setting on OpenCR

#define TORQUE_ENABLE                   1       // Value for enabling the torque
#define TORQUE_DISABLE                  0       // Value for disabling the torque

/**/
// CHANGED ADDED address of the four motors
// #define LEFT                            0
// #define RIGHT                           1

#define LEFT_FRONT                      0       // Address of left front motor
#define RIGHT_FRONT                     1       // Address of right front motor
#define LEFT_REAR                       2       // Address of left rear motor
#define RIGHT_REAR                      3       // Address of right rear motor

#define LINEAR_X                        0
#define LINEAR_Y                        1
#define ANGULAR                         2

/**/

#define VELOCITY_CONSTANT_VALUE         41.69988758  // V = r * w = r     *        (RPM             * 0.10472)
                                                     //           = r     * (0.229 * Goal_Velocity) * 0.10472
                                                     //                      0.229 rev/min  for unit -> Dynamixel XL430-W250T
                                                     //
                                                     // Goal_Velocity = V / r * 41.69988757710309
                                                     // Goal_Velocity = w * 41.69988757710309

#define DEBUG_SERIAL  SerialBT2

class Turtlebot3MotorDriver
{
 public:
  Turtlebot3MotorDriver();
  ~Turtlebot3MotorDriver();
  bool init(String turtlebot3);
  void close(void);
  bool setTorque(bool onoff);
  bool getTorque();
  bool readEncoder(int32_t &left_front_value, int32_t &right_front_value, int32_t &left_rear_value, int32_t &right_rear_value);
  bool writeVelocity(int64_t left_front_value, int64_t right_front_value, int64_t left_rear_value, int64_t right_rear_value);
  bool controlMotor(const float wheel_radius, const float wheel_separation, float* value);

 private:
  uint32_t baudrate_;
  float  protocol_version_;

  /**/
  // ADDED Variables for 4 wheels
  // uint8_t left_wheel_id_;
  // uint8_t right_wheel_id_;

  uint8_t left_front_wheel_id_;
  uint8_t right_front_wheel_id_;
  uint8_t left_rear_wheel_id_;
  uint8_t right_rear_wheel_id_;

  /**/
  
  bool torque_;

  uint16_t dynamixel_limit_max_velocity_;

  dynamixel::PortHandler *portHandler_;
  dynamixel::PacketHandler *packetHandler_;

  dynamixel::GroupSyncWrite *groupSyncWriteVelocity_;
  dynamixel::GroupSyncRead *groupSyncReadEncoder_;
};

#endif // TURTLEBOT3_MECANUM_MOTOR_DRIVER_H_
