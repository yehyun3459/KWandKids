#include "iostream"
using namespace std;
int red[21] = {0,2,4,6,8,10,12,14,16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 };
int blue_1[9] = { 0, 13, 16, 19, 25, 30, 35, 40 }; 
int blue_2[8] = { 0, 22, 24, 25, 30, 35, 40 };
int blue_3[9] = { 30, 28, 27, 26, 25, 30, 35, 40 };
pair<int,int> h[5]; //경로, 위치
int maxx, dice[11];

int fu(int cnt, int h_idx) {
	int tmp_sum = 0, tmp_lct = h[h_idx].second;
	if (h[h_idx].first == -1) {
		return 0;
	}

	tmp_lct += dice[cnt];

	switch (h[h_idx].first) {
	case 0:

		if(tmp_lct <= 20)	tmp_sum = red[tmp_lct];
		

		if (tmp_lct > 20) {
			tmp_sum = 0;
			h[h_idx].first = -1;
			h[h_idx].second = -1;
		}
		else if (tmp_lct == 5) {
			for (int i = 0; i < 4; i++) {
				if (h[i].first == 1 && h[i].second == 0)	return -1;
			}

			h[h_idx].first = 1;
			h[h_idx].second = 0;
		}
		else if (tmp_lct == 10) {
			for (int i = 0; i < 4; i++) {
				if (h[i].first == 2 && h[i].second == 0)	return -1;
			}

			h[h_idx].first = 2;
			h[h_idx].second = 0;
		}
		else if (tmp_lct == 15) {
			for (int i = 0; i < 4; i++) {
				if (h[i].first == 3 && h[i].second == 0)	return -1;
			}

			h[h_idx].first = 3;
			h[h_idx].second = 0;
		}
		else if (tmp_lct == 20) {
			for (int i = 0; i < 4; i++) {
				if (h[i].first == 0 && h[i].second == 20)	return -1;
				if (h[i].first == 1 && h[i].second == 7)	return -1;
				if (h[i].first == 2 && h[i].second == 6)	return -1;
				if (h[i].first == 3 && h[i].second == 7)	return -1;
			}

			h[h_idx].second = tmp_lct;
		}		
		else {
			for (int i = 0; i < 4; i++) {
				if (h[i].first == 0 && h[i].second == tmp_lct)	return -1;
			}

			h[h_idx].second = tmp_lct;
		}	

		break;

	case 1:
		if (tmp_lct > 7) {
			tmp_sum = 0;
			h[h_idx].first = -1;
			h[h_idx].second = -1;
		}
		else if(tmp_lct >= 4){
			tmp_sum = blue_1[tmp_lct];
			for (int i = 0; i < 4; i++) {
				if (h[i].first == 1 && h[i].second == tmp_lct)	return -1;
				if (h[i].first == 2 && h[i].second == tmp_lct - 1)	return -1;
				if (h[i].first == 3 && h[i].second == tmp_lct)	return -1;

				if (tmp_lct == 7 && h[i].first == 0 && h[i].second == 20)	return -1;
			}
		}
		else {
			tmp_sum = blue_1[tmp_lct];
			for (int i = 0; i < 4; i++) {
				if (h[i].first == 1 && h[i].second == tmp_lct)	return -1;
			}
		}

		h[h_idx].second = tmp_lct;

		break;

	case 2:
		if (tmp_lct > 6) {
			tmp_sum = 0;
			h[h_idx].first = -1;
			h[h_idx].second = -1;
		}
		else if (tmp_lct >= 3) {
			tmp_sum = blue_2[tmp_lct];

			for (int i = 0; i < 4; i++) {
				if (h[i].first == 1 && h[i].second == tmp_lct + 1)	return -1;
				if (h[i].first == 2 && h[i].second == tmp_lct)	return -1;
				if (h[i].first == 3 && h[i].second == tmp_lct + 1)	return -1;

				if (tmp_lct == 6 && h[i].first == 0 && h[i].second == 20)	return -1;
			}
		}
		else {
			tmp_sum = blue_2[tmp_lct];

			for (int i = 0; i < 4; i++) {
				if (h[i].first == 2 && h[i].second == tmp_lct)	return -1;
			}
		}

		h[h_idx].second = tmp_lct;

		break;

	case 3:
		if (tmp_lct > 7) {
			tmp_sum = 0;
			h[h_idx].first = -1;
			h[h_idx].second = -1;
		}
		else if (tmp_lct >= 4) {
			tmp_sum = blue_3[tmp_lct];

			for (int i = 0; i < 4; i++) {
				if (h[i].first == 1 && h[i].second == tmp_lct)	return -1;
				if (h[i].first == 2 && h[i].second == tmp_lct - 1)	return -1;
				if (h[i].first == 3 && h[i].second == tmp_lct)	return -1;

				if (tmp_lct == 7 && h[i].first == 0 && h[i].second == 20)	return -1;
			}
		}
		else {
			tmp_sum = blue_3[tmp_lct];

			for (int i = 0; i < 4; i++) {
				if (h[i].first == 3 && h[i].second == tmp_lct)	return -1;
			}
		}

		h[h_idx].second = tmp_lct;

		break;
	}

	return tmp_sum;
}

int main() {
	for (int i = 1; i <= 10; i++)	cin >> dice[i];
	int xxx[11] = { 0 };

	while(xxx[10] <= 3) {
		int summ = 0, tmp;
		for (int hh = 0; hh < 4; hh++) {
			h[hh].first = 0;
			h[hh].second = 0;
		}

		for (int cntt = 1; cntt <= 10; cntt++) {
			tmp = fu(cntt, xxx[cntt]);
			if (tmp == -1)	break;
			summ += tmp;
		}

		if (tmp > -1 && maxx < summ)	maxx = summ;
		xxx[1]++;
		for (int k = 1; k < 10; k++) {
			if (xxx[k] > 3) {
				xxx[k + 1]++;
				xxx[k] = 0;			
			}
		}
	}

	cout << maxx;

	return 0;
}