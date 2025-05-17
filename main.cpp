#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct FootballPassData 
{
    int receiver;
    int passer;
    int startTime;
    int endTime;
};

void extractMatches(vector<FootballPassData>& passes, vector<FootballPassData> matchData[14])
{
    int matchIndex = 0;

    while (!passes.empty())
    {
        vector<FootballPassData> currentMatch;
        FootballPassData currentPass = passes[0];
        currentMatch.push_back(currentPass);
        passes.erase(passes.begin()); 

        while (true) 
        {
            bool foundNextPass = false;

            for (auto it = passes.begin(); it != passes.end(); it++)
            {
                if (it->passer == currentPass.receiver && it->startTime >= currentPass.endTime)
                {
                    currentPass = *it; 
                    currentMatch.push_back(currentPass);
                    passes.erase(it); 
                    foundNextPass = true;
                    break;
                }
            }

            if (!foundNextPass)
                break; 
        }

        matchData[matchIndex++] = currentMatch; 

        if (matchIndex >= 14) 
            break; 
    }
}

//void createOberoiFiles(std::vector<FootballPassData> teamData[], int timeWindow, int time) {
//    int fileIndex = 1;
//
//    for (int i = 0; i < 14; i++) 
//    {
//        vector<FootballPassData> currentSnapshotPasses;
//
//        for (int j = 0; j < teamData[i].size(); j++) 
//        {
//            if (teamData[i][j].startTime <= timeWindow) 
//                currentSnapshotPasses.push_back(teamData[i][j]);
//            else 
//            {
//                ofstream file("dg" + to_string(fileIndex) + ".txt");
//
//                file << 14 << '\n';
//                for (int k = 0; k < 14; k++)
//                    file << k << " " << "\"A" + to_string(k + 1) << "\"\n";
//
//                for (int k = 0; k < 14; k++) 
//                {
//                    int passCount = 0;
//
//                    for (const auto& pass : currentSnapshotPasses) 
//                    {
//                        if (pass.passer - 1 == k) 
//                            passCount++;
//                    }
//
//                    file << passCount << '\n';
//
//                    for (const auto& pass : currentSnapshotPasses)
//                    {
//                        if (pass.passer - 1 == k) 
//                        {
//                            file << pass.passer - 1 << " " << pass.receiver - 1 << "\n";
//                        }
//                    }
//                }
//
//				if (currentSnapshotPasses.size() > 0 && j + 1 == teamData[i].size()) 
//                {
//					ofstream file("dg" + to_string(fileIndex) + ".txt");
//					file << 14 << '\n'; 
//					for (int k = 0; k < 14; k++) 
//						file << k << " " << "\"A" + to_string(k + 1) << "\"\n";
//					for (int k = 0; k < 14; k++) 
//                    {
//						int passCount = 0;
//						for (const auto& pass : currentSnapshotPasses) 
//                        {
//							if (pass.passer - 1 == k) 
//								passCount++;
//						
//						}
//
//						file << passCount << '\n';
//
//						for (const auto& pass : currentSnapshotPasses) 
//                        {
//							if (pass.passer - 1 == k) 
//								file << pass.passer - 1 << " " << pass.receiver - 1 << "\n";
//							
//						}
//					}
//				}
//
//                fileIndex++;
//                timeWindow += time;
//                currentSnapshotPasses.clear();
//            }
//        }
//    }
//}


void createOberoiFiles(vector<FootballPassData> teamData[], bool a)
{
    
    int fileIndex;

	if (a)
		fileIndex = 1;
	else
		fileIndex = 15;

    cout << fileIndex;

	for (int i = 0; i < 14; i++)
	{
		ofstream file("dg" + to_string(fileIndex) + ".txt");

		file << 14 << '\n';

		for (int k = 0; k < 14; k++)
			file << k << " " << "\"V" + to_string(k + 1) << "\"\n";

		for (int k = 0; k < 14; k++)
		{
			int passCount = 0;

			for (const auto& pass : teamData[i])
			{
				if (!a && pass.passer-15==k)
					passCount++;
				else if (pass.passer - 1 == k)
					passCount++;
			}

			file << passCount << '\n';

			for (const auto& pass : teamData[i])
			{
				if (!a && pass.passer - 15 == k)
					file << pass.passer - 15 << " " << pass.receiver - 15 << "\n";
				else if (pass.passer - 1 == k)
					file << pass.passer - 1 << " " << pass.receiver - 1 << "\n";
			}
		}

		fileIndex++;
	}
}


int main() 
{
    vector<FootballPassData> passes;
    string fileName = "passes.csv";
    ifstream file(fileName);

    if (!file.is_open()) 
    {
        cout << "Error: Could not open the file." << endl;
        return 0;
    }

    string line;

    getline(file, line); 

    while (getline(file, line)) 
    {
        FootballPassData pass;
        stringstream ss(line);
        string cell;

        getline(ss, cell, ',');
        pass.startTime = stoi(cell);
        getline(ss, cell, ',');
        pass.endTime = stoi(cell);
        getline(ss, cell, ',');
        pass.passer = stoi(cell);
        getline(ss, cell, ',');
        pass.receiver = stoi(cell);

        passes.push_back(pass);
    }

    cout << "Number of passes: " << passes.size() << endl;

    file.close();

    vector<FootballPassData> matchData[14];
	cout << "Extracting matches..." << endl;
    extractMatches(passes, matchData);

    for(int i=0;i<14;i++)
	    cout << endl << matchData[i].size() << endl;

	for (int i = 0; i < matchData[0].size(); i++)
	{
		cout << matchData[0][i].passer << " " << matchData[0][i].receiver << " " << matchData[0][i].startTime << " " << matchData[0][i].endTime << endl;
	}

	cout << "Passes Left : " << passes.size() << endl;
    
	for (int i = 0; i < 14; i++)
		cout << "Match " << i + 1 << " Passes : " << matchData[i].size() << endl;

    vector<FootballPassData> team1Data[14];
	vector<FootballPassData> team2Data[14];

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < matchData[i].size(); j++)
		{
            if (matchData[i][j].passer >= 1 && matchData[i][j].receiver <= 14)
 {
				bool found = false;

				for (int k = 0; k < team1Data[i].size(); k++)
				{
					if (team1Data[i][k].passer == matchData[i][j].passer && team1Data[i][k].receiver == matchData[i][j].receiver)
					{
						found = true;
						break;
					}
				}
				if (!found)
                    team1Data[i].push_back(matchData[i][j]);

            }
            else if (matchData[i][j].passer >= 15 && matchData[i][j].receiver >= 15)
            {
				bool found = false;
                for (int k = 0; k < team2Data[i].size(); k++)
                {
                    if (team2Data[i][k].passer == matchData[i][j].passer && team2Data[i][k].receiver == matchData[i][j].receiver)
                    {
                        found = true;
                        break;
                    }
                }
				if (!found)
                    team2Data[i].push_back(matchData[i][j]);
            }
		}
	}

    int timeWindow = 900000; //15 minutes
   // createOberoiFiles(team1Data, timeWindow, timeWindow);
	createOberoiFiles(team1Data,1);
	createOberoiFiles(team2Data,0);

	for (int i = 0; i < 14; i++)
	{
		cout << "Match " << i + 1 << " : " << endl;
		cout << "Team 1 : " << team1Data[i].size() << " passes" << endl;
		cout << "Team 2 : " << team2Data[i].size() << " passes" << endl;
	}


    return 0;
}
