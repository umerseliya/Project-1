#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Structure to represent a rule in the expert system
struct Rule 
{
    int id; // Rule ID
    vector<string> conditions; // Conditions (if part of the rule)
    string conclusion; // Conclusion (then part of the rule)
};

// KnowledgeBaseBackward class to manage the backward chaining rules
class KnowledgeBaseBackward {
public:
    vector<Rule> rules;
    map<int, string> conclusionList;
    map<int, string> clauseVarList; // Not directly used in this implementation
    map<string, string> questionVarList;

    KnowledgeBaseBackward() {
        // Initialize rules
        rules = 
        {
            {10, {"CHEST_PAIN", "RADIATING_PAIN", "EXERTION_STRESS", "RELIEF_WITH_REST"}, "Coronary Artery Disease"},
            {20, {"CHEST_PAIN", "RADIATING_PAIN", "EXERTION_STRESS", "NAUSEA_VOMITING"}, "Heart Attack (Myocardial Infarction)"},
            {30, {"CHEST_PAIN", "RADIATING_PAIN", "EXERTION_STRESS", "DISCOMFORT_OVER_MINUTES"}, "Heart Attack (Myocardial Infarction)"},
            {40, {"CHEST_PAIN", "RADIATING_PAIN", "EXERTION_STRESS", "CHEST_PAIN_RANDOM"}, "Unstable Angina"},
            {50, {"CHEST_PAIN", "RADIATING_PAIN", "EXERTION_STRESS"}, "Stable Angina"},
            {60, {"CHEST_PAIN", "CHEST_PAIN_WORSE_LYING_DOWN"}, "Pericarditis"},
            {70, {"CHEST_PAIN", "FLUTTERING_HEARTBEAT", "DIZZINESS_FAINTING"}, "Arrhythmia"},
            {80, {"CHEST_PAIN", "FLUTTERING_HEARTBEAT", "IS_SHORTNESS_BREATH_WITH_EXERTION"}, "Arrhythmia"},
            {90, {"CHEST_PAIN", "FLUTTERING_HEARTBEAT"}, "Benign Palpitations"},
            {100, {"CHEST_PAIN", "SHORTNESS_BREATH_CHEST_TIGHTNESS"}, "Pulmonary Hypertension"},
            {110, {"CHEST_PAIN", "RECENT_FEVER_ILLNESS"}, "Endocarditis"},
            {120, {"CHEST_PAIN", "FEVER_WEIGHT_LOSS", "NIGHT_SWEATS_CHILLS", "NEW_HEART_MURMUR"}, "Endocarditis"},
            {130, {"CHEST_PAIN", "FEVER_WEIGHT_LOSS", "NIGHT_SWEATS_CHILLS", "PAINFUL_SWOLLEN_JOINTS"}, "Rheumatic Heart Disease"},
            {140, {"SWELLING_LEGS_ANKLES", "SHORTNESS_BREATH_LYING_DOWN", "PRODUCTIVE_COUGH_WHEEZING"}, "Congestive Heart Failure"},
            {150, {"SWELLING_LEGS_ANKLES", "SHORTNESS_BREATH_LYING_DOWN", "SWOLLEN_LIVER_ABDOMEN"}, "Right-Sided Heart Failure"},
            {160, {"SWELLING_LEGS_ANKLES", "SHORTNESS_BREATH_LYING_DOWN", "HIGH_BLOOD_PRESSURE"}, "Hypertensive Heart Disease"},
            {170, {"SWELLING_LEGS_ANKLES", "SHORTNESS_BREATH_LYING_DOWN", "SHORTNESS_BREATH_CHEST_PAIN_EXERTION"}, "Congestive Heart Failure"},
            {180, {"SWELLING_LEGS_ANKLES", "SHORTNESS_BREATH_LYING_DOWN", "PERSISTENT_DRY_COUGH"}, "Pulmonary Hypertension"},
            {190, {"SWELLING_LEGS_ANKLES", "SHORTNESS_BREATH_LYING_DOWN"}, "Valvular Heart Disease"},
            {200, {"SWELLING_LEGS_ANKLES", "HISTORY_ALCOHOL_DRUGS"}, "Cardiomyopathy"},
            {210, {"SWELLING_LEGS_ANKLES", "FREQUENT_INFECTIONS_FEVER"}, "Endocarditis"},
            {220, {"SWELLING_LEGS_ANKLES", "RECENT_INFECTION_TRAUMA"}, "Pericarditis"},
            {230, {"SWELLING_LEGS_ANKLES"}, "Congestive Heart Failure"},
            {240, {"LEG_PAIN_WHEN_WALKING", "PAIN_SUBSIDES_AFTER_REST"}, "Peripheral Artery Disease"},
            {250, {"LEG_PAIN_WHEN_WALKING"}, "Aortic Aneurysm"},
            {260, {"NUMBNESS_COLDNESS_LIMBS"}, "Peripheral Artery Disease"},
            {270, {"PAIN_SUDDEN_SEVERE"}, "Aortic Aneurysm"},
            {280, {"NUMBNESS_COLDNESS_LIMBS"}, "Congenital Heart Disease"},
            {290, {"CHEST_PAIN", "FEVER_WEIGHT_LOSS", "SWELLING_LEGS_DIFFICULTY_BREATHING"}, "Congestive Heart Failure"},
            {300, {"CHEST_PAIN", "SHARP_CHEST_PAIN_DEEP_BREATHS", "RECENT_INFECTION_TRAUMA"}, "Pericarditis"},
            {310, {"CHEST_PAIN", "SHARP_CHEST_PAIN_DEEP_BREATHS", "DIFFICULTY_BREATHING_LYING_DOWN"}, "Pericarditis"},
            {320, {"CHEST_PAIN", "SHARP_CHEST_PAIN_DEEP_BREATHS"}, "Stable Angina"},
            {330, {"CHEST_PAIN", "HIGH_BP_HEADACHES_BLURRED_VISION"}, "Hypertensive Heart Disease"},
            {340, {"CHEST_PAIN", "BLUISH_SKIN_LIPS", "PRESENT_SINCE_BIRTH"}, "Congenital Heart Disease"},
            {350, {"CHEST_PAIN", "BLUISH_SKIN_LIPS", "EXTREME_SHORTNESS_BREATH_FATIGUE_EXERTION"}, "Pulmonary Hypertension"},
            {360, {"CHEST_PAIN"}, "Benign Condition"}
        };

        // Initialize conclusionList
        for (const auto& rule : rules) {
            conclusionList[rule.id] = rule.conclusion;
        }

        // Initialize clauseVarList (optional usage)
        // This mapping can be used if you have specific clause numbers to variables
        // For this implementation, it's not directly utilized
        int clauseNumber = 1;
        for (const auto& rule : rules) {
            for (const auto& cond : rule.conditions) {
                clauseVarList[clauseNumber++] = cond;
            }
        }

        // Initialize questionVarList
        questionVarList = 
        {
            {"CHEST_PAIN", "Chest pain or discomfort?"},
            {"RADIATING_PAIN", "Pain radiating to arms, neck, jaw, or back?"},
            {"SWELLING_LEGS_ANKLES", "Swelling in the legs or ankles?"},
            {"EXERTION_STRESS", "Occurs after exertion or stress?"},
            {"CHEST_PAIN_WORSE_LYING_DOWN", "Does chest pain worsen when lying down?"},
            {"SHORTNESS_BREATH_LYING_DOWN", "Do you have shortness of breath while lying down?"},
            {"LEG_PAIN_WHEN_WALKING", "Leg pain or cramping while walking?"},
            {"RELIEF_WITH_REST", "Relief with rest or nitroglycerin?"},
            {"NAUSEA_VOMITING", "Nausea, vomiting, sweating, shortness of breath?"},
            {"DISCOMFORT_OVER_MINUTES", "Discomfort lasts over ___ minutes?"},
            {"CHEST_PAIN_RANDOM", "Chest pain occurs randomly?"},
            {"DIZZINESS_FAINTING", "Do you experience dizziness or fainting?"},
            {"FLUTTERING_HEARTBEAT", "Do you feel a fluttering or irregular heartbeat?"},
            {"SHORTNESS_BREATH_CHEST_TIGHTNESS", "Shortness of breath with chest tightness?"},
            {"IS_SHORTNESS_BREATH_WITH_EXERTION", "Is there shortness of breath with exertion?"},
            {"RECENT_FEVER_ILLNESS", "Recent fever or illness?"},
            {"FEVER_WEIGHT_LOSS", "Fever with unexplained weight loss?"},
            {"NIGHT_SWEATS_CHILLS", "Do you experience night sweats or chills?"},
            {"NEW_HEART_MURMUR", "Do you have a new or worsening heart murmur?"},
            {"PAINFUL_SWOLLEN_JOINTS", "Do you have painful, swollen joints?"},
            {"SWELLING_LEGS_DIFFICULTY_BREATHING", "Do you have swelling in your legs and difficulty breathing?"},
            {"SHARP_CHEST_PAIN_DEEP_BREATHS", "Do you experience sharp, stabbing chest pain that worsens with deep breaths?"},
            {"RECENT_INFECTION_TRAUMA", "Was there a recent infection or trauma?"},
            {"HIGH_BP_HEADACHES_BLURRED_VISION", "High blood pressure with severe headaches or blurred vision?"},
            {"BLUISH_SKIN_LIPS", "Bluish skin or lips (cyanosis)?"},
            {"PRESENT_SINCE_BIRTH", "Has this been present since birth?"},
            {"EXTREME_SHORTNESS_BREATH_FATIGUE_EXERTION", "Do you experience extreme shortness of breath or fatigue with exertion?"},
            {"HIGH_BLOOD_PRESSURE", "Do you have high blood pressure?"},
            {"SHORTNESS_BREATH_CHEST_PAIN_EXERTION", "Do you have shortness of breath and chest pain with exertion?"},
            {"PERSISTENT_DRY_COUGH", "Do you have a persistent dry cough?"},
            {"PRODUCTIVE_COUGH_WHEEZING", "Is there a productive cough or wheezing?"},
            {"SWOLLEN_LIVER_ABDOMEN", "Do you have swollen liver or abdomen?"},
            {"HISTORY_ALCOHOL_DRUGS", "Do you have a history of alcohol abuse or drug use?"},
            {"FREQUENT_INFECTIONS_FEVER", "Do you have frequent infections or fever?"},
            {"PAIN_SUBSIDES_AFTER_REST", "Does the pain subside after rest?"},
            {"NUMBNESS_COLDNESS_LIMBS", "Do you experience numbness or coldness in your limbs?"},
            {"PAIN_SUDDEN_SEVERE", "Does the pain or numbness occur suddenly with severe intensity?"},
            {"DIFFICULTY_BREATHING_LYING_DOWN", "Difficulty breathing when lying down?"}
        };
    } // Removed the semicolon here
};

