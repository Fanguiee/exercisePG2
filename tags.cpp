#include "pg2.h"

const std::string db_file = "pg2tagdb";

void help_and_quit(const string &prog_name, int returncode) {
	cout << "Usage: " << prog_name << " option arguments..." << endl;
	cout << "A simple tag database" << endl << endl;
	cout << "  -h, --help         Show this help text" << endl;
	exit(returncode);
}

void add(const string &tags, const string &data) {
	// datenbank zum anhängen öffnen
	ofstream db(db_file, ios::app);
	// zeile der form "tag1,tag2,...,tagn restlicher content in frei form" anhängen
	db << tags << " " << data << endl;
}

void query(const string &tag) {
	// datenbank öffnen
	ifstream db(db_file);
	string line, tags;

	// so lange laufen wie nötig
	while (true) {
		// tag-liste und "rest" einlesen (bis datei fertig)
		db >> tags;
		if (!db) break;
		getline(db, line);

		// tag-liste am , aufsplitten
		string work;
		vector<string> individual_tags;
		for (int i = 0; i < tags.length(); ++i)
			if (tags[i] != ',')
				work += tags[i];
			else {
				individual_tags.push_back(work);
				work = "";
			}
		individual_tags.push_back(work);

		// prüfen, ob der gewünschte tag in diesem eintrag gesetzt ist
		for (int i = 0; i < individual_tags.size(); ++i)
			if (individual_tags[i] == tag) {
				cout << line << endl;
				break;
			}

		// dann weiter mit nächster zeile
	}
}

int main(int argc, char **argv) {
	if (argc == 1)
		help_and_quit(argv[0], 1);
	string command = argv[1];
	if (command == "--help" || command == "-h")
		help_and_quit(argv[0], 0);

	if (command == "--add" || command == "-a") {
		if (argc < 3) {
			cerr << "Missing argument to --add" << endl;
			return 1;
		}
		string tags = argv[2];
		if (argc < 4) {
			cerr << "Missing content" << endl;
			return 1;
		}
		ostringstream concat;
		concat << argv[3];
		for (int i = 4; i < argc; ++i)
			concat << " " << argv[i];
		add(tags, concat.str());
	}
	else if (command == "--query" || command == "-q") {
		if (argc != 3) {
			cerr << "Either there is no query, or too much of it" << endl;
			return 1;
		}
		query(argv[2]);
	}
	else {
		cerr << "Unknown option " << command << endl;
		return 1;
	}

	return 0;
}
