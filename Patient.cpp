#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

// Patient class based on the provided structur
class Patient {
public:
    string ptFName;     // Patient's First Name
    string ptLName;     // Patient's Last Name
    int ptPhone;        // Patient's Phone
    string ptEmail;     // Patient's Email
    int ptAge;          // Patient's Age
    string ptPwd;       // Patient Password
    string ptStatus;    // Patient's Status (Active or Inactive)
    int patientID;      // Unique identifier

    Patient() : ptPhone(0), ptAge(0), patientID(0) {}
    
    Patient(string fname, string lname, int phone, string email, int age, string pwd, string status, int id) 
        : ptFName(fname), ptLName(lname), ptPhone(phone), ptEmail(email), 
          ptAge(age), ptPwd(pwd), ptStatus(status), patientID(id) {}
};

// Session class for counseling sessions
class Session {
public:
    int sessionID;
    int patientID;
    string sessionDate;
    string sessionTime;
    string counselorName;
    string sessionNotes;
    string sessionStatus; // Scheduled, Completed, Cancelled
    
    Session() : sessionID(0), patientID(0) {}
    
    Session(int sID, int pID, string date, string time, string counselor, string notes, string status)
        : sessionID(sID), patientID(pID), sessionDate(date), sessionTime(time), 
          counselorName(counselor), sessionNotes(notes), sessionStatus(status) {}
};

// Counseling Management System class
class CounselingSystem {
private:
    vector<Patient> patients;
    vector<Session> sessions;
    int nextPatientID;
    int nextSessionID;
    
public:
    CounselingSystem() : nextPatientID(1), nextSessionID(1) {
        loadPatientsFromFile();
        loadSessionsFromFile();
    }
    
    ~CounselingSystem() {
        savePatientsToFile();
        saveSessionsToFile();
    }
    
    // Patient Management Functions
    void addPatient() {
        Patient newPatient;
        
        cout << "\n=== ADD NEW PATIENT ===" << endl;
        cout << "Enter First Name: ";
        cin.ignore();
        getline(cin, newPatient.ptFName);
        
        cout << "Enter Last Name: ";
        getline(cin, newPatient.ptLName);
        
        cout << "Enter Phone Number: ";
        cin >> newPatient.ptPhone;
        
        cout << "Enter Email: ";
        cin.ignore();
        getline(cin, newPatient.ptEmail);
        
        cout << "Enter Age: ";
        cin >> newPatient.ptAge;
        
        cout << "Enter Password: ";
        cin.ignore();
        getline(cin, newPatient.ptPwd);
        
        newPatient.ptStatus = "Active";
        newPatient.patientID = nextPatientID++;
        
        patients.push_back(newPatient);
        
        cout << "\nPatient added successfully! Patient ID: " << newPatient.patientID << endl;
    }
    
    void displayAllPatients() {
        cout << "\n=== ALL PATIENTS ===" << endl;
        cout << left << setw(5) << "ID" << setw(15) << "First Name" << setw(15) << "Last Name" 
             << setw(12) << "Phone" << setw(25) << "Email" << setw(5) << "Age" << setw(10) << "Status" << endl;
        cout << string(87, '-') << endl;
        
        for (const auto& patient : patients) {
            cout << left << setw(5) << patient.patientID 
                 << setw(15) << patient.ptFName 
                 << setw(15) << patient.ptLName
                 << setw(12) << patient.ptPhone 
                 << setw(25) << patient.ptEmail 
                 << setw(5) << patient.ptAge 
                 << setw(10) << patient.ptStatus << endl;
        }
    }
    
