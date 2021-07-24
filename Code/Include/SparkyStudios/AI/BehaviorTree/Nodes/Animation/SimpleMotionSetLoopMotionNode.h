#pragma once

#include <SparkyStudios/AI/BehaviorTree/Core/SSBehaviorTreeNode.h>
#include <SparkyStudios/AI/BehaviorTree/Core/SSBehaviorTreeRegistry.h>

namespace SparkyStudios::AI::BehaviorTree::Nodes::Animation
{
    class SimpleMotionSetLoopMotionNode : public Core::SSBehaviorTreeNode
    {
    public:
        AZ_CLASS_ALLOCATOR(SimpleMotionSetLoopMotionNode, AZ::SystemAllocator, 0);
        AZ_RTTI(SimpleMotionSetLoopMotionNode, "{5d158fa0-079d-4b96-adbb-1c346e22cabb}", Core::SSBehaviorTreeNode);

        static constexpr const char* NODE_NAME = "SimpleMotionSetLoopMotion";

        static constexpr const char* NODE_PORT_VALUE_NAME = "value";
        static constexpr const char* NODE_PORT_VALUE_DESCRIPTION = "The loop state to define to the simple motion.";

        SimpleMotionSetLoopMotionNode(const std::string& name, const Core::SSBehaviorTreeNodeConfiguration& config);

        static void Reflect(AZ::ReflectContext* reflection);

        static void RegisterNode(const AZStd::shared_ptr<Core::SSBehaviorTreeRegistry>& registry);

        static Core::SSBehaviorTreePortsList providedPorts();

        const std::string NodeCategory() const override
        {
            return "Animation";
        }

    protected:
        Core::SSBehaviorTreeNodeStatus Tick();
    };
} // namespace SparkyStudios::AI::BehaviorTree::Nodes::Animation