// VariableList class to manage variables and their status
class VariableList {
public:
    map<string, bool> variableList; // Stores user responses
    map<string, bool> derivedGlobalVariableList; // Stores derived conclusions

    // Function to get the status of a variable
    bool getStatus(const string& variable) {
        if (variableList.find(variable) != variableList.end()) {
            return variableList[variable];
        }
        return false;
    }

    // Function to set the status of a variable
    void setStatus(const string& variable, bool status) {
        variableList[variable] = status;
    }

    // Function to add a derived conclusion
    void addDerived(const string& variable) {
        derivedGlobalVariableList[variable] = true;
    }

    // Function to check if a conclusion has been derived
    bool isDerived(const string& variable) {
        return derivedGlobalVariableList.find(variable) != derivedGlobalVariableList.end();
    }
};

// InferenceEngineBackward class to perform backward chaining
class InferenceEngineBackward {
private:
    KnowledgeBaseBackward* kb;
    VariableList* vl;

public:
    InferenceEngineBackward(KnowledgeBaseBackward* kb_ptr, VariableList* vl_ptr) {
        kb = kb_ptr;
        vl = vl_ptr;
    }

    // Function to process rules and derive diagnosis
    bool Process(string goal, string &diagnosis, int &usedRuleNumber) {
        // Sort rules based on their IDs (ascending order)
        vector<Rule> sortedRules = kb->rules;
        sort(sortedRules.begin(), sortedRules.end(), [&](const Rule &a, const Rule &b) -> bool {
            return a.id < b.id;
        });

        // Iterate through each rule
        for (const auto& rule : sortedRules) {
            bool ruleSatisfied = true;

            // Iterate through each condition in the rule
            for (const auto& condition : rule.conditions) {
                // Check if the variable has already been answered
                if (vl->variableList.find(condition) != vl->variableList.end()) {
                    if (!vl->variableList[condition]) {
                        // If previously answered 'No', skip this rule
                        ruleSatisfied = false;
                        break;
                    }
                    // If 'Yes', continue to next condition
                    continue;
                }

                // Ask the user the corresponding question
                if (kb->questionVarList.find(condition) != kb->questionVarList.end()) {
                    string question = kb->questionVarList[condition];
                    cout << question << " (1 for Yes / 0 for No): ";
                    int response;
                    while (true) {
                        cin >> response;
                        if (response == 1 || response == 0) {
                            break;
                        } else {
                            cout << "Please enter 1 for Yes or 0 for No: ";
                        }
                    }
                    vl->setStatus(condition, response == 1);
                    if (!vl->variableList[condition]) {
                        // If answered 'No', skip the rest of the conditions for this rule
                        ruleSatisfied = false;
                        break;
                    }
                } else {
                    // If no question is defined for the variable, assume false
                    vl->setStatus(condition, false);
                    ruleSatisfied = false;
                    break;
                }
            }

            if (ruleSatisfied) {
                // All conditions are satisfied for this rule
                diagnosis = rule.conclusion;
                usedRuleNumber = rule.id;
                vl->addDerived(rule.conclusion);
                return true;
            }
        }

        return false; // No matching rule satisfied
    }
};