    void searchPatient() {
        int choice;
        cout << "\n=== SEARCH PATIENT ===" << endl;
        cout << "1. Search by ID" << endl;
        cout << "2. Search by Name" << endl;
        cout << "3. Search by Phone" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                int id;
                cout << "Enter Patient ID: ";
                cin >> id;
                auto it = find_if(patients.begin(), patients.end(), 
                    [id](const Patient& p) { return p.patientID == id; });
                if (it != patients.end()) {
                    displayPatientDetails(*it);
                } else {
                    cout << "Patient not found!" << endl;
                }
                break;
            }
            case 2: {
                string name;
                cout << "Enter First or Last Name: ";
                cin.ignore();
                getline(cin, name);
                bool found = false;
                for (const auto& patient : patients) {
                    if (patient.ptFName.find(name) != string::npos || 
                        patient.ptLName.find(name) != string::npos) {
                        displayPatientDetails(patient);
                        found = true;
                    }
                }
                if (!found) cout << "No patients found with that name!" << endl;
                break;
            }
            case 3: {
                int phone;
                cout << "Enter Phone Number: ";
                cin >> phone;
                auto it = find_if(patients.begin(), patients.end(), 
                    [phone](const Patient& p) { return p.ptPhone == phone; });
                if (it != patients.end()) {
                    displayPatientDetails(*it);
                } else {
                    cout << "Patient not found!" << endl;
                }
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    void updatePatient() {
        int id;
        cout << "\n=== UPDATE PATIENT ===" << endl;
        cout << "Enter Patient ID to update: ";
        cin >> id;
        
        auto it = find_if(patients.begin(), patients.end(), 
            [id](const Patient& p) { return p.patientID == id; });
        
        if (it != patients.end()) {
            cout << "Current Patient Details:" << endl;
            displayPatientDetails(*it);
            
            cout << "\nEnter new details (press Enter to keep current value):" << endl;
            
            string input;
            cout << "First Name [" << it->ptFName << "]: ";
            cin.ignore();
            getline(cin, input);
            if (!input.empty()) it->ptFName = input;
            
            cout << "Last Name [" << it->ptLName << "]: ";
            getline(cin, input);
            if (!input.empty()) it->ptLName = input;
            
            cout << "Phone [" << it->ptPhone << "]: ";
            getline(cin, input);
            if (!input.empty()) it->ptPhone = stoi(input);
            
            cout << "Email [" << it->ptEmail << "]: ";
            getline(cin, input);
            if (!input.empty()) it->ptEmail = input;
            
            cout << "Age [" << it->ptAge << "]: ";
            getline(cin, input);
            if (!input.empty()) it->ptAge = stoi(input);
            
            cout << "Status [" << it->ptStatus << "] (Active/Inactive): ";
            getline(cin, input);
            if (!input.empty()) it->ptStatus = input;
            
            cout << "Patient updated successfully!" << endl;
        } else {
            cout << "Patient not found!" << endl;
        }
    }
    
    void deletePatient() {
        int id;
        cout << "\n=== DELETE PATIENT ===" << endl;
        cout << "Enter Patient ID to delete: ";
        cin >> id;
        
        auto it = find_if(patients.begin(), patients.end(), 
            [id](const Patient& p) { return p.patientID == id; });
        
        if (it != patients.end()) {
            cout << "Patient to be deleted:" << endl;
            displayPatientDetails(*it);
            
            char confirm;
            cout << "Are you sure you want to delete this patient? (y/n): ";
            cin >> confirm;
            
            if (confirm == 'y' || confirm == 'Y') {
                patients.erase(it);
                cout << "Patient deleted successfully!" << endl;
            } else {
                cout << "Deletion cancelled!" << endl;
            }
        } else {
            cout << "Patient not found!" << endl;
        }
    }
    
    // Session Management Functions
    void scheduleSession() {
        int patientID;
        cout << "\n=== SCHEDULE SESSION ===" << endl;
        cout << "Enter Patient ID: ";
        cin >> patientID;
        
        auto it = find_if(patients.begin(), patients.end(), 
            [patientID](const Patient& p) { return p.patientID == patientID; });
        
        if (it != patients.end()) {
            Session newSession;
            newSession.sessionID = nextSessionID++;
            newSession.patientID = patientID;
            
            cout << "Enter Session Date (DD/MM/YYYY): ";
            cin.ignore();
            getline(cin, newSession.sessionDate);
            
            cout << "Enter Session Time (HH:MM): ";
            getline(cin, newSession.sessionTime);
            
            cout << "Enter Counselor Name: ";
            getline(cin, newSession.counselorName);
            
            newSession.sessionStatus = "Scheduled";
            newSession.sessionNotes = "";
            
            sessions.push_back(newSession);
            cout << "Session scheduled successfully! Session ID: " << newSession.sessionID << endl;
        } else {
            cout << "Patient not found!" << endl;
        }
    }
    
    void viewSessions() {
        cout << "\n=== ALL SESSIONS ===" << endl;
        cout << left << setw(8) << "Sess ID" << setw(8) << "Pat ID" << setw(12) << "Date" 
             << setw(8) << "Time" << setw(15) << "Counselor" << setw(12) << "Status" << endl;
        cout << string(75, '-') << endl;
        
        for (const auto& session : sessions) {
            cout << left << setw(8) << session.sessionID 
                 << setw(8) << session.patientID 
                 << setw(12) << session.sessionDate 
                 << setw(8) << session.sessionTime 
                 << setw(15) << session.counselorName 
                 << setw(12) << session.sessionStatus << endl;
        }
    }
    
    void updateSessionNotes() {
        int sessionID;
        cout << "\n=== UPDATE SESSION NOTES ===" << endl;
        cout << "Enter Session ID: ";
        cin >> sessionID;
        
        auto it = find_if(sessions.begin(), sessions.end(), 
            [sessionID](const Session& s) { return s.sessionID == sessionID; });
        
        if (it != sessions.end()) {
            cout << "Current Session Details:" << endl;
            cout << "Session ID: " << it->sessionID << endl;
            cout << "Patient ID: " << it->patientID << endl;
            cout << "Date: " << it->sessionDate << endl;
            cout << "Time: " << it->sessionTime << endl;
            cout << "Status: " << it->sessionStatus << endl;
            cout << "Current Notes: " << it->sessionNotes << endl;
            
            cout << "\nEnter new session notes: ";
            cin.ignore();
            getline(cin, it->sessionNotes);
            
            cout << "Update session status? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << "Enter new status (Scheduled/Completed/Cancelled): ";
                cin.ignore();
                getline(cin, it->sessionStatus);
            }
            
            cout << "Session updated successfully!" << endl;
        } else {
            cout << "Session not found!" << endl;
        }
    }
    
