#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>

using namespace std;

#define MAX_NUMBER 99999

int n; //n for total number
int k; //k for the kth smallest number
vector<int> arr; //store all number

void readFile(string file_name) {

	fstream file;
	int tmp;
	file.open(file_name, ios::in);
	file >> n; 
	file >> k; 
	cout << "total number is " << n << endl;

	for (int i = 0; i < n; i++) {
		file >> tmp;
		arr.push_back(tmp);
	}
	file.close();
}

void swap(vector<int>& vec, int a, int b) {      //swap function
    int temp = vec[a];
    vec[a] = vec[b];
    vec[b] = temp;
}

void quickSort(vector<int> &vec, int head, int tail) {
    int i, j, mid, piv;
    i = head;
    j = tail;
    mid = head + (tail - head) / 2;
    piv = vec[mid];

    while (i<tail || j>head) {
        while (vec[i] < piv)
            i++;
        while (vec[j] > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j); //error=swap function doesnt take 3 arguments
            i++;
            j--;
        }
        else {
            if (i < tail)
                quickSort(vec, i, tail);
            if (j > head)
                quickSort(vec, head, j);
            return;
        }
    }
}


void select_qs() {

	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	vector<int> arrq = arr;
	quickSort(arrq, 0, n - 1);
	// calculate time
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	double t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	t /= 1000000;

	// save to file
	fstream file;
	file.open("QS.txt", ios::out);
	file.setf(ios::fixed);
	file << arrq[k - 1] << endl; //number
	file << setprecision(6) << t << endl; //time
	file.close();
	cout << "quick sort:" << endl;
	cout<< arrq[k - 1] << endl;
	cout<< setprecision(6) << t << " s" << endl;

}

int select(vector<int> arrp, int number, int rank) {

	int other = number % 5;

	if (other > 0) other = 5 - other;
	number += other;
	for (int i = 0; i < other; i++) {
		arrp.push_back(MAX_NUMBER);
	}

	if (number <= 5) {
		quickSort(arrp, 0, number - 1);  // brute force search directly    
		return arrp[rank - 1];
	}
	else {

		vector<int> middle;       //sort each 5 item group and sort all group by median 

		int number_d = number / 5;
		for (int i = 0; i < number_d; i++) {

			quickSort(arrp, 5 * i, 5 * i + 4);
			middle.push_back(arrp[5 * i + 2]);

		}
		quickSort(middle, 0, number_d - 1);

		int median = middle[number / 10 - 1];
		int small = 0;
		int equal = 0;
		int big = 0;
		vector<int> arrb;
		vector<int> arrs;

		for (auto x : arrp) {
			if (x > median && x != MAX_NUMBER) {
				arrb.push_back(x);
				big++;
			}
			else if (x < median) {
				arrs.push_back(x);
				small++;
			}

		}
		equal = number - small - big - other;
		// next recursive

		if (rank <= small)  return select(arrs, small, rank);
		else if (rank <= small + equal) return median;
		else return select(arrb, number - small - equal - other, rank - small - equal);

	}
}

void select_ps(){   

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    //pre-add some big number to make array can be divided by 5
   
    int result = select(arr,n,k);

    // calculate time
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    t /= 1000000;
    
    // save to file
    
    fstream file;
    file.open("PS.txt",ios::out);
    file.setf(ios::fixed);
    file << result << endl;
    file << setprecision(6)<<t<< endl;
    file.close();
	cout << "prune and search:" << endl;
	cout << result << endl;
	cout << setprecision(6) << t <<" s"<< endl;
}



int main(void){

	readFile("input.txt");

    select_qs();
    select_ps();

	system("pause");
    return 0;
}
