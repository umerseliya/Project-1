#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

// -----------------------------
// Rule Classes
// -----------------------------

// Class for Backward Chaining Rules
class RuleBackward {
public:
    int ruleNumber;
    unordered_map<string, string> conditions; // Variable -> Value
    pair<string, string> conclusion;          // Variable -> Value

    RuleBackward(int num, unordered_map<string, string> cond, pair<string, string> concl)
        : ruleNumber(num), conditions(cond), conclusion(concl) {}
};

// Class for Forward Chaining Rules
class RuleForward {
public:
    int ruleNumber;
    unordered_map<string, string> conditions; // Variable -> Value
    string conclusion;

    RuleForward(int num, unordered_map<string, string> cond, string concl)
        : ruleNumber(num), conditions(cond), conclusion(concl) {}
};

// -----------------------------
// Knowledge Base Classes
// -----------------------------

// Knowledge Base for Backward Chaining (Diagnosis)
class KnowledgeBaseBackward {
public:
    vector<RuleBackward*> rules;

    KnowledgeBaseBackward() {
        // Rule 10
        rules.push_back(new RuleBackward(10, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "YES"},
            {"EXERTION_STRESS", "YES"},
            {"RELIEF_WITH_REST", "YES"}
        }, {"DIAGNOSIS", "Coronary Artery Disease"}));

        // Rule 20
        rules.push_back(new RuleBackward(20, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "YES"},
            {"EXERTION_STRESS", "YES"},
            {"RELIEF_WITH_REST", "NO"},
            {"NAUSEA_VOMITING", "YES"}
        }, {"DIAGNOSIS", "Heart Attack (Myocardial Infarction)"}));

        // Rule 30
        rules.push_back(new RuleBackward(30, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "YES"},
            {"EXERTION_STRESS", "YES"},
            {"RELIEF_WITH_REST", "NO"},
            {"NAUSEA_VOMITING", "NO"},
            {"DISCOMFORT_OVER_MINUTES", "YES"}
        }, {"DIAGNOSIS", "Heart Attack (Myocardial Infarction)"}));

        // Rule 40
        rules.push_back(new RuleBackward(40, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "YES"},
            {"EXERTION_STRESS", "YES"},
            {"RELIEF_WITH_REST", "NO"},
            {"NAUSEA_VOMITING", "NO"},
            {"DISCOMFORT_OVER_MINUTES", "NO"},
            {"CHEST_PAIN_RANDOM", "YES"}
        }, {"DIAGNOSIS", "Unstable Angina"}));

        // Rule 50
        rules.push_back(new RuleBackward(50, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "YES"},
            {"EXERTION_STRESS", "YES"},
            {"RELIEF_WITH_REST", "NO"},
            {"NAUSEA_VOMITING", "NO"},
            {"DISCOMFORT_OVER_MINUTES", "NO"},
            {"CHEST_PAIN_RANDOM", "NO"}
        }, {"DIAGNOSIS", "Stable Angina"}));

        // Rule 60
        rules.push_back(new RuleBackward(60, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"CHEST_PAIN_WORSE_LYING_DOWN", "YES"}
        }, {"DIAGNOSIS", "Pericarditis"}));

        // Rule 70
        rules.push_back(new RuleBackward(70, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"CHEST_PAIN_WORSE_LYING_DOWN", "NO"},
            {"FLUTTERING_HEARTBEAT", "YES"},
            {"DIZZINESS_FAINTING", "YES"}
        }, {"DIAGNOSIS", "Arrhythmia"}));

        // Rule 80
        rules.push_back(new RuleBackward(80, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"CHEST_PAIN_WORSE_LYING_DOWN", "NO"},
            {"FLUTTERING_HEARTBEAT", "YES"},
            {"DIZZINESS_FAINTING", "NO"},
            {"IS_SHORTNESS_BREATH_WITH_EXERTION", "YES"}
        }, {"DIAGNOSIS", "Arrhythmia"}));

        // Rule 90
        rules.push_back(new RuleBackward(90, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"CHEST_PAIN_WORSE_LYING_DOWN", "NO"},
            {"FLUTTERING_HEARTBEAT", "YES"},
            {"DIZZINESS_FAINTING", "NO"},
            {"IS_SHORTNESS_BREATH_WITH_EXERTION", "NO"}
        }, {"DIAGNOSIS", "Benign Palpitations"}));

        // Rule 100
        rules.push_back(new RuleBackward(100, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"CHEST_PAIN_WORSE_LYING_DOWN", "NO"},
            {"FLUTTERING_HEARTBEAT", "NO"},
            {"SHORTNESS_BREATH_CHEST_TIGHTNESS", "YES"}
        }, {"DIAGNOSIS", "Pulmonary Hypertension"}));

        // Rule 110
        rules.push_back(new RuleBackward(110, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"CHEST_PAIN_WORSE_LYING_DOWN", "NO"},
            {"FLUTTERING_HEARTBEAT", "NO"},
            {"SHORTNESS_BREATH_CHEST_TIGHTNESS", "NO"},
            {"RECENT_FEVER_ILLNESS", "YES"}
        }, {"DIAGNOSIS", "Endocarditis"}));

        // Rule 120
        rules.push_back(new RuleBackward(120, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"CHEST_PAIN_WORSE_LYING_DOWN", "NO"},
            {"FLUTTERING_HEARTBEAT", "NO"},
            {"SHORTNESS_BREATH_CHEST_TIGHTNESS", "NO"},
            {"RECENT_FEVER_ILLNESS", "NO"},
            {"FEVER_WEIGHT_LOSS", "YES"},
            {"NIGHT_SWEATS_CHILLS", "YES"},
            {"NEW_HEART_MURMUR", "YES"}
        }, {"DIAGNOSIS", "Endocarditis"}));

        // Rule 130
        rules.push_back(new RuleBackward(130, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"CHEST_PAIN_WORSE_LYING_DOWN", "NO"},
            {"FLUTTERING_HEARTBEAT", "NO"},
            {"SHORTNESS_BREATH_CHEST_TIGHTNESS", "NO"},
            {"RECENT_FEVER_ILLNESS", "NO"},
            {"FEVER_WEIGHT_LOSS", "YES"},
            {"NIGHT_SWEATS_CHILLS", "YES"},
            {"NEW_HEART_MURMUR", "NO"},
            {"PAINFUL_SWOLLEN_JOINTS", "YES"}
        }, {"DIAGNOSIS", "Rheumatic Heart Disease"}));

        // Rule 140
        rules.push_back(new RuleBackward(140, {
            {"SWELLING_LEGS_ANKLES", "YES"},
            {"SHORTNESS_BREATH_LYING_DOWN", "YES"},
            {"PRODUCTIVE_COUGH_WHEEZING", "YES"}
        }, {"DIAGNOSIS", "Congestive Heart Failure"}));

        // Rule 150
        rules.push_back(new RuleBackward(150, {
            {"SWELLING_LEGS_ANKLES", "YES"},
            {"SHORTNESS_BREATH_LYING_DOWN", "YES"},
            {"PRODUCTIVE_COUGH_WHEEZING", "NO"},
            {"SWOLLEN_LIVER_ABDOMEN", "YES"}
        }, {"DIAGNOSIS", "RightSided Heart Failure"}));

        // Rule 160
        rules.push_back(new RuleBackward(160, {
            {"SWELLING_LEGS_ANKLES", "YES"},
            {"SHORTNESS_BREATH_LYING_DOWN", "YES"},
            {"PRODUCTIVE_COUGH_WHEEZING", "NO"},
            {"SWOLLEN_LIVER_ABDOMEN", "NO"},
            {"HIGH_BLOOD_PRESSURE", "YES"}
        }, {"DIAGNOSIS", "Hypertensive Heart Disease"}));

        // Rule 170
        rules.push_back(new RuleBackward(170, {
            {"SWELLING_LEGS_ANKLES", "YES"},
            {"SHORTNESS_BREATH_LYING_DOWN", "YES"},
            {"PRODUCTIVE_COUGH_WHEEZING", "NO"},
            {"SWOLLEN_LIVER_ABDOMEN", "NO"},
            {"HIGH_BLOOD_PRESSURE", "NO"},
            {"SHORTNESS_BREATH_CHEST_PAIN_EXERTION", "YES"}
        }, {"DIAGNOSIS", "Congestive Heart Failure"}));

        // Rule 180
        rules.push_back(new RuleBackward(180, {
            {"SWELLING_LEGS_ANKLES", "YES"},
            {"SHORTNESS_BREATH_LYING_DOWN", "YES"},
            {"PRODUCTIVE_COUGH_WHEEZING", "NO"},
            {"SWOLLEN_LIVER_ABDOMEN", "NO"},
            {"HIGH_BLOOD_PRESSURE", "NO"},
            {"SHORTNESS_BREATH_CHEST_PAIN_EXERTION", "NO"},
            {"PERSISTENT_DRY_COUGH", "YES"}
        }, {"DIAGNOSIS", "Pulmonary Hypertension"}));

        // Rule 190
        rules.push_back(new RuleBackward(190, {
            {"SWELLING_LEGS_ANKLES", "YES"},
            {"SHORTNESS_BREATH_LYING_DOWN", "YES"},
            {"PRODUCTIVE_COUGH_WHEEZING", "NO"},
            {"SWOLLEN_LIVER_ABDOMEN", "NO"},
            {"HIGH_BLOOD_PRESSURE", "NO"},
            {"SHORTNESS_BREATH_CHEST_PAIN_EXERTION", "NO"},
            {"PERSISTENT_DRY_COUGH", "NO"}
        }, {"DIAGNOSIS", "Valvular Heart Disease"}));

        // Rule 200
        rules.push_back(new RuleBackward(200, {
            {"SWELLING_LEGS_ANKLES", "YES"},
            {"SHORTNESS_BREATH_LYING_DOWN", "NO"},
            {"HISTORY_ALCOHOL_DRUGS", "YES"}
        }, {"DIAGNOSIS", "Cardiomyopathy"}));

        // Rule 210
        rules.push_back(new RuleBackward(210, {
            {"SWELLING_LEGS_ANKLES", "YES"},
            {"SHORTNESS_BREATH_LYING_DOWN", "NO"},
            {"HISTORY_ALCOHOL_DRUGS", "NO"},
            {"FREQUENT_INFECTIONS_FEVER", "YES"}
        }, {"DIAGNOSIS", "Endocarditis"}));

        // Rule 220
        rules.push_back(new RuleBackward(220, {
            {"SWELLING_LEGS_ANKLES", "YES"},
            {"SHORTNESS_BREATH_LYING_DOWN", "NO"},
            {"HISTORY_ALCOHOL_DRUGS", "NO"},
            {"FREQUENT_INFECTIONS_FEVER", "NO"},
            {"RECENT_INFECTION_TRAUMA", "YES"}
        }, {"DIAGNOSIS", "Pericarditis"}));

        // Rule 230
        rules.push_back(new RuleBackward(230, {
            {"SWELLING_LEGS_ANKLES", "YES"},
            {"SHORTNESS_BREATH_LYING_DOWN", "NO"},
            {"HISTORY_ALCOHOL_DRUGS", "NO"},
            {"FREQUENT_INFECTIONS_FEVER", "NO"},
            {"RECENT_INFECTION_TRAUMA", "NO"}
        }, {"DIAGNOSIS", "Congestive Heart Failure"}));

        // Rule 240
        rules.push_back(new RuleBackward(240, {
            {"SWELLING_LEGS_ANKLES", "NO"},
            {"LEG_PAIN_WHEN_WALKING", "YES"},
            {"PAIN_SUBSIDES_AFTER_REST", "YES"}
        }, {"DIAGNOSIS", "Peripheral Artery Disease"}));

        // Rule 250
        rules.push_back(new RuleBackward(250, {
            {"SWELLING_LEGS_ANKLES", "NO"},
            {"LEG_PAIN_WHEN_WALKING", "YES"},
            {"PAIN_SUBSIDES_AFTER_REST", "NO"}
        }, {"DIAGNOSIS", "Aortic Aneurysm"}));

        // Rule 260
        rules.push_back(new RuleBackward(260, {
            {"SWELLING_LEGS_ANKLES", "NO"},
            {"LEG_PAIN_WHEN_WALKING", "NO"},
            {"NUMBNESS_COLDNESS_LIMBS", "YES"}
        }, {"DIAGNOSIS", "Peripheral Artery Disease"}));

        // Rule 270
        rules.push_back(new RuleBackward(270, {
            {"SWELLING_LEGS_ANKLES", "NO"},
            {"LEG_PAIN_WHEN_WALKING", "NO"},
            {"NUMBNESS_COLDNESS_LIMBS", "NO"},
            {"PAIN_SUDDEN_SEVERE", "YES"}
        }, {"DIAGNOSIS", "Aortic Aneurysm"}));

        // Rule 280
        rules.push_back(new RuleBackward(280, {
            {"SWELLING_LEGS_ANKLES", "NO"},
            {"LEG_PAIN_WHEN_WALKING", "NO"},
            {"NUMBNESS_COLDNESS_LIMBS", "NO"},
            {"PAIN_SUDDEN_SEVERE", "NO"}
        }, {"DIAGNOSIS", "Congenital Heart Disease"}));

        // Rule 290
        rules.push_back(new RuleBackward(290, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"CHEST_PAIN_WORSE_LYING_DOWN", "NO"},
            {"SHORTNESS_BREATH_CHEST_TIGHTNESS", "NO"},
            {"RECENT_FEVER_ILLNESS", "NO"},
            {"FEVER_WEIGHT_LOSS", "YES"},
            {"NIGHT_SWEATS_CHILLS", "NO"},
            {"SWELLING_LEGS_DIFFICULTY_BREATHING", "YES"}
        }, {"DIAGNOSIS", "Congestive Heart Failure"}));

        // Rule 300
        rules.push_back(new RuleBackward(300, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"SHARP_CHEST_PAIN_DEEP_BREATHS", "YES"},
            {"RECENT_INFECTION_TRAUMA", "YES"}
        }, {"DIAGNOSIS", "Pericarditis"}));

        // Rule 310
        rules.push_back(new RuleBackward(310, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"SHARP_CHEST_PAIN_DEEP_BREATHS", "YES"},
            {"RECENT_INFECTION_TRAUMA", "NO"},
            {"DIFFICULTY_BREATHING_LYING_DOWN", "YES"}
        }, {"DIAGNOSIS", "Pericarditis"}));

        // Rule 320
        rules.push_back(new RuleBackward(320, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"SHARP_CHEST_PAIN_DEEP_BREATHS", "YES"},
            {"RECENT_INFECTION_TRAUMA", "NO"},
            {"DIFFICULTY_BREATHING_LYING_DOWN", "NO"}
        }, {"DIAGNOSIS", "Stable Angina"}));

        // Rule 330
        rules.push_back(new RuleBackward(330, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"SHARP_CHEST_PAIN_DEEP_BREATHS", "NO"},
            {"HIGH_BP_HEADACHES_BLURRED_VISION", "YES"}
        }, {"DIAGNOSIS", "Hypertensive Heart Disease"}));

        // Rule 340
        rules.push_back(new RuleBackward(340, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"SHARP_CHEST_PAIN_DEEP_BREATHS", "NO"},
            {"HIGH_BP_HEADACHES_BLURRED_VISION", "NO"},
            {"BLUISH_SKIN_LIPS", "YES"},
            {"PRESENT_SINCE_BIRTH", "YES"}
        }, {"DIAGNOSIS", "Congenital Heart Disease"}));

        // Rule 350
        rules.push_back(new RuleBackward(350, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"SHARP_CHEST_PAIN_DEEP_BREATHS", "NO"},
            {"HIGH_BP_HEADACHES_BLURRED_VISION", "NO"},
            {"BLUISH_SKIN_LIPS", "YES"},
            {"PRESENT_SINCE_BIRTH", "NO"},
            {"EXTREME_SHORTNESS_BREATH_FATIGUE_EXERTION", "YES"}
        }, {"DIAGNOSIS", "Pulmonary Hypertension"}));

        // Rule 360
        rules.push_back(new RuleBackward(360, {
            {"CHEST_PAIN", "YES"},
            {"RADIATING_PAIN", "NO"},
            {"SHARP_CHEST_PAIN_DEEP_BREATHS", "NO"},
            {"HIGH_BP_HEADACHES_BLURRED_VISION", "NO"},
            {"BLUISH_SKIN_LIPS", "NO"},
            {"EXTREME_SHORTNESS_BREATH_FATIGUE_EXERTION", "NO"}
        }, {"DIAGNOSIS", "Benign Condition"}));
    }

    ~KnowledgeBaseBackward() {
        for(auto rule : rules)
            delete rule;
    }
};

