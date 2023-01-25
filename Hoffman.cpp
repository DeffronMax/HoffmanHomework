#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

// Helper function to print the Huffman tree
void printCodes(unordered_map<char, string>& huffmanCodes, string str)
{
    for (auto i : huffmanCodes) {
        cout << i.first << ": " << str + i.second << endl;
    }
}

// Build the Huffman tree and create the Huffman codes
void createHuffmanCodes(unordered_map<char, int>& freq,
                        unordered_map<char, string>& huffmanCodes,
                        string str,
                        priority_queue<pair<int, char>>& pq)
{
    // Base case: if there is only one node left
    if (pq.size() == 1) {
        huffmanCodes[pq.top().second] = str;
        return;
    }

    // Take the two nodes with the lowest frequencies
    pair<int, char> left = pq.top(); pq.pop();
    pair<int, char> right = pq.top(); pq.pop();

    // Create a new node with the sum of their frequencies
    int sum = left.first + right.first;
    char c = '#';
    pq.push({sum, c});

    // Traverse the left and right subtrees and add a 0 or 1 to the code
    createHuffmanCodes(freq, huffmanCodes, str + "0", pq);
    createHuffmanCodes(freq, huffmanCodes, str + "1", pq);
}

// Compress the input text using the Huffman codes
string compressText(string text, unordered_map<char, string> huffmanCodes)
{
    string compressedText = "";
    for (char c : text) {
        compressedText += huffmanCodes[c];
    }
    return compressedText;
}

// Decompress the compressed text using the Huffman tree
string decompressText(string compressedText, unordered_map<char, string> huffmanCodes)
{
    unordered_map<string, char> huffmanDecode;
    for (auto i : huffmanCodes) {
        huffmanDecode[i.second] = i.first;
    }

    string text = "";
    string code = "";
    for (char c : compressedText) {
        code += c;
        if (huffmanDecode.count(code)) {
            text += huffmanDecode[code];
            code = "";
        }
    }

    return text;
}

int main()
{
    string text;
    cout << "Enter the text to compress: ";
    getline(cin, text);

    // Count the frequency of each character
    unordered_map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }

    // Create a priority queue of characters
    priority_queue<pair<int, char>> pq;
    for (auto i : freq) {
        pq.push({i.second, i.first});
    }

    // Build the Huffman tree and create the Huffman codes
    unordered_map<char, string> huffmanCodes;
    createHuffmanCodes(freq, huffmanCodes, "", pq);

    // Print the Huffman codes
    cout << "Huffman Codes:" << endl;
    printCodes(huffmanCodes, "");

    // Compress the input text
    string compressedText = compressText(text, huffmanCodes);
    cout << "Compressed Text: " << compressedText << endl;

    // Decompress the compressed text
    string decompressedText = decompressText(compressedText, huffmanCodes);
    cout << "Decompressed Text: " << decompressedText << endl;

    return 0;
}
