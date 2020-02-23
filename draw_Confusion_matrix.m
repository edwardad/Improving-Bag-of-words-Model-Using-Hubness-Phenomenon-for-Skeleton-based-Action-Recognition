res_acc = -1*ones(100000,504);
res_c = 0;
for knn = 10
    knn
    for rate = [0.03]
        rate
    for k = 490
        k
        filename = ['.\bar_txt\' num2str(knn) ' ' num2str(rate) '0000 ' num2str(k) '.txt'];
%         filename = '10 0.030000 10.txt';
        [data1]=textread(filename,'%f');
        m_all=reshape(data1,k+1,size(data1,1)/(k+1))';
        m_all(m_all(:,1)>130000) = m_all(m_all(:,1)>130000) - 130000;
        no = floor(m_all(:,1)/10000);
        tongji = [];
        for i = 1 : 12
            tongji(i) = sum(no(:)==i);
        end
        m_all(:,1) = floor(m_all(:,1)/10000);
%         k = size(m_all,2)-1;
        a = 1:500;
        c = 1:100; 
      
        
        for m = 1 :3
            a = unifrnd(0,1,700,1);
            a(a(:)>=0.8) = 1;
            a(a(:)<0.8) = 0;
            a = [1	0	0	0	0	0	0	0	1	0	0	0	1	1	0	0	0	1	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	1	0	0	1	1	0	1	0	0	0	0	0	1	0	0	1	1	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	1	1	1	1	0	1	0	0	0	0	1	0	1	0	0	0	0	0	0	0	1	0	0	0	0	1	0	0	1	0	0	1	0	0	1	0	0	0	0	1	0	0	0	0	0	1	0	0	0	1	0	0	0	0	0	0	0	0	1	1	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	1	1	1	0	0	0	0	0	0	0	1	0	0	0	0	1	0	0	1	0	0	0	0	0	0	0	0	0	1	0	1	0	0	0	0	0	1	0	0	1	1	0	0	0	0	0	1	0	0	0	0	0	0	0	1	0	0	1	0	0	0	1	0	0	0	0	1	0	0	0	0	1	1	0	0	1	0	0	0	0	1	0	1	0	0	1	0	0	0	0	0	0	0	0	1	0	0	0	1	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	1	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	1	0	0	0	0	1	1	0	0	0	0	0	0	1	1	0	0	1	0	0	0	1	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	1	0	0	0	0	0	1	0	0	1	1	1	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	1	0	1	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	1	1	0	0	0	0	0	0	0	0	0	0	1	0	0	1	0	0	0	0	1	0	0	0	0	0	0	0	0	0	1	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	1	0	0	0	1	0	0	0	0	0	1	0	0	0	0	0	0	0	0	1	0	1	0	1	0	0	0	1	1	0	1	0	0	0	0	1	0	0	0	0	1	0	1	0	1	0	0	0	0	0	1	1	0	0	0	1	1	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	1	0	0	0	0	1	1	0	0	0	1	0	0	1	0	0	0	1	0	0	1	0	0	0	0	0	1	1	0	0	0	0	0	0	1	0	1	1	0	0	0	0	0	0	0	0	0	0	1	1	0	0	0	1	0	1	1	1	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	1	1	0	0	0	0	0	0	0	1	0	1	0	0	0	1	0	0	0	0	0	0	1];
            t_label = [];
            t_matrix = [];
            p_label = [];
            p_matrix = [];
            for i = 1 : 12
                no = [];
                for j = 1 : tongji(i)
%                     if(j<=500)
                        if(a(j)==1)
                            p_label = [p_label;m_all(sum(tongji(1:i-1))+j,1)];
                            p_matrix = [p_matrix;m_all(sum(tongji(1:i-1))+j,2:k+1)];
                        else
                            t_label = [t_label;m_all(sum(tongji(1:i-1))+j,1)];
                            t_matrix = [t_matrix;m_all(sum(tongji(1:i-1))+j,2:k+1)];
                        end
%                     else
%                         t_label = [t_label;m_all(sum(tongji(1:i-1))+j,1)];
%                         t_matrix = [t_matrix;m_all(sum(tongji(1:i-1))+j,2:k+1)];
%                     end
                end
            end
            model = svmtrain(t_label, t_matrix, 'libsvm_options');
            [predicted_label, accuracy, c] = svmpredict(p_label, p_matrix, model, 'libsvm_options');
            res_c = res_c + 1;
            res_label = predicted_label;
            res_acc(res_c,1:3) = [knn rate k];
            res_acc(res_c,4) = accuracy(1);
            res_acc(res_c,5:704) = a;
            if(res_c==100)
                mm = 1;
            end
        end
    end
    end
end

res_label = [p_label res_label];
res_label(:,3) = res_label(:,1) - res_label(:,2);

tongji = zeros(12,1);
for i = 1 : 12
    tongji(i) = sum(p_label(:)==i);
end
label_no_count = 12;
every_label_count = 4;
Confusion_matrix = zeros(label_no_count,label_no_count);
for i = 1 : label_no_count
    Confusion_matrix(i,i) = 1;
end
step = 1/every_label_count;
for i = 1 : size(res_label,1)
    
    label_org = res_label(i,1);
    predict_label = res_label(i,2);
    step = 1/tongji(label_org);
    if label_org ~= predict_label
        Confusion_matrix(label_org,label_org) = Confusion_matrix(label_org,label_org) - step;
        Confusion_matrix(label_org,predict_label) = Confusion_matrix(label_org,predict_label) + step;
    end
end