// Knowledge Base for Forward Chaining (Treatment)
class KnowledgeBaseForward {
public:
    vector<RuleForward*> rules;

    KnowledgeBaseForward() {
        // Initialize forward chaining rules

        // Rule 10
        rules.push_back(new RuleForward(10, {
            {"DISEASE", "Coronary Artery Disease"},
            {"SYMPTOM", "Chest pain or discomfort"}
        }, "Lifestyle changes (diet, exercise, smoking cessation)"));

        // Rule 20
        rules.push_back(new RuleForward(20, {
            {"DISEASE", "Coronary Artery Disease"},
            {"SYMPTOM", "Pain radiating to arms, neck, jaw, or back"}
        }, "Medications (statins, beta blockers)"));

        // Rule 30
        rules.push_back(new RuleForward(30, {
            {"DISEASE", "Heart Attack (Myocardial Infarction)"},
            {"SYMPTOM", "Severe chest pain lasting over 15 minutes"}
        }, "Immediate administration of aspirin"));

        // Rule 40
        rules.push_back(new RuleForward(40, {
            {"DISEASE", "Heart Attack (Myocardial Infarction)"},
            {"SYMPTOM", "Shortness of breath"}
        }, "Thrombolytic therapy (clot busting drugs)"));

        // Rule 50
        rules.push_back(new RuleForward(50, {
            {"DISEASE", "Unstable Angina"},
            {"SYMPTOM", "Chest pain occurs randomly, even at rest"}
        }, "Hospitalization for monitoring"));

        // Rule 60
        rules.push_back(new RuleForward(60, {
            {"DISEASE", "Unstable Angina"},
            {"SYMPTOM", "Chest pain not relieved by rest or nitroglycerin"}
        }, "Medications (antiplatelet agents, anticoagulants)"));

        // Rule 70
        rules.push_back(new RuleForward(70, {
            {"DISEASE", "Stable Angina"},
            {"SYMPTOM", "Chest pain during physical exertion"}
        }, "Medications (nitrates, beta blockers)"));

        // Rule 80
        rules.push_back(new RuleForward(80, {
            {"DISEASE", "Stable Angina"},
            {"SYMPTOM", "Chest pain relieved by rest or nitroglycerin"}
        }, "Lifestyle changes (exercise, healthy diet)"));

        // Rule 90
        rules.push_back(new RuleForward(90, {
            {"DISEASE", "Pericarditis"},
            {"SYMPTOM", "Sharp, stabbing chest pain worsening when lying down"}
        }, "Nonsteroidal antiinflammatory drugs (NSAIDs)"));

        // Rule 100
        rules.push_back(new RuleForward(100, {
            {"DISEASE", "Pericarditis"},
            {"SYMPTOM", "Pain improves when sitting up or leaning forward"}
        }, "Colchicine"));

        // Rule 110
        rules.push_back(new RuleForward(110, {
            {"DISEASE", "Arrhythmia"},
            {"SYMPTOM", "Fluttering or irregular heartbeat"}
        }, "Antiarrhythmic medications"));

        // Rule 120
        rules.push_back(new RuleForward(120, {
            {"DISEASE", "Arrhythmia"},
            {"SYMPTOM", "Dizziness or fainting"}
        }, "Pacemaker implantation"));

        // Rule 130
        rules.push_back(new RuleForward(130, {
            {"DISEASE", "Benign Palpitations"},
            {"SYMPTOM", "Sensation of skipped or extra heartbeats"}
        }, "Reassurance and monitoring"));

        // Rule 140
        rules.push_back(new RuleForward(140, {
            {"DISEASE", "Benign Palpitations"},
            {"SYMPTOM", "No associated dizziness or fainting"}
        }, "Lifestyle changes (reduce caffeine and stress)"));

        // Rule 150
        rules.push_back(new RuleForward(150, {
            {"DISEASE", "Pulmonary Hypertension"},
            {"SYMPTOM", "Shortness of breath with chest tightness"}
        }, "Vasodilator medications"));

        // Rule 160
        rules.push_back(new RuleForward(160, {
            {"DISEASE", "Pulmonary Hypertension"},
            {"SYMPTOM", "Extreme fatigue during exertion"}
        }, "Endothelin receptor antagonists"));

        // Rule 170
        rules.push_back(new RuleForward(170, {
            {"DISEASE", "Endocarditis"},
            {"SYMPTOM", "Fever with unexplained weight loss"}
        }, "Prolonged intravenous antibiotic therapy"));

        // Rule 180
        rules.push_back(new RuleForward(180, {
            {"DISEASE", "Endocarditis"},
            {"SYMPTOM", "New or worsening heart murmur"}
        }, "Surgical repair or replacement of damaged valves"));

        // Rule 190
        rules.push_back(new RuleForward(190, {
            {"DISEASE", "RightSided Heart Failure"},
            {"SYMPTOM", "Swelling in legs or ankles (edema)"}
        }, "Diuretics to reduce fluid overload"));

        // Rule 200
        rules.push_back(new RuleForward(200, {
            {"DISEASE", "RightSided Heart Failure"},
            {"SYMPTOM", "Swollen liver or abdomen"}
        }, "Medications to improve heart function (ACE inhibitors)"));

        // Rule 210
        rules.push_back(new RuleForward(210, {
            {"DISEASE", "Congestive Heart Failure"},
            {"SYMPTOM", "Shortness of breath with exertion or lying down"}
        }, "Medications (diuretics, beta blockers)"));

        // Rule 220
        rules.push_back(new RuleForward(220, {
            {"DISEASE", "Congestive Heart Failure"},
            {"SYMPTOM", "Fatigue and weakness"}
        }, "Lifestyle changes (sodium restriction, exercise)"));

        // Rule 230
        rules.push_back(new RuleForward(230, {
            {"DISEASE", "Cardiomyopathy"},
            {"SYMPTOM", "Shortness of breath"}
        }, "Medications (beta blockers, ACE inhibitors)"));

        // Rule 240
        rules.push_back(new RuleForward(240, {
            {"DISEASE", "Cardiomyopathy"},
            {"SYMPTOM", "History of alcohol abuse or drug use"}
        }, "Lifestyle modifications (avoid alcohol, drugs)"));

        // Rule 250
        rules.push_back(new RuleForward(250, {
            {"DISEASE", "Hypertensive Heart Disease"},
            {"SYMPTOM", "High blood pressure with severe headaches"}
        }, "Antihypertensive medications"));

        // Rule 260
        rules.push_back(new RuleForward(260, {
            {"DISEASE", "Hypertensive Heart Disease"},
            {"SYMPTOM", "Blurred vision"}
        }, "Lifestyle changes (diet, exercise)"));

        // Rule 270
        rules.push_back(new RuleForward(270, {
            {"DISEASE", "Valvular Heart Disease"},
            {"SYMPTOM", "Shortness of breath"}
        }, "Medications to manage symptoms (diuretics, vasodilators)"));

        // Rule 280
        rules.push_back(new RuleForward(280, {
            {"DISEASE", "Valvular Heart Disease"},
            {"SYMPTOM", "Heart murmur"}
        }, "Surgical valve repair or replacement"));

        // Rule 290
        rules.push_back(new RuleForward(290, {
            {"DISEASE", "Rheumatic Heart Disease"},
            {"SYMPTOM", "Painful, swollen joints"}
        }, "Anti Inflammatory medications"));

        // Rule 300
        rules.push_back(new RuleForward(300, {
            {"DISEASE", "Rheumatic Heart Disease"},
            {"SYMPTOM", "Fever"}
        }, "Antibiotics to eliminate residual streptococcal infection"));

        // Rule 310
        rules.push_back(new RuleForward(310, {
            {"DISEASE", "Congenital Heart Disease"},
            {"SYMPTOM", "Bluish skin or lips (cyanosis)"}
        }, "Surgical repair of defects"));

        // Rule 320
        rules.push_back(new RuleForward(320, {
            {"DISEASE", "Congenital Heart Disease"},
            {"SYMPTOM", "Fatigue during exertion"}
        }, "Medications to manage symptoms"));

        // Rule 330
        rules.push_back(new RuleForward(330, {
            {"DISEASE", "Peripheral Artery Disease"},
            {"SYMPTOM", "Leg pain or cramping while walking (intermittent claudication)"}
        }, "Structured exercise program"));

        // Rule 340
        rules.push_back(new RuleForward(340, {
            {"DISEASE", "Peripheral Artery Disease"},
            {"SYMPTOM", "Numbness or coldness in limbs"}
        }, "Medications (antiplatelet agents)"));

        // Rule 350
        rules.push_back(new RuleForward(350, {
            {"DISEASE", "Aortic Aneurysm"},
            {"SYMPTOM", "Sudden, severe chest or back pain"}
        }, "Emergency surgical repair"));

        // Rule 360
        rules.push_back(new RuleForward(360, {
            {"DISEASE", "Aortic Aneurysm"},
            {"SYMPTOM", "Pain or numbness occurs suddenly with severe intensity"}
        }, "Endovascular aneurysm repair (EVAR)"));

        // Rule 370
        rules.push_back(new RuleForward(370, {
            {"DISEASE", "Benign Condition"},
            {"SYMPTOM", "Mild or no significant symptoms"}
        }, "Reassurance and education"));

        // Rule 380
        rules.push_back(new RuleForward(380, {
            {"DISEASE", "Benign Condition"},
            {"SYMPTOM", "No serious underlying heart disease"}
        }, "Lifestyle modifications"));
    }

