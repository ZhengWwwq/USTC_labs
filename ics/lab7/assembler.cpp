#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include<bitset>
#include<sstream>
#include<iomanip>

using namespace std;

vector<string> read_asm_file(const string &filename);
void write_output_file(const string &filename, const vector<string> &output);
vector<string> assemble(const vector<string> &input_lines);
//string translate_instruction(const string &instruction, map<string,string> symbol_table);

// TODO: Define any additional functions you need to implement the assembler, e.g. the symbol table.
map<string,int> firstpass(const vector<string> &input_lines);
vector<string> secondpass(const vector<string> input_lines, map<string, int> symbol_table);
void Initialize();
bool IsOPCode(string line);
bool ISPseudoOperation(string line);
string TranslateOPC(string line, map<string, int> symbol_table, int PC);
void TranslatePO(string line, vector<string> &output_lines, int &PC);
string GetPCOffset(string line, map<string, int> symbol_table, int bits, int PC);

// some global variable
map<string,string> OPCode;

int main(int argc, char *argv[])
{
    // Command-line argument parsing
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <input_file.asm> <output_file.txt>" << std::endl;
        return 1;
    }

    string input_filename = argv[1];
    string output_filename = argv[2];

    //Initialize some basic variable
    Initialize();

    // Read the input ASM file
    vector<string> input_lines = read_asm_file(input_filename);

    // Assemble the input file
    vector<string> output_lines = assemble(input_lines);

    // Write the output file
    write_output_file(output_filename, output_lines);

    return 0;
}

vector<string> read_asm_file(const string &filename)
{
    vector<string> lines;
    string line;
    ifstream file(filename);

    if (file.is_open())
    {
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file: " << filename << std::endl;
    }

    return lines;
}

