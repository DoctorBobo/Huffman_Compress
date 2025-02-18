#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 哈夫曼树节点结构体
 * 
 * 该结构体表示哈夫曼树的一个节点，包含字符数据、频率、左子节点和右子节点。
 */
struct HuffmanNode {
    char data;  // 节点存储的字符
    int freq;   // 字符出现的频率
    HuffmanNode* left;  // 左子节点指针
    HuffmanNode* right; // 右子节点指针

    // 构造函数，用于创建叶子节点
    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    // 构造函数，用于创建内部节点
    HuffmanNode(int freq, HuffmanNode* left, HuffmanNode* right) : data('\0'), freq(freq), left(left), right(right) {}
};

/**
 * @brief 优先队列比较器结构体
 * 
 * 该结构体定义了优先队列中节点的比较规则，频率小的节点优先级高。
 */
struct Compare {
    /**
     * @brief 比较两个哈夫曼节点的频率
     * 
     * @param left 左节点指针
     * @param right 右节点指针
     * @return true 如果左节点频率大于右节点频率
     * @return false 否则
     */
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->freq > right->freq; 
    }
};

/**
 * @brief 构建哈夫曼树
 * 
 * 根据字符频率映射构建哈夫曼树。
 * 
 * @param freq_map 字符频率映射
 * @return HuffmanNode* 哈夫曼树的根节点指针
 */
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freq_map) {
    // 创建优先队列，使用自定义比较器
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    // 将每个字符及其频率插入优先队列
    for (const auto& pair : freq_map) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    // 当队列中节点数大于1时，不断合并节点
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();  // 取出频率最小的节点
        HuffmanNode* right = pq.top(); pq.pop(); // 取出频率次小的节点
        int combinedFreq = left->freq + right->freq; // 计算合并后的频率
        pq.push(new HuffmanNode(combinedFreq, left, right)); // 插入合并后的节点
    }

    return pq.top(); // 返回哈夫曼树的根节点
}

/**
 * @brief 生成哈夫曼编码
 * 
 * 递归遍历哈夫曼树，生成每个字符的哈夫曼编码。
 * 
 * @param root 哈夫曼树的根节点指针
 * @param str 当前编码字符串
 * @param huffmanCodes 存储哈夫曼编码的映射
 */
void generateHuffmanCodes(HuffmanNode* root, const string& str, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) return; // 如果节点为空，直接返回

    if (root->data != '\0') { // 如果是叶子节点
        huffmanCodes[root->data] = str; // 记录该字符的哈夫曼编码
    }

    // 递归遍历左子树，编码加0
    generateHuffmanCodes(root->left, str + "0", huffmanCodes);
    // 递归遍历右子树，编码加1
    generateHuffmanCodes(root->right, str + "1", huffmanCodes);
}

/**
 * @brief 压缩文件
 * 
 * 使用哈夫曼编码压缩指定文件。
 * 
 * @param inputFile 输入文件名
 * @param outputFile 输出文件名
 * @param huffmanCodes 存储哈夫曼编码的映射
 */
void compressFile(const string& inputFile, const string& outputFile, unordered_map<char, string>& huffmanCodes) {
    ifstream inFile(inputFile, ios::binary); // 以二进制模式打开输入文件
    ofstream outFile(outputFile, ios::binary); // 以二进制模式打开输出文件

    unordered_map<char, int> freq_map; // 存储字符频率的映射
    char ch;
    // 统计输入文件中每个字符的频率
    while (inFile.get(ch)) {
        freq_map[ch]++;
    }
    HuffmanNode* root = buildHuffmanTree(freq_map); // 构建哈夫曼树
    generateHuffmanCodes(root, "", huffmanCodes); // 生成哈夫曼编码
    cout << "Huffman Codes for characters in the file:" << endl;
    // 输出每个字符的哈夫曼编码
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    inFile.clear(); // 清除文件流的错误标志
    inFile.seekg(0, ios::beg); // 将文件指针移到文件开头
    string encodedStr;
    // 将输入文件中的字符转换为哈夫曼编码
    while (inFile.get(ch)) {
        encodedStr += huffmanCodes[ch];
    }
    string byteBuffer;
    // 将编码字符串按8位一组写入输出文件
    for (size_t i = 0; i < encodedStr.size(); i++) {
        byteBuffer += encodedStr[i];
        if (byteBuffer.size() == 8) {
            outFile.put(static_cast<unsigned char>(stoi(byteBuffer, nullptr, 2)));
            byteBuffer.clear();
        }
    }
    // 处理剩余不足8位的编码
    if (!byteBuffer.empty()) {
        while (byteBuffer.size() < 8) {
            byteBuffer += '0';
        }
        outFile.put(static_cast<unsigned char>(stoi(byteBuffer, nullptr, 2)));
    }

    inFile.close(); // 关闭输入文件
    outFile.close(); // 关闭输出文件
}

/**
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

/**
 * @brief 构建反向哈夫曼编码映射
 * 
 * 根据哈夫曼编码映射构建反向哈夫曼编码映射。
 * 
 * @param huffmanCodes 存储哈夫曼编码的映射
 * @return unordered_map<string, char> 反向哈夫曼编码映射
 */
unordered_map<string, char> buildReverseHuffmanCodes(const unordered_map<char, string>& huffmanCodes) {
    unordered_map<string, char> reverseHuffmanCodes;
    // 交换键值对，构建反向映射
    for (const auto& pair : huffmanCodes) {
        reverseHuffmanCodes[pair.second] = pair.first;
    }
    return reverseHuffmanCodes;
}

// 计算压缩比
// double calculateCompression

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
