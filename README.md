# ti5
钛虎机器人TI5

在工作区/src目录下git clone https://github.com/ti5robot/ti5.git
安装本软件包:
先创建catkin工作空间。 然后将本文件夹克隆到src/目录下，rosdep安装必须的包，用catkin_make来编译。
需要运行的命令如下,假设工作区在~/ros_ws：

cd ~/ros_ws/src

git clone https://github.com/ti5robot/ti5.git

cd ..

rosdep install --from-paths src --ignore-src -r -y

catkin_make

source devel/setup.bash

使用仿真模型
下面给出的是启动钛虎机械臂的一系列命令。启动arm1、arm2、arm3、arm5的方法类似，只要在相应的地方替换掉相应的前缀即可。
1公斤机械臂执行 roslaunch arm1 demo.launch

1公斤机械臂夹爪执行 roslaunch arm1handle demo.launch

2公斤机械臂执行 roslaunch arm2 demo.launch

3公斤机械臂执行 roslaunch arm3 demo.launch

3公斤机械臂夹爪执行 roslaunch arm3handle demo.launch


关于MoveIt!的使用方法可以参考docs/moveit_plugin_tutorial.md

使用真实的钛虎机器人
加载钛虎机械人模型:
roslaunch arm1 demo.launch
打开串口通信
sudo chmod 777 /dev/ttyUSB0
rosrun serial_demo serial_demo
