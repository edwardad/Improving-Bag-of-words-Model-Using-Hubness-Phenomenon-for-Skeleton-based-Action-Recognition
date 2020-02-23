res_acc = -1*ones(100000,504);
res_c = 0;
for knn = 10 : 50 : 10
    knn
    for rate = [0.03]
        rate
    for k = 300 : 50 : 600
        k
        filename = [num2str(knn) ' ' num2str(rate) '0000 ' num2str(k) '_all.txt'];
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
        b = unifrnd(0,1,500,1);
        
        for m = 1 :3
            a = unifrnd(0,1,700,1);
            a(a(:)>=0.8) = 1;
            a(a(:)<0.8) = 0;
            
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


res_acc = res_acc(1:res_c,:);
res_acc = sortrows(res_acc,-4);