    // Utility Functions
    void displayPatientDetails(const Patient& patient) {
        cout << "\n--- Patient Details ---" << endl;
        cout << "ID: " << patient.patientID << endl;
        cout << "Name: " << patient.ptFName << " " << patient.ptLName << endl;
        cout << "Phone: " << patient.ptPhone << endl;
        cout << "Email: " << patient.ptEmail << endl;
        cout << "Age: " << patient.ptAge << endl;
        cout << "Status: " << patient.ptStatus << endl;
        cout << "----------------------" << endl;
    }
    
    void generateReports() {
        cout << "\n=== SYSTEM REPORTS ===" << endl;
        cout << "Total Patients: " << patients.size() << endl;
        
        int activePatients = count_if(patients.begin(), patients.end(), 
            [](const Patient& p) { return p.ptStatus == "Active"; });
        cout << "Active Patients: " << activePatients << endl;
        cout << "Inactive Patients: " << patients.size() - activePatients << endl;
        
        cout << "Total Sessions: " << sessions.size() << endl;
        
        int completedSessions = count_if(sessions.begin(), sessions.end(), 
            [](const Session& s) { return s.sessionStatus == "Completed"; });
        int scheduledSessions = count_if(sessions.begin(), sessions.end(), 
            [](const Session& s) { return s.sessionStatus == "Scheduled"; });
        int cancelledSessions = count_if(sessions.begin(), sessions.end(), 
            [](const Session& s) { return s.sessionStatus == "Cancelled"; });
        
        cout << "Completed Sessions: " << completedSessions << endl;
        cout << "Scheduled Sessions: " << scheduledSessions << endl;
        cout << "Cancelled Sessions: " << cancelledSessions << endl;
    }
    
