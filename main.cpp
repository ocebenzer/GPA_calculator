#include <iostream>
#include <map>
#include <list>
#include <vector>

using namespace std;

const map<string, double> converter {
        {"AA", 4},
        {"BA", 3.5},
        {"BB", 3},
        {"CB", 2.5},
        {"CC", 2},
        {"DC", 2},
        {"DD", 1.5},
        {"F", 0}
};

pair<int,double>* calculateGPA(list<pair<string,int>>* courses){
    double totalPoints = 0, totalCredits = 0;
    for (pair<string, int>& course : *courses){
        // course.first: letter grade, see converter above
        // course.second: credits for the course

        //if pass, dont add it to the GPA
        if (course.first == "P") continue;

        totalPoints += converter.at(course.first) * course.second;
        totalCredits += course.second;
    }
    return new pair<int,double> (totalCredits, totalPoints/totalCredits);
}

int main()
{
    auto you = new list<pair<string,int>>;

    //add courses
    pair<string, int>* tmpCourse;
    cout << "=> Enter your course results as <letter_grade, credits>" << endl << "---\nExample: \nBB 3\nAA 4\nP 2\nF 4\nDONE\n---" << endl;
    while(true){
        tmpCourse = new pair<string,int>;
        cin >> tmpCourse->first;
        // uppercase, check "DONE"
        for (auto& chr : tmpCourse->first) chr = toupper(chr);
        if(tmpCourse->first == "DONE") break;
        // add the course into the list
        cin >> tmpCourse->second;
        you->push_back(*tmpCourse);
        try{
            double tmpGPA = calculateGPA(you)->second;
            cout << "=> (" << you->size() << " courses) \n\t-> Your current GPA is: " << tmpGPA << ", type \"DONE\" to exit" << endl;
        }
        catch (out_of_range e) {
            you->pop_back();
            cout << "=> Last input had a problem, please try again" << endl;
            if (!you->empty()){
                cout << "\t-> Last processed input: \"" << you->back().first << " " << you->back().second <<"\"" << endl;
            }
            // delete invalid pair
            delete tmpCourse;
            // clear the invalid input from cin
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
    }
    pair<int,double>* finalScore = calculateGPA(you);
    cout << "=> Final result: " << endl
    << "\t-> Number of Courses: " << you->size() << endl
    << "\t-> Number of Credits: " << finalScore->first << endl
    << "\t-> Your final GPA is: " << finalScore->second << endl;

    return 0;
}