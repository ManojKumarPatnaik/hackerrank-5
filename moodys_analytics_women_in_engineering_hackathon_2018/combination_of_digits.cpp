#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts LONG_INTEGER_ARRAY a as parameter.
 */


class Sequencer{
    public:
        map<long long, long long> trib;
        map<long long, long long>::iterator tribit;
    
        Sequencer();
        long long solve(vector<long> a);
        long long tribonacci(long long n);
        long long d_tribonacci(long long n);
};

Sequencer::Sequencer() {
    return;
}

long long Sequencer::tribonacci(long long n) {
    if (n == 1) {
        return 1;
    }
    else if (n == 2) {
        return 2;
    }
    else if (n == 3) {
        return 4;
    }
    else {
        tribit = trib.find(n);
        if (tribit != trib.end()) {
            return tribit->second;
        }
        else {
            long long modsum = 0;
            
            modsum = (modsum + tribonacci(n-1)) % 1000000007;
            modsum = (modsum + tribonacci(n-2)) % 1000000007;
            modsum = (modsum + tribonacci(n-3)) % 1000000007;
            
            trib[n] = modsum;
            return modsum;
        } 
    }
}

long long Sequencer::d_tribonacci(long long n) {
    long long first = 1;
    long long second = 2; 
    long long third = 4; 
    
    if (n == 1) {
        return first;  
    }
    else if (n == 2) {
        return second;
    }
    else if (n == 3) {
        return third;
    }
    else {
        long long curr;
        for (int i = 4; i <= n; i++)  {
            curr = (first + second) % 1000000007 ;
            curr = (curr + third) % 1000000007; 
            first = second; 
            second = third; 
            third = curr; 
        } 
        
        return curr;
    }
}

long long Sequencer::solve(vector<long> a) {
    long long s_sum = 0;
    
    for (int i = 0; i < a.size(); i++) {
        s_sum = (s_sum + d_tribonacci(a[i])) % 1000000007;
    }
    
    return s_sum;
}

void multiply(long long T[3][3], long long M[3][3]) 
{ 
    long long a, b, c, d, e, f, g, h, i; 
    a = ((T[0][0] * M[0][0]) % 1000000007) +  ((T[0][1] * M[1][0]) % 1000000007) +  ((T[0][2] * M[2][0]) % 1000000007); 
    b = ((T[0][0] * M[0][1]) % 1000000007) +  ((T[0][1] * M[1][1]) % 1000000007) +  ((T[0][2] * M[2][1]) % 1000000007); 
    c = ((T[0][0] * M[0][2]) % 1000000007) +  ((T[0][1] * M[1][2]) % 1000000007) +  ((T[0][2] * M[2][2]) % 1000000007); 
    d = ((T[1][0] * M[0][0]) % 1000000007) +  ((T[1][1] * M[1][0]) % 1000000007) +  ((T[1][2] * M[2][0]) % 1000000007); 
    e = ((T[1][0] * M[0][1]) % 1000000007) +  ((T[1][1] * M[1][1]) % 1000000007) +  ((T[1][2] * M[2][1]) % 1000000007); 
    f = ((T[1][0] * M[0][2]) % 1000000007) +  ((T[1][1] * M[1][2]) % 1000000007) +  ((T[1][2] * M[2][2]) % 1000000007); 
    g = ((T[2][0] * M[0][0]) % 1000000007) +  ((T[2][1] * M[1][0]) % 1000000007) +  ((T[2][2] * M[2][0]) % 1000000007); 
    h = ((T[2][0] * M[0][1]) % 1000000007) +  ((T[2][1] * M[1][1]) % 1000000007) +  ((T[2][2] * M[2][1]) % 1000000007); 
    i = ((T[2][0] * M[0][2]) % 1000000007) +  ((T[2][1] * M[1][2]) % 1000000007) +  ((T[2][2] * M[2][2]) % 1000000007); 
    
    T[0][0] = a % 1000000007; 
    T[0][1] = b % 1000000007; 
    T[0][2] = c % 1000000007; 
    T[1][0] = d % 1000000007; 
    T[1][1] = e % 1000000007; 
    T[1][2] = f % 1000000007; 
    T[2][0] = g % 1000000007; 
    T[2][1] = h % 1000000007; 
    T[2][2] = i % 1000000007; 
} 
  
// Recursive function to raise  
// the matrix T to the power n 
void power(long long T[3][3], long long n) 
{ 
    // base condition. 
    if (n == 0 || n == 1) 
        return; 
    long long M[3][3] = {{ 1, 1, 1 },  
                   { 1, 0, 0 },  
                   { 0, 1, 0 }}; 
  
    // recursively call to 
    // square the matrix 
    power(T, n / 2); 
  
    // calculating square  
    // of the matrix T 
    multiply(T, T); 
  
    // if n is odd multiply  
    // it one time with M 
    if (n % 2) 
        multiply(T, M); 
} 
long long tribonacci(long long n) 
{ 
    long long T[3][3] = {{ 1, 1, 1 },  
                   { 1, 0, 0 }, 
                   { 0, 1, 0 }}; 
  
    // base condition 
    if (n == 0 || n == 1) 
        return 0; 
    else
        power(T, n - 2); 
  
    // T[0][0] contains the  
    // tribonacci number so 
    // return it 
    return T[0][0]; 
} 

long long solve(vector<long> a) {
    long long s_sum = 0;
    
    for (int i = 0; i < a.size(); i++) {
        s_sum = (s_sum + tribonacci(a[i]+2)) % 1000000007;
    }
    
    return s_sum;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a_count_temp;
    getline(cin, a_count_temp);

    int a_count = stoi(ltrim(rtrim(a_count_temp)));

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split(rtrim(a_temp_temp));

    vector<long> a(a_count);

    for (int i = 0; i < a_count; i++) {
        long a_item = stol(a_temp[i]);

        a[i] = a_item;
    }
    //Sequencer *sequencer = new Sequencer();

    //int result = sequencer->solve(a);
    int result = solve(a);

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