    ~KnowledgeBaseForward() {
        for(auto rule : rules)
            delete rule;
    }
};

// -----------------------------
// Variable List Class
// -----------------------------

class VariableList {
public:
    unordered_map<string, string> variables;

    bool isInstantiated(const string& var) {
        return variables.find(var) != variables.end();
    }

    void setVariable(const string& var, const string& value) {
        // Convert variable name to uppercase to maintain consistency
        string var_upper = var;
        transform(var_upper.begin(), var_upper.end(), var_upper.begin(), ::toupper);
        variables[var_upper] = value;
    }

    string getVariable(const string& var) {
        string var_upper = var;
        transform(var_upper.begin(), var_upper.end(), var_upper.begin(), ::toupper);
        if(isInstantiated(var_upper))
            return variables[var_upper];
        else
            return "";
    }

    void printVariables() {
        cout << "\nVariable List:\n";
        for(auto& pair : variables){
            cout << pair.first << " = " << pair.second << "\n";
        }
    }
};

// -----------------------------
// Inference Engine for Backward Chaining
// -----------------------------

class InferenceEngineBackward {
private:
    KnowledgeBaseBackward* kb;
    VariableList* varList;

public:
    InferenceEngineBackward(KnowledgeBaseBackward* knowledgeBase, VariableList* variables)
        : kb(knowledgeBase), varList(variables) {}

