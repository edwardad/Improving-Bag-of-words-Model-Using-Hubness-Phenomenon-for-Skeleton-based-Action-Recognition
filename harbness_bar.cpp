#include<bits/stdc++.h>
using   namespace   std;
const int maxn = 750000;
double joints_all[maxn][145];
int knn_table[maxn];
struct Dis_Knn {
	int no;
	double dis;
};
Dis_Knn dis_knn[maxn];
struct Knn_Count {
	int no;
	long long count;
};
Knn_Count knn_count[maxn];
bool cmp1(Dis_Knn a, Dis_Knn b) {
	return a.dis<b.dis;
}
bool cmp2(Knn_Count a, Knn_Count b) {
	return a.count > b.count;
}
double get_dis(int a, int b) {
	double dis = 0;
	for (int i = 1; i <= 144; ++i) {
		dis += pow(joints_all[a][i] - joints_all[b][i], 2);
	}
	return sqrt(dis);
}
int knnCndidate[750000];
int harb_res_point_no[10000], harb_count = 0;
double max_min_dis[750000], mmd;
int bar_all[260000][1000];
template <class T>
std::string fmt(T in, int width = 0, int prec = 0) {
	std::ostringstream s;
	s << std::setw(width) << std::setprecision(prec) << in;
	return s.str();
}
double weight_txtNo_realNo[750000][3];
int main() {
	// 数据预输入
	// 读数据  weight_txtNo_realNo.txt
	char *weight_txtNo = "C:\\Users\\lsn_1\\Desktop\\Kinect新实验\\5.MSRC-12\\weight_txtNo_realNo.txt";
	ifstream no_file(weight_txtNo);
	if (!no_file.is_open()) {
		cout << "Error opening file";
		exit(1);
	}
	double nnn;
	long long count_no = -1;
	long long row_n = 0;
	cout << weight_txtNo << "  row:";
	while (!no_file.eof()) {
		no_file >> nnn;
		weight_txtNo_realNo[0][++count_no] = nnn;
		if (count_no % 30000 == 0)	cout << count_no / 3 << " ";
	}cout << endl;

	no_file.close();
	cout << count_no << " row_num:";
	row_n = count_no / 3;
	cout << row_n << endl;

	// 读数据  data_1_144_GuiYi
		char *file_name1 = "C:\\Users\\lsn_1\\Desktop\\Kinect新实验\\5.MSRC-12\\data_1_144_GuiYi.txt";
		ifstream in_file(file_name1);
		if (!in_file.is_open()) {
			cout << "Error opening file";
			exit(1);
		}
		double get_num;
		long long count = -1;
		long long row_num = 0;
		cout << file_name1 << "  row:";
		while (!in_file.eof()) {
			in_file >> get_num;
			joints_all[0][++count] = get_num;
			if(count%1450000==0)	cout << count/145 << " ";
		}cout << endl;
		
		in_file.close();
		cout << count << " row_num:";
		row_num = count/145;
		cout << row_num << endl;

	// 测试参数 
	for (int knn_k = 10; knn_k <= 60; knn_k += 50) {
		// knn***************************************************start
		cout << "knn start" << endl << "row:";
		for (int i = 0; i < row_num; ++i) {
			knn_count[i].count = 0;
		}
		// knn_count 
		long long pos_no, knn_txt_no[3000];
		long long row_num = 0;
		cout << "----------------read file-----------------" << endl;
		// 读取多文件 
		

		int st[21] = {0,30000,120000,140000,160000,200000,240000,280000,320000,360000,400000,440000,480000,510000,540000,570000,600000,630000,660000,690000,707123};
		for (int txt_no = 0; txt_no<20; ++txt_no) {
			string file_knn1 = "C:\\Users\\lsn_1\\Desktop\\Kinect新实验\\5.MSRC-12\\table_knn_" + to_string(st[txt_no]) + "_" + to_string(st[txt_no + 1]) + ".txt";
			cout << file_knn1 << endl;
			ifstream knn_file(file_knn1); if (!knn_file.is_open()) { cout << "Error opening file"; exit(1); }
			while (!knn_file.eof()) {
				++row_num;
				if (row_num % 5000 == 0)	cout << row_num << " ";
				knn_file >> pos_no;
				for (int i = 0; i < 2200; ++i) {
					knn_file >> knn_txt_no[i];
				}
				for (int i = 0; i < knn_k; ++i) {
					++knn_count[knn_txt_no[i]].count;
				}
			}cout << endl;
			cout << "row_num: " << row_num << endl;
			knn_file.close();
		}
		//		string file_knn1 = "table_knn_0_30000.txt";
		cout << "read done,row_num:" << row_num << endl;
		for (int i = 0; i < row_num; ++i) {
			knn_count[i].no = i;
		}
		sort(knn_count, knn_count + row_num, cmp2);
		cout << "knn end" << endl;
		// knn***************************************************end 

		for (double knn_rate = 0.03; knn_rate <= 0.06; knn_rate += 0.03) {
			// harb_res_point_no***************************************************start 
			cout << "harb_res_point_no start" << endl;
			harb_count = 0;
			int candia_num = (int)(knn_rate*row_num);
			for (int i = 0; i < candia_num; ++i) {
				knnCndidate[i] = knn_count[i].no;
			}
			// knn_res_point_no
			// 第1点 
			harb_res_point_no[0] = knnCndidate[0];
			knnCndidate[0] = -1;
			harb_count++;
			for (int i = 1; i < candia_num; ++i) {
				int a, b;
				a = harb_res_point_no[0];
				b = knnCndidate[i];
				max_min_dis[i] = get_dis(a, b);
			}
			// 选其他中心点 
			int a, b;
			double dis;
			cout << "harbness：";
			for (int k = 1; k < 520; ++k) {
				cout << k + 1 << " ";
				// 取最大
				double max_v = -555;
				int max_ind = -1;
				for (int i = 0; i < candia_num; ++i) {
					if (knnCndidate[i] != -1 && max_min_dis[i]>max_v) {
						max_v = max_min_dis[i];
						max_ind = i;
					}
				}
				harb_res_point_no[k] = knnCndidate[max_ind];
				knnCndidate[max_ind] = -1;
				harb_count++;
				for (int i = 0; i < candia_num; ++i) {
					max_min_dis[i] = 0;
					if (knnCndidate[i] != -1) {
						double min_v = 99999999;
						for (int j = 0; j < harb_count; ++j) {
							a = harb_res_point_no[j];
							b = knnCndidate[i];
							dis = get_dis(a, b);
							if (dis<min_v) {
								min_v = dis;
							}
						}
						max_min_dis[i] = min_v;
					}
				}
			}
			cout << endl;
			//			cout << harb_count << endl;
			//			for(int i = 0; i < harb_count; ++i){
			//				cout << harb_res_point_no[i] << " ";
			//			}
			//			cout << endl;
			cout << "harb_res_point_no end" << endl;
			// harb_res_point_no***************************************************end 
			for (int center_num = 10; center_num <= 520; center_num += 30) {
				cout << "write:   knn_k:" << knn_k << "  knn_rate:" << knn_rate << "  center_num:" << center_num << endl;
				if (center_num>harb_count) {
					cout << "break!" << " ";
					continue; //继续做下去的话结果重复  因此跳到下一轮 
				}
				cout << "center_point_no:  count" << center_num << endl;
				for (int i = 0; i < center_num; ++i) {
					cout << harb_res_point_no[i] << " ";
				}cout << endl;
				// bar***************************************************start 
				cout << "bar start" << endl;
				memset(bar_all, 0, sizeof(bar_all));
				double min_v;
				int min_no = 0;
				long long seq = 0;
				cout << "row:";
				for (int i = 0; i < row_num; ++i) {
					if (i % 5000 == 0) cout << i + 1 << " ";
					min_v = 9999999;
					min_no = -1;
					a = i;
					for (int j = 0; j < center_num; ++j) {
						b = harb_res_point_no[j];
						dis = get_dis(a, b);
						if (dis<min_v) {
							min_v = dis;
							min_no = j;
						}
					}
					if (weight_txtNo_realNo[i][2] != -1) {
						long long z = joints_all[i][0]/10000;
						seq = z /1000  * 10000 + z%100*100+ weight_txtNo_realNo[i][2];
						if (z % 1000 / 100 == 1) seq += 130000;
						bar_all[seq][min_no + 1]++;
						bar_all[seq][0] = 1; // 标记改行有效 
					}

				}
				cout << row_num << endl;
				cout << "bar end" << endl;
				// bar***************************************************end 
				string f_name1 = ".\\bar_txt\\" + to_string(knn_k) + " " + to_string(knn_rate) + " " + to_string(center_num) + ".txt";
//				string f_name1 = to_string(knn_k) + " " + to_string(knn_rate) + " " + to_string(center_num) + "_all.txt";
				ofstream fout1(f_name1);
				for (int i = 1; i < 260000; ++i) {
					if (bar_all[i][0] == 1) {
						fout1 << i << " ";
						for (int j = 1; j <= center_num; ++j) {
							fout1 << bar_all[i][j] << " ";
						}
						fout1 << endl;
					}
				}
				fout1.close();
			}
		}
	}

	return 0;
}

