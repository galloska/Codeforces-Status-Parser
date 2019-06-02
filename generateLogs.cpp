#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >

using namespace std;

const int frozenTime= 60;
const int numberOfProblems = 11;
const int durationOfContest = 300;
const int totalNumberOfArguments = 3;
const int totalNumberOfColumnsBySubmission = 8;

ofstream logs;
int fileStatus;
string initialDateOfContest;
set<string> teams;

struct Submission {
	lli id;
	lli submissionTime;
	string team;
	string problem;
	string lang;
	string verdict;
	string time;
	string memory;

	Submission(string a, lli b, string c, string d, string e, string f, string g, string h) {
		istringstream iss(a);
		iss >> id;
		submissionTime = b;
		team = c;
		problem = d[0];
		lang = e;
		verdict = f;
		time = g;
		memory = h;
		if(submissionTime <= durationOfContest) {
			teams.insert(team);
		}
	}
};

time_t calculate_seconds_between(
	const uint Y1, const uint M1, const uint D1, const uint H1, const uint m1, const uint S1, // YY/MM/DD HH:mm:SS
	const uint Y2, const uint M2, const uint D2, const uint H2, const uint m2, const uint S2) {
	time_t raw;
	time(&raw);

	struct tm t1 = *gmtime(&raw), t2 = t1;

	t1.tm_year = Y1 - 1900;
	t1.tm_mon = M1 - 1;
	t1.tm_mday = D1;
	t1.tm_hour = H1;
	t1.tm_min = m1;
	t1.tm_sec = S1;

	t2.tm_year = Y2 - 1900;
	t2.tm_mon = M2 - 1;
	t2.tm_mday = D2;
	t2.tm_hour = H2;
	t2.tm_min = m2;
	t2.tm_sec = S2;

	time_t tt1, tt2;
	tt1 = mktime(&t1);
	tt2 = mktime(&t2);
	return abs(tt2 - tt1);
}

string getMonthFrom(string cad) {
	if(cad == "Jan") return "01";
	if(cad == "Feb") return "02";
	if(cad == "Mar") return "03";
	if(cad == "Apr") return "04";
	if(cad == "May") return "05";
	if(cad == "Jun") return "06";
	if(cad == "Jul") return "07";
	if(cad == "Aug") return "08";
	if(cad == "Sep") return "09";
	if(cad == "Oct") return "10";
	if(cad == "Nov") return "11";
	if(cad == "Dec") return "12";
	cout<<cad<<endl;
	perror("Date malformated.");
	exit(0);
}

// MM/DD/YY HH:MM:SS
vector<int> parseDate(string A) {
	vector<int> result;
	A += " ";
	string cad = "";
	forn(i, A.size()) {
		if(A[i] == ' ' || A[i] == '/' || A[i] == ':') {
			if(cad.size() > 0) {
				int aux;
				if(!result.size()) {
					cad = getMonthFrom(cad);
				}
				istringstream iss(cad);
				iss >> aux;
				result.pb(aux);
			}
			cad = "";
			continue;
		}
		cad += A[i];
	}
	result.pb(0);
	return result;
}

time_t computeDifferenceInMinutes(string A, string B) {
	vector<int> a = parseDate(A);
	vector<int> b = parseDate(B);
	return calculate_seconds_between(
		a[2], a[0], a[1], a[3], a[4], a[5],
		b[2], b[0], b[1], b[3], b[4], b[5]
	) / 60;
}

bool isNumber(const string &s) {
	for(auto &c: s) {
		if(!isdigit(c)) {
			return false;
		}
	}
	return true;
}

void parseArguments(int argc, char **argv) {
	if (argc != totalNumberOfArguments) {
		perror ("Number of arguments is not correct.");
		exit(0);
	}
	else {
		cout<<"Parsing arguments..."<<endl;
	}
	string arg(argv[1]);
	if(!isNumber(arg)) {
		perror ("First argument is not a number - Number of file status of codeforces.");
		exit(0);
	}
	istringstream iss(arg);
	iss >> fileStatus;

	string auxDate(argv[2]);
	initialDateOfContest = auxDate;
	if(parseDate(initialDateOfContest).size() != 6) {
		perror("Initial date of contest is malformed. Format should be MM:DD:YY HH:MM as in codeforces. Example: May/04/2019 00:54");
		exit(0);
	}

	cout<<"Arguments correct..."<<endl;
	cout<<endl;
}

