


//HEADERS
#include <iostream>
#include <thread>//for wait
#include <chrono>//for wait
#include <conio.h>//for key detection
#include <string>//for directory choice
#include <fstream>//for text files
#include <cstdlib>//for windows command
#include <windows.h>
#include <fcntl.h>
#include <io.h>
using namespace std;

//GLOBAL VARIABLES
int rep;
int STATE;

//FUNCTIONS
void printWithDelay(const string& str, int delay_ms) {
	for (char c : str) {
		cout << c; this_thread::sleep_for(chrono::milliseconds(delay_ms));
	}
}
void animate(const wstring& wideString) {
	// Get console width dynamically
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left;

	int speed = 50; // Delay in milliseconds
	int maxOffset = consoleWidth;

	// Animation loop moving right and disappearing
	for (int offset = 0; offset <= maxOffset + 10; ++offset) {
		system("cls");

		// Shift ship right by adding spaces at the start of each line
		wstring shiftedString = L"";
		for (const wchar_t* line = wideString.c_str(); *line; ++line) {
			if (*line == L'\n') {
				shiftedString += L"\n" + wstring(min(offset, consoleWidth), L' ');
			}
			else {
				int currentPos = shiftedString.length() - shiftedString.rfind(L'\n') - 1;
				if (currentPos < consoleWidth) {
					shiftedString += *line;
				}
			}
		}

		// Convert wide string to multibyte for console output
		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, shiftedString.c_str(), -1, nullptr, 0, nullptr, nullptr);
		char* multiByteString = new char[bufferSize];
		WideCharToMultiByte(CP_UTF8, 0, shiftedString.c_str(), -1, multiByteString, bufferSize, nullptr, nullptr);

		cout << multiByteString << endl;
		delete[] multiByteString;
		Sleep(speed);
	}
	system("cls");
}
void wcoutForWindowsCMD(const wchar_t* wideString) {

	int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, nullptr, 0, nullptr, nullptr); //Windows c++ function that handles finding the size reqiured of the input buffer to move it the output one, pointed to by "multiByteString"

	char* multiByteString = new char[bufferSize]; // Allocates the new buffer

	WideCharToMultiByte(CP_UTF8, 0, wideString, -1, multiByteString, bufferSize, nullptr, nullptr); // Converts my unicode text from UTF-16 to UTF-8

	cout << multiByteString << std::endl; // Outputs the newly converted text in the output buffer

	delete[] multiByteString;
}
void pauseForEnter() {
	printWithDelay("PRESS ENTER TO CONTINUE...\n", 50);
	while (true) {
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 13) {
				break;
			}
			else {}
		}
	}
	system("cls");
}
int qte(int timeoutSeconds) {
	clock_t startTime = clock();  // Start timing
	while (true) {
		// Check if 3 seconds have passed
		if (((clock() - startTime) / CLOCKS_PER_SEC) >= timeoutSeconds) {
			cout << "Something very, very bad just happened...\n";
			exit(0);  // Timeout failure
		}
		// Check if a key is pressed
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 32) {  // Enter key (ASCII 13)
				return 1;  // Success
			}
		}
	}
}

