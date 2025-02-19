#include <bits/stdc++.h>
using namespace std;

/*
 * @brief 哈夫曼树节点类
 * 
 * 表示哈夫曼树的一个节点，包含字符数据、频率、左子节点和右子节点。
 */
class HuffmanNode {
public:
    char data;  // 节点存储的字符
    int freq;   // 字符出现的频率
    HuffmanNode* left;  // 左子节点指针
    HuffmanNode* right; // 右子节点指针

    // 构造函数，用于创建叶子节点
    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    // 构造函数，用于创建内部节点
    HuffmanNode(int freq, HuffmanNode* left, HuffmanNode* right) : data('\0'), freq(freq), left(left), right(right) {}
};

// 哈夫曼树类
class HuffmanTree {
private:
    HuffmanNode* root;
    unordered_map<char, string> huffmanCodes;

    // 优先队列比较器结构体，优先队列中节点的比较规则，频率小的节点优先级高。
    /*
     * @brief 比较两个哈夫曼节点的频率
     * 
     * @param left 左节点指针
     * @param right 右节点指针
     * @return true 如果左节点频率大于右节点频率
     * @return false 否则
     */
    struct Compare {
        bool operator()(HuffmanNode* left, HuffmanNode* right) {
            return left->freq > right->freq; 
        }
    };

    // 构建哈夫曼树
    /*
     * @brief 构建哈夫曼树
     * 
     * 根据字符频率映射构建哈夫曼树。
     * 
     * @param freq_map 字符频率映射
     * @return HuffmanNode* 哈夫曼树的根节点指针
     */
    HuffmanNode* buildTree(const unordered_map<char, int>& freq_map) {
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
        for (const auto& pair : freq_map) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }
        while (pq.size() > 1) {
            HuffmanNode* left = pq.top(); pq.pop();  // 取出频率最小的节点
            HuffmanNode* right = pq.top(); pq.pop(); // 取出频率次小的节点
            int combinedFreq = left->freq + right->freq; // 计算合并后的频率
            pq.push(new HuffmanNode(combinedFreq, left, right)); // 插入合并后的节点
        }
        return pq.top();
    }

    // 生成哈夫曼编码
    /*
     * @brief 生成哈夫曼编码
     * 
     * 递归遍历哈夫曼树，生成每个字符的哈夫曼编码。
     * 
     * @param node 哈夫曼树的根节点指针
     * @param str 当前编码字符串
     * @param huffmanCodes 存储哈夫曼编码的映射
     */
    void generateCodes(HuffmanNode* node, const string& str) {
        if (node == nullptr) return;
        if (node->data != '\0') {
            huffmanCodes[node->data] = str;
        }
        generateCodes(node->left, str + "0");
        generateCodes(node->right, str + "1");
    }

public:
    // 构造函数，根据字符频率映射构建哈夫曼树并生成哈夫曼编码
    HuffmanTree(const unordered_map<char, int>& freq_map) {
        root = buildTree(freq_map);
        generateCodes(root, "");
    }

    // 获取哈夫曼编码映射
    unordered_map<char, string> getHuffmanCodes() const {
        return huffmanCodes;
    }

    // 获取哈夫曼树根节点（主要用于调试或进一步操作）
    HuffmanNode* getRoot() const {
        return root;
    }

    // 压缩文件函数
    /*
     * @brief 压缩文件
     * 
     * 使用哈夫曼编码压缩指定文件。
     * 
     * @param inputFile 输入文件名
     * @param outputFile 输出文件名
     * @param huffmanCodes 存储哈夫曼编码的映射
     */
    void compressFile(const string& inputFile, const string& outputFile, const unordered_map<char, string>& huffmanCodes) {
        ifstream inFile(inputFile, ios::binary);
        ofstream outFile(outputFile, ios::binary);

        unordered_map<char, int> freq_map;
        char ch;
        while (inFile.get(ch)) {
            freq_map[ch]++;
        }

        cout << "Huffman Codes for characters in the file:" << endl;
        for (const auto& pair : huffmanCodes) {
            cout << pair.first << ": " << pair.second << endl;
        }

        inFile.clear();
        inFile.seekg(0, ios::beg);
        string encodedStr;
        while (inFile.get(ch)) {
            encodedStr += huffmanCodes.at(ch);
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
    /*
     * @brief 解压缩文件
     * 
     * 使用哈夫曼编码解压缩指定文件。
     * 
     * @param inputFile 输入文件名
     * @param outputFile 输出文件名
     * @param reverseHuffmanCodes 存储反向哈夫曼编码的映射
     */
    void decompressFile(const std::string& inputFile, const std::string& outputFile, const std::unordered_map<std::string, char>& reverseHuffmanCodes) {
        std::ifstream inFile(inputFile, std::ios::binary); // 以二进制模式打开输入文件
        std::ofstream outFile(outputFile, std::ios::binary); // 以二进制模式打开输出文件
    
        std::string encodedStr;
        char ch;
        // 将输入文件中的二进制数据转换为编码字符串
        while (inFile.get(ch)) {
            for (int i = 7; i >= 0; --i) {
                encodedStr += ((ch >> i) & 1) ? '1' : '0';
            }
        }
        std::string tempStr;
        // 根据反向哈夫曼编码将编码字符串转换为原始字符
        for (size_t i = 0; i < encodedStr.size(); ++i) {
            tempStr += encodedStr[i];
            if (reverseHuffmanCodes.find(tempStr) != reverseHuffmanCodes.end()) {
                outFile.put(reverseHuffmanCodes.at(tempStr));
                tempStr.clear();
            }
        }
    
        inFile.close(); // 关闭输入文件
        outFile.close(); // 关闭输出文件
    }
    
    // 构建反向哈夫曼编码映射
    unordered_map<string, char> buildReverseHuffmanCodes(const unordered_map<char, string>& huffmanCodes) {
        unordered_map<string, char> reverseHuffmanCodes;
        // 交换键值对，构建反向映射
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
};



// 主函数
int main() {
    system("chcp 65001");
    string inputFile = "test.txt";
    string compressedFile = "compressed.txt";
    string decompressedFile = "decompressed.txt";

    // 读取文件并统计字符频率
    ifstream inFile(inputFile, ios::binary);
    unordered_map<char, int> freq_map;
    char ch;
    while (inFile.get(ch)) {
        freq_map[ch]++;
    }
    inFile.close();

    // 构建哈夫曼树并获取哈夫曼编码
    HuffmanTree huffmanTree(freq_map);
    unordered_map<char, string> huffmanCodes = huffmanTree.getHuffmanCodes();

    // 压缩文件
    huffmanTree.compressFile(inputFile, compressedFile, huffmanCodes);

    // 构建反向哈夫曼编码映射并解压缩文件
    unordered_map<string, char> reverseHuffmanCodes = huffmanTree.buildReverseHuffmanCodes(huffmanCodes);
    huffmanTree.decompressFile(compressedFile, decompressedFile, reverseHuffmanCodes);

    cout << "\nOriginal File Content:" << endl;
    ifstream originalFile(inputFile);
    string originalContent((istreambuf_iterator<char>(originalFile)), istreambuf_iterator<char>());
    cout << originalContent << endl;

    cout << "\nDecompressed File Content:" << endl;
    ifstream decompressedFileStream(decompressedFile);
    string decompressedContent((istreambuf_iterator<char>(decompressedFileStream)), istreambuf_iterator<char>());
    cout << decompressedContent << endl;
    double compressionRatio = huffmanTree.calculateCompressionRatio(inputFile, compressedFile);
    cout << "Compression ratio: " << compressionRatio << "\n";
    return 0;
}
