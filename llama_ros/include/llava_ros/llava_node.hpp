// MIT License

// Copyright (c) 2024  Miguel Ángel González Santamarta

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef LLAMA_ROS__LLAVA_NODE_HPP
#define LLAMA_ROS__LLAVA_NODE_HPP

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

#include <memory>
#include <string>

#include "common.h"
#include "llama_msgs/action/generate_response.hpp"
#include "llama_utils/gpt_params.hpp"
#include "llava_ros/llava.hpp"

namespace llava_ros {

class LlavaNode : public rclcpp::Node {

  using GenerateResponse = llama_msgs::action::GenerateResponse;
  using GoalHandleGenerateResponse =
      rclcpp_action::ServerGoalHandle<GenerateResponse>;

public:
  LlavaNode();

  std::shared_ptr<Llava> llava;
  llama_utils::GptParams gpt_params;

  std::string base64_encode(unsigned char const *bytes_to_encode, size_t in_len,
                            bool url = false);

private:
  rclcpp_action::Server<GenerateResponse>::SharedPtr
      generate_response_action_server_;
  std::shared_ptr<GoalHandleGenerateResponse> goal_handle_;

  rclcpp_action::GoalResponse
  handle_goal(const rclcpp_action::GoalUUID &uuid,
              std::shared_ptr<const GenerateResponse::Goal> goal);
  rclcpp_action::CancelResponse
  handle_cancel(const std::shared_ptr<GoalHandleGenerateResponse> goal_handle);
  void handle_accepted(
      const std::shared_ptr<GoalHandleGenerateResponse> goal_handle);

  void execute(const std::shared_ptr<GoalHandleGenerateResponse> goal_handle);
  void send_text(const struct completion_output &completion);
};

} // namespace llava_ros

#endif