void write_output_file(const string &filename, const std::vector<std::string> &output)
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (const auto &line : output)
        {
            file << line << std::endl;
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

vector<string> assemble(const vector<string> &input_lines)
{
    vector<string> output_lines;

    // TODO: Implement the assembly process
    // Implement the 2-pass process described in textbook.
    map<string, int> symbol_table = firstpass(input_lines);//scan the instructions and create the symbol table

    //show the symbol_table
    for (const auto &label : symbol_table) {
        std::stringstream ss;
        ss << std::hex << label.second;
        cout<<label.first<<" x"<< ss.str() <<endl;
    }
    
    output_lines = secondpass(input_lines, symbol_table);//create the machine code

    // show the code
    for(int i = 0; i< output_lines.size(); i++){
        int decimalValue = std::bitset<16>(output_lines[i]).to_ulong();
        std::stringstream ss;
        ss << std::hex << std::setw(4) << std::setfill('0') << decimalValue;
        cout << "x" << ss.str() <<endl;
    }

    return output_lines;
}

map<string,int> firstpass(const vector<string> &input_lines){
    //Scan the instructions to create symbol_table
    map<string, int> symbol_table;
    int i = 0, LC = 0;
    for(i=0;i<input_lines.size();i++){
        //find the begining
        if(input_lines[i].substr(0, 5) == ".ORIG"){
            LC = stoi(input_lines[i].substr(7), nullptr, 16);//set LC
            break;
        }
    }
    for(int t = i+1; t<input_lines.size();t++){
        if(!IsOPCode(input_lines[t]) && !ISPseudoOperation(input_lines[t])){
            //not a opcode or a pseudo operation, then it means it has a label
            string label;
            for (int j = 0; input_lines[t][j] != ' '; j++) {
                label.push_back(input_lines[t][j]);
            }
            symbol_table.insert(pair<string, int>(label, LC));
            if(ISPseudoOperation(input_lines[t].substr(label.length()+1))){
                //update LC
                vector<string> tempt;//tempt is useless, just to fill the operations of the function
                TranslatePO(input_lines[t].substr(label.length()+1), tempt, LC);
            }
        }
        if(ISPseudoOperation(input_lines[t])){
            vector<string> tempt;
            TranslatePO(input_lines[t], tempt, LC);
        }
        //the end of the code
        if(input_lines[t].compare(0, 4, ".END") == 0){
            break;
        }
        LC++;
    }
    return symbol_table;
}

vector<string> secondpass(const vector<string> input_lines, map<string, int> symbol_table){
    int i = 0, PC = 0;
    vector<string> output_lines;    // the machine code output
    //find the begining
    for(i=0;i<input_lines.size();i++){
        if(input_lines[i].substr(0, 5) == ".ORIG"){
            PC = stoi(input_lines[i].substr(7), nullptr, 16);
            break;
        }
    }
    //start decoding
    for(int t = i; t < input_lines.size() ; t++){
        //cout<<t<<" "<<PC<<" "<<input_lines[t]<<" ";
        if(IsOPCode(input_lines[t])){
            output_lines.push_back(TranslateOPC(input_lines[t], symbol_table, PC));
            //cout<<output_lines[output_lines.size()-1];
        }
        else if(ISPseudoOperation(input_lines[t])){
            // the end
            if(input_lines[t].substr(0, 4) == ".END"){
                return output_lines;
            }
            TranslatePO(input_lines[t], output_lines, PC);
        }
        else{//contain a label
            //take off the label
            int length = 1;
            for(length = 1;length<input_lines[t].size();length++){
                if(isspace(input_lines[t][length - 1])){
                    break;
                }
            }
            string line = input_lines[t].substr(length);
            //cout<<line<<" ";
            if(IsOPCode(line)){
                output_lines.push_back(TranslateOPC(line, symbol_table, PC));
                //cout<<output_lines[output_lines.size()-1];
            }
            else if(ISPseudoOperation(line)){
                TranslatePO(line, output_lines, PC);
            }
        }
        PC++;
        // for debug : cout<<endl;
    }
    return output_lines;
}

void Initialize(){
    //Create map OPCode
    OPCode.clear();
    OPCode.insert(pair<string, string>("ADD", "0001"));
    OPCode.insert(pair<string, string>("AND", "0101"));
    OPCode.insert(pair<string, string>("BR", "0000"));
    OPCode.insert(pair<string, string>("BRN", "0000"));
    OPCode.insert(pair<string, string>("BRZ", "0000"));
    OPCode.insert(pair<string, string>("BRNZ", "0000"));
    OPCode.insert(pair<string, string>("BRNP", "0000"));
    OPCode.insert(pair<string, string>("BRZP", "0000"));
    OPCode.insert(pair<string, string>("BRNZP", "0000"));
    OPCode.insert(pair<string, string>("JMP", "1100"));
    OPCode.insert(pair<string, string>("JSR", "0100"));
    OPCode.insert(pair<string, string>("JSRR", "0100"));
    OPCode.insert(pair<string, string>("LD", "0010"));
    OPCode.insert(pair<string, string>("LDI", "1010"));
    OPCode.insert(pair<string, string>("LDR", "0110"));
    OPCode.insert(pair<string, string>("LEA", "1110"));
    OPCode.insert(pair<string, string>("NOT", "1001"));
    OPCode.insert(pair<string, string>("RET", "1100"));
    OPCode.insert(pair<string, string>("RTI", "1000"));
    OPCode.insert(pair<string, string>("ST", "0011"));
    OPCode.insert(pair<string, string>("STI", "1011"));
    OPCode.insert(pair<string, string>("STR", "0111"));
    OPCode.insert(pair<string, string>("TRAP", "1111"));

}

bool IsOPCode(string line) {
    for (const auto &opcode : OPCode) {
        string opcodeKey = opcode.first;
        //some extreme cases e.g the label called START
        if (line.substr(0, opcodeKey.length()) == opcodeKey && (line.size() == opcodeKey.length() || line[opcodeKey.length()] == ' ')) {
            return true;
        }
    }
    return false;
}

bool ISPseudoOperation(string line) {
    if (line.substr(0, 5) == ".ORIG" ||
        line.substr(0, 4) == ".END" ||
        line.substr(0, 5) == ".BLKW" ||
        line.substr(0, 8) == ".STRINGZ"||
        line.substr(0, 5) == ".FILL") {
        return true;
    }

    return false;
}

string TranslateOPC(string line, map<string, int> symbol_table, int PC){
    //translate the code into machine code
    map<string,string>::iterator i;
    int length = 1;
    //find opcode
    for(length = 1;length<line.size();length++){
        if(isspace(line[length])){
            break;
        }
    }
    i = OPCode.find(line.substr(0, length));
    string output = i->second;
    //ADD and AND
    if(output == "0001" || output == "0101"){
        // use std::bitset change into binary string
        output.append(bitset<3>(line[5] - '0').to_string()); 
        output.append(bitset<3>(line[9] - '0').to_string()); 
        if(line[12] == 'R'){
            output.append("000");
            output.append(bitset<3>(line[13] - '0').to_string());
        }
        else if(line[12]=='#'){
            output.push_back('1');
            output.append(bitset<5>(stoi(line.substr(13))).to_string());
        }
        else if(line[12] == 'x' || line[12] == 'X'){
            output.push_back('1');
            output.append(bitset<5>(stoi(line.substr(13), nullptr, 16)).to_string());
        }
        else{
            output.push_back('1');
            output.append(bitset<5>(stoi(line.substr(12), nullptr, 2)).to_string());
        }
    }
    //BR
    else if(line.substr(0, 2) == "BR"){
        output = "0000";
        if(line.substr(0,5) == "BRNZP"){
            output.append("111");
        }
        else if(line.substr(0, 4) == "BRNZ"){
            output.append("110");
        }
        else if(line.substr(0, 4) == "BRNP"){
            output.append("101");
        }
        else if(line.substr(0, 4) == "BRZP"){
            output.append("011");
        }
        else if(line.substr(0, 3) == "BRN"){
            output.append("100");
        }
        else if(line.substr(0, 3) == "BRZ"){
            output.append("010");
        }
        else if(line.substr(0, 3) == "BRP"){
            output.append("001");
        }
        else{//just BR
            output.append("000");
        }
        int i;
        for(i = 1; i<line.size();i++){
            if(isspace(line[i])){
                break;
            }
        }
        output.append(GetPCOffset(line.substr(i+1), symbol_table, 9, PC));
    }
    //JMP
    else if(line.substr(0, 3) == "JMP"){
        output.append("000");
        output.append(bitset<3>(line[5] - '0').to_string());
        output.append("000000");
    }
    //JSR
    else if(line.substr(0, length) == "JSR"){
        output.push_back('1');
        output.append(GetPCOffset(line.substr(4), symbol_table, 11, PC));
    }
    //JSRR
    else if(line.substr(0, length) == "JSRR"){
        output.append("000");
        output.append(bitset<3>(line[6] - '0').to_string());
        output.append("000000");
    }
    //LD and ST
    else if(output == "0010" || output == "0011"){
        output.append(bitset<3>(line[4] - '0').to_string());
        output.append(GetPCOffset(line.substr(7), symbol_table, 9, PC));
    }
    //LDI and LEA and STI
    else if(output == "1010" || output == "1110" || output == "1011"){
        output.append(bitset<3>(line[5] - '0').to_string());
        output.append(GetPCOffset(line.substr(8), symbol_table, 9, PC));
    }
    //LDR and STR
    else if(output == "0110" || output == "0111"){
        output.append(bitset<3>(line[5] - '0').to_string());
        output.append(bitset<3>(line[9] - '0').to_string());
        if(line[12]=='#'){
            output.append(bitset<6>(stoi(line.substr(13))).to_string());
        }
        else if(line[12] == 'x' || line[12] == 'X'){
            output.append(bitset<6>(stoi(line.substr(13), nullptr, 16)).to_string());
        }
        else{
            output.append(bitset<6>(stoi(line.substr(12), nullptr, 2)).to_string());
        }
    }
    //NOT
    else if(output == "1001"){
        output.append(bitset<3>(line[5] - '0').to_string());
        output.append(bitset<3>(line[9] - '0').to_string());
        output.append("111111");
    }
    //RET
    else if(line.substr(0, 3) == "RET"){
        output.append("000111000000");
    }
    //RTI
    else if(output == "1000"){
        output.append("000000000000");
    }
    //TRAP
    else{
        output.append("0000");
        output.append(bitset<8>(stoi(line.substr(6), nullptr, 16)).to_string());
    }
    return output;
}

void TranslatePO(string line, vector<string> &output_lines, int &PC){
    //.BLKW
    if(line.substr(0, 5) == ".BLKW"){
        int num;
        if (line[6] == '#') {
            num = stoi(line.substr(7), nullptr);
        }
        // 如果是十六进制数
        else if (line[6] == 'x' || line[0] == 'X') {
            num = stoi(line.substr(6), nullptr, 16);
        }
        // 如果是二进制数
        else {
            num = stoi(line.substr(6), nullptr, 2);
        }
        for(int i=0; i<num; i++){
            output_lines.push_back("0000000000000000");
            PC++;
        }
        PC--;
    }
    //.STRINGZ
    else if(line.substr(0, 8) == ".STRINGZ"){
        int start = 1, end = 1;
        for(int i = 8; i<line.size();i++){
            if(line[i] == '"'){
                if(start == 1){
                    start = i;
                }
                else{
                    end = i;
                }
            }
        }
        for(int j = start + 1; j<end;j++){
            output_lines.push_back(bitset<16>(int(line[j])).to_string());
            PC++;
        }
        output_lines.push_back("0000000000000000");
    }
    //.FILL
    else if(line.substr(0, 5) == ".FILL"){
        output_lines.push_back(bitset<16>(stoi(line.substr(7), nullptr, 16)).to_string());
    }
    //.ORIG
    else if(line.substr(0, 5) == ".ORIG"){
        output_lines.push_back(bitset<16>(stoi(line.substr(7), nullptr, 16)).to_string());
    }
}

string GetPCOffset(string line, map<string, int> symbol_table, int bits, int PC){
    string output;
    int tag = 0;
    for (const auto &label : symbol_table) {
        //find label
        string labelKey = label.first;
        if (line == labelKey) {
            if(bits == 9){
                output = bitset<9>(label.second - PC).to_string();            
            }
            else{
                output = bitset<11>(label.second - PC).to_string();
            }
            tag = 1;
        }
    }
    if(tag == 0){
        // 如果是立即数
        if (line[0] == '#') {
            try {
                if (bits == 9) {
                    output = bitset<9>(stoi(line.substr(1))).to_string();
                } else {
                    output = bitset<11>(stoi(line.substr(1))).to_string();
                }
            } catch (const std::invalid_argument& e) {
                cerr << "Error: Invalid argument in stoi: " << e.what() << endl;
                return "000000000"; // 返回一个默认值
            }
        }
        // 如果是十六进制数
        else if (line[0] == 'x' || line[0] == 'X') {
            try {
                if (bits == 9) {
                    output = bitset<9>(stoi(line.substr(1), nullptr, 16)).to_string();
                } else {
                    output = bitset<11>(stoi(line.substr(1), nullptr, 16)).to_string();
                }
            } catch (const std::invalid_argument& e) {
                cerr << "Error: Invalid argument in stoi: " << e.what() << endl;
                return "000000000"; // 返回一个默认值
            }
        }
        // 如果是二进制数
        else {
            try {
                if (bits == 9) {
                    output = bitset<9>(stoi(line.substr(1), nullptr, 2)).to_string();
                } else {
                    output = bitset<11>(stoi(line.substr(1), nullptr, 2)).to_string();
                }
            } catch (const std::invalid_argument& e) {
                cerr << "Error: Invalid argument in stoi: " << e.what() << endl;
                return "000000000"; 
            }
        }
    }
    return output;
}