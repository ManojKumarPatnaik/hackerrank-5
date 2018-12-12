#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY p as parameter.
 */

int solve(vector<int> p) {
    p.insert(p.begin(), 0);
    int p_start_distance = 0;
    for (int floor = 0; floor < p.size() - 1; floor++) {
        p_start_distance += abs(p[floor] - p[floor + 1]);
    }
        
    int max_change_distance = 0; 
    
    int start1_left;
    int start1;
    int start1_right;
    int start2_left;
    int start2;
    int start2_right;
    
    int new1_left;
    int new1;
    int new1_right;
    int new2_left;
    int new2;
    int new2_right;
    
    
    for (int floor1_index = 1; floor1_index < p.size() - 1; floor1_index++) {
        for (int floor2_index = floor1_index + 1; floor2_index < p.size(); floor2_index++) {
            
            // end of the array edge case
            if (floor2_index == p.size() - 1) {
                start2_right = p[floor2_index]; // make it 0 before switch
                new2_right = p[floor1_index]; // make it 0 after switch
            }
            else {
                start2_right = p[floor2_index + 1];
                new2_right = p[floor2_index + 1];
            }
                
            // next to each other edge case
            if (floor1_index + 1 == floor2_index) {
                start1_right = p[floor1_index]; // make one of the doubles 0, normally would be floor2_index + 1
                new1_right = p[floor2_index]; // make one of the doubles 0, normally would be floor1_index
                new2_left = p[floor2_index]; // floor2 switched to just before itself
            }
            else {
                start1_right = p[floor1_index + 1];
                new1_right = p[floor1_index + 1];
                new2_left = p[floor2_index - 1];
            }
             
            start1_left = p[floor1_index - 1];
            start1 = p[floor1_index];
            // start1_right
            start2_left = p[floor2_index - 1];
            start2 = p[floor2_index];
            // start2_right
            
            new1_left = p[floor1_index - 1];
            new1 = p[floor2_index];
            // new1_right
            // new2_left
            new2 = p[floor1_index];
            // new2_right
            
            int start_distance = 0;
            start_distance += abs(start1_left - start1);
            start_distance += abs(start1 - start1_right);
            start_distance += abs(start2_left - start2);
            start_distance += abs(start2 - start2_right);
            
            int new_distance = 0;
            new_distance += abs(new1_left - new1);
            new_distance += abs(new1 - new1_right);
            new_distance += abs(new2_left - new2);
            new_distance += abs(new2 - new2_right);
        
            int change_distance = start_distance - new_distance;
            
            if (change_distance > max_change_distance) {
                max_change_distance = change_distance;
            }
        }
    }
                
    return p_start_distance - max_change_distance;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string p_count_temp;
    getline(cin, p_count_temp);

    int p_count = stoi(ltrim(rtrim(p_count_temp)));

    string p_temp_temp;
    getline(cin, p_temp_temp);

    vector<string> p_temp = split(rtrim(p_temp_temp));

    vector<int> p(p_count);

    for (int i = 0; i < p_count; i++) {
        int p_item = stoi(p_temp[i]);

        p[i] = p_item;
    }

    int result = solve(p);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

