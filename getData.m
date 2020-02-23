
% function [  ] = getData( con_data_file_name )
%UNTITLED 此处显示有关此函数的摘要
%   此处显示详细说明
fid=fopen('all_skeleton_data.txt','a+');
Path = '.\data\';                   % 设置数据存放的文件夹路径
File = dir(fullfile(Path,'*.csv'));  % 显示文件夹下所有符合后缀名为.txt文件的完整信息
FileNames = {File.name}';  
for file_no = 1 : size(FileNames,1)
    file_no
    pos = strfind(FileNames{file_no},'_');
    %  12A_p11：121110000   12_p11：120110000
    data_no = 0;
    if(FileNames{file_no}(pos(3)-1)=='A')
        x = 0;
        for p = pos(2)+1:pos(3)-2
            x = x*10 + (FileNames{file_no}(p)-'0');
        end
        data_no = data_no + x*10000000 + 1000000;
        data_no = data_no + (FileNames{file_no}(pos(3)+2)-'0')*100000 ...
            + (FileNames{file_no}(pos(3)+3)-'0')*10000;
    else
        x = 0;
        for p = pos(2)+1:pos(3)-1
            x = x*10 + (FileNames{file_no}(p)-'0');
        end
        data_no = data_no + x*10000000;
        data_no = data_no + (FileNames{file_no}(pos(3)+2)-'0')*100000 ...
            + (FileNames{file_no}(pos(3)+3)-'0')*10000;
    end
    % 读数据
    B = [];
    
    fp=fopen([Path FileNames{file_no}]);
    if (fp>0)
       B=fscanf(fp,'%f');
       fclose(fp);
    end
    row = 1;
    col = 1;
    joints = zeros(size(B,1)/81,81);
    for i = 1 : size(B,1)
        row = floor((i-1)/81)+1;
        col = mod(i-1,81)+1;
        joints(row,col) = B(i);
    end
    
    for s=1:row
        if sum(joints(s,2:81))~=0
            fprintf(fid,'%d ',data_no+s); %预留一万
            for i = 1 : 20
                fprintf(fid,'%f %f %f ',joints(s,(i-1)*4+2),joints(s,(i-1)*4+3),joints(s,(i-1)*4+4));
            end
            fprintf(fid,'\n');
        end
    end
end
fclose(fid);
% end

