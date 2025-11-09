#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <exception>
#include<random>
using namespace std;

class Question {
protected:
    string questionText; 
    int pointValue;
public:
    Question(const string& q, int p) : questionText(q), pointValue(p) {}
    virtual ~Question() {}
    virtual void displayQuestion() const = 0;
    virtual int checkAnswer(const string&) const = 0;
    virtual string getCorrectAnswer() const = 0;
    int getPointValue() const { return pointValue; }
};

string trim(const string& s) { 
    size_t a = s.find_first_not_of(" \t"), b = s.find_last_not_of(" \t"); 
    return (a==string::npos)?"":s.substr(a,b-a+1); 
}
string toLower(string s){ for(char& c:s)c=tolower(c); return s; }
string toUpper(string s){ for(char& c:s)c=toupper(c); return s; }

class QuestionTF : public Question {
    bool answer;
public:
    QuestionTF(const string& q,int p,bool a):Question(q,p),answer(a){}
    void displayQuestion() const override { cout << "Question: " << questionText << "\n"; }
    int checkAnswer(const string& in) const override {
        string x = trim(in); 
        if(toUpper(x)=="SKIP") return 0;
        x = toLower(x);
        return (x=="true") ? (answer?pointValue:-pointValue) : (x=="false"? (answer?-pointValue:pointValue):-pointValue);
    }
    string getCorrectAnswer() const override { return answer?"true":"false"; }
};

class QuestionSA : public Question {
    string answer;
public:
    QuestionSA(const string& q,int p,const string& a):Question(q,p),answer(a){}
    void displayQuestion() const override { cout << "Question: " << questionText << "\n"; }
    int checkAnswer(const string& in) const override { 
        string x=trim(in);
        if(toUpper(x)=="SKIP") return 0;
        return toLower(x)==toLower(answer)?pointValue:-pointValue; 
    }
    string getCorrectAnswer() const override { return answer; }
};

class QuestionMC : public Question {
    vector<string> choices; 
    char correctAnswer;
public:
    QuestionMC(const string& q,int p,const vector<string>& c,char ca):Question(q,p),choices(c),correctAnswer(ca){}
    void displayQuestion() const override {
        cout << "Question: " << questionText << "\n";
        for(size_t i=0;i<choices.size();++i) cout << char('A'+i) << ") " << choices[i] << "\n";
    }
    int checkAnswer(const string& in) const override {
        string x=trim(in); 
        if(toUpper(x)=="SKIP") return 0;
        if(x.size()!=1) return -pointValue;
        char u=toupper(x[0]);
        if(u<'A'||u>='A'+choices.size()) return -pointValue;
        return u==correctAnswer?pointValue:-pointValue;
    }
    string getCorrectAnswer() const override { return string(1,correctAnswer); }
};

class Player {
    string firstName,lastName; 
    int points=0;
public:
    Player(const string& f,const string& l):firstName(f),lastName(l){}
    void addPoints(int p){points+=p;}
    int getPoints() const {return points;}
    string getName() const {return firstName+" "+lastName;}
};

class QuizBowl {
public:
    static int run() {
        srand(time(nullptr));
        string line;
        cout<<"First name: "; getline(cin,line); string first=trim(line);
        cout<<"Last name: "; getline(cin,line); string last=trim(line);
        Player player(first,last);

        cout<<"File name: "; getline(cin,line); string fileName=trim(line);
        ifstream file(fileName);
        if(!file){ cout<<"File not found.\n"; return 1; }

        getline(file,line); int n=stoi(trim(line));
        vector<Question*> questions;
        for(int i=0;i<n;++i){
            getline(file,line); istringstream iss(trim(line)); string type; int pts; iss>>type>>pts;
            getline(file,line); string qtext=line;
            if(type=="TF"){ getline(file,line); questions.push_back(new QuestionTF(qtext,pts,toLower(trim(line))=="true")); }
            else if(type=="SA"){ getline(file,line); questions.push_back(new QuestionSA(qtext,pts,trim(line))); }
            else if(type=="MC"){
                getline(file,line); int k=stoi(trim(line)); vector<string> ch(k);
                for(int j=0;j<k;++j) getline(file,ch[j]);
                getline(file,line); char ca=toupper(trim(line)[0]);
                questions.push_back(new QuestionMC(qtext,pts,ch,ca));
            }
        }
        file.close();

        int maxQ=questions.size(),numQ;
        while(true){
            cout<<"How many questions (1-"<<maxQ<<")? "; getline(cin,line);
            try{ numQ=stoi(trim(line)); if(numQ>=1&&numQ<=maxQ) break; }catch(...){}
            cout<<"Invalid.\n";
        }

        shuffle(questions.begin(),questions.end(),mt19937(random_device{}()));

        for(int i=0;i<numQ;++i){
            Question* q=questions[i];
            cout<<"\nPoints: "<<q->getPointValue()<<"\n";
            q->displayQuestion();
            getline(cin,line); int score=q->checkAnswer(line);
            if(score==0) cout<<"Skipped.\n";
            else if(score>0) cout<<"Correct! +"<<score<<"\n";
            else cout<<"Wrong. Ans: "<<q->getCorrectAnswer()<<" (-"<<-score<<")\n";
            player.addPoints(score);
        }

        cout<<"\n"<<player.getName()<<", your score: "<<player.getPoints()<<"\n";
        if(player.getPoints()<0) cout<<"Better luck next time!\n";

        for(auto* q:questions) delete q;
        return 0;
    }
};

int main(){ return QuizBowl::run(); }