    // Function 1: search_con
    // Finds all rules that conclude the goal variable
    vector<RuleBackward*> search_con(const string& goalVariable) {
        vector<RuleBackward*> matchingRules;
        for(auto rule : kb->rules){
            if(rule->conclusion.first == goalVariable){
                matchingRules.push_back(rule);
            }
        }
        return matchingRules;
    }

    // Function 2: rule_to_clause
    int rule_to_clause(int Ri) {
        // Assuming rules are sequenced like 10,20,30,... hence use the second formula
        // CLAUSE NUMBER (Ci) = 4* (RULE NUMBER / 10 - 1) + 1
        return 4 * (Ri / 10 - 1) + 1;
    }

    // Function 3: update_VL
    bool update_VL(int Ci, RuleBackward* rule) {
        // Ci is not directly used in this implementation, but kept for adherence
        // Ask user for each condition in the rule if not already instantiated
        for(auto& cond : rule->conditions){
            if(!varList->isInstantiated(cond.first)){
                string response;
                cout << "Is " << cond.first << " (YES/NO): ";
                getline(cin, response);
                // Convert to uppercase for consistency
                transform(response.begin(), response.end(), response.begin(), ::toupper);
                if(response != "YES" && response != "NO"){
                    cout << "Invalid input. Assuming NO.\n";
                    response = "NO";
                }
                varList->setVariable(cond.first, response);
            }
        }
        return true;
    }