// KnowledgeBaseForward class to manage treatment recommendations
class KnowledgeBaseForward {
public:
    map<string, vector<string>> treatmentRecommendations;

    KnowledgeBaseForward() {
        // Initialize treatment recommendations based on diagnosis
        treatmentRecommendations = {
            {"Coronary Artery Disease", {"Lifestyle changes", "Medications (e.g., aspirin, beta-blockers)", "Angioplasty or surgery"}},
            {"Heart Attack (Myocardial Infarction)", {"Immediate medical attention", "Medications (e.g., thrombolytics)", "Surgical procedures (e.g., bypass surgery)"}},
            {"Unstable Angina", {"Medications (e.g., nitrates, anticoagulants)", "Lifestyle modifications", "Surgical interventions if necessary"}},
            {"Stable Angina", {"Lifestyle changes", "Medications (e.g., nitrates, beta-blockers)", "Possible angioplasty"}},
            {"Pericarditis", {"Anti-inflammatory medications", "Rest", "Treatment of underlying cause"}},
            {"Arrhythmia", {"Medications to control heart rate", "Pacemaker or defibrillator", "Lifestyle modifications"}},
            {"Benign Palpitations", {"Reassurance", "Lifestyle changes if necessary"}},
            {"Pulmonary Hypertension", {"Medications to dilate blood vessels", "Oxygen therapy", "Lifestyle changes"}},
            {"Endocarditis", {"Antibiotics", "Surgery in severe cases"}},
            {"Rheumatic Heart Disease", {"Antibiotics to treat strep infection", "Medications to manage symptoms"}},
            {"Congestive Heart Failure", {"Medications (e.g., diuretics, ACE inhibitors)", "Lifestyle changes", "Surgical options"}},
            {"Right-Sided Heart Failure", {"Treat underlying cause", "Medications to reduce fluid buildup"}},
            {"Hypertensive Heart Disease", {"Antihypertensive medications", "Lifestyle modifications"}},
            {"Valvular Heart Disease", {"Medications to manage symptoms", "Surgical repair or replacement of valves"}},
            {"Cardiomyopathy", {"Medications to manage symptoms", "Lifestyle changes", "Surgical interventions if necessary"}},
            {"Peripheral Artery Disease", {"Lifestyle changes", "Medications to manage symptoms", "Surgical procedures"}},
            {"Aortic Aneurysm", {"Regular monitoring", "Surgical repair if necessary"}},
            {"Congenital Heart Disease", {"Surgical interventions", "Medications", "Lifestyle adjustments"}},
            {"Benign Condition", {"Reassurance and regular monitoring"}}
        };
    }
};