    // File I/O Functions
    void savePatientsToFile() {
        ofstream file("patients.txt");
        if (file.is_open()) {
            file << nextPatientID << endl;
            for (const auto& patient : patients) {
                file << patient.patientID << "|" << patient.ptFName << "|" << patient.ptLName 
                     << "|" << patient.ptPhone << "|" << patient.ptEmail << "|" << patient.ptAge 
                     << "|" << patient.ptPwd << "|" << patient.ptStatus << endl;
            }
            file.close();
        }
    }
    
    void loadPatientsFromFile() {
        ifstream file("patients.txt");
        if (file.is_open()) {
            file >> nextPatientID;
            file.ignore();
            
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string item;
                Patient patient;
                
                getline(ss, item, '|'); patient.patientID = stoi(item);
                getline(ss, patient.ptFName, '|');
                getline(ss, patient.ptLName, '|');
                getline(ss, item, '|'); patient.ptPhone = stoi(item);
                getline(ss, patient.ptEmail, '|');
                getline(ss, item, '|'); patient.ptAge = stoi(item);
                getline(ss, patient.ptPwd, '|');
                getline(ss, patient.ptStatus, '|');
                
                patients.push_back(patient);
            }
            file.close();
        }
    }
    
    void saveSessionsToFile() {
        ofstream file("sessions.txt");
        if (file.is_open()) {
            file << nextSessionID << endl;
            for (const auto& session : sessions) {
                file << session.sessionID << "|" << session.patientID << "|" << session.sessionDate 
                     << "|" << session.sessionTime << "|" << session.counselorName << "|" 
                     << session.sessionNotes << "|" << session.sessionStatus << endl;
            }
            file.close();
        }
    }
    
    void loadSessionsFromFile() {
        ifstream file("sessions.txt");
        if (file.is_open()) {
            file >> nextSessionID;
            file.ignore();
            
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string item;
                Session session;
                
                getline(ss, item, '|'); session.sessionID = stoi(item);
                getline(ss, item, '|'); session.patientID = stoi(item);
                getline(ss, session.sessionDate, '|');
                getline(ss, session.sessionTime, '|');
                getline(ss, session.counselorName, '|');
                getline(ss, session.sessionNotes, '|');
                getline(ss, session.sessionStatus, '|');
                
                sessions.push_back(session);
            }
            file.close();
        }
    }
    
    // Main Menu
    void showMainMenu() {
        int choice;
        do {
            cout << "\n========================================" << endl;
            cout << "    COUNSELING MANAGEMENT SYSTEM" << endl;
            cout << "========================================" << endl;
            cout << "1.  Add New Patient" << endl;
            cout << "2.  View All Patients" << endl;
            cout << "3.  Search Patient" << endl;
            cout << "4.  Update Patient" << endl;
            cout << "5.  Delete Patient" << endl;
            cout << "6.  Schedule Session" << endl;
            cout << "7.  View All Sessions" << endl;
            cout << "8.  Update Session Notes" << endl;
            cout << "9.  Generate Reports" << endl;
            cout << "10. Save Data" << endl;
            cout << "0.  Exit" << endl;
            cout << "========================================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            
            switch(choice) {
                case 1: addPatient(); break;
                case 2: displayAllPatients(); break;
                case 3: searchPatient(); break;
                case 4: updatePatient(); break;
                case 5: deletePatient(); break;
                case 6: scheduleSession(); break;
                case 7: viewSessions(); break;
                case 8: updateSessionNotes(); break;
                case 9: generateReports(); break;
                case 10: 
                    savePatientsToFile();
                    saveSessionsToFile();
                    cout << "Data saved successfully!" << endl;
                    break;
                case 0: 
                    cout << "Thank you for using Counseling Management System!" << endl;
                    break;
                default: 
                    cout << "Invalid choice! Please try again." << endl;
            }
            
            if (choice != 0) {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }
            
        } while (choice != 0);
    }
};

int main() {
    CounselingSystem system;
    system.showMainMenu();
    return 0;
}