#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'invitations' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY pairs
 */

class Company {
    public:
        vector <vector <int> > direct_children;
        vector<int> total_children;
        int n;
    
        int how_many_children(int boss);
        void calculate_all_children(void);
        Company(int n, vector< vector<int> > pairs);
};

Company::Company(int n, vector< vector<int> > pairs) {
    this->n = n;
    
    for (int i = 0; i < n; i++) {
        vector<int> empty_vec;
        direct_children.push_back(empty_vec);
        
        total_children.push_back(-1);
    }
        
    for (int i = 0; i < pairs.size(); i++) {
        direct_children[pairs[i][0] - 1].push_back(pairs[i][1]);
    }
}

int Company::how_many_children(int boss) {
    int child_count = 0;
    
    if (total_children[boss - 1] != -1) {
        child_count = total_children[boss - 1];
    }
    else {
        child_count = 0;
        for (int i = 0; i < direct_children[boss - 1].size(); i++) {
            child_count += 1 + how_many_children(direct_children[boss - 1][i]);
        }
        
        total_children[boss - 1] = child_count;
    }
    return child_count;
}
    
void Company::calculate_all_children(void) {
    for (int boss = n; boss > 0; boss--) {
        total_children[boss - 1] = how_many_children(boss);
    }
}

// C function for extended Euclidean Algorithm 
int gcdExtended(int a, int b, int *x, int *y) 
{ 
    // Base Case 
    if (a == 0) { 
        *x = 0, *y = 1; 
        return b; 
    } 
  
    int x1, y1; // To store results of recursive call 
    int gcd = gcdExtended(b%a, a, &x1, &y1); 
  
    // Update x and y using results of recursive 
    // call 
    *x = y1 - (b/a) * x1; 
    *y = x1; 
  
    return gcd; 
} 

// Function to find modulo inverse of a 
int modInverse(int a, int m) 
{ 
    int x, y; 
    int g = gcdExtended(a, m, &x, &y); 
    if (g != 1) {
        cout << "Inverse doesn't exist"; 
        return -1;
    }
    else { 
        // m is added to handle negative x 
        int res = (x%m + m) % m; 
        return res;
    } 
} 
    
int factorialMod(int n, int modulus) {
    long long ans = 1;
    
    //if (n <= int(modulus/2.0)) {
        // calculate the factorial normally (right argument of range() is exclusive)
    for (int i = 1; i < n+1; i++) {
        ans = (ans * i) % modulus;
    }
    /*}
    else {
        // Fancypants method for large n
        for (int i = 1; i < modulus - n; i++) {
            ans = (ans * i) % modulus;
        }

        ans = modInverse(ans, modulus);

        // Since m is an odd-prime, (-1)^(m-n) = -1 if n is even, +1 if n is odd
        if (n % 2 == 0){
            ans = -1 * ans + modulus;
        }
    }  
    */
    
    return ans % modulus;
}

int invitations(int n, vector<vector<int>> pairs) {
    
    
    Company *company = new Company(n, pairs);
    company->calculate_all_children();
    
    int factorial = factorialMod(n, 1000000007);
    long long answer = factorial;
    //cout << "factorial: " << answer << "\n";
    
    for (int i = 0; i < company->total_children.size(); i++) {
        
        if (company->total_children[i] + 1 != 1) {
            long long mod_inv = modInverse(company->total_children[i] + 1, 1000000007);
            answer = (answer * mod_inv) % 1000000007;
        
            //cout << i+1 << ": " << company->total_children[i] + 1 << " " << mod_inv << "\n";
        }
    }
    
    return answer;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string tc_temp;
    getline(cin, tc_temp);

    int tc = stoi(ltrim(rtrim(tc_temp)));

    for (int tc_itr = 0; tc_itr < tc; tc_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<vector<int>> pairs(m);

        for (int i = 0; i < m; i++) {
            pairs[i].resize(2);

            string pairs_row_temp_temp;
            getline(cin, pairs_row_temp_temp);

            vector<string> pairs_row_temp = split(rtrim(pairs_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int pairs_row_item = stoi(pairs_row_temp[j]);

                pairs[i][j] = pairs_row_item;
            }
        }

        int result = invitations(n, pairs);

        fout << result << "\n";
        //cout << "\n";
    }

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

