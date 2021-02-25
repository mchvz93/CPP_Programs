//
//  main.cpp
//  Solutions_epp_practice_part2
//
//  Created by XxTheEyeOfSauronxX on 9/17/20.
//  Copyright © 2020 Marco A. Chavez Jr. All rights reserved.
//
//
//  medanalyze.cpp
//  epp_practice_part2_3May2018
//
//  Created by William McCarthy on 5/3/18.
//  Copyright © 2018 William McCarthy. All rights reserved.
//

/*
 PRACTICE EPP TEST --- part 2 --- 3 MAY 2018
 *** DOUBLE SPRINT TIME ***


 //--------------------------------------------------------------------------------------------------
 Write a program to analyze medical record data from the file medical_records.txt.

 In that file, you will see the following fields: lname fname day month year (of birth) systolic diastolic (blood pressure) medicalID for several famous people.

 You must read data from that file into a class or struct that represents the data, and save the class or struct instance into a collection class (such as std::vector<T>, or std::list<T>).

 That collection class should be part of an analysis class (medicalAnalysis), that can calculate the following: earliest and latest dob, and lowest and highest bp.

 Blood pressure is ranked as follows: higher diastolic is greater than higher systolic, e.g.,
 110/95 > 130/90
 130/80 > 120/80
 130/78 < 120/79

 You should also be able to print out a table of medical records, ranked by dob, then by bp (if there are any dob ties), then alphabetically (if there are any dob and bp ties).

 (You might want to consider using std::tie or using lambda functions for doing these comparisons and sorts).

 Your program should be DOCUMENTED (each class/struct should be documented, and all public methods (by default or by declaration) should have a brief (1-2 line) summary of their purpose).

 Your program MUST compile, and MUST produce the correct results.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <functional>
// #include <string>     // only necessary for Visual Studio

#define ARGC_ERROR 1
#define FILE_ERROR 2


//-------------------------------------------------------------------------------------------------------------------------------
// struct that encapsulates a name
struct name {
    name() : name("", "") {}
    name(const std::string& lname, const std::string& fname)
    : lname_(lname), fname_(fname) {}
    
    friend bool operator<(const name& a, const name& b) {
        return a.lname_ < b.lname_ || (a.lname_ == b.lname_ && a.fname_ < b.fname_);
    }
    friend bool operator==(const name& a, const name& b) { return  a.lname_ == b.lname_ && a.fname_ == b.fname_; }
    friend bool operator>(const name& a, const name& b) {  return !(a < b) && !(a == b); }    // because the opposite of a < b is a >= b
    friend std::istream& operator>>(std::istream& is, name& nm) {
        is >> nm.lname_;    // split on separate lines for debugging
        is >> nm.fname_;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const name& nm) {
        return os << std::setw(12) << nm.lname_ << "," << std::setw(10) << nm.fname_;
    }
    std::string lname_;
    std::string fname_;
};

//-------------------------------------------------------------------------------------------------------------------------------
// struct that encapsulates a bloodpressure
struct bloodpressure {
    bloodpressure() : bloodpressure(0,0) {}
    bloodpressure(size_t systolic, size_t diastolic)
    : systolic_(systolic), diastolic_(diastolic) {}

    friend bool operator<(const bloodpressure& a, const bloodpressure& b) {
        return (a.diastolic_ < b.diastolic_) || (a.diastolic_ == b.diastolic_ && a.systolic_ < b.systolic_);
    }
    friend bool operator>(const bloodpressure& a, const bloodpressure& b) { return !(a < b) && !(a == b); }
    friend bool operator==(const bloodpressure& a, const bloodpressure& b) {
        return (a.diastolic_ == b.diastolic_ && a.systolic_ == b.systolic_);
    }

    friend std::istream& operator>>(std::istream& is, bloodpressure& bp) {
        is >> bp.systolic_;     // split on separate lines for debugging
        is >> bp.diastolic_;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const bloodpressure& bp) {
        return os << "(" << std::setw(3) << bp.systolic_ << " / " << std::setw(3) << bp.diastolic_ << ")";
    }
    size_t systolic_;
    size_t diastolic_;
};

//-------------------------------------------------------------------------------------------------------------------------------
// struct that encapsulates a date of birth
struct dob {
    dob() : dob(1, 1, 1) {}
    dob(size_t day, size_t month, size_t year)
    : day_(day), month_(month), year_(year) {}
    
    friend bool operator<(const dob& a, const dob& b) {
        return (a.year_ < b.year_) || (a.year_ == b.year_ && a.month_ < b.month_) ||
               (a.year_ == b.year_ && a.month_ == b.month_ && a.day_ < b.day_);
    }
    friend bool operator>(const dob& a, const dob& b) { return !(a < b) && !(a == b); }
    friend bool operator==(const dob& a, const dob& b) {
        return (a.year_ == b.year_ && a.month_ == b.month_ && a.day_ == b.day_);
    }

    friend std::istream& operator>>(std::istream& is, dob& bday) {
        is >> bday.day_;        // split on separate lines for debugging
        is >> bday.month_;
        is >> bday.year_;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const dob& bday) {
        return os << "(" << std::setw(2) << bday.day_ << " / " << std::setw(2) << bday.month_ << " / " << std::setw(4) << bday.year_ << ")";
    }
    size_t day_;
    size_t month_;
    size_t year_;
};

//-------------------------------------------------------------------------------------------------------------------------------
struct medical {
    medical() : medical(name(), dob(), bloodpressure(), 0) {}
    medical(const name& name, const dob& dob, const bloodpressure& bp, size_t medicalID)
    : name_(name), dob_(dob), bp_(bp), medicalID_(medicalID) {}
    
    friend bool operator<(const medical& a, const medical& b) {
        return (a.dob_ < b.dob_) || (a.dob_ == b.dob_ && a.bp_ < b.bp_) ||
               (a.dob_ == b.dob_ && a.bp_ == b.bp_ && a.name_ < b.name_);
    }
    friend std::istream& operator>>(std::istream& is, medical& med) {
        is >> med.name_;    // split on separate lines for debugging
        is >> med.dob_;
        is >> med.bp_;
        is >> med.medicalID_;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const medical& med) {
        return os << med.name_ << ", dob:" << med.dob_ << ", bp:" << med.bp_ << ", id: " << med.medicalID_;
    }
    name name_;
    dob dob_;
    bloodpressure bp_;
    size_t medicalID_;
};

//-------------------------------------------------------------------------------------------------------------------------------
// class that holds all medical records, calculates the earliest/latest DOBs, and lowest/highest BPs, and that can
//    print out lists of all records by a designated LAMBDA function (e.g., ascendingBP, descending BP, ascendingDOB, descendingDOB, ...
class medicalAnalysis {
public:
    // default ctor ok -- uses default ctor of std::vector<T>
    
    void add(const medical& med) { records_.push_back(med); }

    void analyze(std::ostream& os) {
        if (records_.empty()) { throw new std::invalid_argument("cannot run BP, DOB analysis if no records"); }
        
        const medical& first = records_[0];     // alias
        medical earliestDOB(first), latestDOB(first), lowestBP(first), highestBP(first);
        for (auto el : records_) {
            lowestBP  = (lowestBP.bp_  < el.bp_ ? lowestBP : el);
            highestBP = (highestBP.bp_ > el.bp_ ? highestBP : el);
           
            earliestDOB = (earliestDOB.dob_ < el.dob_ ? earliestDOB : el);
            latestDOB   = (latestDOB.dob_ > el.dob_ ? latestDOB : el);
        }
    
        os << "earliest dob\n" << earliestDOB << "\n";
        os << "latest dob\n"   << latestDOB   << "\n\n";
        os << "lowest bp\n"    << lowestBP    << "\n";
        os << "highest bp\n"   << highestBP  << "\n\n";
        
        std::sort(records_.begin(), records_.end());                 // sort analysis records using default criteria (dob, then bp, then name)
        os << "List of medical records is...\n" << *this << "\n";    // print all medical records using above sort criteria
        
        printByLambda("ascending BP order",   [](const medical& a, const medical& b){ return a.bp_  < b.bp_; });     // sort records and print list by ngBP...
        printByLambda("descending BP order",  [](const medical& a, const medical& b){ return a.bp_  > b.bp_; } );    // ... by descendingBP
        printByLambda("ascending DOB order",  [](const medical& a, const medical& b){ return a.dob_ < b.dob_; } );   // ... by ascending DOB
        printByLambda("descending DOB order", [](const medical& a, const medical& b){ return a.dob_ > b.dob_; } );   // ... by descending DOB
    }
    void sortByLambda(const std::string& msg, std::function<bool(const medical& a, const medical& b)> predicate) {
        std::cout << "sorted by LAMBDA! using... " << msg << "\n";
        std::sort(records_.begin(), records_.end(), predicate);
    }
    void printByLambda(const std::string& msg, std::function<bool(const medical& a, const medical& b)> predicate){
        sortByLambda(msg, predicate);
        std::cout << *this << "\n\n";
    }
    friend std::ostream& operator<<(std::ostream& os, const medicalAnalysis& medAnalyze) {
        if (medAnalyze.records_.empty()) { os << "no records to be found...\n"; }
        for (auto el : medAnalyze.records_) { os << el << "\n"; }
        return os;
    }
private:
    std::vector<medical> records_;
};


//-------------------------------------------------------------------------------------------------------------------------------
// class that abstracts away from main the details of opening, reading, and closing a file, by...
    //    checking if the file can be opened, opening it if it can, announcing the file is opened, then...
    //    routing each line of input to a medical struct, and finally...
    //    closing the file, and announcing it was closed.
class filewrapper {
public:
    filewrapper(const std::string& filename)
    : filename_(filename) {
        ifs_.open(filename_);
        if (!ifs_.is_open()) {
            std::cerr << "\t\tcould not open file: " << filename_ << "\n";
            exit(FILE_ERROR);
        }
        std::cout << "\t\tfile: " << filename_ << " is open...\n";
    }
    ~filewrapper() {
        ifs_.close();
        std::cout << "\t\tfile: " << filename_ <<  " is closed...\n";
    }
    friend std::istream& operator>>(filewrapper& fw, medical& med) { return fw.ifs_ >> med; }
    
private:
    std::string filename_;
    std::ifstream ifs_;
};


//-------------------------------------------------------------------------------------------------------------------------------
// heart of program -- opens the input file, adds records to analysis object, analyzes the data, prints the results, and finally
//     prints out the data sorted by different criteria (ascending/descending BP, or ascending/descending DOB)
//
int main(int argc, const char * argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./medanalyze filename\n";
        exit(ARGC_ERROR);
    }
    std::string filename(argv[1]);
    filewrapper fw(filename);       // filewrapper class instance that handles opening, closing, and reading from the input file
    
    medical med;                    // medical struct instance that holds a single medical record
    medicalAnalysis medanalyze;     // analysis class instance that holds all medical records

    while (fw >> med) {         // reads a record from the input file...
        medanalyze.add(med);    // ... and adds it to the analysis class
    }

    medanalyze.analyze(std::cout);   // prints out earliest/latest dob and min/max bp and list of records sorted by default for medical struct
    
    std::cout << "\n\t\t... medical_records analysis COMPLETED.\n";
    return 0;
}

/*
 OUTPUT:
 
         file: medical_records.txt is open...
 earliest dob
        gauss, friedrich, dob:(23 /  4 / 1564), bp:(101 /  78), id: 38393
 latest dob
     einstein,    albert, dob:(14 /  3 / 1879), bp:(111 /  76), id: 44332

 lowest bp
     liebnitz, gottfried, dob:( 1 /  7 / 1646), bp:(110 /  55), id: 94033
 highest bp
       chopin,  frederic, dob:( 1 /  3 / 1810), bp:(140 /  90), id: 22595

 List of medical records is...
        gauss, friedrich, dob:(23 /  4 / 1564), bp:(101 /  78), id: 38393
       newton,     isaac, dob:( 4 /  1 / 1643), bp:(115 /  85), id: 30399
     liebnitz, gottfried, dob:( 1 /  7 / 1646), bp:(110 /  55), id: 94033
         bach,    johann, dob:(31 /  3 / 1685), bp:(120 /  65), id: 23455
       mozart,   amadeus, dob:(27 /  1 / 1756), bp:(104 /  79), id: 11233
    beethoven,    ludwig, dob:(17 / 12 / 1770), bp:(130 /  80), id: 55433
       chopin,  frederic, dob:( 1 /  3 / 1810), bp:(140 /  90), id: 22595
  tchaikovsky,     pyotr, dob:( 7 /  5 / 1840), bp:(125 /  77), id: 34512
     einstein,    albert, dob:(14 /  3 / 1879), bp:(111 /  76), id: 44332

 sorted by LAMBDA! using... ascending BP order
     liebnitz, gottfried, dob:( 1 /  7 / 1646), bp:(110 /  55), id: 94033
         bach,    johann, dob:(31 /  3 / 1685), bp:(120 /  65), id: 23455
     einstein,    albert, dob:(14 /  3 / 1879), bp:(111 /  76), id: 44332
  tchaikovsky,     pyotr, dob:( 7 /  5 / 1840), bp:(125 /  77), id: 34512
        gauss, friedrich, dob:(23 /  4 / 1564), bp:(101 /  78), id: 38393
       mozart,   amadeus, dob:(27 /  1 / 1756), bp:(104 /  79), id: 11233
    beethoven,    ludwig, dob:(17 / 12 / 1770), bp:(130 /  80), id: 55433
       newton,     isaac, dob:( 4 /  1 / 1643), bp:(115 /  85), id: 30399
       chopin,  frederic, dob:( 1 /  3 / 1810), bp:(140 /  90), id: 22595


 sorted by LAMBDA! using... descending BP order
       chopin,  frederic, dob:( 1 /  3 / 1810), bp:(140 /  90), id: 22595
       newton,     isaac, dob:( 4 /  1 / 1643), bp:(115 /  85), id: 30399
    beethoven,    ludwig, dob:(17 / 12 / 1770), bp:(130 /  80), id: 55433
       mozart,   amadeus, dob:(27 /  1 / 1756), bp:(104 /  79), id: 11233
        gauss, friedrich, dob:(23 /  4 / 1564), bp:(101 /  78), id: 38393
  tchaikovsky,     pyotr, dob:( 7 /  5 / 1840), bp:(125 /  77), id: 34512
     einstein,    albert, dob:(14 /  3 / 1879), bp:(111 /  76), id: 44332
         bach,    johann, dob:(31 /  3 / 1685), bp:(120 /  65), id: 23455
     liebnitz, gottfried, dob:( 1 /  7 / 1646), bp:(110 /  55), id: 94033


 sorted by LAMBDA! using... ascending DOB order
        gauss, friedrich, dob:(23 /  4 / 1564), bp:(101 /  78), id: 38393
       newton,     isaac, dob:( 4 /  1 / 1643), bp:(115 /  85), id: 30399
     liebnitz, gottfried, dob:( 1 /  7 / 1646), bp:(110 /  55), id: 94033
         bach,    johann, dob:(31 /  3 / 1685), bp:(120 /  65), id: 23455
       mozart,   amadeus, dob:(27 /  1 / 1756), bp:(104 /  79), id: 11233
    beethoven,    ludwig, dob:(17 / 12 / 1770), bp:(130 /  80), id: 55433
       chopin,  frederic, dob:( 1 /  3 / 1810), bp:(140 /  90), id: 22595
  tchaikovsky,     pyotr, dob:( 7 /  5 / 1840), bp:(125 /  77), id: 34512
     einstein,    albert, dob:(14 /  3 / 1879), bp:(111 /  76), id: 44332


 sorted by LAMBDA! using... descending DOB order
     einstein,    albert, dob:(14 /  3 / 1879), bp:(111 /  76), id: 44332
  tchaikovsky,     pyotr, dob:( 7 /  5 / 1840), bp:(125 /  77), id: 34512
       chopin,  frederic, dob:( 1 /  3 / 1810), bp:(140 /  90), id: 22595
    beethoven,    ludwig, dob:(17 / 12 / 1770), bp:(130 /  80), id: 55433
       mozart,   amadeus, dob:(27 /  1 / 1756), bp:(104 /  79), id: 11233
         bach,    johann, dob:(31 /  3 / 1685), bp:(120 /  65), id: 23455
     liebnitz, gottfried, dob:( 1 /  7 / 1646), bp:(110 /  55), id: 94033
       newton,     isaac, dob:( 4 /  1 / 1643), bp:(115 /  85), id: 30399
        gauss, friedrich, dob:(23 /  4 / 1564), bp:(101 /  78), id: 38393



         ... medical_records analysis COMPLETED.
         file: medical_records.txt is closed...
 Program ended with exit code: 0
 
 */