//MAIN SCRIPT
int main() {
	SetConsoleOutputCP(CP_UTF8);//allows the program to output unicode characters required for the title screen to properly display
	//displays connecting message
	cout << "Connecting"; // Print the word "Connecting"
	while (rep < 3) {
		this_thread::sleep_for(std::chrono::milliseconds(500));
		printWithDelay("...", 500);
		cout << "\033[11G";
		cout << "   ";
		cout << "\033[11G";
		rep++;
	}
	cout << "\rConnecting...\n";
	//prints first message, and resets repeat counter variable, and pauses code for 1500 ms.	
	cout << "ERR: No radio contact with default channel. Retrying with backup...\n";
	rep = 0;
	this_thread::sleep_for(std::chrono::milliseconds(1500));
	cout << "Connecting";
	rep = 0;
	while (rep < 3) {
		this_thread::sleep_for(std::chrono::milliseconds(500));
		printWithDelay("...", 500);
		cout << "\033[11G";
		cout << "   ";
		cout << "\033[11G";
		rep++;
	}
	cout << "\rConnecting...\n";
	//displays message of switching to radio mode.
	cout << "WARN: Backup connection failed. Switching to scan mode";
	printWithDelay("...", 500);
	this_thread::sleep_for(std::chrono::milliseconds(250));
	cout << "Done.\n\n";
	this_thread::sleep_for(std::chrono::milliseconds(1000));
	wcoutForWindowsCMD(L"░▒▓███████▓▒░ ░▒▓█▓▒░         ░▒▓███████▓▒░ ░▒▓████████▓▒░ ░▒▓████████▓▒░   ░▒▓███████▓▒░   ░▒▓███████▓▒░\n░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░         ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░            ░▒▓█▓▒░      ░▒▓█▓▒░         ░▒▓█▓▒░░▒▓█▓▒░\n ░▒▓█▓▒░░▒▓█▓▒ ░▒▓█▓▒░         ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░           ░▒▓█▓▒░      ░▒▓█▓▒░        ░▒▓█▓▒░░░▒▓█▓▒░\n ░▒▓███████▓▒░░▒▓█▓▒░         ░▒▓████████▓▒░ ░▒▓██████▓▒░       ░▒▓█▓▒░      ░▒▓██████▓▒░    ░▒▓█▓▒░░▒▓█▓▒░\n ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░         ░▒▓█▓▒░░▒▓█▓▒░         ░▒▓█▓▒░     ░▒▓█▓▒░     ░▒▓█▓▒░         ░▒▓█▓▒░░░▒▓█▓▒░\n ░▒▓█▓▒░░▒▓█▓▒░ ▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░         ░▒▓█▓▒░   ░▒▓█▓▒░      ░▒▓█▓▒░          ░▒▓█▓▒░░▒▓█▓▒░\n░▒▓███████▓▒░ ░▒▓████████▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓███████▓▒░       ░▒▓█▓▒░      ░▒▓████████▓▒░   ░▒▓███████▓▒░\n");
	this_thread::sleep_for(std::chrono::milliseconds(1000));//full chunk displays title, and waits 1000 ms. //this segment was generated by AI, and edited by me.
	//displays subtitle
	cout << "A SHORT TEXT BASED PUZZLE GAME BY JACK TRUSCOTT\n\n";
	cout << "PRESS ENTER TO BEGIN, OR ESC TO QUIT\n";
	while (true) {
		if (_kbhit()) {  // Check if a key has been pressed
			char ch = _getch();  // Get the pressed key's ascii value
			if (ch == 27) {  // 27 is the ASCII value for the Escape key, so when getch tells the computer the value is 27, this code runs
				cout << "Exiting...\n\n";
				this_thread::sleep_for(std::chrono::milliseconds(1000));
				exit(0);
			}
			if (ch == 13) {  // 13 is the ASCII value for the Enter key, same process with getch
				cout << "Loading...\n\n";
				this_thread::sleep_for(std::chrono::milliseconds(1000));
				STATE = 0;
				break;
			}
			if (ch == 68) {
				cout << "DEBUG MODE\n\n";
				this_thread::sleep_for(std::chrono::milliseconds(1000));
				STATE = 1;
				break;
			}
			else {}
		}
	}
	system("cls");
	if (STATE == 0) {
		string pass;
		string name;
		cout << "LOGIN:\n\nUSERNAME\n\n";
		cin >> name;
		cout << "\nPASSWORD\n\n";
		cin >> pass;
		cout << "Loading user data...";
		this_thread::sleep_for(std::chrono::milliseconds(1500));
		cout << "Done.\n";
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("cls");
		this_thread::sleep_for(std::chrono::milliseconds(1500));
		printWithDelay("cd\\home\\" + name + "\\documents\\logs\\2034\\april\\\n", 50);
		this_thread::sleep_for(std::chrono::milliseconds(500));
		cout << "\\home\\" << name << "\\documents\\logs\\2034\\april\\\n";
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		printWithDelay("ls", 50);
		this_thread::sleep_for(std::chrono::milliseconds(1500));
		cout << "\\home\\" << name << "\\documents\\logs\\2034\\april\\\n";
		this_thread::sleep_for(std::chrono::milliseconds(100));
		cout << "1.txt	2.txt	3.txt	4.txt	5.txt	6.txt	7.txt\n\n\n\n";
		string file;
		cin >> file;
		rep = 0;
		while (rep < 7) {
			if (file == "1.txt") {
				ofstream outFile("1.txt");
				outFile << "Personal log 04/01/2034\nWe've started the slow process of decommissioning the ISS today, following the usual protocols. The station is old - 36 years in orbit and barely holding together. It's routine. Powering down the science labs, clearing out the old research equipment, shutting off communication relays. The systems are dated, some on their last legs, but we've kept them operational longer than anyone thought possible. Now, it's just about making sure everything is safely powered off, secured, and ready for the eventual re-entry. The Earth below is as stunning as ever, rotating peacefully in the distance. There's talk of rising tensions among the major powers back home, but we have our work cut out for us. The last thing we expect is for the decommissioning to be anything but routine." << endl;
				outFile.close();
				system("notepad.exe 1.txt");
				rep++;
				if (rep < 7) { cin >> file; }
			}
			else if (file.find("2.txt") != string::npos) {
				ofstream outFile("2.txt");
				outFile << "Personal log 04/02/2034\nToday's task was to power down the life support systems. It's a delicate process - closing down the oxygen generators and thermal regulation, making sure there are no leaks. The same checks we've done a thousand times. But as I reach for the switch, the comms crackle unexpectedly. At first, it's just static - fragments of voices breaking through the noise. We're used to occasional glitches, but this feels different. Then the transmission cuts out entirely. The static lingers longer than it should, and we sit in silence, waiting for any response. But there's nothing. We can still hear each other in the station, but no word from ground control. A strange sense of unease settles over us. We've been trained for emergencies, but this doesn't feel like one. Something is off." << endl;
				outFile.close();
				system("notepad.exe 2.txt");
				rep++;
				if (rep < 7) { cin >> file; }
			}
			else if (file.find("3.txt") != string::npos) {
				ofstream outFile("3.txt");
				outFile << "Personal log 04/03/2034\nThe station hums around us, but the stillness has settled into something far worse than quiet. It's as if the world below has stopped entirely. I check the comms again, trying to re-establish contact with Houston, but there's no response. And then—just as we begin to focus on what to do next - a bright flash erupts on the surface of the Earth. At first, it looks like a distant thunderstorm, but it's too intense, too sudden. I freeze. The flash is followed by another, then another. Cities are lighting up all over, dotting the ground like some kind of messed up firework show in the night. Only this isn't a celebration. It's something much worse. I don’t know what's happening down there, but the flashes seem too consistent, too deliberate." << endl;
				outFile.close();
				system("notepad.exe 3.txt");
				rep++;
				if (rep < 7) { cin >> file; }
			}
			else if (file.find("4.txt") != string::npos) {
				ofstream outFile("4.txt");
				outFile << "Personal log 04/04/2034\nThe flashes continue all night, and the world below seems to be burning with them. I try again to get any kind of communication, but the system is dead. The radio waves are filled with nothing but static, likely due to the massive amounts of smoke and debris now visible from up here. We were supposed to have redundancy for issues like these, but it's as if we're disconnected entirely from Earth. My heart is racing as I watch the blinding light of explosions flicker across the planet's surface, lighting up entire regions in the blink of an eye. One of my colleagues suggests we send a distress signal, but without comms, that's impossible. We've been trained for these moments, but there's no protocol for a situation like this - where the world has erupted in flames, and we're floating in the silence of space, unable to reach anyone. The Earth we've known is slipping away. And we're still here, helpless." << endl;
				outFile.close();
				system("notepad.exe 4.txt");
				rep++;
				if (rep < 7) { cin >> file; }
			}
			else if (file.find("5.txt") != string::npos) {
				ofstream outFile("5.txt");
				outFile << "Personal log 04/05/2034\nI'm working on the backup communication systems now. It's a long shot, given all the smoke, but maybe we can get a signal through. I've gone through the manual twice already, checking every connection, every wire, every protocol, but nothing seems to work. It's like the system has been completely fried. It could well be, given that explosions of that magnitude put off an electromagnetic pulse. For all we know, our equipment could only think it works, while not getting a single signal through. Meanwhile, the flashes continue below, relentless. I can't look away. There's a sinking feeling in my chest as I watch the world I once knew being wiped out, piece by piece. The blasts are too bright, too frequent to be random. This isn’t just a war - it's something much larger, much worse than any conflict we've ever known. And we are stuck here, out of reach." << endl;
				outFile.close();
				system("notepad.exe 5.txt");
				rep++;
				if (rep < 7) { cin >> file; }
			}
			else if (file.find("6.txt") != string::npos) {
				ofstream outFile("6.txt");
				outFile << "Personal log 04/06/2034\nThe Earth below is shrouded in a chaotic storm of fire and smoke. Satellite and radio communications went down 4 days ago, and with it, our contact with Earth’s space agencies - Houston, Moscow, Beijing - all gone. That's assuming someone hasn't blown their centres to bits yet. The silence is deafening. I've been monitoring frequencies all night using the ham radio, desperate for any sign of life. Then - finally - amidst the static, I heard a faint voice. It was scrambled at first, but I caught the call sign: 'Kilo Foxtrot 3-9-8'. Amateur radio operators, somehow still operating their HAM radio stations in the midst of the devastation. I immediately responded, desperate for some form of communication. (TRANSCRIPT BELOW)\n\nISS: NA1SS to Kilo Foxtrot 3 - 9 - 8, do you copy? This is NA1SS, we are still in orbit.\n //The transmission was broken, filled with bursts of interference, but I could make out their reply.\nKF398: NA1SS, we hear you! We're here. Holding. How's the sky?\n //I don't know how long their survival will last, but for now, they remain. It's our last connection to the world below." << endl;
				outFile.close();
				system("notepad.exe 6.txt");
				rep++;
				if (rep < 7) { cin >> file; }
			}
			else if (file.find("7.txt") != string::npos) {
				ofstream outFile("7.txt");
				outFile << "Personal log 04/07/2034\nThis morning's transmission was more stable than last night's. I managed to make contact with KF398 again. The signal was weak, but there was clarity in their words. They spoke of rationing, keeping the small community together, and using the ham radio as their lifeline. They asked about the Earth, about the ISS, about what was left. (TRANSCRIPT BELOW)\n\nKF398: NA1SS, what's left of the world down there? What's happening?\n //I took a deep breath before responding, knowing the truth would hurt. \nISS: Kilo Foxtrot 3-9-8, the sky is dark with smoke. The cities, they've fallen. There's nothing left but ashes, and we can't see any lights until the smoke clears. But you're still there. You're holding.\n //There was a pause, long enough for me to worry if the signal had dropped again. Then their voice crackled through the static once more, tinged with both relief and sorrow: \nKF398: We're still here. We'll keep holding. You're our last link.\n //The isolation is overwhelming, but hearing their voices again, it keeps something alive inside us. As long as we're still in touch, there's a glimmer of hope. For now, at least, we keep the signal open." << endl;
				outFile.close();
				system("notepad.exe 7.txt");
				rep++;
				if (rep < 7) { cin >> file; }
			}
			else if (file.find("skip") != string::npos) {
				rep = 7;
			}
			else {
				cout << "Could not find the file specified.\n";
				cin >> file;
			}
		}
		system("cls");
		printWithDelay("NEW MISSION DIRECTIVE: MAKE IT HOME\n\n", 50);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		int shift = 0;
		printWithDelay("PART 1: MAKING CONNECTIONS\n\n\n", 50);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		printWithDelay("//We've decided to try to contact the others in space. It's cruel to try to go home without them.\n\n", 50);
		cout << "				 ___________________________\n";
		cout << "				| NASA RADIO UTILITY, 1998. |\n";
		const wchar_t* wideString = L"				 ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n";
		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, nullptr, 0, nullptr, nullptr); //Windows c++ function that handles finding the size reqiured of the input buffer to move it the output one, pointed to by "multiByteString"
		char* multiByteString = new char[bufferSize]; // Allocates the new buffer
		WideCharToMultiByte(CP_UTF8, 0, wideString, -1, multiByteString, bufferSize, nullptr, nullptr); // Converts my unicode text from UTF-16 to UTF-8
		cout << multiByteString << std::endl; // Outputs the newly converted text in the output buffer
		delete[] multiByteString;
		cout << "\n\nERR: SIGNAL TOO WEAK TO AUTO-ADJUST. PLEASE INPUT MANUAL ANGLE ADJUSTMENT.\n\n";
		printWithDelay("OUTBOUND: 'Tiangong, TSS, this is ISS, NA1SS, do you copy?' \n\n", 150);
		printWithDelay("INBOUND: 'LVV, zh kdyh vrolg frsb! Wklv lv Wldqjrqj, zh uhdg!' \n\n", 150);
		pauseForEnter();
		printWithDelay("//The signal is weak, and we can't tell what they're saying. Maybe a number can help us tune in...\n\n", 50);
		pauseForEnter();
		cout << "				 ___________________________\n";
		cout << "				| NASA RADIO UTILITY, 1998. |\n";
		wcout << L"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n";
		bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, nullptr, 0, nullptr, nullptr); //Windows c++ function that handles finding the size reqiured of the input buffer to move it the output one, pointed to by "multiByteString"
		multiByteString = new char[bufferSize]; // Allocates the new buffer
		WideCharToMultiByte(CP_UTF8, 0, wideString, -1, multiByteString, bufferSize, nullptr, nullptr); // Converts my unicode text from UTF-16 to UTF-8
		cout << multiByteString << std::endl; // Outputs the newly converted text in the output buffer
		delete[] multiByteString;
		cout << "\n\nERR: SIGNAL TOO WEAK TO AUTO-ADJUST. PLEASE INPUT MANUAL ANGLE ADJUSTMENT.\n\n";
		cin >> shift;
		while (shift != 3) {
			cin >> shift;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nERR: INPUT INVALID.\n\n";
			}
			else {
				cout << "\n ERR: WEAK OR NO SIGNAL DETECTED.";
			}
		}
		cout << "\nINFO: STABLE SIGNAL ESTABLISHED. MAINTAIN 3 DEGREES (SET ANGLE) FOR OPTIMAL CONNECTION.\n\n";
		printWithDelay("\nINBOUND: 'ISS, we have solid copy! This is Tiangong, we read!'\n\n", 150);
		pauseForEnter();
		printWithDelay("//The transmission was garbled, and the English was heavily accented, but with some fine tuning, we made contact.\n\n", 50);
		pauseForEnter();
	}
	else if (STATE == 1) {}
	animate(L"\n\n\n\n\n                            ░                                                \n                       ▓▓▓▒░▓▒▓▓▓███▒▒▓▒░                                    \n                      ░░▒▒▒░▒▒░▒▒▒▒▒▒░▒▒▓░                                    \n                        ▒    ▒▒▒░                                               \n   ▒▓▒░░░░░▓▓▓  ░░      ░▒▓░ ░▓▒▒            ░░░░░ ░░░░░░░▒▒▒░░░░░░             \n  ░▒▒▒▒▒░░▓▓▓▓▓▓▒▒▒▒▒░▒▓▓▓▓███████▓▓▓█▓▓▓██▓▓▒█▓▓▓▓▓▓░▓█▓▒▓▒░▒▓▓▓▒▒▓▒░░░░░░░           \n  ░▒▒▒▒▒▒▒▒▓▓▒░ ▒▒░ ▓█ ░▒▒▓▓▓▒▓▒▓   ░░▒▓▒▒▒▒░██▒▓▒▓░ ░▒ ░▓░      ░▓░                    \n  ▓▓ ░░▒▒  ▓█     ▓█▓█▒▓░ ░░░▒▒▒▒▒▒▒▓█▓█▒█░    ░█░      ░▓░                    \n  ▓▓       ▓█     ▓█▓█▒█░    ░░  ░▒ ██▓█▒█░    ░▓░      ░▓░                    \n  ▓█       ▒█     ▓█▓█▒▓░    ░░░    ██▓█▒█░    ▒█░       ▓░                    \n  ░▒       ░▒     ▓█▒█▒█▒    ░░░    █▓▒█▒█░     ░                              \n                  ▒█▒█▒░▒    ▒▓▒    █▓▓█▒█░                                    \n                  ▒█▒█░▒░    ▒▒░    ▓▒▒▒░░                                     \n                             ▒▓▒                                               \n                       ░░░░░░▒█▒░░░░░░                                         \n                            ░▓▒▒                                              \n                             ▒▓▒                                               \n");
	printWithDelay("PART 2: FIRE IN THE SKY\n\n\n", 50);
	printWithDelay("//We've gotten a number of things done. We've established contact with the Chinese scientists aboard the TSS, and made plans to dock the two stations, using their clone of our APAS docking system. Here's to hoping we'll make it. Due to our limited fuel, both stations will be burning at times we scheduled over the radio, but the margin for error is pretty scary.\n", 50);
	pauseForEnter();
	cout << "				 ___________________________\n";
	cout << "				| NASA RADIO UTILITY, 1998. |\n";
	wcoutForWindowsCMD(L"				 ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
	printWithDelay("OUTBOUND: 'Tiangong, this is ISS, how copy?'\n\n", 150);
	printWithDelay("INBOUND: 'ISS, we read you loud and clear.'\n\n", 150);
	printWithDelay("OUTBOUND: 'Copy, Tiangong. We're burning on schedule. Standby.\n\n", 150);
	pauseForEnter();
	cout << "ENGINE START...\n";
	this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << "IGNITION...\n";
	this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << "PRESS SPACE IN 3s OR LESS TO ENGAGE.\n";
	qte(3);
	cout << "IGNITION ENGAGED. STARTING BURN...\n";
	this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << "PRESS SPACE NOW!\n";
	qte(1);
	system("cls");
	cout << "				 ___________________________\n";
	cout << "				| NASA RADIO UTILITY, 1998. |\n";
	wcoutForWindowsCMD(L"				 ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
	printWithDelay("OUTBOUND: 'Initiating burn in 3, 2, 1. Burning for 10, 9, 8, 7, 6, 5, 4, 3, 2, 1. Engines are shut down, repeat, burn is complete and engines are off.'\n\n", 150);
	printWithDelay("INBOUND: 'Copy, ISS. We're standing by until it is time for our burn. Good luck.'\n\n", 150);
	pauseForEnter();
	printWithDelay("//The burn was successful, and we're now on course for an intercept with the TSS. We're just waiting on their own burn.\n\n", 50);
	this_thread::sleep_for(chrono::milliseconds(1000));
	return 0;
}