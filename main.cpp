#include <fstream>
#include <string>
#include <iostream>

std::string brainFuck(const std::string &code, const std::string &input) {
    unsigned char tape[30000] = {0};
    unsigned char *m = tape;   
    std::string result;

    int i = 0;
    int ci = 0;

    while (ci < code.size()) {
        char ch = code[ci];

        switch (ch) {
            case '>':
                ++m;
                if (m >= tape + 30000) {
                    return "ERROR";
                }
                break;

            case '<':
                if (m == tape) {
                    return "ERROR";
                }
                --m;
                break;

            case '+':
                ++(*m);
                break;

            case '-':
                --(*m);
                break;

            case '.':
                result += static_cast<char>(*m);
                break;

            case ',':
                if (i >= input.size()) {
                    *m = 0;
                }
                *m = static_cast<unsigned char>(input[i++]);
                break;

            case '[':
                if (*m == 0) {
                    int f = 1;
                    ++ci;
                    while (ci < code.size() && f > 0) {
                        if (code[ci] == '[') {
                        	++f;
                        }
                        else if (code[ci] == ']') {
                        	--f;
                        }
                        if (f > 0) {
                        	++ci;
                        }
                    }
                    if (f != 0) {
                        return "ERROR"; 
                    }
                    break; 
                }
                break;

            case ']':
                if (*m != 0) {
                    if (ci == 0) {
                        return "ERROR";
                    }
                    int f = 1;
                    --ci;
                    while (ci < code.size() && f > 0) {
                        if (code[ci] == ']') {
                        	++f;
                        }
                        else if (code[ci] == '[') {
                        	--f;
                        }
                        if (f > 0) {
                            if (ci == 0) {
                                return "ERROR";
                            }
                            --ci;
                        }
                    }
                    if (f != 0) {
                        return "ERROR";
                    }
                    break;
                }
                break;

        }

        ++ci;
    }

    return result;
}


std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "ERROR";
        return "";
    }

	std::string content;
	std::string line;
	while (std::getline(file, line)) {
		content += line;
	}

	if (content.empty() == true) {
		std::cout << "ERROR";
		return "";
	}
    return content;
}

int main(int argc, char* argv[]) {
    std::string code = read_file(argv[1]);
    std::string input = read_file(argv[2]);

	std::cout << brainFuck(code, input);
	
	return 0;
}
