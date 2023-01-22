#include <bits/stdc++.h>
using namespace std;

int main()
{

    vector<int> id;
    vector<int> remaining;
    vector<int> arrival;
    vector<int> burst;
    vector<int> gnatt;
    vector<int> wait;
    vector<int> finish;
    vector<int> turnaround;
    vector<int> inp;

    // Take input from file:

    string mytext;
    ifstream MyReadFile("input.txt");
    while (getline(MyReadFile, mytext))
    {

        stringstream ss(mytext);
        string word;
        int i = 0;
        while (ss >> word)
        {
            if (i == 0)
            {
                id.push_back(stoi(word));
            }
            if (i == 1)
            {
                arrival.push_back(stoi(word));
            }
            if (i == 2)
            {
                burst.push_back(stoi(word));
            }
            i++;
        }
    }

    // print details:
    cout << "id  arrival  burst" << endl;
    int n = id.size();
    for (int i = 0; i < n; i++)
    {
        inp.push_back(i);
        cout << id[i] << " " << arrival[i] << " " << burst[i] << endl;
    }

    // Sorting
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (arrival[j] > arrival[j + 1])
            {
                int temp = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = temp;

                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;

                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;

                temp = inp[j];
                inp[j] = inp[j + 1];
                inp[j + 1] = temp;
            }
        }
    }
    int still = 0;

    int choise;
    cout << "which process: " << endl;
    cout << "1. first come first serve\n2. shortest job first\n3. shortest remaining time first\n4. round robin" << endl;
    cin >> choise;

    // FCFS
    if (choise == 1)
    {
        finish.push_back(burst[0]);

        for (int i = 0; i < n; i++)
        {
            if (i >= 1)
            {
                finish.push_back(burst[i] + finish[i - 1]);
            }

            if (arrival[i] > still)
            {
                for (int j = 0; j < arrival[i] - still; j++)
                {
                    gnatt.push_back(-1);
                }
            }
            for (int j = 0; j < burst[i]; j++)
            {
                gnatt.push_back(id[i]);
            }

            still += burst[i];
        }

        for (int i = 0; i < finish.size(); i++)
        {

            turnaround.push_back(finish[i] - arrival[i]);
        }

        for (int i = 0; i < finish.size(); i++)
        {
            wait.push_back(abs(turnaround[i] - burst[i]));
        }

        for (int i = 0; i < n; i++)
        {
            cout << finish[i] << " " << turnaround[i] << " " << wait[i] << endl;
        }

        float avg_waiting = 0, avg_turnaround = 0;
        for (int i = 0; i < n; i++)
        {
            avg_waiting += wait[i];
            avg_turnaround += turnaround[i];
        }

        avg_turnaround /= n;
        avg_waiting /= n;        

        cout << "gnatt chart" << endl;

        for (int i = 0; i < gnatt.size(); i++)
        {
            cout << gnatt[i] << " ";
        }
        cout<<endl;
        cout << "avarage turn around time: "<<avg_turnaround << " avarage wait time: " << avg_waiting << endl;

        // Lets go fot the responce time:- first tme proccess show  in gnatt chart will be this
        int avg_responce=0;        
        for(int i=0; i<n; i++){
            for (int j = 0; j < gnatt.size(); j++)
            {
                if(gnatt[j] == id[i]){
                    avg_responce+=j;
                    break;
                }
            
            }
        }
        avg_responce/=n;

        cout<<"Avg_responce time: "<<avg_responce<<endl; 
        
    }

    //SJF

    if (choise == 2)
    {
        int minindex = 0;

        for (int i = 0; i < n; i++)
        {
            minindex = i;
            for (int j = i; j < n; j++)
            {
                if (arrival[j] <= still && burst[j] < burst[minindex])
                {
                    minindex = j;
                }
            }
            if (minindex != i)
            {                
                int temp = arrival[i];
                arrival[i] = arrival[minindex];
                arrival[minindex] = temp;

                temp = id[i];
                id[i] = id[minindex];
                id[minindex] = temp;

                temp = burst[i];
                burst[i] = burst[minindex];
                burst[minindex] = temp;
            }
            if (arrival[i] > still)
            {
                for (int j = 0; j < arrival[i] - still; j++)
                {
                    gnatt.push_back(-1);
                }
            }
            for (int j = 0; j < burst[i]; j++)
            {
                gnatt.push_back(id[i]);
            }
            still += burst[i];
            finish.push_back(still);
        }

        for (int i = 0; i < n; i++)
        {
            turnaround.push_back(finish[i] - arrival[i]);
            wait.push_back(turnaround[i] - burst[i]);
        }
        float avg_waiting = 0, avg_turnaround = 0;
        for (int i = 0; i < n; i++)
        {        
            avg_waiting += wait[i];
            avg_turnaround += turnaround[i];
        }
        avg_waiting /= n;
        avg_turnaround /= n;
        cout << "gnatt chart: " << endl;
        for (int i = 0; i < gnatt.size(); i++)
        {
            cout << gnatt[i] << " ";
        }
        cout << endl;
        cout << "avarage turn around time: "<<avg_turnaround << " avarage wait time: " << avg_waiting << endl;

        // Lets go fot the responce time:- first tme proccess show  in gnatt chart will be this
        int avg_responce=0;        
        for(int i=0; i<n; i++){
            for (int j = 0; j < gnatt.size(); j++)
            {
                if(gnatt[j] == id[i]){
                    avg_responce+=j;
                    break;
                }
            
            }
        }
        avg_responce/=n;

        cout<<"Avg_responce time: "<<avg_responce<<endl;
    }

    //SRTF

    if (choise == 3)
    {
        for (int i = 0; i < n; i++)
        {
            remaining.push_back(burst[i]);            
            finish.push_back(burst[i]);
        }    
        int minindex = 0,count=0;
        while (count != n - 1)
        {
            minindex = 0;
            for (int j = 0; j < n; j++)
            {
                if (arrival[j] <= still && remaining[j] < remaining[minindex])
                {
                    minindex = j;
                }
            }
            int k;
            long long int alpha = std::min(arrival[count + 1] - arrival[count], remaining[minindex]);
            for (k=0; k < alpha; k++)
            {
                gnatt.push_back(id[minindex]);
            }
            still = arrival[count + 1];
            remaining[minindex] -= k;
            if (remaining[minindex] == 0)
            {
                finish[minindex] = still;
            }
            count++;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (remaining[j] > remaining[j + 1])
                {
                    int temp = remaining[j];
                    remaining[j] = remaining[j + 1];
                    remaining[j + 1] = temp;

                    temp = id[j];
                    id[j] = id[j + 1];
                    id[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < remaining[i]; j++)
            {
                gnatt.push_back(id[i]);
            }
            still += remaining[i];
            finish[i] = still;
            remaining[i] = 0;
        }
        for (int i = 0; i < gnatt.size(); i++)
        {
            cout << gnatt[i] << " ";
        }
        cout << endl;
        float avg_wait = 0, avg_turn = 0;
        for (int i = 0; i < n; i++)
        {
            turnaround.push_back(finish[i] - arrival[i]);
            avg_turn += turnaround[i];
            wait.push_back(turnaround[i] - burst[i]);
            avg_wait += wait[i];
        }

        avg_turn /= n;
        avg_wait /= n;

        cout << "avarage turn around time: "<<avg_turn << " avarage wait time: " << avg_wait << endl;

        // Lets go fot the responce time:- first tme proccess show  in gnatt chart will be this
        int avg_responce=0;        
        for(int i=0; i<n; i++){
            for (int j = 0; j < gnatt.size(); j++)
            {
                if(gnatt[j] == id[i]){
                    avg_responce+=j;
                    break;
                }
            
            }
        }
        avg_responce/=n;

        cout<<"Avg_responce time: "<<avg_responce<<endl;
    }

    // RR

    if (choise == 4)
    {

        for (int i = 0; i < n; i++)
        {
            remaining.push_back(burst[i]);
            finish.push_back(burst[i]);
        }
        cout << "Enter Quantum time." << endl;
        int quantum;
        cin >> quantum;
        cout << "contextswitch time:" << endl;
        int conswi;
        cin >> conswi;
        queue<int> proccess;

        int count = 0;
        if (proccess.size() != n)
        {
            for (int i = 0; i < n; i++)
            {
                if (arrival[i] <= still)
                {
                    proccess.push(id[i]);
                }
            }
        }
        while (count != n)
        {
            if (remaining[inp[proccess.front()]] <= quantum)
            {
                for (int i = 0; i < remaining[inp[proccess.front()]]; i++)
                {
                    gnatt.push_back(id[inp[proccess.front()]]);
                }
                still += remaining[inp[proccess.front()]];
                remaining[inp[proccess.front()]] = 0;
            }
            else
            {
                for (int i = 0; i < quantum; i++)
                {
                    gnatt.push_back(id[inp[proccess.front()]]);
                }
                remaining[inp[proccess.front()]] -= quantum;
                still += quantum;
            }
            for (int i = 0; i < conswi; i++)
            {
                gnatt.push_back(-2);
            }

            for (int i = 0; i < n; i++)
            {
                int f = 1;
                if (arrival[i] <= still && remaining[i] != 0)
                {
                    for (int j = 0; j < proccess.size(); j++)
                    {
                        if (proccess.front() == id[i])
                        {
                            f = 0;
                        }
                        proccess.push(proccess.front());
                        proccess.pop();
                    }
                    if (f == 1)
                    {
                        proccess.push(id[i]);
                    }
                }
            }
            if (remaining[inp[proccess.front()]] == 0)
            {
                finish[inp[proccess.front()]] = still;
                count++;
            }
            still += conswi;
            if (remaining[inp[proccess.front()]] != 0)
            {
                proccess.push(id[inp[proccess.front()]]);
            }

            proccess.pop();
        }

        for (int i = 0; i < n; i++)
        {
            int f = 0;
            still += remaining[i];
            finish[i] += remaining[i];

            while (remaining[i] != 0)
            {
                gnatt.push_back(id[i]);
                remaining[i]--;
                f = 1;
            }
            if (f == 1)
            {
                gnatt.push_back(-2);
                still += conswi;
            }
        }
        for (int i = 0; i < gnatt.size(); i++)
        {
            cout << gnatt[i] << " ";
        }
        cout << endl;
        float avg_turn = 0, avg_wait = 0;
        for (int i = 0; i < n; i++)
        {
            turnaround.push_back(finish[i] - arrival[i]);
            avg_turn += turnaround[i];
            wait.push_back(turnaround[i] - burst[i]);
            avg_wait += wait[i];
        }

        avg_wait /= n;
        avg_turn /= n;
        cout << "avarage turn around time: "<<avg_turn << " avarage wait time: " << avg_wait << endl;

        // Lets go fot the responce time:- first tme proccess show  in gnatt chart will be this
        int avg_responce=0;        
        for(int i=0; i<n; i++){
            for (int j = 0; j < gnatt.size(); j++)
            {
                if(gnatt[j] == id[i]){
                    avg_responce+=j;
                    break;
                }
            
            }
        }
        avg_responce/=n;

        cout<<"Avg_responce time: "<<avg_responce<<endl;
    }

    return 0;
}