    // Function 4: validate_Ri
    bool validate_Ri(RuleBackward* rule, string& diagnosis) {
        // Check if all conditions are satisfied
        bool valid = true;
        for(auto& cond : rule->conditions){
            if(!varList->isInstantiated(cond.first) || varList->getVariable(cond.first) != cond.second){
                valid = false;
                break;
            }
        }

        if(valid){
            diagnosis = rule->conclusion.second;
            varList->setVariable("DIAGNOSIS", diagnosis);
            cout << "Rule " << rule->ruleNumber << " validated: " << diagnosis << "\n";
            return true;
        }
        else{
            cout << "Rule " << rule->ruleNumber << " conditions not satisfied.\n";
        }
        return false;
    }

    // Function 5: Process
    bool Process(const string& goalVariable, string& result) {
        // Start with the goal variable
        // Find all rules that conclude the goal variable
        vector<RuleBackward*> matchingRules = search_con(goalVariable);

        if(matchingRules.empty()){
            cout << "No rules found to conclude " << goalVariable << ".\n";
            return false;
        }

        for(auto rule : matchingRules){
            cout << "\nEvaluating Rule " << rule->ruleNumber << " for " << goalVariable << "...\n";
            int Ri = rule->ruleNumber;
            int Ci = rule_to_clause(Ri);
            // Update Variable List by asking user for conditions
            if(!update_VL(Ci, rule)){
                cout << "Failed to update variable list for rule " << Ri << ".\n";
                continue;
            }

            // Validate the rule
            string diagnosis;
            if(validate_Ri(rule, diagnosis)){
                result = diagnosis;
                return true;
            }
            else{
                // Conditions not satisfied, try next rule
                continue;
            }
        }

        // If none of the rules validate, return false
        return false;
    }
};