// InferenceEngineForward class to perform forward chaining for treatment recommendations
class InferenceEngineForward {
private:
    KnowledgeBaseForward* kb_forward;
    VariableList* vl_forward;
    vector<string> treatments;

public:
    InferenceEngineForward(KnowledgeBaseForward* kb_ptr, VariableList* vl_ptr) {
        kb_forward = kb_ptr;
        vl_forward = vl_ptr;
    }

    // Function to recommend treatments based on diagnosis
    void recommendTreatments(const string& diagnosis) {
        if (kb_forward->treatmentRecommendations.find(diagnosis) != kb_forward->treatmentRecommendations.end()) {
            treatments = kb_forward->treatmentRecommendations[diagnosis];
        } else {
            treatments.push_back("No treatment recommendations available.");
        }
    }

    // Function to print treatment recommendations
    void printConclusions() {
        if (!treatments.empty()) {
            cout << "Recommended Treatments:\n";
            for (const auto& treatment : treatments) {
                cout << "- " << treatment << "\n";
            }
        } else {
            cout << "No treatment recommendations available.\n";
        }
    }
};

// Main Function
int main(){
    // Initialize Knowledge Bases
    KnowledgeBaseBackward kb_backward;
    KnowledgeBaseForward kb_forward;

    // Initialize Variable Lists
    VariableList varList_backward;
    VariableList varList_forward;

    // Initialize Inference Engines
    InferenceEngineBackward ie_backward(&kb_backward, &varList_backward);
    InferenceEngineForward ie_forward(&kb_forward, &varList_forward);

    cout << "-------------------------------------------------------\n";
    cout << "=== Cardiovascular Diseases Diagnosis Expert System ===\n";
    cout << "-------------------------------------------------------\n\n";

    // -----------------------------
    // Backward Chaining for Diagnosis
    // -----------------------------
    cout << "=== Diseases Diagnosis (Backwards) ===\n";
    cout << "Determining diagnosis - Please answer the following symptoms:\n\n";

    // Start processing
    string diagnosis;
    int usedRuleNumber = -1;
    bool found = ie_backward.Process("DIAGNOSIS", diagnosis, usedRuleNumber);

    if(found && !diagnosis.empty()){
        cout << "\nDiagnosis: " << diagnosis << " (Rule " << usedRuleNumber << ")\n";
    }
    else{
        cout << "\nGoal cannot be determined.\n";
        return 0;
    }

    // -----------------------------
    // Forward Chaining for Treatment
    // -----------------------------
    cout << "\n=== Treatment Recommendations (Forwards) ===\n";

    // Recommend treatments based on the diagnosis
    ie_forward.recommendTreatments(diagnosis);

    // Print treatment recommendations
    ie_forward.printConclusions();

    return 0;
}
