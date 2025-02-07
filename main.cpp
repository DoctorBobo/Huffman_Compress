// #include <bits/stdc++.h>
// using namespace std;

// struct HuffmanNode {
//     char data;
//     int freq;
//     HuffmanNode* left;
//     HuffmanNode* right;

//     HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
//     HuffmanNode(int freq, HuffmanNode* left, HuffmanNode* right) : data('\0'), freq(freq), left(left), right(right) {}
// };
// struct Compare {
//     bool operator()(HuffmanNode* left, HuffmanNode* right) {
//         return left->freq > right->freq; 
//     }
// };

// HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freq_map) {
//     priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
//     for (const auto& pair : freq_map) {
//         pq.push(new HuffmanNode(pair.first, pair.second));
//     }
//     while (pq.size() > 1) {
//         HuffmanNode* left = pq.top(); pq.pop();
//         HuffmanNode* right = pq.top(); pq.pop();
//         int combinedFreq = left->freq + right->freq;
//         pq.push(new HuffmanNode(combinedFreq, left, right));
//     }

//     return pq.top();
// }

// void generateHuffmanCodes(HuffmanNode* root, const string& str, unordered_map<char, string>& huffmanCodes) {
//     if (root == nullptr) return;

//     if (root->data != '\0') {
//         huffmanCodes[root->data] = str;
//     }

//     generateHuffmanCodes(root->left, str + "0", huffmanCodes);
//     generateHuffmanCodes(root->right, str + "1", huffmanCodes);
// }

// void compressFile(const string& inputFile, const string& outputFile) {
//     ifstream inFile(inputFile, ios::binary);
//     ofstream outFile(outputFile, ios::binary);

//     unordered_map<char, int> freq_map;
//     char ch;
//     while (inFile.get(ch)) {
//         freq_map[ch]++;
//     }
//     HuffmanNode* root = buildHuffmanTree(freq_map);
//     unordered_map<char, string> huffmanCodes;
//     generateHuffmanCodes(root, "", huffmanCodes);
//     inFile.clear();
//     inFile.seekg(0, ios::beg);
//     string encodedStr;
//     while (inFile.get(ch)) {
//         encodedStr += huffmanCodes[ch];
//     }
//     string byteBuffer;
//     for (size_t i = 0; i < encodedStr.size(); i++) {
//         byteBuffer += encodedStr[i];
//         if (byteBuffer.size() == 8) {
//             outFile.put(static_cast<unsigned char>(stoi(byteBuffer, nullptr, 2)));
//             byteBuffer.clear();
//         }
//     }
//     if (!byteBuffer.empty()) {
//         while (byteBuffer.size() < 8) {
//             byteBuffer += '0';
//         }
//         outFile.put(static_cast<unsigned char>(stoi(byteBuffer, nullptr, 2)));
//     }

//     inFile.close();
//     outFile.close();
// }

// void decompressFile(const std::string& inputFile, const std::string& outputFile, const std::unordered_map<std::string, char>& reverseHuffmanCodes) {
//     std::ifstream inFile(inputFile, std::ios::binary);
//     std::ofstream outFile(outputFile, std::ios::binary);

//     std::string encodedStr;
//     char ch;
//     while (inFile.get(ch)) {
//         for (int i = 7; i >= 0; --i) {
//             encodedStr += ((ch >> i) & 1) ? '1' : '0';
//         }
//     }
//     std::string tempStr;
//     for (size_t i = 0; i < encodedStr.size(); ++i) {
//         tempStr += encodedStr[i];
//         if (reverseHuffmanCodes.find(tempStr) != reverseHuffmanCodes.end()) {
//             outFile.put(reverseHuffmanCodes.at(tempStr));
//             tempStr.clear();
//         }
//     }

//     inFile.close();
//     outFile.close();
// }

// unordered_map<string, char> buildReverseHuffmanCodes(const unordered_map<char, string>& huffmanCodes) {
//     unordered_map<string, char> reverseHuffmanCodes;
//     for (const auto& pair : huffmanCodes) {
//         reverseHuffmanCodes[pair.second] = pair.first;
//     }
//     return reverseHuffmanCodes;
// }

// // 测试主函数
// int main() {
//     system("chcp 65001");
//     string inputFile = "test.txt";
//     string compressedFile = "compressed.txt";
//     string decompressedFile = "decompressed.txt";
//     // ofstream outFile(inputFile);
//     // outFile.close();
//     compressFile(inputFile, compressedFile);
//     ifstream inFile(inputFile, ios::binary);
//     unordered_map<char, int> freq_map;
//     char ch;
//     while (inFile.get(ch)) {
//         freq_map[ch]++;
//     }

//     HuffmanNode* root = buildHuffmanTree(freq_map);
//     unordered_map<char, string> huffmanCodes;
//     generateHuffmanCodes(root, "", huffmanCodes);
//     unordered_map<string, char> reverseHuffmanCodes = buildReverseHuffmanCodes(huffmanCodes);
//     decompressFile(compressedFile, decompressedFile, reverseHuffmanCodes);
//     cout << "Original File Content:" << endl;
//     ifstream originalFile(inputFile);
//     string originalContent((istreambuf_iterator<char>(originalFile)), istreambuf_iterator<char>());
//     cout << originalContent << endl;

//     cout << "Decompressed File Content:" << endl;
//     ifstream decompressedFileStream(decompressedFile);
//     string decompressedContent((istreambuf_iterator<char>(decompressedFileStream)), istreambuf_iterator<char>());
//     cout << decompressedContent << endl;
    

