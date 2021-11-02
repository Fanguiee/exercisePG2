#include"pg2.h"
using namespace std;
const std::string db_file = "pg2tagdb";

void help_quit(const string &prog_name, int returncode){
	cout << "Usage: " << prog_name << " option arguments..." << endl;
	cout << "A simple tag database" << endl << endl;
	cout << "  -h, --help         Show this help text" << endl;
	exit(returncode);
}

void add(const string &tag, const string &line) {
	ofstream ofs(db_file, ios::app);
	ofs<<tag<<"  "<<line<<endl;
}

void query(const string &tag){
	string line, tags;
	while(true){
		ifstream ifs(db_file);
		ifs>>tags;
		if(!ifs) break;
		getline(ifs, line);
		
		string work;
		vector<string> current_tags;
		for(int i = 0; i < tags.length(); ++i){
				if(tags[i] != ',')
					work += tags[i];
				else {
					current_tags.push_back(work);
					work = "";
				}
		}
		current_tags.push_back(work);
		
		//search for the tag 
		for(int i = 0; i < current_tags.size(); ++i){
			if(current_tags.at(i) == tag)
				cout<<line;
				break;
		}
	}
	
	return 0;
}

int main(int argc, char **argv){
	
	if(argc == 1)
		help_quit(argv[0],1);
	string command = argv[1];
	if(command == "-h")
		help_quit(argv[0],0);
	if(command == "-a"){
		if(argc < 4){
			cout<<"false input";
			help_quit(argv[0],1);
		}
		string tags = argv[2];
		ostringstream concat;
		concat<<argv[3];
		for(int i = 4; i < argc; ++i){
			concat<<" "<<argv[i];
		}
		add(tags,concat.str());
	}	
	else if(command == "-q") {
		if(argc < 3){
			cout<<"false input";
			help_quit(argv[0],1);
		}
		
		string tags= argv[2];
		query(tags);
	}
	else {
		cerr<<"unknown command "<<command<<endl;
		return 1;
	}
	return 0;
}