#pragma once

#if !defined(Q_MOC_RUN)
#include <Editor/Application/precompiled.h>

#include <AzCore/IO/Path/Path.h>

#include <AzQtComponents/Components/DockMainWindow.h>
#include <AzQtComponents/Components/FancyDocking.h>
#include <AzQtComponents/Components/StyledDockWidget.h>

#include <SparkyStudios/AI/BehaviorTree/Core/SSBehaviorTreeFactory.h>

#include <QDomDocument>
#include <QMainWindow>
#include <QXmlStreamWriter>

#include <Editor/Widgets/BlackboardProperties.h>
#include <Editor/Widgets/GraphicContainer.h>
#include <Editor/Widgets/NodeProperties.h>
#include <Editor/Widgets/NodesSidePanel.h>
#include <Editor/Widgets/StatusBar.h>
#endif

namespace SparkyStudios::AI::BehaviorTree::Editor::Windows
{
    class MainWindow : public AzQtComponents::DockMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent, const AZ::IO::PathView& projectPath);

        Widgets::GraphicContainer* CurrentTabInfo();
        Widgets::GraphicContainer* GetTabByName(const QString& name);
        void LockEditor(const bool locked);
        void LoadFromXML(const QString& xml);
        void SetCurrentNode(QtNodes::Node* node = nullptr);

        BehaviorTree::Core::SSBehaviorTreeFactory m_factory;

    public slots:
        void OnAutoArrange();
        void OnSceneChanged();
        void OnUndoInvoked();
        void OnRedoInvoked();
        void OnTabSetMainTree(int index);
        void OnTabCustomContextMenuRequested(const QPoint& pos);
        void OnActionClearTriggered(bool createMew);
        void OnPushUndo();
        void OnCreateAbsBehaviorTree(const Core::AbstractBehaviorTree& tree, const QString& bt_name, bool secondary_tabs = true);
        void OnActionSaveTriggered();
        void OnActionSaveAsTriggered();
        void OnActionLoadTriggered();
        void OnAddToModelRegistry(const Core::NodeModel& model);
        void OnTabRenameRequested(int tab_index, QString new_name = QString());
        void OnTreeNodeEdited(QString prev_ID, QString new_ID);

    signals:
        void ValidTree();
        void InvalidTree();

    private:
        struct SavedState
        {
            QString main_tree;
            QString current_tab_name;
            QTransform view_transform;
            QRectF view_area;
            std::map<QString, QByteArray> json_states;
            bool operator==(const SavedState& other) const;
            bool operator!=(const SavedState& other) const
            {
                return !(*this == other);
            }
        };

        enum SubtreeExpandOption
        {
            SUBTREE_EXPAND,
            SUBTREE_COLLAPSE,
            SUBTREE_CHANGE,
            SUBTREE_REFRESH
        };

        void setupShortcuts();
        Widgets::GraphicContainer* createTab(const QString& name, bool setActive = true);
        std::shared_ptr<QtNodes::DataModelRegistry> createDataModelRegistry();
        void loadSavedStateFromJson(SavedState state);
        SavedState saveCurrentState();
        void clearUndoStacks();
        QString saveToXML() const;
        QString xmlDocumentToString(const QDomDocument& document) const;
        void streamElementAttributes(QXmlStreamWriter& stream, const QDomElement& element) const;
        void recursivelySaveNodeCanonically(QXmlStreamWriter& stream, const QDomNode& parent_node) const;
        QtNodes::Node* subTreeExpand(Widgets::GraphicContainer& container, QtNodes::Node& node, MainWindow::SubtreeExpandOption option);
        void saveFile(bool overwrite);

        AzQtComponents::FancyDocking* m_fancyDocking;

        AzQtComponents::TabWidget* m_tabWidget;
        Widgets::NodesSidePanel* m_sidePanel;
        Widgets::StatusBar* m_statusBar;
        Widgets::NodeProperties* m_nodeProperties;
        Widgets::BlackboardProperties* m_blackboardProperties;

        std::deque<SavedState> _undo_stack;
        std::deque<SavedState> _redo_stack;
        SavedState _current_state;

        std::shared_ptr<QtNodes::DataModelRegistry> _model_registry;
        std::map<QString, Widgets::GraphicContainer*> _tab_info;
        QtNodes::PortLayout _current_layout;
        Core::NodeModels _treenode_models;
        Core::BlackboardPropertyModels _blackboard_models;
        QString _main_tree;

        QString _opened_file;

        QString _project_path;
    };

} // namespace SparkyStudios::AI::BehaviorTree::Editor::Windows