//     std::filesystem::path filePath_1 = "test.txt";
//     std::filesystem::path filePath_2 = "compressed.txt";
    
//     if (std::filesystem::exists(filePath_1) && std::filesystem::exists(filePath_2)) {
//         std::uintmax_t fileSize_1 = std::filesystem::file_size(filePath_1);
//         std::uintmax_t fileSize_2 = std::filesystem::file_size(filePath_2);
//         std::cout << "Before compressed: " << fileSize_1 << " bytes\n";
//         std::cout << "After compressed: " << fileSize_2 << " bytes\n";
//         std::cout << "Compression ratio: " << (1.0 * fileSize_1 / (1.0 * fileSize_2)) << "\n";
//     }
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(int freq, HuffmanNode* left, HuffmanNode* right) : data('\0'), freq(freq), left(left), right(right) {}
};

struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->freq > right->freq; 
    }
};

HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freq_map) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (const auto& pair : freq_map) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        int combinedFreq = left->freq + right->freq;
        pq.push(new HuffmanNode(combinedFreq, left, right));
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode* root, const string& str, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) return;

    if (root->data != '\0') {
        huffmanCodes[root->data] = str;
    }

    generateHuffmanCodes(root->left, str + "0", huffmanCodes);
    generateHuffmanCodes(root->right, str + "1", huffmanCodes);
}

void compressFile(const string& inputFile, const string& outputFile, unordered_map<char, string>& huffmanCodes) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    unordered_map<char, int> freq_map;
    char ch;
    while (inFile.get(ch)) {
        freq_map[ch]++;
    }
    HuffmanNode* root = buildHuffmanTree(freq_map);
    generateHuffmanCodes(root, "", huffmanCodes);
    cout << "Huffman Codes for characters in the file:" << endl;
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    inFile.clear();
    inFile.seekg(0, ios::beg);
    string encodedStr;
    while (inFile.get(ch)) {
        encodedStr += huffmanCodes[ch];
    }
    string byteBuffer;
    for (size_t i = 0; i < encodedStr.size(); i++) {
        byteBuffer += encodedStr[i];
        if (byteBuffer.size() == 8) {
            outFile.put(static_cast<unsigned char>(stoi(byteBuffer, nullptr, 2)));
            byteBuffer.clear();
        }
    }
    if (!byteBuffer.empty()) {
        while (byteBuffer.size() < 8) {
            byteBuffer += '0';
        }
        outFile.put(static_cast<unsigned char>(stoi(byteBuffer, nullptr, 2)));
    }

    inFile.close();
    outFile.close();
}

void decompressFile(const std::string& inputFile, const std::string& outputFile, const std::unordered_map<std::string, char>& reverseHuffmanCodes) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    std::string encodedStr;
    char ch;
    while (inFile.get(ch)) {
        for (int i = 7; i >= 0; --i) {
            encodedStr += ((ch >> i) & 1) ? '1' : '0';
        }
    }
    std::string tempStr;
    for (size_t i = 0; i < encodedStr.size(); ++i) {
        tempStr += encodedStr[i];
        if (reverseHuffmanCodes.find(tempStr) != reverseHuffmanCodes.end()) {
            outFile.put(reverseHuffmanCodes.at(tempStr));
            tempStr.clear();
        }
    }

    inFile.close();
    outFile.close();
}

unordered_map<string, char> buildReverseHuffmanCodes(const unordered_map<char, string>& huffmanCodes) {
    unordered_map<string, char> reverseHuffmanCodes;
    for (const auto& pair : huffmanCodes) {
        reverseHuffmanCodes[pair.second] = pair.first;
    }
    return reverseHuffmanCodes;
}

// 计算压缩比
double calculateCompressionRatio(const string& inputFile, const string& outputFile) {
    std::filesystem::path filePath_1 = inputFile;
    std::filesystem::path filePath_2 = outputFile;

    if (std::filesystem::exists(filePath_1) && std::filesystem::exists(filePath_2)) {
        std::uintmax_t fileSize_1 = std::filesystem::file_size(filePath_1);
        std::uintmax_t fileSize_2 = std::filesystem::file_size(filePath_2);
        cout << "Before compressed: " << fileSize_1 << " bytes\n";
        cout << "After compressed: " << fileSize_2 << " bytes\n";
        return 1.0 * fileSize_1 / (1.0 * fileSize_2);
    }
    return 0.0;
}
int main() {
    system("chcp 65001");
    string inputFile = "test.txt";
    string compressedFile = "compressed.txt";
    string decompressedFile = "decompressed.txt";

    unordered_map<char, string> huffmanCodes;
    compressFile(inputFile, compressedFile, huffmanCodes);

    unordered_map<string, char> reverseHuffmanCodes = buildReverseHuffmanCodes(huffmanCodes);
    decompressFile(compressedFile, decompressedFile, reverseHuffmanCodes);

    cout << "\nOriginal File Content:" << endl;
    ifstream originalFile(inputFile);
    string originalContent((istreambuf_iterator<char>(originalFile)), istreambuf_iterator<char>());
    cout << originalContent << endl;

    cout << "\nDecompressed File Content:" << endl;
    ifstream decompressedFileStream(decompressedFile);
    string decompressedContent((istreambuf_iterator<char>(decompressedFileStream)), istreambuf_iterator<char>());
    cout << decompressedContent << endl;
    double compressionRatio = calculateCompressionRatio(inputFile, compressedFile);
    cout << "Compression ratio: " << compressionRatio << "\n";

    return 0;
}
