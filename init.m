function [ joints_no,size_table,joints_all,add1,add2,add3,add4 ] = init()
%UNTITLED2 �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
%% ��ȡ���ݣ�һ�� -> �淶���ָ�����
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
%%   joints_all  ������������
joints_no = all_skeleton_data_correct(:,1);
%  size_table
size_table = [];
joints_all = all_skeleton_data_correct(:,2:col_num+1);
%% add4�� ����Ǻ�����
point_arr3 = [4 5;4 6;8 9;8 10;12 13;12 14;16 17;16 18;];  %����������ϸ����
add4 = zeros(size(joints_all,1),16);  %����Ǻ�����
for row = 1 : size(joints_all)
    for i = 1 : 8
        P1 = joints_all(row,point_arr3(i,1)*3+1:point_arr3(i,1)*3+3);
        P2 = joints_all(row,point_arr3(i,2)*3+1:point_arr3(i,2)*3+3);
        % �����:angle1   
        v = (P2(3)-P1(3))/(P2(1)-P1(1));
        angle1 = atan(v)*180/pi;
        % ���ǣ�angle2
        v = (P2(2)-P1(2))/sqrt((P2(3)-P1(3))*(P2(3)-P1(3))+(P2(1)-P1(1))*(P2(1)-P1(1)));
        angle2 = atan(v)*180/pi;
        add4(row,i*2-1:i*2) = [angle1 angle2];
    end
end
%% add2 :8�Ƕ���Ϣ
add2 = zeros(size(joints_all,1),8);
point_arr = [
    4 8 9  %�Ҽ�-���-��첲�����Ҽ��������磬��word����ȥ���Ҽ磬������ȷ����
    8 4 5  %���-�Ҽ�-�Ҹ첲
    8 9 10 %�Ҽ�-����-����
    4 5 6  %���
    0 16 17 % �Ҵ���-�Ƕ�
    0 12 13 %����ȽǶ�
    16 17 18 %����ϥ�ǽǶ�
    12 13 14% ����ϥ�ǽǶ�
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
%% add1 ��һ֡xyz��ȥǰһ֡����  add3:add2��һ֡��ȥǰһ֡
add1 = zeros(size(joints_all,1),60);
add3 = zeros(size(joints_all,1),8);
for i = 1:size(joints_all,1)-1
    add1(i,:) = joints_all(i+1,1:60)-joints_all(i,1:60);
    add3(i,:) = add2(i+1,:)-add2(i,:);
    % ȥ������
    if floor(joints_no(i)/1000)~=floor(joints_no(i+1)/1000)
        add1(i,:) = 0;
        add3(i,:) = 0;
    end
end
add1(size(joints_all,1),:) = 0;
add3(size(joints_all,1),:) = 0;

end