// -----------------------------
// Inference Engine for Forward Chaining
// -----------------------------

class InferenceEngineForward {
private:
    KnowledgeBaseForward* kb;
    VariableList* varList;
    vector<string> derivedConclusions;
    queue<string> conclusionQueue;

public:
    InferenceEngineForward(KnowledgeBaseForward* knowledgeBase, VariableList* variables)
        : kb(knowledgeBase), varList(variables) {}

    // Function 1: search_cvl
    // Finds all rules that match the current variable
    vector<RuleForward*> search_cvl(const string& variable) {
        vector<RuleForward*> matchingRules;
        for(auto rule : kb->rules){
            bool match = true;
            for(auto& cond : rule->conditions){
                if(cond.first == "DISEASE"){
                    if(varList->isInstantiated("DISEASE") && varList->getVariable("DISEASE") != cond.second){
                        match = false;
                        break;
                    }
                }
                // Add more condition checks if needed
            }
            if(match){
                matchingRules.push_back(rule);
            }
        }
        return matchingRules;
    }

    // Function 2: clause_to_rule
    int clause_to_rule(int Ci) {
        // Since clause number corresponds to rule number, return Ci
        return Ci;
    }

    // Function 3: update_VL_forward
    bool update_VL_forward(RuleForward* rule) {
        // Ask user for each condition in the rule if not already instantiated
        for(auto& cond : rule->conditions){
            if(!varList->isInstantiated(cond.first)){
                string response;
                cout << "Enter value for " << cond.first << " (" << cond.second << " expected): ";
                getline(cin, response);
                // For simplicity, assume user inputs correct values
                // Convert to uppercase for consistency
                transform(response.begin(), response.end(), response.begin(), ::toupper);
                varList->setVariable(cond.first, response);
            }
        }
        return true;
    }