bool existsFile (const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}

void checkFileStatusExistence() {
	cout<<"Checking files existences as 1.html, 2.html..."<<endl;
	for(int i=1;i<=fileStatus;++i) {
		stringstream ss;
		ss << i;
		string fileName = "status/" + ss.str() + ".html";
		if(!existsFile(fileName)) {
			perror ("One or more file do not exist.");
			exit(0);
		}
		cout<<"File "<<fileName<<" correct..."<<endl;
	}
	cout<<"Files correct..."<<endl;
	cout<<endl;
}

bool isValidCharacter(char a) {
	if(a == '\n') return false;
	if(a == '\t') return false;
	if(a == '\r') return false;
	return true;
}

string clean(const string &s) {
	string cad;
	forn(i, s.size()) {
		if(isValidCharacter(s[i])) {
			cad += s[i];
		}
	}
	return cad;
}

void writeLogSubmission(Submission s, int f) {
	logs<<"	  {"<<endl;
	logs<<"		\"Id\": "<<" "<<s.id<<","<<endl;
	logs<<"		\"timeSubmission\": "<<" "<<s.submissionTime<<","<<endl;
	logs<<"		\"TeamName\": "<<" \""<<s.team<<"\","<<endl;
	logs<<"		\"Problem\": "<<" \""<<s.problem<<"\","<<endl;
	logs<<"		\"Lang\": "<<" \""<<s.lang<<"\","<<endl;
	logs<<"		\"Verdict\": "<<" \""<<s.verdict<<"\","<<endl;
	logs<<"		\"Time\": "<<" \""<<s.time<<"\","<<endl;
	logs<<"		\"Memory\": "<<" \""<<s.memory<<"\""<<endl;
	logs<<"	  }"<<(f ? "" : ",")<<endl;
}

void writeContestInfo() {
	logs<<"	\"Contest\": {"<<endl;
	logs<<"		\"Duration\": "<<durationOfContest<<","<<endl;
	logs<<"		\"FrozenTime\": "<<frozenTime<<","<<endl;
	logs<<"		\"NumberOfProblems\": "<<numberOfProblems<<endl;
	logs<<"	},"<<endl;
}

void writeTeamsInfo() {
	logs<<"	\"Teams\": {"<<endl;
	int id = 1;
	for(auto &t: teams) {
		logs<<"		\""<<id<<"\": "<<"\""<<t<<"\"";
		if(id != teams.size()) {
			logs<<",";
		}
		logs<<endl;
		id++;
	}
	logs<<"	},"<<endl;
}

void writeVerdictsInfo() {
	logs<<"	\"VerdictWithoutPenalty\": {"<<endl;
	logs<<"		\"1\": \"Compilation error\""<<endl;
	logs<<"	},"<<endl;
}

void writeLogs(vector<Submission> info) {
	logs<<"{"<<endl;
	writeContestInfo();
	writeTeamsInfo();
	writeVerdictsInfo();
	logs<<"	\"Submissions\": ["<<endl;
	forn(i, info.size()) {
		writeLogSubmission(info[i], (i + 1 == info.size()));
	}
	logs<<"	]"<<endl;
	logs<<"}"<<endl;
}

vector<string> findSubmissionInformation(vector<string> text, string open, string close) {
	size_t id;
	vector<string> result;
	forn(i, text.size()) {
		while((id = text[i].find(open)) != string::npos) {
			text[i] = text[i].substr(id, string::npos);
			id = text[i].find(close);
			if(id == string::npos) {
				perror("log is malformed...");
				exit(0);
			}
			string info = text[i].substr(0, id + close.size());
			result.pb(info);
			text[i] = text[i].substr(id + close.size(), string::npos);
		}
	}
	return result;
}

string cleanFromKeywords(string result) {
	vector<string> removeStrings = {"&nbsp;", "Shadow", "subm.", "/&nbsp;"};
	for(auto &s: removeStrings) {
		size_t id;
		while((id = result.find(s)) != string::npos) {
			result.erase(id, s.size());
		}
	}
	return result;
}

