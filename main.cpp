#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<random>
#include<cctype>
#include<algorithm>


// check if the word exist in our vector (list of words)
bool vector_contains_word(const std::vector<std::string> &words, const std::string &the_word) {

    for (const std::string &s : words)
        if (the_word == s)
            return true;

    return false;
}

std::vector<char> Fill_Vec_word(const std::string &word) {
    std::vector<char> vec;
    for (int i = 0; i <= 4; ++i) {
        vec.push_back(word[i]);
    }
    return vec;
}

int score_match_char(const std::string &word1, const std::string &word2) {
    if (word1 == word2)
        return 15;

    std::vector<char> VectOfWord1 = Fill_Vec_word(word1);
    std::vector<char> VectOfWord2 = Fill_Vec_word(word2); // Plyaer_word
    int score = 0;


    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (VectOfWord1[i] == VectOfWord2[j]) {
                score += 2;
                if (i == j)
                    score++;
                VectOfWord2[j] = '0';
                break;
            }

        }
    }

    return score;
}


int main() {
    std::string word;
    std::vector<std::string> five_words;
    {
        std::ifstream read_file("/home/mohammed-la/CLionProjects/guess/20k.txt");
        for (std::string line; getline(read_file, line);) {
            if (line.empty() || line.length() != 5)
                continue;
            five_words.push_back(line);
        }
    }

    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, five_words.size() - 1);

    const std::string target_word = five_words[dist(mt)];
    std::string player_word;

    while (true) {
        std::cout << "Guess a word of five letter : ";
        std::getline(std::cin, player_word);


        //lowwerCase
        for (char &c : player_word) {
            c = (char) std::tolower(c);
        }


        // print the Solution
        if (player_word == "pgms") {
            std::cout << "Hahaaaa You could'nt guess it  " << std::endl;
            std::cout << "The Word is  : " << target_word << std::endl;
            std::cout << "Game Over!!!" << std::endl;
            break;
        }


        if (player_word.length() != 5) {
            std::cout << "I said five letter word !!!" << std::endl;
            continue;
        }
        if (!vector_contains_word(five_words, player_word)) {
            std::cout << "Thats isn't even a word -_-" << std::endl;
            continue;
        }

        const int score = score_match_char(target_word, player_word);

        if (score == 15) {
            std::cout << "You did it . Congrats" << std::endl;
            break;
        } else {
            std::cout << "Naaah that ain't it , I'll give you " << score << " points for you efforts" << std::endl;
            continue;
        }

    }


    return 0;
}