    // Function 4: validate_Ri_forward
    bool validate_Ri_forward(RuleForward* rule) {
        // Check if all conditions are satisfied
        for(auto& cond : rule->conditions){
            if(!varList->isInstantiated(cond.first) || varList->getVariable(cond.first) != cond.second){
                return false;
            }
        }

        // If satisfied, add conclusion to derived conclusions and queue
        derivedConclusions.push_back(rule->conclusion);
        conclusionQueue.push(rule->conclusion);
        return true;
    }

    // Function 5: process_forward
    void process_forward() {
        while(!conclusionQueue.empty()){
            string currentConclusion = conclusionQueue.front();
            conclusionQueue.pop();

            // Debug statement
            cout << "\nProcessing conclusion: " << currentConclusion << "\n";

            // Find and process rules that have this conclusion as a condition
            vector<RuleForward*> matchingRules = search_cvl(currentConclusion);

            for(auto rule : matchingRules){
                cout << "Evaluating Rule " << rule->ruleNumber << " for treatment recommendation...\n";
                if(validate_Ri_forward(rule)){
                    // Rule validated, enqueue the conclusion
                    // Already handled in validate_Ri_forward
                    cout << "Rule " << rule->ruleNumber << " validated: " << rule->conclusion << "\n";
                }
                else{
                    cout << "Rule " << rule->ruleNumber << " conditions not satisfied.\n";
                }
            }
        }
    }

