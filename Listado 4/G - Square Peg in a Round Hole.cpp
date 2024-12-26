#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> plotRadii(n);
    for (int i = 0; i < n; i++){
        cin >> plotRadii[i];
    }

    vector<int> circularHouses(m);
    for (int i = 0; i <  m; i++){
        cin >> circularHouses[i];
    }

    vector<int> squareHouses(k);
    for (int i = 0; i <  k; i++){
        cin >> squareHouses[i];
    }

    sort(plotRadii.begin(), plotRadii.end());
    sort(circularHouses.begin(), circularHouses.end());
    sort(squareHouses.begin(), squareHouses.end());

    int i = 0;
	int j = 0;
    int placedHouses = 0;
    for (int radioPlot : plotRadii){
        if (circularHouses[i] < radioPlot && i < m){
            placedHouses++;
            i++;
            continue;
        }

        if (squareHouses[j]*squareHouses[j] < 2*(radioPlot*radioPlot) && j < k){
            placedHouses++;
            j++;
            continue;
        }
    }

    cout << placedHouses << endl;
}

