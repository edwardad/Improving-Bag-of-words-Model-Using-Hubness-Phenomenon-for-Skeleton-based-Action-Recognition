#include<bits/stdc++.h>
using namespace std;
const int maxn = 750000;
double joints_all[maxn][145];
int knn_table[maxn];
struct Dis_Knn{
	int no;
	double dis;
};
Dis_Knn dis_knn[maxn];
struct Knn_Count{
	int no;
	int count;
};
Knn_Count knn_count[maxn];
bool cmp1(Dis_Knn a,Dis_Knn b){
	return a.dis<b.dis;
}
bool cmp2(Knn_Count a,Knn_Count b){
	return a.count > b.count;
}
double get_dis(int a,int b){
	double dis = 0;
	for(int i = 1; i <= 144; ++i){
		dis += pow(joints_all[a][i]-joints_all[b][i],2);
	}
	return sqrt(dis);
}
int main(int argc,char* a[]){
	int no_st = -1;
	int no_ed = -1;
	int w = 0,r = 0;
	while(a[1][w]!='\0'){
		r = r*10 + a[1][w++]-'0';
	}
//	cout << r << endl;
	no_st = r;
	w = 0,r = 0;
	while(a[2][w]!='\0'){
		r = r*10 + a[2][w++]-'0';
	}
	no_ed = r;
	cout << "no_st:" << no_st << "    no_ed:" << no_ed << endl;
	// ¶ÁÊý¾Ý 
	char *file_name1 = "data_1_144_GuiYi.txt";
	cout << "read " << file_name1 << endl;
	ifstream in_file(file_name1);
	if (!in_file.is_open()) {
		cout << "Error opening file";
		exit(1);
	}
	double get_num;
	int count = -1;
	int row_num = 0;
	cout << "row_num:";
	while (!in_file.eof()) {
		in_file >> get_num;
		joints_all[0][++count] = get_num;
		if(count%1450000==0)	cout << (int)(count/145)  << " ";//<< "get_num:" << (int)get_num << endl;
	}
	in_file.close();
	cout << count << endl;
	row_num = count/145;
	cout << "row_num:" << row_num << endl;
	
	// knn
	cout << "knn start" << endl;
	
	string f_name2 = "table_knn_" + to_string(no_st) + "_" + to_string(no_ed) +".txt";
	ofstream fout2(f_name2);
	for(int i = 0; i < row_num; ++i){
		knn_count[i].no = i;
	}
	double dis = 0;
	int knn_k = 2200;
	if(row_num <= 2200) knn_k = row_num;
	else	knn_k = 2200;
	cout << "row:";
	for(int a = no_st; a < no_ed; ++a){
		cout << a << " ";
//		fout1 << (int)joints_all[a][0] << " ";
		for(int b = 0; b < row_num;++b){
			dis = get_dis(a,b);
			dis_knn[b].dis = dis;
			dis_knn[b].no = b;
//			fout1 << dis << " ";
		}
//		fout1 << endl;
		// knn
		sort(dis_knn,dis_knn+row_num,cmp1);
		fout2 << (int)joints_all[a][0] << " ";
		for(int i = 0; i < knn_k; ++i){
//			++knn_count[dis_knn[i].no].count;
			fout2 <<  dis_knn[i].no << " ";
		}
		fout2 << endl;
	}
	cout << "knn end" << endl;
	
//	fout1.close(); 
	fout2.close(); 
	return 0;
}