    // Function to add initial treatment symptom
    void add_initial_symptom(const string& symptom) {
        // Assuming "SYMPTOM" is a key in the variable list
        // Convert symptom to uppercase for consistency
        string symptom_upper = symptom;
        transform(symptom_upper.begin(), symptom_upper.end(), symptom_upper.begin(), ::toupper);
        varList->setVariable("SYMPTOM", symptom_upper);
        conclusionQueue.push(symptom_upper);
    }

    // Function to print derived conclusions
    void print_conclusions() {
        cout << "\n--- Treatment Recommendations ---\n";
        for(auto& concl : derivedConclusions){
            cout << "- " << concl << "\n";
        }
    }
};

// -----------------------------
// Main Function
// -----------------------------

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

    // -----------------------------
    // Backward Chaining for Diagnosis
    // -----------------------------
    cout << "=== Backward Chaining Diagnosis ===\n";

    // Hardcode the goal variable to "DIAGNOSIS" to avoid user input errors
    string goal = "DIAGNOSIS";
    cout << "Determining diagnosis...\n";

    // Start processing
    string diagnosis;
    bool found = ie_backward.Process(goal, diagnosis);

    if(found && !diagnosis.empty()){
        cout << "\nDiagnosis: " << diagnosis << "\n";

        // Pass diagnosis to forward chaining
        varList_forward.setVariable("DISEASE", diagnosis);
    }
    else{
        cout << "\nGoal cannot be determined.\n";
        return 0;
    }

    // -----------------------------
    // Forward Chaining for Treatment
    // -----------------------------
    cout << "\n=== Forward Chaining Treatment Recommendations ===\n";
    string symptom;
    cout << "Enter the symptom for treatment recommendation: ";
    getline(cin, symptom);

    // Add initial symptom to forward chaining
    ie_forward.add_initial_symptom(symptom);

    // Process forward chaining
    ie_forward.process_forward();

    // Print treatment recommendations
    ie_forward.print_conclusions();

    return 0;
}
