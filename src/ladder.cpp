#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << word1 << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    if (abs(len1 - len2) > d) {
        return false;
    }

    if (str1 == str2) {
        return 0 <= d;
    }

    if (len1 == len2) {
        int diff = 0;
        for (size_t i = 0; i < len1; ++i) {
            if (str1[i] != str2[i]) {
                ++diff;
                if (diff > d) {
                    return false;
                }
            }
        }
        return true;
    }

    if (len1 == len2 + 1) {
        for (size_t i = 0; i < len1; ++i) {
            string temp = str1;
            temp.erase(i, 1);
            if (temp == str2) {
                return true;
            }
        }
    }

    if (len2 == len1 + 1) {
        for (size_t i = 0; i < len2; ++i) {
            string temp = str2;
            temp.erase(i, 1);
            if (temp == str1) {
                return true;
            }
        }
    }
    return false;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (const string & word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder." << endl;
    } else {
        for (const string & word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }

}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "/home/yfirsten/ICS46/ics-46-hw-9-yilayfirst/src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}