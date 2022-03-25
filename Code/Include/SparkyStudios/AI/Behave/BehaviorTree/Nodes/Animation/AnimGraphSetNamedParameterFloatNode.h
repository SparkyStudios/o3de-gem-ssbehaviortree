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

#pragma once

#include <SparkyStudios/AI/Behave/BehaviorTree/Nodes/Animation/AnimGraphSetNamedParameterNode.h>

namespace SparkyStudios::AI::Behave::BehaviorTree::Nodes::Animation
{
    class AnimGraphSetNamedParameterFloatNode : public AnimGraphSetNamedParameterNode<float>
    {
    public:
        AZ_CLASS_ALLOCATOR(AnimGraphSetNamedParameterFloatNode, AZ::SystemAllocator, 0);
        AZ_RTTI(AnimGraphSetNamedParameterFloatNode, "{dae0974d-abd1-468b-8fbc-90eb82e5fd33}", AnimGraphSetNamedParameterNode<float>);

        static constexpr const char* NODE_NAME = "AnimGraphSetNamedParameterFloat";

        AnimGraphSetNamedParameterFloatNode(const std::string& name, const Core::SSBehaviorTreeNodeConfiguration& config);

        static void Reflect(AZ::ReflectContext* context);

        static void RegisterNode(const AZStd::shared_ptr<Core::SSBehaviorTreeRegistry>& registry);

        static Core::SSBehaviorTreePortsList providedPorts();

    protected:
        void SetParameter() override;
    };
} // namespace SparkyStudios::AI::Behave::BehaviorTree::Nodes::Animation