string cleanInformation(string s) {
	bool include = true;
	string result = "";
	forn(i, s.size()) {
		if(s[i] == '<') include = false;
		if(include == true) {
			result += s[i];
		}
		if(s[i] == '>') include = true;
	}

	return cleanFromKeywords(result);
}

string trim(string s) {
	int i = 0, j = s.size() - 1;
	while(i < s.size() && s[i] == ' ') i++;
	while(j >= 0 && s[j] == ' ') j--;
	if(i <= j) {
		s = s.substr(i, j - i + 1);
	}
	else {
		s = "";
	}
	return s;
}

vector<string> cleanInformation(vector<string> info) {
	vector<string> result;
	forn(i, info.size()) {
		string aux = trim(cleanInformation(info[i]));
		if(aux.size() > 0) {
			result.pb(aux);
		}
	}
	return result;
}

vector<Submission> formatLogs(vector<string> info) {
	if(info.size() % totalNumberOfColumnsBySubmission != 0) {
		perror("logs are not complete. It is not divisble by the number of columns.");
		exit(0);
	}

	vector<Submission> results;
	forn(i, info.size()) {
		lli submissionTime = computeDifferenceInMinutes(info[i + 1], initialDateOfContest);
		Submission s(info[i], submissionTime, info[i+2], info[i+3], info[i+4], info[i+5], info[i+6], info[i+7]);
		results.pb(s);
		i += 7;
	}

	return results;
}

vector<Submission> findSubmissionsTable(string text) {
	string open = "<table", close = "</table>";
	size_t id = text.find(open);
	if(id == string::npos) {
		perror("logs were not found in this file...");
		exit(0);
	}
	text = text.substr(id, string::npos);

	id = text.find(close);
	if(id == string::npos) {
		perror("logs were not found in this file...");
		exit(0);
	}
	text = text.substr(0, id + close.size());
	vector<string> submissions(1, text);
	submissions = findSubmissionInformation(submissions, "<tr", "</tr>");
	vector<string> header = findSubmissionInformation(submissions, "<th", "</th>");
	submissions = findSubmissionInformation(submissions, "<td", "</td>");
	submissions = cleanInformation(submissions);
	vector<Submission> logs = formatLogs(submissions);
	return logs;
}

vector<Submission> parseFile(string text) {
	string stringSearching = "Contest status";
	bool stringFound = false;
	vector<Submission> logs;
	forn(i, text.size() - stringSearching.size()) {
		string currentString = text.substr(i, stringSearching.size());
		if(currentString == stringSearching) {
			text = text.substr(i, string::npos);
			vector<Submission> aux = findSubmissionsTable(text);
			for(auto &s: aux) {
				logs.pb(s);
			}
			stringFound = true;
			break;
		}
	}

	if(!stringFound) {
		perror("logs were not found in this file...");
	}
	else {
		cout<<"logs were found succesfully..."<<endl;
	}

	return logs;
}

vector<Submission> readFile(const string &fileName) {
	ifstream myFile;
	myFile.open(fileName);

	vector<Submission> logs;
	if(myFile.is_open()) {
		string cad, text = "";
		while(getline(myFile, cad)) text += clean(cad);
		logs = parseFile(text);
		myFile.close();
	}
	return logs;
}

void readFilesStatusAndGetLogs() {
	cout<<"Reading and parsing file status."<<endl;
	vector<Submission> logsInfo;
	for(int i=1;i<=fileStatus;++i) {
		stringstream ss;
		ss << i;
		string fileName = "status/" + ss.str() + ".html";
		cout<<"File "<<fileName<<endl;
		vector<Submission> aux = readFile(fileName);
		for(auto &s: aux) {
			logsInfo.pb(s);
		}
	}
	logs.open("logs/logs.json");
	writeLogs(logsInfo);
	logs.close();
	cout<<"Logs generated succesfully..."<<endl;
		cout<<endl;
}

// чтение и перевод это будет пустой тратой времени
int main(int argc, char **argv) {
	parseArguments(argc, argv);
	checkFileStatusExistence();
	readFilesStatusAndGetLogs();
	return 0;
}
