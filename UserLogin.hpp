#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

class UserLogin {
private:
    
    unordered_map< string, string > table;
    

public:
    UserLogin(); // default constructor

    void readIn(const string& filename); // add data from file to hash table

    size_t numberOfUsers(); // return the number of users

    string passWordCheck(const string& userName); // returns the passWord of the given user

    size_t wordBucketIdMethod1(const string& userName); // return the bucket number where the given user is located

    size_t wordBucketIdMethod2(const string& userName); // another way to find the bucket number where the given user is located

    bool validateUser(const string& userName); // look up given user

    bool authenticateUser(const string& userName, const string& passWord);// authenticate given user and password
       
};

UserLogin::UserLogin() {
}

// COMPLETE THE FOLLOWING FUNCTIONS

void UserLogin::readIn(const string& filename) {
    ifstream file;
    file.open(filename);

    string user, pass;

    while(file >> user >> pass) {
        string password = pass;

        table[user] += password;
    }
}

size_t UserLogin::numberOfUsers() {
    return table.size();
}

string UserLogin::passWordCheck(const string& userName) {
    if(table.find(userName) == table.end())
        return "Non-existent User";
    return table.at(userName);
}

size_t UserLogin::wordBucketIdMethod1(const string& userName) {
    return table.bucket(userName);
}

size_t UserLogin::wordBucketIdMethod2(const string& userName) {
    int bucketNum;
    for(auto i = 0; i < table.bucket_count(); i++) {
        for(auto j = table.begin(i); j != table.end(i); j++)
            if(j->first == userName)
                bucketNum = i;
    }
    return bucketNum;
}

bool UserLogin::validateUser(const string& userName) {
    if(table.find(userName) == table.end())
        return false;
    return true;
}

bool UserLogin::authenticateUser(const string& userName, const string& passWord) { 
    if(table.find(userName) == table.end())
        return false;
    else if(table.at(userName) != passWord)
        return false;
    return true; 
}