// Copyright (c) 2021-present Sparky Studios. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <StdAfx.h>

#include <SparkyStudios/AI/Behave/Nodes/Animation/SimpleMotionSetLoopMotionNode.h>

#include <Integration/SimpleMotionComponentBus.h>

namespace SparkyStudios::AI::Behave::BehaviorTree::Nodes::Animation
{
    SimpleMotionSetLoopMotionNode::SimpleMotionSetLoopMotionNode(
        const std::string& name, const Core::SSBehaviorTreeNodeConfiguration& config)
        : Core::SSBehaviorTreeNode(name, config)
    {
    }

    void SimpleMotionSetLoopMotionNode::Reflect(AZ::ReflectContext* reflection)
    {
        AZ_UNUSED(reflection);
    }

    void SimpleMotionSetLoopMotionNode::RegisterNode(const AZStd::shared_ptr<Core::SSBehaviorTreeRegistry>& registry)
    {
        registry->DelayNodeRegistration<SimpleMotionSetLoopMotionNode>(NODE_NAME);
    }

    Core::SSBehaviorTreePortsList SimpleMotionSetLoopMotionNode::providedPorts()
    {
        Core::SSBehaviorTreePortsList ports = Core::SSBehaviorTreeNode::providedPorts();

        ports.merge(Core::SSBehaviorTreePortsList({
            BT::InputPort<bool>(NODE_PORT_VALUE_NAME, NODE_PORT_VALUE_DESCRIPTION),
        }));

        return ports;
    }

    Core::SSBehaviorTreeNodeStatus SimpleMotionSetLoopMotionNode::Tick()
    {
        Core::Optional<bool> value = GetInputValue<bool>(NODE_PORT_VALUE_NAME);

        if (value.has_value())
        {
            EBUS_EVENT_ID(GetEntityId(), EMotionFX::Integration::SimpleMotionComponentRequestBus, LoopMotion, value.value());
            return Core::SSBehaviorTreeNodeStatus::SUCCESS;
        }

        return Core::SSBehaviorTreeNodeStatus::SUCCESS;
    }
} // namespace SparkyStudios::AI::Behave::BehaviorTree::Nodes::Animation
