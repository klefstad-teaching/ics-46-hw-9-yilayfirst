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

map<string, vector<string>> preprocess(const set<string> & word_list) {
    map<string, vector<string>> adj_map;

    for (const string & word : word_list) {
        for (size_t i = 0; i < word.length(); ++i) {
            string pat = word;
            pat[i] = '*';
            adj_map[pat].push_back(word);
        }

        for (size_t i = 0; i <= word.length(); ++i) {
            string pat = word.substr(0, i) + '*' + word.substr(i);
            adj_map[pat].push_back(word);
        }
    }

    return adj_map;
}

vector<string> get_adj(const string & word, const map<string, vector<string>> & adj_map) {
    vector<string> adj_words;

    for (size_t i = 0; i < word.length(); ++i) {
        string pat = word;
        pat[i] = '*';

        if (adj_map.count(pat) > 0) {
            const vector<string> & potential = adj_map.at(pat);
            for (const string & pot : potential) {
                if (pot != word) {
                    adj_words.push_back(pot);
                }
            }
        }
    }

    for (size_t i = 0; i < word.length(); ++i) {
        string pat = word.substr(0, i) + '*' + word.substr(i);

        if (adj_map.count(pat) > 0) {
            const vector<string> & potential = adj_map.at(pat);
            for (const string & pot : potential) {
                if (pot.length() == word.length() - 1) {
                    adj_words.push_back(pot);
                }
            }
        }
    }

    for (size_t i = 0; i < word.length(); ++i) {
        string pat = word.substr(0, i) + '*' + word.substr(i + 1);

        if (adj_map.count(pat) > 0) {
            const vector<string> & potential = adj_map.at(pat);
            for (const string & pot : potential) {
                if (pot.length() == word.length() + 1) {
                    adj_words.push_back(pot);
                }
            }
        }
    }

    return adj_words;
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

    const string & longer = (len1 > len2) ? str1 : str2;
    const string & shorter = (len1 > len2) ? str2 : str1;
    int longI = 0;
    int shortI = 0;
    bool skip = false;
    while (longI < longer.length() && shortI < shorter.length()) {
        if (longer[longI] == shorter[shortI]) {
            ++longI;
            ++shortI;
        } else {
            if (skip) {
                return false;
            }
            skip = true;
            ++longI;
        }
    }
    return (shortI == shorter.length() && (longI == longer.length() || !skip));
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    //map<string, vector<string>> adj_map = preprocess(word_list);
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        //vector<string> adj_words = get_adj(last_word, adj_map);
        for (const string & word : word_list) {
            if (is_adjacent(last_word, word)){
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
        cout << "No word ladder found." << endl;
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