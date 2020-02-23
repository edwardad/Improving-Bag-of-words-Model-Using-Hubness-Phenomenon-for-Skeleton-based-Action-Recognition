#include<bits/stdc++.h>
using namespace std;

int segment_line_no[24][2] = { { 2,3 },{ 20,2 },{ 20,4 },{ 20,8 },{ 4,5 },{ 5,6 },{ 6,7 },{ 6,22 },{ 7,21 },{ 8,9 },{ 9,10 },{ 10,11 },
{ 10,24 },{ 11,23 },{ 1,20 },{ 1,0 },{ 0,12 },{ 12,13 },{ 13,14 },{ 14,15 },{ 0,16 },{ 16,17 },{ 17,18 },{ 18,19 } };
int main(){
	double std[25][3] = { { 970,500,0 },{ 970,330,0 },{ 970,215,0 },{ 970,110,0 },{ 870,270,0 },{ 826,474,0 },
	{ 799,609,0 },{ 769,650,0 },{ 1065,280,0 },{ 1115,487,0 },{ 1145,623,0 },{ 1175,663,0 },{ 910,513,0 },
	{ 875,790,0 },{ 867,977,0 },{ 870,1063,0 },{ 1030,513,0 },{ 1067,790,0 },{ 1070,977,0 },{ 1073,1063,0 },
	{ 970,257,0 },{ 759,696,0 },{ 804,657,0 },{ 1180,705,0 },{ 1140,675,0 } };
	//1.取数据
	char *file_name1 = "all_skeleton_data.txt";
	ifstream in_file(file_name1);
	if (!in_file.is_open()) {
		cout << "Error opening file";
		exit(1);
	}
	string f_name1 = "all_skeleton_data_correct.txt";
	ofstream fout1(f_name1);
	double p[25][3] = {};
	double PointArr[61] = {};
	int count = 0;
	cout << "read " << endl; 
	while (!in_file.eof()) {
		count++;
		for(int i = 0; i < 61; ++i)	in_file >> PointArr[i];
		if(count%1000==0)	cout << "row:" << count << endl;
		for (int k = 0; k < 60; ++k) p[0][k] = PointArr[k+1];
		//20 SpineShoulder 
		for (int k = 0; k < 3; ++k)	p[20][k] = PointArr[2 * 3 + 1 + k];
		//21 HandTipLeft 
		for (int k = 0; k < 3; ++k)	p[21][k] = PointArr[7 * 3 + 1 + k];
		//22 ThumbLeft 
		for (int k = 0; k < 3; ++k)	p[22][k] = PointArr[6 * 3 + 1 + k];
		//23 HandTipRight 
		for (int k = 0; k < 3; ++k)	p[23][k] = PointArr[11 * 3 + 1 + k];
		//24 ThumbRight 
		for (int k = 0; k < 3; ++k)	p[24][k] = PointArr[10 * 3 + 1 + k];
		//2 平移使1号 SpineMid   坐标为0，0，0
		for (int i = 0; i < 25; ++i) {
			p[i][0] -= p[1][0];
			p[i][1] -= p[1][1];
			p[i][2] -= p[1][2];
		}
//		for (int k = 0; k < 25; ++k) {
//			cout << k << " " << p[k][0] << " " << p[k][1] << " " << p[k][2] << endl;
//		}
		// 3 伸展骨节，统一骨长比例
		double correct_dis[25][3] = {};
		for (int i = 0; i < 24; ++i) {
			int point_st, point_ed;
			double std_dis_x, std_dis_y, std_dis_z, experiment_dis_x, line_length, experiment_dis_y, experiment_dis_z, experiment_line_length;
			point_st = segment_line_no[i][0];
			point_ed = segment_line_no[i][1];
			// 模板线段长度
			std_dis_x = std[point_ed][0] - std[point_st][0];
			std_dis_y = std[point_ed][1] - std[point_st][1];
			std_dis_z = std[point_ed][2] - std[point_st][2];
			line_length = sqrt(std_dis_x * std_dis_x + std_dis_y * std_dis_y + std_dis_z * std_dis_z);
			experiment_dis_x = p[point_ed][0] - p[point_st][0];
			experiment_dis_y = p[point_ed][1] - p[point_st][1];
			experiment_dis_z = p[point_ed][2] - p[point_st][2];
			// 实验线段长度
			experiment_line_length = sqrt(experiment_dis_x * experiment_dis_x + experiment_dis_y * experiment_dis_y + experiment_dis_z * experiment_dis_z);
			// 修正点需要修正的长度
			// 后期修改可能直接确定corect_proportion（比例）的值
			double corect_proportion;
			if (line_length != 0 && experiment_line_length != 0) {
				corect_proportion = line_length / experiment_line_length - 1;
				correct_dis[point_ed][0] = corect_proportion * experiment_dis_x;
				correct_dis[point_ed][1] = corect_proportion * experiment_dis_y;
				correct_dis[point_ed][2] = corect_proportion * experiment_dis_z;
			}
		}
		//for (int i = 0; i < 25; ++i) {
		//	cout << i << ". " << correct_dis[i][0] << " " << correct_dis[i][1] << " " << correct_dis[i][2] << endl;
		//}
		double corrected_p[25][3] = {};
		//开始修正关节点   corrected_p:修正后的p
		for (int i = 0; i < 3; ++i) {
			corrected_p[1][i] = p[1][i];
			corrected_p[0][i] = p[0][i] + correct_dis[0][i];
			corrected_p[12][i] = p[12][i] + correct_dis[0][i] + correct_dis[12][i];
			corrected_p[13][i] = p[13][i] + correct_dis[0][i] + correct_dis[12][i] + correct_dis[13][i];
			corrected_p[14][i] = p[14][i] + correct_dis[0][i] + correct_dis[12][i] + correct_dis[13][i] + correct_dis[14][i];
			corrected_p[15][i] = p[15][i] + correct_dis[0][i] + correct_dis[12][i] + correct_dis[13][i] + correct_dis[14][i] + correct_dis[15][i];
			corrected_p[16][i] = p[16][i] + correct_dis[0][i] + correct_dis[16][i];
			corrected_p[17][i] = p[17][i] + correct_dis[0][i] + correct_dis[16][i] + correct_dis[17][i];
			corrected_p[18][i] = p[18][i] + correct_dis[0][i] + correct_dis[16][i] + correct_dis[17][i] + correct_dis[18][i];
			corrected_p[19][i] = p[19][i] + correct_dis[0][i] + correct_dis[16][i] + correct_dis[17][i] + correct_dis[18][i] + correct_dis[19][i];
			corrected_p[20][i] = p[20][i] + correct_dis[20][i];
			corrected_p[2][i] = p[2][i] + correct_dis[20][i] + correct_dis[2][i];
			corrected_p[3][i] = p[3][i] + correct_dis[20][i] + correct_dis[2][i] + correct_dis[3][i];
			corrected_p[4][i] = p[4][i] + correct_dis[20][i] + correct_dis[4][i];
			corrected_p[5][i] = p[5][i] + correct_dis[20][i] + correct_dis[4][i] + correct_dis[5][i];
			corrected_p[6][i] = p[6][i] + correct_dis[20][i] + correct_dis[4][i] + correct_dis[5][i] + correct_dis[6][i];
			corrected_p[7][i] = p[7][i] + correct_dis[20][i] + correct_dis[4][i] + correct_dis[5][i] + correct_dis[6][i] + correct_dis[7][i];
			corrected_p[21][i] = p[21][i] + correct_dis[20][i] + correct_dis[4][i] + correct_dis[5][i] + correct_dis[6][i] + correct_dis[7][i] + correct_dis[21][i];
			corrected_p[22][i] = p[22][i] + correct_dis[20][i] + correct_dis[4][i] + correct_dis[5][i] + correct_dis[6][i] + correct_dis[22][i];
			corrected_p[8][i] = p[8][i] + correct_dis[20][i] + correct_dis[8][i];
			corrected_p[9][i] = p[9][i] + correct_dis[20][i] + correct_dis[8][i] + correct_dis[9][i];
			corrected_p[10][i] = p[10][i] + correct_dis[20][i] + correct_dis[8][i] + correct_dis[9][i] + correct_dis[10][i];
			corrected_p[11][i] = p[11][i] + correct_dis[20][i] + correct_dis[8][i] + correct_dis[9][i] + correct_dis[10][i] + correct_dis[11][i];
			corrected_p[24][i] = p[24][i] + correct_dis[20][i] + correct_dis[8][i] + correct_dis[9][i] + correct_dis[10][i] + correct_dis[24][i];
			corrected_p[23][i] = p[23][i] + correct_dis[20][i] + correct_dis[8][i] + correct_dis[9][i] + correct_dis[10][i] + correct_dis[11][i] + correct_dis[23][i];
		}
		//for (int i = 0; i < 25; ++i) {
		//	cout << i << " " << corrected_p[i][0] << " " << corrected_p[i][1] << " " << corrected_p[i][2] << endl;
		//}
		// 4 旋转
		double s = atan(corrected_p[16][2]/ corrected_p[16][0]);
		double x1, y1, z1;
		for (int i = 0; i < 25; ++i) {
			x1 = corrected_p[i][0] *cos(s) + corrected_p[i][2] *sin(s);
			y1 = corrected_p[i][1];
			z1 = -1 * corrected_p[i][0] *sin(s) + corrected_p[i][2] *cos(s);
			if (x1<1e-6&&x1>-1e-6)	x1 = 0;
			if (y1<1e-6&&y1>-1e-6)	y1 = 0;
			if (z1<1e-6&&z1>-1e-6)	z1 = 0;
			corrected_p[i][0] = x1;
			corrected_p[i][1] = y1;
			corrected_p[i][2] = z1;
			//cout << i << " " <<  x1 << " " << y1 << " " << z1 << endl;
		}

		//for (int i = 0; i < 25; ++i) {
		//	cout << i << " " << corrected_p[i][0] << " " << corrected_p[i][1] << " " << corrected_p[i][2] << endl;
		//}
		//cout << m;
		fout1 << (int)PointArr[0] << " ";
		for (int i = 0; i < 60; ++i)
			fout1 << corrected_p[0][i] << " ";
		fout1 << endl;
	}
	in_file.close();
	fout1.close();
	cout << "end  row:" << count << endl;
	return 0;
}

