function [ joints_no,size_table,joints_all,add1,add2,add3,add4 ] = init()
%UNTITLED2 此处显示有关此函数的摘要
%   此处显示详细说明
%% 读取数据：一列 -> 规范化分割数据
col_num = 60;
filename = 'all_skeleton_data_correct.txt';
[data1]=textread(filename,'%f');
all_skeleton_data_correct = zeros(size(data1,1)/61,col_num+1);
for i = 1 : size(data1,1)
    row = floor((i-1)/61)+1;
    col = mod(i-1,61)+1;
    all_skeleton_data_correct(row,col) = data1(i);
end
%
%%   joints_all  连接所有数据
joints_no = all_skeleton_data_correct(:,1);
%  size_table
size_table = [];
joints_all = all_skeleton_data_correct(:,2:col_num+1);
%% add4： 方向角和仰角
point_arr3 = [4 5;4 6;8 9;8 10;12 13;12 14;16 17;16 18;];  %论文中有详细解释
add4 = zeros(size(joints_all,1),16);  %方向角和仰角
for row = 1 : size(joints_all)
    for i = 1 : 8
        P1 = joints_all(row,point_arr3(i,1)*3+1:point_arr3(i,1)*3+3);
        P2 = joints_all(row,point_arr3(i,2)*3+1:point_arr3(i,2)*3+3);
        % 方向角:angle1   
        v = (P2(3)-P1(3))/(P2(1)-P1(1));
        angle1 = atan(v)*180/pi;
        % 仰角：angle2
        v = (P2(2)-P1(2))/sqrt((P2(3)-P1(3))*(P2(3)-P1(3))+(P2(1)-P1(1))*(P2(1)-P1(1)));
        angle2 = atan(v)*180/pi;
        add4(row,i*2-1:i*2) = [angle1 angle2];
    end
end
%% add2 :8角度信息
add2 = zeros(size(joints_all,1),8);
point_arr = [
    4 8 9  %右肩-左肩-左胳膊（该右肩可能是左肩，是word看上去的右肩，后面再确定）
    8 4 5  %左肩-右肩-右胳膊
    8 9 10 %右肩-右肘-右手
    4 5 6  %左边
    0 16 17 % 右大腿-角度
    0 12 13 %左大腿角度
    16 17 18 %右腿膝盖角度
    12 13 14% 左腿膝盖角度
];
for row = 1 : size(joints_all)
    for i = 1:8
        X1 = joints_all(row,point_arr(i,1)*3+1:point_arr(i,1)*3+3);
        X2 = joints_all(row,point_arr(i,2)*3+1:point_arr(i,2)*3+3);
        X3 = joints_all(row,point_arr(i,3)*3+1:point_arr(i,3)*3+3);
        A = X1-X2;
        B = X2-X3;
        v = sum(A.*B)/(sqrt(sum(A.^2))*sqrt(sum(B.^2)));
        angle = acos(v)*180/pi;
        add2(row,i) = angle;
    end
end
%% add1 后一帧xyz减去前一帧数据  add3:add2后一帧减去前一帧
add1 = zeros(size(joints_all,1),60);
add3 = zeros(size(joints_all,1),8);
for i = 1:size(joints_all,1)-1
    add1(i,:) = joints_all(i+1,1:60)-joints_all(i,1:60);
    add3(i,:) = add2(i+1,:)-add2(i,:);
    % 去除多余
    if floor(joints_no(i)/1000)~=floor(joints_no(i+1)/1000)
        add1(i,:) = 0;
        add3(i,:) = 0;
    end
end
add1(size(joints_all,1),:) = 0;
add3(size(joints_all,1),:) = 0;

end

