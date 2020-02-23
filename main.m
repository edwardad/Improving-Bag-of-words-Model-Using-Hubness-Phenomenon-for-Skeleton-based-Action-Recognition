% %% 2.��ȡC++������������ʼ������
[ joints_no,size_table,joints_all,add1,add2,add3,add4 ] = init();
% %% 3 joints_all ������� ��һ��
joints_all = joints_all(:,1:60);
joints_all(:,61:120) = add1;
joints_all(:,121:128) = add2;
joints_all(:,129:144) = add4;
g = [1 60;61 120;121 128;129 144];
col_num = size(joints_all,2);  %�Զ����������
for i = 1 : size(joints_all,1)
    for j = 1 : size(g,1)
        joints_all(i,g(j,1):g(j,2)) = (joints_all(i,g(j,1):g(j,2))-min(joints_all(i,g(j,1):g(j,2))))/(max(joints_all(i,g(j,1):g(j,2)))-min(joints_all(i,g(j,1):g(j,2))));
    end
end
for i = 1:size(joints_all,1)-1
    % ȥ������
    if floor(joints_no(i)/1000)~=floor(joints_no(i+1)/1000)
        joints_all(i,61:120) = 0;
    end
end
joints_all(size(joints_all,1),61:120) = 0;
joints_all(isnan(joints_all(:))==1)=0;  %ȥ��NAN
%% ������ļ�C++����
fid=fopen('data_1_144_GuiYi.txt','a+');
for i = 1 : size(joints_all,1)
    fprintf(fid,'%d ',joints_no(i));
    for col = 1 : 144
        fprintf(fid,'%f ',joints_all(i,col));
    end
    fprintf(fid,'\n');
end
fclose(fid);