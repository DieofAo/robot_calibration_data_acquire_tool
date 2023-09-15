## urdf文件转成dae文件（openrave生成ikfast需要的数据文件）
1. rosrun xacro xacro -o ./ur5.urdf /home/zkkj/workspace/catkin_ws/src/ur_ws/universal_robot/ur_description/urdf/ur5.xacro
2. rosrun collada_urdf urdf_to_collada ./ur5.urdf ./ur5.dae
3. rosrun  moveit_kinematics round_collada_numbers.py ./ur5.dae ./ur5_dot8.dae 8
4. 建立 ur5.xml


## openrave依赖libboost_python
- 依赖libboost_python
- ./
- ./b2 install

## 生成ikfast反解器
- openrave.py --database inversekinematics --robot=./ur5.xml --manipname=ur5  --iktype=transform6d
- openrave.py --database kinematicreachability --robot=./ur5.xml --manipname=ur5 --xyzdelta=0.01 --quatdelta=0.2 --numthreads=10
- openrave-robot.py ./ur5.dae --info links

- 注：openrave 0.9 生成的 ur5反解器有问题（可能跟urdf中坐标系定义有关，第5个关节没有出现在所有的方程中，所以求解不出来）

## docker运行openrave0.9
- docker pull personalrobotics/ros-openrave   （0.9）
- docker run -i -t personalrobotics/ros-openrave /bin/bash 

## docker用户配置
- sudo groupadd docker
- sudo gpasswd -a $USER docker
- newgrp docker
- docker version
- docker images
- docker ps

## docker和宿主机器之间文件传递
- docker cp ./ikfast_ur5/ur5.xml 25bae93b9485:/root
- docker cp  25bae93b9485:/root/.openrave/kinematics.2c9c2acbb12ebc6406118d4ff86046dc/ikfast0x10000049.Transform6D.0_1_2_3_4_5.cpp  .

## docker运行openrave0.5.3
- docker pull fishros2/openrave
- docker run -i -t fishros2/openrave   （0.5.3）  
- docker cp  3b64e9c7fc37:/root/.openrave/kinematics.2c9c2acbb12ebc6406118d4ff86046dc/ikfast0x1000004b.Transform6D.0_1_2_3_4_5.cpp .
- docker cp  3b64e9c7fc37:/root/.openrave/kinematics.2c9c2acbb12ebc6406118d4ff86046dc/ikfast.h .
- exit
- 注：openrave 0.5.3 生成的ur5反解器有问题。需要研究一下，为啥ur5的urdf放到openrave生成的分解器，第五个角度永远是零。

## universal_robot中已经有了ur的分解器，头文件中有介绍基连杆，末端连杆前后的坐标系变化关系
- /home/zkkj/workspace/catkin_ws/src/ur_ws/universal_robot/ur_kinematics/ 中已经有了反解器。
- 可以看看openrave原理的博士论文，如何建立多组关节变量方程。
