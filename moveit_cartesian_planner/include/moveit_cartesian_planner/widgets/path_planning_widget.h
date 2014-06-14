#ifndef path_planning_widget_H_
#define path_planning_widget_H_

#include <tf/transform_datatypes.h>
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <tf/tf.h>

#include <ui_path_planning_widget.h>

 #include <moveit_cartesian_planner/add_way_point.h>

#include <QWidget>
#include <QTimer>
#include <QtConcurrentRun>
#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSplitter>
#include <QHeaderView>
#include <QCompleter>
#include <QIntValidator>

namespace moveit_cartesian_planner
{
	namespace widgets {

		class PathPlanningWidget: public QWidget
		{
		Q_OBJECT
		public:
			PathPlanningWidget(std::string ns="");
			virtual ~PathPlanningWidget();
		    std::string get_name()
			{
				return "RobotPathPlanner";
			}
		protected:
			void init();
			std::string param_ns_;
			Ui::PathPlanningWidget ui_;
			QStandardItemModel* pointDataModel;
		private:
			QStringList pointList;
			// checks the range of the points and restricts the user entry for deleting
			// a point from the line edit only to the available points
			void pointRange();
		protected Q_SLOTS:
		    void initTreeView();
			void point_deleted_from_UI();
			void point_added_from_UI();
			void insert_row(const tf::Vector3& position,const tf::Quaternion& orientation,const int count);
			void remove_row(int marker_nr);
			void point_pos_updated_slot(const char* marker_name, const tf::Vector3& position, const tf::Quaternion& orientation);
			void selectedPoint(const QModelIndex& current, const QModelIndex& previous);
			void treeViewDataChanged(const QModelIndex &index,const QModelIndex &index2); 
		Q_SIGNALS:
		    void addPoint( const tf::Vector3 position,const tf::Quaternion orientation);
		    void point_del_UI_signal( std::string marker_name);
		    void point_pos_updated_signal(const char* marker_name, const tf::Vector3& position, const tf::Quaternion& orientation);
			
		};
	}


} //end of namespace moveit_cartesian_planner

#endif //path_planning_widget_H_