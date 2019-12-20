#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int>ii;
typedef long long ll;
#define sz(s) int((s).size())
#define mkp make_pair
#define debug(x) cout<<(#x)<<": \""<<x<<"\""<<endl;
#define sc(x) scanf("%d", &(x))
#define all(x) (x).begin(), (x).end()
#define F first
#define S second
const int N = (int) 2e5+1;
const int inf = (int) 1e9;

int graph[N] , arrivingTime[N] , burstTime[N] , Priority[N] , finishingTime[N] , TA[N] , WT[N]; double WTA[N] ;

int start = 0;
void FCFS(int num , int context_time){

	priority_queue<pair<int , int> , vector<pair<int , int>>,greater<pair<int,int>>> pq;
	for(int i = 1 ; i <= num ; ++i) pq.push({arrivingTime[i] , i});
	while(!pq.empty()){
		int process_number = pq.top().S;
		int arr_time = pq.top().F;
		if(start < arr_time) start = arr_time;
		for(int r = 0 ; r < burstTime[process_number] ; ++r) graph[start++] = process_number;
		start += context_time;
		pq.pop();
	}
}

void HPF(int num , int context_time){

	priority_queue<pair<int , int> , vector<pair<int , int>>,greater<pair<int , int>>> pq1;
	priority_queue<pair<int , int> , vector<pair<int , int>> > pq2;
	for(int i = 1 ; i <= num ; ++i){
		pq1.push({arrivingTime[i] , i});
	}
	start = max(start , pq1.top().F);
	while(!pq1.empty()){
		if(pq1.top().F <= start){
			pq2.push({Priority[pq1.top().S] ,pq1.top().S });
			pq1.pop();
		}
		else break;
	}

	while(!pq2.empty()){
		int process_number = pq2.top().S;
		pq2.pop();
		for(int r = 0 ; r < burstTime[process_number] ; ++r){
			graph[start++] = process_number;
		}
		start += context_time;
		if(pq2.empty() && !pq1.empty()) start = max(start , pq1.top().F);
		while(!pq1.empty()){
			if(pq1.top().F <= start){
				pq2.push({Priority[pq1.top().S] ,pq1.top().S });
				pq1.pop();
			}
			else break;
		}
	}

}

void RR(int num , int context_time , int quantum){
	int qm = quantum;
	priority_queue<pair<int , int> , vector<pair<int , int>>,greater<pair<int , int>>> pq;
	for(int i = 1 ; i <= num ; i++){
		pq.push({arrivingTime[i] , i});
	}
	queue<pair<int , int>> ready;
	start=max(start,pq.top().F);
	ready.push({pq.top().S , burstTime[pq.top().S]});
	pq.pop();
	while(1){
		if(ready.empty() && pq.empty()) break;

		int n = ready.front().F;
		int r = ready.front().S;
		ready.pop();
		for(int i = 0 ; i < qm ; i++){
			graph[start++] = n;
			r--;
			if(r<=0) break;
		}

		start += context_time;
		if(ready.empty() && !pq.empty()){
			start = max(start,pq.top().F);
		}

		while(!pq.empty()){
			if(pq.top().F <= start)
			{
				ready.push({pq.top().S , burstTime[pq.top().S]});
				pq.pop();
			}
			else break;
		}

		if(r>0)ready.push({n,r});

	}

}

int main()
{
	cout<<"Enter input file name.....\n";
	string filename; cin>>filename;
	cout<<"Enter the number of the algorithm you want to run...... \n";
	cout<<"1- HPF algorithm\n";
	cout<<"2- FCFS algorithm\n";
	cout<<"3- RR algorithm\n";
	cout<<"4- SRTN algorithm\n";
	int x; cin>>x;
	cout<<"Specify the context switching time........ \n";
	int c; cin>>c;
	int quantum;
	if(x == 3){
		cout<<"Specify Time quantum.....\n";
		cin>>quantum;
	}
	ifstream cin;
	cin.open(filename);
	int n; cin>>n;
	for(int i = 1 ; i <= n ; i++){
		cin>>arrivingTime[i]>>burstTime[i]>>Priority[i];
	}


	if(x == 1) HPF(n,c);
	else if(x == 2) FCFS(n,c);
	else if(x == 3) RR(n,c,quantum);

	ofstream cout;
	cout.open("data1.txt");
	for(int i = 0 ; i <= start ; i++){
		cout<<i<<" ";
	}
	cout<<endl;
	for(int i = 0 ; i<= start ; i++)
		cout<<graph[i]<<" ";
	cout.close();
	//calculating turn around time
	freopen("statistics.txt" , "w" , stdout);
	for(int i = 0 ; i<= start ; i++ ){
		if(graph[i]) finishingTime[graph[i]] = i;
	}

	int totalTA = 0;
	double totalWTA = 0;
	for(int i =1 ; i<= n ; i++){
		TA[i] = finishingTime[i]-arrivingTime[i]+1;
		WT[i] = TA[i]-burstTime[i];
		totalTA += TA[i];
		WTA[i] = double(TA[i])/burstTime[i];
		totalWTA += WTA[i];
	}
	for(int i = 1 ; i<= n ; i++){
		printf("process #%d----> turn arround time = %d --- waiting time = %d --- weighted TA = %f\n" ,
				i , TA[i] , WT[i]  , WTA[i]);
	}

	printf("Average Turnaround time of theschedule : %f\n" , float(totalTA)/n);
	printf("Average Weighted turnaround time of theschedule : %f\n" , float(totalWTA)/n);





}
