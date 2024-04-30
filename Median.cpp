#include<iostream>
#include<vector>
#include<random>
using namespace std;

#define int long long
int inf = 1e9;
int n;
int comparisons =0;


vector<int> mergeSort(vector<int> &avector) {
    if (avector.size()>1) {
        int mid = avector.size()/2;
        vector<int> lefthalf(avector.begin(),avector.begin()+mid);
        vector<int> righthalf(avector.begin()+mid,avector.begin()+avector.size());

        lefthalf = mergeSort(lefthalf);
        righthalf = mergeSort(righthalf);

        unsigned i = 0;
        unsigned j = 0;
        unsigned k = 0;
        while (i < lefthalf.size() && j < righthalf.size()) {
            if (lefthalf[i] < righthalf[j]) {
                avector[k]=lefthalf[i];
                i++;
            } else {
                avector[k] = righthalf[j];
                j++;
            }
            k++;
            comparisons++;
        }

        while (i<lefthalf.size()) {
            avector[k] = lefthalf[i];
            i++;
            k++;
            comparisons++;
        }

        while (j<righthalf.size()) {
            avector[k]=righthalf[j];
            j++;
            k++;
            comparisons++;
        }

    }

    return avector;
}

int help(){

    srand(time(NULL));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 2e9);

    // n random elements
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        int x = dis(gen);
        if(x > inf){v[i] = x%inf;}
        else{i--;}
    }
    if(n==1) return v[0];
    int num = pow(n,0.66)*pow(log(n),0.33)/5;

    int rankx = 0;
    int ranky = 0;
    int x,y;

    vector<int> remaining_elements;

    // finding the elements X and Y and their ranks

    while(!(rankx <= n/2 && ranky >= n/2)){
        remaining_elements.clear();
        rankx = 0;
        ranky = 0;
        vector<int> v1;
        int n1 = 0;
        while(1){
            for(int i=n-1;i>-1;i--) {
                int x= dis(gen);
                x= x%(n/num);
                if(x==0) v1.push_back(v[i]);
            }
            if(v1.size() < num*9/10 || v1.size() > num*11/10) v1.clear();
            else break;
        }

        int x,y;
        int t = sqrt(num * log(n))/5;
        mergeSort(v1); 
        int size= v1.size();
        x = v1[num/2 - t - 1];
        y = v1[num/2 + t - 1];

        rankx = 0, ranky = 0;
        for(int i = 0; i < n; i++){
            if(v[i] < x){
                rankx++;
                ranky++;
                comparisons++;
            }
            else if(v[i] < y){
                remaining_elements.push_back(v[i]);
                ranky++;
                comparisons+=2;
            }
            else {
                comparisons+=2;
            }
        } 
    }
    mergeSort(remaining_elements);
    int required_rank = (n/2) - rankx;
    int median = remaining_elements[required_rank-1];
    
    sort(v.begin(), v.end());
    cout << "Median: " << median << "\nActual Median: " << v[n/2-1] << endl;

    return median;

}

signed main(){
    
    cin >> n;
    help();
    cout << "Number of Comparisons: "<< comparisons << endl ;
}